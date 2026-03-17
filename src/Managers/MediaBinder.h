
#ifndef INTRASTATION_VERSEPLAYER_H
#define INTRASTATION_VERSEPLAYER_H

#include "../Units/Verse.h"

namespace SPI {

    class MediaBinder {

        std::vector<Clip*> currentClips;

        std::shared_ptr<Verse> verse = nullptr;

    public:

        MediaBinder();
        ~MediaBinder();

        void BindVerse(std::shared_ptr<Verse> );
        void UnbindVerse();
        std::shared_ptr<Verse> getVerse() const { return verse; }

        std::vector<std::shared_ptr<Clip>> DataToBind(double);

    };

}

#endif 
