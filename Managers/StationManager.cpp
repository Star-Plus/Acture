//
// Created by Ahmed Mustafa on 3/5/2025.
//

#include "StationManager.h"

namespace SPI {

    StationManager* StationManager::instance = nullptr;

    StationManager::StationManager() : network(rootStation) {
        instance = this;
        nextStation = nullptr;
        this->InitializeStation();
    }

    StationManager::~StationManager() {
        instance = nullptr;
        rootStation.reset();
        prevStation.reset();
        nextStation.reset();
    }

    void StationManager::InitializeStation(){
        prevStation = rootStation;
        nextStation = rootStation;
    }

    void StationManager::Travel(const unsigned int thread)
    {
        if (nextStation == nullptr) return;
        history.push(prevStation);
        prevStation = nextStation;
        nextStation = nextStation->GetConnectedStation(thread);
        threadHistory.push(thread);

        stationed = false;
    }

    void StationManager::ReverseTravel()
    {
        if (history.empty()) return;
        nextStation = prevStation;
        prevStation = history.top();
        history.pop();
        threadHistory.pop();
    }

    bool StationManager::CheckTimelapse(const double time) {
        if (nextStation == nullptr) return false;
        if (time >= nextStation->GetTimelapse() && !stationed) {
            stationed = true;
            return true;
        }

        return false;
    }

    
}
