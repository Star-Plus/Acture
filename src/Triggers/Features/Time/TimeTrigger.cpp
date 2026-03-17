//
// Created by Ahmed Mustafa on 7/1/2025.
//

#include "TimeTrigger.h"
#include "../../../Application.h"

namespace SPI {

    bool TimeTrigger::IsActive() {
        if (context == nullptr) {
            return false;
        }

        const double currentTime = context->GetCurrentTime();
        const auto nextStation = context->GetStationManager()->getNextStation();

        if (nextStation == nullptr) {
            return false;
        }

        return currentTime == nextStation->GetTimelapse();

    }

} // namespace SPI