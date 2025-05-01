//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <functional>

namespace SPI {

    template<class T>
    using Callback = std::function<void(std::shared_ptr<T>)>;

    template<class T>
    class Event {

        std::vector<Callback<T>> callbacks;

    public:

        void Subscribe(Callback<T> callback) {
            callbacks.push_back(callback);
        }

        void Unsubscribe(Callback<T> callback) {
            callbacks.erase(std::remove(callbacks.begin(), callbacks.end(), callback), callbacks.end());
        }

        void Dispatch(T data) {
            for (const auto& callback : callbacks) {
                callback(data);
            }
        }

    };

}

#endif //EVENT_H
