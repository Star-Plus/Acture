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
        std::map<float, StationPtr> idCache;
        unsigned int count{};

        void RecursiveSearchById(float id, const StationPtr& currentStation, float currentId, unsigned int level, StationPtr& stationFound);
        void RecursiveSearchWithinTimeRange(double start, double end, StationPtr currentStation, std::vector<StationPtr>& stationsFound);
        float SearchForId(const StationPtr& station);

    public:
        StationNetwork();
        explicit StationNetwork(std::shared_ptr<RootStation> rootStation);
        ~StationNetwork();

        StationPtr GetRoot() { return root; }
        unsigned int Size() const { return count; }

        StationPtr GetStationById(float id);
        std::vector<StationPtr> GetStationsWithinTimeRange(double start, double end);

        float PushStation(float subRootId, const StationPtr& stationToPush);
        void RemoveStation(float id);

    };
}

#endif //INTRASTATION_STATIONSTORE_H
