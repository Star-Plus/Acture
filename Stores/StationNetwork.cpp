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
        stations.insert({0, root});
    }

    StationNetwork::~StationNetwork() {
        root.reset();
        stations.clear();
    }

    StationPtr StationNetwork::GetStationById(const ID_T id) {

        if (id < 0) {
            throw std::invalid_argument("Cannot get the root station");
        }

        const auto stationFound = stations.find(id);
        if (stationFound == stations.end()) {
            return nullptr;
        }

        return stationFound->second;
    }

    ID_T StationNetwork::PushStation(const ID_T subRootId, const StationPtr& stationToPush) {
        const auto subRootStation = GetStationById(subRootId);

        if (!subRootStation) {
            throw std::invalid_argument("Cannot push to a non-existing station");
        }

        const auto id = SMath::GenerateId();
        stationToPush->id = id;

        subRootStation->PushStation(stationToPush);
        stations.insert({id, stationToPush});

        count++;

        return id;
    }

    void StationNetwork::RemoveStation(const ID_T id) {

        if (id <= 0) {
            throw std::invalid_argument("Cannot remove the root station");
        }

        auto stationToRemove = GetStationById(id);
        if (!stationToRemove) return;

        for (const auto& parentId : stationToRemove->parents) {
            auto parentStation = GetStationById(parentId);
            if (parentStation) {
                parentStation->DisconnectStation(id);
            }
        }

        stationToRemove.reset();
        stations.erase(id);
        count--;
    }

    ID_T StationNetwork::SearchForId(const StationPtr& station) {
        for (const auto& [key, value] : stations) {
            if (value == station) {
                return key;
            }
        }
        return 0;
    }

}
