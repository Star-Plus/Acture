
#ifndef INTRASTATION_VERSEPLAYER_H
#define INTRASTATION_VERSEPLAYER_H

#include "../Units/Verse.h"

namespace SPI {

    class MediaBinder {

        std::vector<Clip*> currentClips;

        Verse* verse = nullptr;

    public:

        MediaBinder();
        ~MediaBinder();

        void BindVerse(Verse* verse);
        void UnbindVerse();
        Verse* getVerse() const { return verse; }

        std::vector<Clip*> DataToBind(double);

    };

}

#endif 
