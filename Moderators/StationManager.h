//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H
#include "Station.h"
#include "Features/RootStation.h"
#include <map>

namespace SPI {

    class StationManager {

        static StationManager* instance;

        std::shared_ptr<RootStation> root;
        std::shared_ptr<Station> nextStation;

        std::map<unsigned int, std::shared_ptr<Station>> idCache;

    public:
        StationManager();

        StationManager& Get() { return *instance; }
        
        std::shared_ptr<RootStation> getRoot() { return root; }
        std::shared_ptr<Station> getNextStation() { return nextStation; }

        void InitializeStation();

        void Travel(unsigned int thread);

        std::shared_ptr<Station> getStationById(unsigned int id);

    private:
        std::shared_ptr<Station> recursiveSearch(unsigned int id, std::shared_ptr<Station> station, unsigned int& drillCounter);

    };

}




#endif //STATIONMANAGER_H
