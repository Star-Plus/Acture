//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef CHANNEL_H
#define CHANNEL_H

namespace SPI {

    template <typename T>
    class Channel {

    protected:
        std::shared_ptr<T> data = nullptr;
        bool notified = false;

    public:
        Channel() = default;
        virtual ~Channel() = default;

        std::shared_ptr<T> Receive() {
            if (!notified) {
                if (data != nullptr) {
                    data.reset();
                }
                return nullptr;
            }

            notified = false;
            return data;
        }

        virtual void Send(T data) = 0;
    };
}

#endif //CHANNEL_H
