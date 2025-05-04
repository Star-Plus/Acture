//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H
#include "../Machines/Station.h"
#include "../Core/RootStation.h"
#include <stack>

#include "../Stores/StationNetwork.h"

namespace SPI {

    class StationManager {

        static StationManager* instance;

        std::shared_ptr<RootStation> rootStation = std::make_shared<RootStation>();
        StationPtr prevStation;
        StationPtr nextStation;

        std::stack<StationPtr> history;
        std::stack<unsigned int> threadHistory;

        bool stationed = false;

        StationNetwork* network;

    public:
        StationManager();
        ~StationManager();

        static StationManager& Get() { return *instance; }
        
        StationPtr getPrevStation() { return prevStation; }
        StationPtr getNextStation() { return nextStation; }
        StationNetwork* getNetwork() { return network; }
        unsigned int getLastThread() { return threadHistory.top(); }

        void InitializeStation();

        void Travel(unsigned int thread);
        void ReverseTravel();

        bool CheckTimelapse(double time);

        friend class StationNetworkSerializer;
    };

}




#endif //STATIONMANAGER_H
