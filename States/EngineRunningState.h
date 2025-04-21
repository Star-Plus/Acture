//
// Created by am180 on 4/21/2025.
//

#ifndef INTRASTATIONENGINEWORKSPACE_ENGINERUNNINGSTATE_H
#define INTRASTATIONENGINEWORKSPACE_ENGINERUNNINGSTATE_H

#include "EngineStateBase.h"

namespace SPI {
    class EngineRunningState : public EngineStateBase {
    public:
        virtual ~EngineRunningState() = default;

        virtual void OnUpdate(Application& app, float deltaTime) override {

        }
    };
}

#endif //INTRASTATIONENGINEWORKSPACE_ENGINERUNNINGSTATE_H
