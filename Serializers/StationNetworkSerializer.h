//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef APPSERIALIZER_H
#define APPSERIALIZER_H

#include <string>
#include <fstream>

#include "../Stores/StationNetwork.h"

namespace SPI {

    class StationNetworkSerializer {

        StationNetwork* network;
        std::fstream out;

        void SerializeNetwork();
        void RecursiveSerialize(const StationPtr& station);

    public:
        explicit StationNetworkSerializer(StationNetwork* network);

        void ExportSpiFile(const std::string& savePath);
    };

}


#endif //APPSERIALIZER_H
