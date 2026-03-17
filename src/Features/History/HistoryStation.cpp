//
// Created by Ahmed Mustafa on 5/21/2025.
//

#include <algorithm>

#include "HistoryStation.h"

#include "../../Application.h"

namespace SPI {

    void HistoryStation::UseStation(const ID_T id) {
        stationsIds.push_back(id);
    }

    void HistoryStation::RemoveStation(const ID_T id) {
        
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

    void HistoryStation::SetGate(const std::string &gateId, const thread_t gateValue) {
        gates[gateId] = gateValue;
    }

    int HistoryStation::AutoRoad() {
        std::string gateId;
        for (const auto& id : stationsIds) {
            const auto thread = context->GetStationManager()->getStationHistory()->GetChoiceOfStation(id);
            gateId += (thread == -1) ? 'o' : std::to_string(thread)[0];
        }

        std::cout << "HistoryStation::AutoRoad: Gate ID: " << gateId << std::endl;

        auto it = gates.find(gateId);
        if (it != gates.end()) {
            return it->second;
        }

        return -1;
    }

    void HistoryStation::RemoveGate(const std::string& gateId){
        gates.erase(gateId);
    }

}
