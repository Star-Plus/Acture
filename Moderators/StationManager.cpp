//
// Created by Ahmed Mustafa on 3/5/2025.
//

#include "StationManager.h"

namespace SPI {

    StationManager* StationManager::instance = nullptr;

    StationManager::StationManager() {
        instance = this;
        nextStation = nullptr;
        this->InitializeStation();
    }

    void StationManager::InitializeStation(){
        if (root != nullptr) return;
        root = std::make_shared<RootStation>(RootStation());
    }

    void StationManager::Travel(unsigned int thread)
    {
        if (nextStation == nullptr) return;
        nextStation = nextStation->GetConnectedStation(thread);
    }

    std::shared_ptr<Station> StationManager::getStationById(unsigned int id){
        unsigned int rootId = 0;
        return recursiveSearch(id, root, rootId);
    }

    std::shared_ptr<Station> StationManager::recursiveSearch(unsigned int id, std::shared_ptr<Station> station, unsigned int& drillCounter) {
        if (id != drillCounter){
            for (int i = 0; i < station->getStationCount(); i++){
                drillCounter++;
                return recursiveSearch(id, station->GetConnectedStation(i), drillCounter);
            }
        }

        if (idCache.find(id) == idCache.end())
            idCache[id] = station;

        return idCache[id];
    }
    
}
