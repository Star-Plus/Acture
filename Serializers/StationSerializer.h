//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef STATIONSERIALIZER_H
#define STATIONSERIALIZER_H

#include <fstream>
#include "Stores/StationNetwork.h"

namespace SPI {
    class StationSerializer {

        void SerializeBase() const;

    protected:
        StationPtr station;
        std::fstream& out;

        virtual void SerializeBody() = 0;

    public:
        StationSerializer(StationPtr station, std::fstream& out);
        virtual ~StationSerializer() = default;

        void Perform();
    };
}

#endif //STATIONSERIALIZER_H
