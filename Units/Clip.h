//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_CLIP_H
#define INTRASTATION_CLIP_H

#include <filesystem>

namespace SPI {

    class Clip {
    public:
        std::string mediaPath;
        double start = 0;
        double end = 0;

        bool operator>(const Clip &other) const;
        bool operator!() const;
    };

}


#endif //INTRASTATION_CLIP_H
