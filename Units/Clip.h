//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_CLIP_H
#define INTRASTATION_CLIP_H

#include <filesystem>

#include "Core/Core.h"

namespace SPI {

    class Clip {
    public:
        std::string mediaPath;
        itime_t start = 0;
        itime_t end = 0;

        bool operator>(const Clip &other) const;
        bool operator!() const;
    };

}


#endif //INTRASTATION_CLIP_H
