//
// Created by am180 on 4/21/2025.
//

#ifndef INTRASTATIONENGINEWORKSPACE_ENGINERUNNINGSTATE_H
#define INTRASTATIONENGINEWORKSPACE_ENGINERUNNINGSTATE_H

#include "EngineStateBase.h"

namespace SPI {
    class EngineRunningState final : public EngineStateBase {
    public:
        ~EngineRunningState() override = default;

        void OnEnter(Application& app) override {
            std::cout << "EngineState: Entering running state." << std::endl;
            app.GetStationManager()->CalculateNextTimelapse();
        }

        void OnUpdate(Application& app, const float deltaTime) override {
            app.GetTimeService()->StepTime(deltaTime);

            if (app.GetStationManager()->CheckTimelapse(TimeService::Get().GetMainTime())) {
                if (app.GetStationManager()->getNextStation()->WillPause())
                    app.TranslateState(EngineState::STATIONED_PAUSE);
                else
                    app.TranslateState(EngineState::STATIONED_RUN);
            }
        }
    };
}

#endif //INTRASTATIONENGINEWORKSPACE_ENGINERUNNINGSTATE_H
