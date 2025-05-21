//
// Created by Ahmed Mustafa on 5/21/2025.
//

#include "HistoryStation.h"

#include "Application.h"

namespace SPI {

    void HistoryStation::UseStation(const ID_T id) {
        if (std::ranges::find(stationsIds, id) == stationsIds.end()) {
            stationsIds.push_back(id);
        }
    }

    void HistoryStation::RemoveStation(const ID_T id) {
        auto it = std::ranges::find(stationsIds, id);
        if (it != stationsIds.end()) {
            stationsIds.erase(it);
        }
    }

    void HistoryStation::RemoveStationByIndex(const size_t index) {
        if (index < stationsIds.size()) {
            stationsIds.erase(stationsIds.begin() + index);
        }
    }

    void HistoryStation::CreateNewGate() {
        const auto gateId = std::string(stationsIds.size(), 'N');
        gates[gateId] = 0;
    }

    void HistoryStation::SetGate(const std::string &gateId, const std::string& gateValue) {
        if (gates.find(gateId) != gates.end()) {
            gates[gateId] = std::stoi(gateValue);
        }
    }

    int HistoryStation::AutoRoad() {
        std::string gateId;
        for (const auto& id : stationsIds) {
            const auto thread = context->GetStationManager()->getStationHistory()->GetChoiceOfStation(id);
            gateId += (thread == -1) ? 'o' : (char)thread;
        }

        auto it = gates.find(gateId);
        if (it != gates.end()) {
            return it->second;
        }

        return -1;
    }



}
