//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_VERSE_H
#define INTRASTATION_VERSE_H

#include "Track.h"

namespace SPI {

    class Verse {

        double length;

    public:

        std::vector<Track> tracks;

        Verse();
        ~Verse();

        void CreateTrack();
        void DeleteTrack(unsigned int idx);
        double CalculateLength();

        double GetLength() const {return length;}

    };

}

#endif //INTRASTATION_VERSE_H
