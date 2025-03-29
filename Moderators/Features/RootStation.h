//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef ROOTSTATION_H
#define ROOTSTATION_H

#include "../Station.h"

using str = std::string;

namespace SPI {

    class RootStation : public Station {

    public:
        explicit RootStation() : Station(STATION_TYPE::MCQ, 0) {}
    };

}

#endif
