//
// Created by Ahmed Mustafa on 7/11/2025.
//

#ifndef DIRECTCALLSERIALIZER_H
#define DIRECTCALLSERIALIZER_H

#include "../../../Serializers/TriggerSerializer.h"

namespace SPI {

    class DirectCallSerializer final : public TriggerSerializer {
    protected:
        void SerializeData() const override {
        }

        void DeserializeData() override {
        }
    public:
        DirectCallSerializer(std::ostream& out, std::istream& in, Application* context)
            : TriggerSerializer(out, in, context) {}

    };

} // SPI

#endif //DIRECTCALLSERIALIZER_H
