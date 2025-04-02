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
        nextStation = root;
        prevStation = root;
    }

    void StationManager::Travel(unsigned int thread)
    {
        if (nextStation == nullptr) return;
        history.push(prevStation);
        prevStation = nextStation;
        nextStation = nextStation->GetConnectedStation(thread);
        threadHistory.push(thread);
    }

    void StationManager::ReverseTravel()
    {
        if (history.empty()) return;
        nextStation = prevStation;
        prevStation = history.top();
        history.pop();
        threadHistory.pop();
    }

    std::shared_ptr<Station> StationManager::getStationById(unsigned int id){
        unsigned int rootId = 0;
        std::shared_ptr<Station> target;
        recursiveSearch(target, id, root, rootId);
        return target;
    }

    void StationManager::recursiveSearch(std::shared_ptr<Station>& target, unsigned int id, std::shared_ptr<Station> station, unsigned int& drillCounter) {

        if (idCache.find(id) != idCache.end()){
            target = idCache[id];
            return;
        }

        if (id == drillCounter){
            target = station;
            idCache[id] = station;
            return;
        }

        for (int i = 0; i < station->getStationCount(); i++){
            drillCounter++;
            
            if (!target)
                recursiveSearch(target, id, station->GetConnectedStation(i), drillCounter);
        }

    }
    
}
