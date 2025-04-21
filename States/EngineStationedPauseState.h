//
// Created by Ahmed Mustafa on 4/21/2025.
//

#ifndef ENGINESTATIONEDPAUSESTATE_H
#define ENGINESTATIONEDPAUSESTATE_H

#include "EngineStateBase.h"
#include "Managers/MediaBinder.h"
#include "Managers/TimeService.h"

namespace SPI {
    class EngineStationedPauseState final : public EngineStateBase {
    public:
        ~EngineStationedPauseState() override = default;

        void OnEnter(Application& app) override {
            std::cout << "EngineState: Entering paused station state." << std::endl;
        }

        void OnUpdate(Application& app, const float deltaTime) override {

        }
    };
}

#endif //ENGINESTATIONEDPAUSESTATE_H
