//
// Created by Ahmed Mustafa on 5/2/2025.
//


#include "StationNetworkSerializer.h"

#include "VerseSerializer.h"
#include "../Mappers/StationSerialzerMapper.h"

namespace SPI {

    // Exporting

    StationNetworkSerializer::StationNetworkSerializer(Application* app) : app(app), network(app->GetStationNetwork()) {}

    void StationNetworkSerializer::ExportSpiFile(const std::string &savePath) {
        std::ofstream fileStream;
        fileStream.open(savePath, std::ios::out | std::ios::binary);

        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }

        this->SerializeNetwork(fileStream);

        fileStream.close();
        std::cout << "File saved successfully at " << savePath << std::endl;
    }

    std::vector<uint8_t> StationNetworkSerializer::ExportSpiBuffer() {
        std::ostringstream oss;
        this->SerializeNetwork(oss);
        std::string str = oss.str();
        std::vector<uint8_t> buffer(str.begin(), str.end());
        return buffer;
    }


    void StationNetworkSerializer::SerializeNetwork(std::ostream& out) {
        // const stations_size_t stationCount = this->network->Size();
        // this->out.write(reinterpret_cast<const char*>(&stationCount), sizeof(stationCount));
        //
        // const videos_size_t videosCount = stationCount-1;
        // this->out.write(reinterpret_cast<const char*>(&videosCount), sizeof(videosCount));

        const location_t location = 0;
        this->firstvideo_position = this->out.tellp();
        out.write(reinterpret_cast<const char*>(&location), sizeof(location_t));

        // for (auto i = 0; i < stationCount; i++) {
        //     stations_positions.push(this->out.tellp());
        //     this->out.write(reinterpret_cast<const char *>(&location), sizeof(location_t));
        // }
        // for (auto i = 0; i < videosCount; i++) {
        //     videos_positions.push(this->out.tellp());
        //     this->out.write(reinterpret_cast<const char *>(&location), sizeof(location_t));
        // }

        RecursiveSerialize(out, network->GetRoot(), false);
        RecursiveSerialize(out, network->GetRoot(), true);

    }

    void StationNetworkSerializer::RecursiveSerialize(std::ostream& out, const StationPtr& station, const bool mode=false) {
        if (station == nullptr) {
            return;
        }

        // Serialize the station

        if (!mode) {
            const auto station_serializer = CreateStationSerializer(station->GetType(), this->out, this->out);
            station_serializer->Serialize(station);
            const n_threads_t nThreads = station->getThreadCount();
            this->out.write(reinterpret_cast<const char*>(&nThreads), sizeof(nThreads));
            constexpr
            location_t location = 0;


            // Reserve space for the stations locations
            for (auto i = 0; i < station->getThreadCount(); i++) {
                stations_positions.push(this->out.tellp());
                this->out.write(reinterpret_cast<const char *>(&location), sizeof(location_t));
            }

            // Reserve space for the videos locations
            for (auto i = 0; i < station->getThreadCount(); i++) {
                videos_positions.push(this->out.tellp());
                this->out.write(reinterpret_cast<const char *>(&location), sizeof(location_t));
            }

        }

        for (short i = station->getThreadCount()-1; i >= 0; i--) {

            if (!mode) {
                // write the station position
                const auto stationLocation = this->out.tellp();
                this->out.seekp(stations_positions.front());
                this->out.write(reinterpret_cast<const char *>(&stationLocation), sizeof(location_t));
                stations_positions.pop();
                // Go back to the original position
                this->out.seekp(stationLocation);
            }

            if (mode) {

                const auto videoLocation = this->out.tellp();

                this->out.seekp(videos_positions.front());
                this->out.write(reinterpret_cast<const char *>(&videoLocation), sizeof(location_t));
                videos_positions.pop();

                if (station->GetId() == 0) {
                    // Write the first video position
                    this->out.seekp(this->firstvideo_position);
                    this->out.write(reinterpret_cast<const char *>(&videoLocation), sizeof(location_t));
                }

                this->out.seekp(videoLocation);

                VerseSerializer verseSerializer (this->out);
                verseSerializer.Serialize(station->GetConnectedVerse(i));
            }

            const auto child = station->GetConnectedStation(i);
            this->RecursiveSerialize(out, child, mode);
        }
    }

    // Importing

    void StationNetworkSerializer::ImportSpiFile(const std::string &loadPath) {

        if (this->out.is_open()) {
            this->out.close();
        }

        this->out.open(loadPath, std::ios::in | std::ios::binary);
        if (!this->out.is_open()) {
            throw std::runtime_error("Failed to open file for reading");
        }

        this->path = loadPath;

        DeserializeNetwork();

        out.close();

        app->GetStationManager()->network = network;
        app->GetStationManager()->prevStation = network->GetRoot();
        app->GetStationManager()->nextStation = network->GetRoot();

        app->Travel(0);
        app->TranslateState(EngineState::PAUSED);

    }

    void StationNetworkSerializer::DeserializeNetwork() {

        delete network;

        // stations_size_t stationCount;
        // this->out.read(reinterpret_cast<char*>(&stationCount), sizeof(stationCount));
        //
        // videos_size_t videosCount;
        // this->out.read(reinterpret_cast<char*>(&videosCount), sizeof(videosCount));

        location_t firstVideoLocation;
        this->out.read(reinterpret_cast<char*>(&firstVideoLocation), sizeof(location_t));

        this->firstvideo_position = firstVideoLocation;
        std::cout << "First video position: " << firstVideoLocation << std::endl;

        network = new StationNetwork(std::dynamic_pointer_cast<RootStation>(RecursiveDeserialize()));
    }

    StationPtr StationNetworkSerializer::RecursiveDeserialize() {

        std::cout << "Current position: " << this->out.tellg() << std::endl;

        // Read the station type
        STATION_TYPE type;
        this->out.read(reinterpret_cast<char*>(&type), sizeof(uint8_t));

        std::cout << "Station type: " << (int)type << std::endl;

        // Read the station data
        const auto station_serializer = CreateStationSerializer(type, this->out, this->out);
        const auto station = station_serializer->Deserialize(type);

        // Read number of threads
        n_threads_t nThreads;
        this->out.read(reinterpret_cast<char*>(&nThreads), sizeof(nThreads));

        std::cout << "Number of threads: " << (int)nThreads << std::endl;

        std::queue<location_t> stations_positions;
        std::queue<location_t> videos_positions;

        for (auto i = 0; i < nThreads; i++) {
            location_t position;
            this->out.read(reinterpret_cast<char*>(&position), sizeof(location_t));
            std::cout << "Station position: " << position << std::endl;
            stations_positions.push(position);
        }

        for (auto i = 0; i < nThreads; i++) {
            location_t position;
            this->out.read(reinterpret_cast<char*>(&position), sizeof(location_t));
            std::cout << "Video position: " << position << std::endl;
            videos_positions.push(position);
        }

        // Read the connected stations
        while (!stations_positions.empty() && !videos_positions.empty()) {

            const auto station_pos = stations_positions.front();
            stations_positions.pop();
            this->out.seekg(station_pos);

            const auto child = RecursiveDeserialize();
            station->PushStation(child);

            const auto video_pos = videos_positions.front();
            videos_positions.pop();

            const auto verse = station->GetConnectedVerse(station->getThreadCount()-1);

            verse->CreateTrack();
            const auto clip = new Clip{this->path+"/"+std::to_string(video_pos), 0, child->GetTimelapse()};
            verse->tracks[0]->AddClip(0, clip);
        }

        return station;
    }

}
