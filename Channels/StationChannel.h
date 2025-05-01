//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef STATIONCHANNEL_H
#define STATIONCHANNEL_H
#include <iostream>

#include "Channel.h"
#include "../Events/StationCallEvent.h"
#include "../Schemas/StationChannelSchema.h"
#include "../Mappers/SchemaTypeCasting.h"

namespace SPI {

    class StationChannel final : public Channel<StationChannelSchema> {

    public:
        explicit StationChannel(StationCallEvent & event) {
            event.Subscribe([&](StationChannelSchema* data) {
                this->data = CastToSchema(data);
                notified = true;
            });
        }

        ~StationChannel() override = default;

        void Send(StationChannelSchema data) override {

        }

    };

}

#endif //STATIONCHANNEL_H
