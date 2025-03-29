//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_CLIP_H
#define INTRASTATION_CLIP_H

#include <filesystem>

namespace SPI {

    struct Clip {
        std::string path;
        double start;
        double end;
    };

}


#endif //INTRASTATION_CLIP_H
