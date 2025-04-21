//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_STATIONSTORE_H
#define INTRASTATION_STATIONSTORE_H

#include "../Machines/Station.h"
#include "../Core/RootStation.h"

namespace SPI {

    using StationPtr = std::shared_ptr<Station>;

    class StationNetwork {

        std::shared_ptr<RootStation> root;
        std::map<unsigned int, StationPtr> idCache;
        unsigned int count{};

        void RecursiveSearchById(unsigned int id, StationPtr currentStation, unsigned int& count, StationPtr& stationFound);

        void RecursiveSearchWithinTimeRange(double start, double end, StationPtr currentStation, std::vector<StationPtr>& stationsFound);

    public:
        StationNetwork();
        StationNetwork(std::shared_ptr<RootStation> rootStation);
        ~StationNetwork();

        StationPtr GetRoot() { return root; }
        unsigned int Size() { return count; }

        StationPtr GetStationById(unsigned int id);
        std::vector<StationPtr> GetStationsWithinTimeRange(double start, double end);

        void PushStation(unsigned int subRootId, const StationPtr& stationToPush);
        void RemoveStation(unsigned int id);

    };
}

#endif //INTRASTATION_STATIONSTORE_H
