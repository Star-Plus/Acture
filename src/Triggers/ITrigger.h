//
// Created by Ahmed Mustafa on 6/30/2025.
//

#ifndef ITRIGGER_H
#define ITRIGGER_H
#include "../Types/TRIGGER_TYPE.h"

namespace SPI {

    class Application;

    class ITrigger {

    protected:
        Application* context = nullptr;
        TRIGGER_TYPE type = TRIGGER_TYPE::NONE;

    public:
        explicit ITrigger(Application* context) : context(context) {}
        virtual ~ITrigger() = default;

        virtual bool IsActive() = 0;
        TRIGGER_TYPE GetType() const { return type; }
    };

}

#endif //ITRIGGER_H
