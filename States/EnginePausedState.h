//
// Created by am180 on 4/21/2025.
//

#ifndef INTRASTATIONENGINEWORKSPACE_ENGINEPAUSEDSTATE_H
#define INTRASTATIONENGINEWORKSPACE_ENGINEPAUSEDSTATE_H

#include "EngineStateBase.h"

namespace SPI {
    class EnginePausedState : public EngineStateBase {
    public:
        virtual ~EnginePausedState() = default;

        virtual void OnUpdate(Application& app, float deltaTime) override {
            // Paused state does not perform any updates
        }
    };
}

#endif //INTRASTATIONENGINEWORKSPACE_ENGINEPAUSEDSTATE_H
