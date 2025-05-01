//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef STATIONCHANNELSCHEMA_H
#define STATIONCHANNELSCHEMA_H

#include "../Types/STATION_TYPE.h"

namespace SPI {
    struct StationChannelSchema {
        STATION_TYPE stationType;
        bool willPause;

        virtual ~StationChannelSchema() = default;
    };
}

#endif //STATIONCHANNELSCHEMA_H
