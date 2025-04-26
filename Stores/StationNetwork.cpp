//
// Created by Ahmed Mustafa on 4/20/2025.
//

#include "StationNetwork.h"

#include <iostream>
#include <utility>

#include "../Utils/SMath.h"

namespace SPI {


    StationNetwork::StationNetwork() = default;

    StationNetwork::StationNetwork(std::shared_ptr<RootStation> rootStation) : count(1) {
        root = std::move(rootStation);
    }

    StationNetwork::~StationNetwork() {
        root.reset();
    }

    void StationNetwork::RecursiveSearchById(const ID_T id, const StationPtr& currentStation, const ID_T currentId, const unsigned int level, StationPtr& stationFound) {
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
            const ID_T nextId = SMath::EncodeBitPack(level+1, currentStation->GetThreadId(), i);

            if (!stationFound)
                RecursiveSearchById(id, currentStation->GetConnectedStation(i), nextId, level+1, stationFound);

        }
    }

    StationPtr StationNetwork::GetStationById(const ID_T id) {
        StationPtr stationFound = nullptr;

        RecursiveSearchById(id, root, 0.0, 0, stationFound);

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

    ID_T StationNetwork::PushStation(const ID_T subRootId, const StationPtr& stationToPush) {
        const auto subRootStation = GetStationById(subRootId);

        if (!subRootStation) {
            throw std::invalid_argument("Cannot push to a non-existing station");
        }

        subRootStation->PushStation(stationToPush);
        count++;

        const auto decoded = SMath::DecodeBitPack(subRootId);
        std::cout << "Decoded ID: " << decoded[0]+1 << ", " << subRootStation->GetThreadId() << ", " << stationToPush->getThreadCount() << std::endl;
        const auto id = SMath::EncodeBitPack(decoded[0] + 1, subRootStation->GetThreadId(), stationToPush->getThreadCount());

        return id;
    }

    void StationNetwork::RemoveStation(const ID_T id) {

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
