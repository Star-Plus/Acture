//
// Created by Ahmed Mustafa on 7/11/2025.
//

#ifndef TRIGGERMAPPER_H
#define TRIGGERMAPPER_H
#include "../Triggers/ITrigger.h"
#include "../Triggers/Features/DirectCall/DirectCallTrigger.h"
#include "../Triggers/Features/Time/TimeTrigger.h"
#include "../Serializers/TriggerSerializer.h"
#include "../Triggers/Features/DirectCall/DirectCallSerializer.h"

namespace SPI::TriggerMapper {

    inline ITrigger* CreateTrigger(const TRIGGER_TYPE type, Application* context) {
        switch (type) {
            case TRIGGER_TYPE::DIRECT_CALL:
                return new DirectCallTrigger(context);
            case TRIGGER_TYPE::TIMER:
                return new TimeTrigger(context);
            default:
                return nullptr;
        }
    }

    inline TriggerSerializer* CreateTriggerSerializer(const TRIGGER_TYPE type, std::ostream& out, std::istream& in, Application* context) {
        switch (type) {
            case TRIGGER_TYPE::DIRECT_CALL:
                return new DirectCallSerializer(out, in, context);
            case TRIGGER_TYPE::TIMER:
                throw std::runtime_error("TimeTrigger does not have a serializer.");
            default:
                return nullptr;
        }

    }

}


#endif //TRIGGERMAPPER_H
