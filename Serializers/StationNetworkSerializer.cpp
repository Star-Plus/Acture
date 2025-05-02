//
// Created by Ahmed Mustafa on 5/2/2025.
//


#include "StationNetworkSerializer.h"

#include "Mappers/StationSerialzerMapper.h"

namespace SPI {

    StationNetworkSerializer::StationNetworkSerializer(StationNetwork* network) : network(network) {}

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
        for (auto i = 0; i < stationCount+videosCount; i++) {
            this->out.write(reinterpret_cast<const char *>(&location), sizeof(location_t));
        }

        RecursiveSerialize(network->GetRoot());

    }

    void StationNetworkSerializer::RecursiveSerialize(const StationPtr& station) {
        if (station == nullptr) {
            return;
        }

        const auto serializer = CreateStationSerializer(station, this->out);
        serializer->Perform();

        for (auto i = 0; i < station->getThreadCount(); i++) {
            const auto child = station->GetConnectedStation(i);
            this->RecursiveSerialize(child);
        }
    }

}
