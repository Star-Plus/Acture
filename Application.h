#pragma once

#include "Core/EngineState.h"
#include "Managers/TimeService.h"
#include "Managers/StationManager.h"
#include "Managers/MediaBinder.h"
#include "States/EngineStateBase.h"

namespace SPI
{
    class Application
    {
        std::unique_ptr<EngineStateBase> appState;
        EngineState stateType;

        TimeService timeService;
        StationManager stationManager;
        MediaBinder mediaBinder;

        unsigned int currentThread = 0;

    public:

        Application();
        ~Application();

        void TranslateState(EngineState newState);

        unsigned int GetCurrentThread() const { return currentThread; }
        void SetCurrentThread(const unsigned int thread) { currentThread = thread; }

        EngineState GetCurrentState() const { return stateType; }

        double GetCurrentTime() const
        {
            return timeService.GetMainTime();
        }

        StationNetwork* GetStationNetwork()
        {
            return stationManager.getNetwork();
        }
        MediaBinder* GetMediaBinder()
        {
            return &mediaBinder;
        }
        TimeService* GetTimeService()
        {
            return &timeService;
        }
        StationManager* GetStationManager()
        {
            return &stationManager;
        }

        void OnUpdate(float deltaTime);
        std::vector<Clip> DataToBind();

        void Play();
        void Pause();
        void Travel(unsigned int thread);
        void Rewind();
        void Serialize();
        void Deserialize();

        friend class Editor;
    };

}
