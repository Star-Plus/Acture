//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_STATIONSTORE_H
#define INTRASTATION_STATIONSTORE_H

#include "../Core/Core.h"
#include "../Machines/Station.h"
#include "../Core/RootStation.h"

namespace SPI {

    using StationPtr = std::shared_ptr<Station>;

    class StationNetwork {

        std::shared_ptr<RootStation> root;
        std::map<ID_T, StationPtr> idCache;
        stations_size_t count = 0;

        void RecursiveSearchById(ID_T id, const StationPtr& currentStation, ID_T currentId, unsigned int level, StationPtr& stationFound);
        void RecursiveSearchWithinTimeRange(double start, double end, StationPtr currentStation, std::vector<StationPtr>& stationsFound);
        ID_T SearchForId(const StationPtr& station);

    public:
        StationNetwork();
        explicit StationNetwork(std::shared_ptr<RootStation> rootStation);
        ~StationNetwork();

        StationPtr GetRoot() { return root; }
        unsigned int Size() const { return count; }

        StationPtr GetStationById(ID_T id);
        std::vector<StationPtr> GetStationsWithinTimeRange(double start, double end);

        ID_T PushStation(ID_T subRootId, const StationPtr& stationToPush);
        void RemoveStation(ID_T id);

    };
}

#endif //INTRASTATION_STATIONSTORE_H
