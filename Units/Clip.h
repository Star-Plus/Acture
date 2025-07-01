//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_CLIP_H
#define INTRASTATION_CLIP_H

#include <filesystem>
#include "../Types/MEDIA_TYPE.h"

namespace SPI {

    class Clip {
    public:
        MEDIA_TYPE mediaType = MEDIA_TYPE::UNKNOWN;
        std::string mediaPath;

        bool operator!() const;
    };

}


#endif //INTRASTATION_CLIP_H
