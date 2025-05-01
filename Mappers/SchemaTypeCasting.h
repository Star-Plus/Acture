//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef SCHEMATYPECASTING_H
#define SCHEMATYPECASTING_H

#include "../Schemas/StationChannelSchema.h"
#include "../Schemas/McqChannelSchema.h"

namespace SPI {
    inline StationChannelSchema* CastToSchema(StationChannelSchema* data) {
        switch (data->stationType) {
            case STATION_TYPE::MCQ:
                return static_cast<McqChannelSchema*>(data);
            default:
                return nullptr;
        }
    }

} // namespace SPI

#endif //SCHEMATYPECASTING_H
