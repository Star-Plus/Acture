//
// Created by Ahmed Mustafa on 7/11/2025.
//

#include "TriggerSerializer.h"

#include "Application.h"
#include "Mappers/TriggerMapper.h"

namespace SPI {

    TriggerSerializer::TriggerSerializer(std::ostream& out, std::istream& in, Application* context)
        : trigger(nullptr), in(in), out(out), context(context) {}

    void TriggerSerializer::Serialize(const ITrigger* trigger) {
        if (trigger == nullptr) {
            return;
        }

        const TRIGGER_TYPE type = trigger->GetType();
        this->out.write(reinterpret_cast<const char*>(&type), sizeof(TRIGGER_TYPE));

        this->trigger = const_cast<ITrigger*>(trigger);
        this->SerializeData();
    }

    ITrigger* TriggerSerializer::Deserialize(const TRIGGER_TYPE type) {
        this->trigger = TriggerMapper::CreateTrigger(type, this->context);
        this->DeserializeData();
        return this->trigger;
    }

}
