//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef SCHEMAGENERATOR_H
#define SCHEMAGENERATOR_H
#include <Features/MCQStation.h>

#include "../Schemas/StationChannelSchema.h"
#include "../Machines/Station.h"
#include "../Schemas/McqChannelSchema.h"

namespace SPI {
    inline StationChannelSchema* GenerateStationChannel(const std::shared_ptr<Station>& station) {
        switch (station->GetType()) {

            case STATION_TYPE::MCQ: {

                const auto mcqStation = std::dynamic_pointer_cast<MCQStation>(station);
                const auto schema =  new McqChannelSchema{
                    false,
                    mcqStation->getQuestion(),
                    mcqStation->getOptions()
                };

                return schema;

            }
            default:
                throw std::runtime_error("Unknown station type");

        }
    }
}

#endif //SCHEMAGENERATOR_H
