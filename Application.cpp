#include "Application.h"

namespace SPI {

    Application::Application() {
        state = EngineState::EMPTY;
    }

    void Application::OnUpdate(float deltaTime) {
        if (state == EngineState::RUNNING) {
            timeService.StepTime(deltaTime);
            auto clips = mediaBinder.DataToBind();
        }
    }

}