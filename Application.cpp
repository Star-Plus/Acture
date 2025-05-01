#include "Application.h"

#include "States/EngineEmptyState.h"
#include "Mappers/EngineStateMapping.h"

namespace SPI {

    Application::Application()
    :
        appState(std::make_unique<EngineEmptyState>()),
        stateType(EngineState::EMPTY),
        timeService(new TimeService()),
        stationManager(new StationManager()),
        mediaBinder(new MediaBinder()),
        stationChannel(this->stationCallEvent)
    {}

    Application::~Application() {
        delete timeService;
        delete stationManager;
        delete mediaBinder;
    }

    void Application::TranslateState(const EngineState newState) {

        appState = CreateEngineState(newState);
        stateType = newState;
        appState->OnEnter(*this);
    }

    void Application::OnUpdate(const float deltaTime) {
        appState->OnUpdate(*this, deltaTime);
    }

    std::vector<Clip> Application::DataToBind() {
        return mediaBinder->DataToBind(timeService->GetPlayerTime());
    }

    void Application::Play() {
        if (stateType == EngineState::PAUSED)
            TranslateState(EngineState::RUNNING);
    }

    void Application::Pause() {
        if (stateType == EngineState::RUNNING)
            TranslateState(EngineState::PAUSED);
    }

    void Application::Travel(const unsigned int thread) {
        currentThread = thread;
        TranslateState(EngineState::FORWARDING);
    }

    void Application::Rewind() {
    }

    void Application::Serialize() {
    }

    void Application::Deserialize() {
    }

    void Application::ScrubTime(const float time) const {
        timeService->SetTime(time);
    }
}
