//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H
#include "Station.h"
#include "Features/RootStation.h"
#include <map>
#include <stack>

namespace SPI {

    class StationManager {

        static StationManager* instance;

        std::shared_ptr<RootStation> root;
        std::shared_ptr<Station> nextStation;
        std::shared_ptr<Station> prevStation;
        std::stack<std::shared_ptr<Station>> history;
        std::stack<unsigned int> threadHistory;

        std::map<unsigned int, std::shared_ptr<Station>> idCache;

    public:
        StationManager();

        StationManager& Get() { return *instance; }
        
        std::shared_ptr<RootStation> getRoot() { return root; }
        std::shared_ptr<Station> getPrevStation() { return prevStation; }
        std::shared_ptr<Station> getNextStation() { return nextStation; }
        unsigned int getLastThread() { return threadHistory.top(); }

        void InitializeStation();

        void Travel(unsigned int thread);
        void ReverseTravel();

        std::shared_ptr<Station> getStationById(unsigned int id);

    private:
        void recursiveSearch(std::shared_ptr<Station>& target, unsigned int id, std::shared_ptr<Station> station, unsigned int& drillCounter);

    };

}




#endif //STATIONMANAGER_H
