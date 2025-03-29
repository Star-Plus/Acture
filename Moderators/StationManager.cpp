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
}
