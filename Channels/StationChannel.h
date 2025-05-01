//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef STATIONCHANNEL_H
#define STATIONCHANNEL_H
#include <iostream>
#include <utility>

#include "Channel.h"
#include "../Events/StationCallEvent.h"
#include "../Schemas/StationChannelSchema.h"
#include "../Schemas/McqChannelSchema.h"

namespace SPI {

    class StationChannel final : public Channel<StationChannelSchema> {

    public:
        explicit StationChannel(StationCallEvent & event) {
            event.Subscribe([&](std::shared_ptr<StationChannelSchema> data) {
                this->data = std::move(data);
                notified = true;
            });
        }

        ~StationChannel() override = default;

        std::shared_ptr<StationChannelSchema> Receive() override {
            if (!notified) return nullptr;
            notified = false;

            std::cout << std::dynamic_pointer_cast<McqChannelSchema>(this->data)->question << std::endl;

            return this->data;
        }

        void Send(std::shared_ptr<StationChannelSchema> data) override {

        }

    };

}

#endif //STATIONCHANNEL_H
