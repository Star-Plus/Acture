//
// Created by Ahmed Mustafa on 3/5/2025.
//

#include "StationManager.h"

namespace SPI {

    StationManager* StationManager::instance = nullptr;

    StationManager::StationManager() {
        instance = this;
        nextStation = nullptr;
    }

    void StationManager::InitializeStation(STATION_TYPE type, double timelapse){
        if (root != nullptr) return;
        root = new Station(type, timelapse);
        nextStation = root;
    }

    void StationManager::CreateStation(Station *station, STATION_TYPE type, double timelapse, unsigned int thread) {
        station = new Station(type, timelapse);
        station->connectStation(thread, station);
    }
}
