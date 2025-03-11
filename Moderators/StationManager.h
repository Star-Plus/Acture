//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H
#include "Station.h"


namespace SPI {

    class StationManager {

        static StationManager* instance;

        Station* root;
        Station* nextStation;

    public:
        StationManager();

        StationManager& Get() { return *instance; }

        void InitializeStation(STATION_TYPE type, double timelapse);

        void CreateStation(Station* station, STATION_TYPE type, double timelapse, unsigned int thread);

    };

}




#endif //STATIONMANAGER_H
