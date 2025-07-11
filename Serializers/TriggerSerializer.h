//
// Created by Ahmed Mustafa on 7/11/2025.
//

#ifndef TRIGGERSERIALIZER_H
#define TRIGGERSERIALIZER_H

#include <iostream>
#include "../Triggers/ITrigger.h"


namespace SPI {

    class TriggerSerializer {

    protected:
        ITrigger* trigger;
        std::istream& in;
        std::ostream& out;
        Application* context;

        virtual void SerializeData() const = 0;
        virtual void DeserializeData() = 0;

    public:
        TriggerSerializer(std::ostream& out, std::istream& in, Application* context);
        virtual ~TriggerSerializer() = default;

        void Serialize(const ITrigger* trigger);
        ITrigger* Deserialize(TRIGGER_TYPE type);

    };

}




#endif //TRIGGERSERIALIZER_H
