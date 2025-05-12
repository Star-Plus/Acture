//
// Created by Ahmed Mustafa on 3/5/2025.
//

#include "StationManager.h"

namespace SPI {


    StationManager::StationManager() : network(new StationNetwork(rootStation)) {
        nextStation = nullptr;
        this->InitializeStation();
        rootStation.reset();
    }

    StationManager::~StationManager() {
        delete network;
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
        nextStation = network->GetStationById(nextStation->GetConnectedStation(thread));
        threadHistory.push(thread);

        const auto willPause = nextStation->WillPause();
        const auto newTimelapse = prevStation->GetTimelapse() + prevStation->GetConnectedVerse(thread)->GetLength() + nextStation->GetLifetime() * (willPause ? 1.0f : -1.0f);

        std::cout << nextStation->GetId() << " Timelapse: " << newTimelapse << std::endl;

        prevStation->SetTimelapse(newTimelapse);

        stationed = false;
    }

    void StationManager::ReverseTravel()
    {
        if (history.size() <= 1) return;
        nextStation = prevStation;
        prevStation = history.top();
        history.pop();
        threadHistory.pop();
    }

    bool StationManager::CheckTimelapse(const double time) {
        if (nextStation == nullptr) return false;
        if (time >= nextStation->GetTimelapse() && !stationed) {

            if (nextStation->GetType() == STATION_TYPE::LEAF) return false;

            stationed = true;
            return true;
        }

        return false;
    }

    
}
