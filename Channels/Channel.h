//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef CHANNEL_H
#define CHANNEL_H
#include "Events/Event.h"

namespace SPI {

    template <typename T>
    class Channel {

    protected:
        T* data;
        bool notified = false;

    public:
        Channel() = default;
        virtual ~Channel() = default;

        T* Send() {
            if (!notified) {
                return nullptr;
            }
            notified = false;
            const auto copiedData = new T(*data);
            delete data;
            return copiedData;
        }
        virtual void Receive(T data) = 0;
    };
}

#endif //CHANNEL_H
