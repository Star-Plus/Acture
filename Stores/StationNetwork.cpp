//
// Created by Ahmed Mustafa on 4/20/2025.
//

#include "StationNetwork.h"

#include <utility>

namespace SPI {


    StationNetwork::StationNetwork() = default;

    StationNetwork::StationNetwork(std::shared_ptr<RootStation> rootStation) : count(1) {
        root = std::move(rootStation);
    }

    StationNetwork::~StationNetwork() {
        root.reset();
    }

    void StationNetwork::RecursiveSearchById(unsigned int id, StationPtr currentStation, unsigned int& count, StationPtr& stationFound) {
        if (idCache.find(id) != idCache.end()) {
            stationFound = idCache[id];
            return;
        }

        if (id == count){
            stationFound = currentStation;
            idCache[id] = currentStation;
            return;
        }

        for (int i = 0; i < currentStation->getThreadCount(); i++){
            count++;

            if (!stationFound)
                RecursiveSearchById(id, currentStation->GetConnectedStation(i), count, stationFound);
        }
    }

    StationPtr StationNetwork::GetStationById(unsigned int id) {
        StationPtr stationFound = nullptr;
        unsigned int count = 0;

        RecursiveSearchById(id, root, count, stationFound);

        return stationFound;
    }

    void StationNetwork::RecursiveSearchWithinTimeRange(double start, double end, StationPtr currentStation, std::vector<StationPtr> &stationsFound) {

        if (currentStation->GetTimelapse() > end) return;
        if (currentStation->GetTimelapse() >= start && currentStation->GetTimelapse() <= end) {
            stationsFound.push_back(currentStation);
        }
        for (int i = 0; i < currentStation->getThreadCount(); i++) {
            RecursiveSearchWithinTimeRange(start, end, currentStation->GetConnectedStation(i), stationsFound);
        }
    }

    std::vector<StationPtr> StationNetwork::GetStationsWithinTimeRange(double start, double end) {
        std::vector<StationPtr> stationsFound;

        RecursiveSearchWithinTimeRange(start, end, root, stationsFound);

        return stationsFound;
    }

    void StationNetwork::PushStation(const unsigned int subRootId, const StationPtr& stationToPush) {
        const auto subRootStation = GetStationById(subRootId);

        if (!subRootStation) return;

        subRootStation->PushStation(stationToPush);
        count++;
    }

    void StationNetwork::RemoveStation(unsigned int id) {

        if (id <= 0) {
            throw std::invalid_argument("Cannot remove the root station");
        }

        auto stationToRemove = GetStationById(id);
        if (!stationToRemove) return;

        stationToRemove->GetParent()->DisconnectStation(stationToRemove->GetThreadId());

        stationToRemove.reset();
        idCache.erase(id);
        count--;
    }

}