
#ifndef INTRASTATION_VERSEPLAYER_H
#define INTRASTATION_VERSEPLAYER_H

#include "../Units/Verse.h"

namespace SPI {

    class VersePlayer {

        Verse* playingVerse;

    public:

        VersePlayer() {}
            
        void BindVerse(Verse* verse);
        Verse* getPlayingVerse() const { return playingVerse; }

    };

}

#endif 
