//
// Created by Ahmed Mustafa on 4/20/2025.
//

#include "StationNetwork.h"

#include <utility>

#include "Utils/SMath.h"

namespace SPI {


    StationNetwork::StationNetwork() = default;

    StationNetwork::StationNetwork(std::shared_ptr<RootStation> rootStation) : count(1) {
        root = std::move(rootStation);
    }

    StationNetwork::~StationNetwork() {
        root.reset();
    }

    void StationNetwork::RecursiveSearchById(const float id, const StationPtr& currentStation, float currentId, const unsigned int level, StationPtr& stationFound) {
        if (idCache.find(id) != idCache.end()) {
            stationFound = idCache[id];
            return;
        }

        if (currentId == id) {
            stationFound = currentStation;
            idCache[id] = currentStation;
            return;
        }

        for (int i = 0; i < currentStation->getThreadCount(); i++){
            const float nextId = i + (level+1) * 0.1f;

            if (!stationFound)
                RecursiveSearchById(id, currentStation->GetConnectedStation(i), nextId, level+1, stationFound);

        }
    }

    StationPtr StationNetwork::GetStationById(float id) {
        StationPtr stationFound = nullptr;
        unsigned int count = 0;

        RecursiveSearchById(id, root, 0.0, count, stationFound);

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

    float StationNetwork::PushStation(const float subRootId, const StationPtr& stationToPush) {
        const auto subRootStation = GetStationById(subRootId);

        if (!subRootStation) {
            throw std::invalid_argument("Cannot push to a non-existing station");
        }

        subRootStation->PushStation(stationToPush);
        count++;

        const unsigned short level = SMath::GetFloatPart(subRootId)+1;
        const unsigned short thread = stationToPush->GetThreadId();
        const float id = thread + level * 0.1f;

        return id;
    }

    void StationNetwork::RemoveStation(const float id) {

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

    float StationNetwork::SearchForId(const StationPtr& station) {
        for (const auto& [key, value] : idCache) {
            if (value == station) {
                return key;
            }
        }
        return -1.0f;
    }

}
