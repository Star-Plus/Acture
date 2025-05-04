//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef APPSERIALIZER_H
#define APPSERIALIZER_H

#include <string>
#include <fstream>
#include <queue>

#include "../Application.h"
#include "../Stores/StationNetwork.h"

namespace SPI {

    class StationNetworkSerializer {

        Application *app;
        StationNetwork* network;
        std::fstream out;
        std::string path;

        std::queue<std::streampos> stations_positions;
        std::queue<std::streampos> videos_positions;

        void SerializeNetwork();
        void DeserializeNetwork();

        void RecursiveSerialize(const StationPtr& station, bool mode);
        StationPtr RecursiveDeserialize();

    public:
        explicit StationNetworkSerializer(Application* );

        void ExportSpiFile(const std::string& savePath);
        void ImportSpiFile(const std::string& loadPath);

    };

}


#endif //APPSERIALIZER_H
