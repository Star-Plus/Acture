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
        this->out.open(savePath, std::ios::out | std::ios::binary);

        if (!this->out.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }

        this->SerializeNetwork();

        this->out.close();
        std::cout << "File saved successfully at " << savePath << std::endl;
    }

    void StationNetworkSerializer::SerializeNetwork() {
        const stations_size_t stationCount = this->network->Size();
        this->out.write(reinterpret_cast<const char*>(&stationCount), sizeof(stationCount));

        const videos_size_t videosCount = stationCount-1;
        this->out.write(reinterpret_cast<const char*>(&videosCount), sizeof(videosCount));

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

        RecursiveSerialize(network->GetRoot(), false);
        RecursiveSerialize(network->GetRoot(), true);

    }

    void StationNetworkSerializer::RecursiveSerialize(const StationPtr& station, const bool mode=false) {
        if (station == nullptr) {
            return;
        }

        // Serialize the station

        if (!mode) {
            const auto station_serializer = CreateStationSerializer(station->GetType(), this->out);
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
            this->RecursiveSerialize(child, mode);
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

    }

    void StationNetworkSerializer::DeserializeNetwork() {

        delete network;

        stations_size_t stationCount;
        this->out.read(reinterpret_cast<char*>(&stationCount), sizeof(stationCount));

        videos_size_t videosCount;
        this->out.read(reinterpret_cast<char*>(&videosCount), sizeof(videosCount));

        location_t firstVideoLocation;
        this->out.read(reinterpret_cast<char*>(&firstVideoLocation), sizeof(location_t));

        this->firstvideo_position = firstVideoLocation;
        std::cout << "First video position: " << firstVideoLocation << std::endl;

        network = new StationNetwork(std::dynamic_pointer_cast<RootStation>(RecursiveDeserialize()));
    }

    StationPtr StationNetworkSerializer::RecursiveDeserialize() {
        // Read the station type
        STATION_TYPE type;
        this->out.read(reinterpret_cast<char*>(&type), sizeof(type));

        // Read the station data
        const auto station_serializer = CreateStationSerializer(type, this->out);
        const auto station = station_serializer->Deserialize(type);

        // Read number of threads
        n_threads_t nThreads;
        this->out.read(reinterpret_cast<char*>(&nThreads), sizeof(nThreads));

        std::queue<std::streampos> stations_positions;
        std::queue<std::streampos> videos_positions;

        for (auto i = 0; i < nThreads; i++) {
            std::streampos position;
            this->out.read(reinterpret_cast<char*>(&position), sizeof(location_t));
            stations_positions.push(position);
        }

        for (auto i = 0; i < nThreads; i++) {
            std::streampos position;
            this->out.read(reinterpret_cast<char*>(&position), sizeof(location_t));
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
            this->out.seekg(video_pos);

            // Read size of the video
            std::streampos videoSize;
            this->out.read(reinterpret_cast<char*>(&videoSize), sizeof(std::streampos));

            const auto verse = station->GetConnectedVerse(station->getThreadCount()-1);

            verse->CreateTrack();
            const auto clip = new Clip{this->path+"/"+to_string(video_pos)+"-"+std::to_string(videoSize), 0, child->GetTimelapse()};
            verse->tracks[0]->AddClip(0, clip);
        }

        return station;
    }

}
