//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef CHANNEL_H
#define CHANNEL_H
#include "../Events/Event.h"

namespace SPI {

    template <typename T>
    class Channel {

    protected:
        T* data = nullptr;
        bool notified = false;

    public:
        Channel() = default;
        virtual ~Channel() = default;

        T* Send() {
            if (!notified) {
                if (data != nullptr) {
                    delete data;
                    data = nullptr;
                }
                return nullptr;
            }

            notified = false;
            return data;
        }

        virtual void Receive(T data) = 0;
    };
}

#endif //CHANNEL_H
