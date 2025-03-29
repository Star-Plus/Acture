//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_TRACK_H
#define INTRASTATION_TRACK_H

#include <vector>
#include "Clip.h"

namespace SPI {

    class Track {
    public:

        std::vector<Clip> clips;

        unsigned short addClip(const Clip& clip);
        void removeClip(int idx);
        void clearClips();
        const Clip& getClip(unsigned short idx) const;
    };

}

#endif //INTRASTATION_TRACK_H
