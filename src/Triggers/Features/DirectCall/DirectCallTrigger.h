//
// Created by Ahmed Mustafa on 7/10/2025.
//

#ifndef DIRECTCALLTRIGGER_H
#define DIRECTCALLTRIGGER_H

#include "../../ITrigger.h"

namespace SPI {

    class DirectCallTrigger final : public ITrigger {

        bool isCalled = false;

        void OnTravel();

    public:

        explicit DirectCallTrigger(Application* context);

        ~DirectCallTrigger() override = default;

        bool IsActive() override;

    };

} // SPI

#endif //DIRECTCALLTRIGGER_H
