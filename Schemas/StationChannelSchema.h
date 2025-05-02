//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef STATIONCHANNELSCHEMA_H
#define STATIONCHANNELSCHEMA_H

#include "../Types/STATION_TYPE.h"

namespace SPI {
    struct StationChannelSchema : std::enable_shared_from_this<StationChannelSchema> {
        STATION_TYPE stationType;
        bool willPause;

        StationChannelSchema(STATION_TYPE type, bool pause)
            : stationType(type), willPause(pause) {}
        virtual ~StationChannelSchema() = default;
    };
}

#endif //STATIONCHANNELSCHEMA_H
