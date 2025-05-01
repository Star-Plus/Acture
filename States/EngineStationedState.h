//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef ENGINESTATIONEDSTATE_H
#define ENGINESTATIONEDSTATE_H

#include "EngineStateBase.h"
#include "../Mappers/SchemaGenerator.h"

namespace SPI {
    class EngineStationedState : public EngineStateBase {
    public:
        ~EngineStationedState() override = default;

        void OnEnter(Application& app) override {
            std::cout << "EngineState: Entering station state." << std::endl;

            const auto channelData = GenerateStationChannel(app.GetStationManager()->getNextStation());
            std::cout << "From state: " << std::dynamic_pointer_cast<McqChannelSchema>(channelData)->question << std::endl;
            app.GetStationCallEvent()->Dispatch(channelData);
        }

    };
}

#endif //ENGINESTATIONEDSTATE_H
