//
// Created by Ahmed Mustafa on 4/21/2025.
//

#ifndef ENGINETRAVELLINGSTATE_H
#define ENGINETRAVELLINGSTATE_H

#include "EngineStateBase.h"
#include "../Managers/StationManager.h"

namespace SPI {
    class EngineTravellingState final : public EngineStateBase {
    public:
        ~EngineTravellingState() override = default;

        void OnEnter(Application& app) override {
            std::cout << "EngineState: Entering travelling state." << std::endl;
        }

        void OnUpdate(Application& app, const float deltaTime) override {
            std::cout << "Engine thread: " << app.GetCurrentThread() << std::endl;
            app.GetStationManager()->Travel(app.GetCurrentThread());
            const auto verse = app.GetStationManager()->getPrevStation()->GetConnectedVerse(app.GetCurrentThread());
            app.GetMediaBinder()->BindVerse(verse);
            app.TranslateState(EngineState::RUNNING);
            app.SetCurrentThread(-1);
        }
    };
}

#endif //ENGINETRAVELLINGSTATE_H
