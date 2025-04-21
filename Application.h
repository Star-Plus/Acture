#pragma once

#include "Core/EngineState.h"
#include "Managers/TimeService.h"
#include "Managers/StationManager.h"
#include "Managers/MediaBinder.h"

namespace SPI
{
    class Application
    {
        EngineState state;

        TimeService timeService;
        StationManager stationManager;
        MediaBinder mediaBinder;

    public:

        Application();
        ~Application();

        void OnUpdate(float deltaTime);
        void Travel(unsigned int thread);
        void Rewind();
        void Serialize();
        void Deserialize();

    };
}