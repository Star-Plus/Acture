//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef STATIONCHANNEL_H
#define STATIONCHANNEL_H
#include "Channel.h"
#include "../Events/StationCallEvent.h"
#include "../Schemas/StationChannelSchema.h"

namespace SPI {

    class StationChannel final : public Channel<StationChannelSchema> {

    public:
        explicit StationChannel(StationCallEvent & event) {
            event.Subscribe([&](const StationChannelSchema data) {
                this->data = new StationChannelSchema(data);
                notified = true;
            });
        }

        ~StationChannel() override = default;

        // StationChannelSchema* Send() override {
        //     if (!notified) {
        //         return nullptr;
        //     }
        //     notified = false;
        //     const auto copiedData = new StationChannelSchema(*data);
        //     delete data;
        //     return copiedData;
        // }

        void Receive(StationChannelSchema data) override {

        }

    };

}

#endif //STATIONCHANNEL_H
