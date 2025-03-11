//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_VERSE_H
#define INTRASTATION_VERSE_H

#include "Track.h"

namespace SPI {

    class Verse {

        std::vector<Track*> tracks;

    public:

        Verse();
        ~Verse();

        void AddTrack(Track* track);
        void deleteTrack(Track* track);

        const Track& getTrack(int idx) const;
    };

}

#endif //INTRASTATION_VERSE_H
