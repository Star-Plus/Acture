//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_CLIP_H
#define INTRASTATION_CLIP_H

#include <filesystem>

namespace fs = std::filesystem;

namespace SPI {

    struct Clip {
        fs::path media;
        double start;
        double end;
    };

}


#endif //INTRASTATION_CLIP_H
