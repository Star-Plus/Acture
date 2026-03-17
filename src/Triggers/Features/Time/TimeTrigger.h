//
// Created by Ahmed Mustafa on 7/1/2025.
//

#ifndef TIMETRIGGER_H
#define TIMETRIGGER_H

#include "../../ITrigger.h"

namespace SPI {

    class TimeTrigger final : public ITrigger {
        float callingThreshold; // Threshold in seconds to trigger the action
    public:
        explicit TimeTrigger(Application* context, const float threshold = 0.01f)
            : ITrigger(context), callingThreshold(threshold) {
            this->type = TRIGGER_TYPE::TIMER;
        }

        ~TimeTrigger() override = default;
        bool IsActive() override;
    };

}



#endif //TIMETRIGGER_H
