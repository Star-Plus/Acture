
#ifndef INTRASTATION_VERSEPLAYER_H
#define INTRASTATION_VERSEPLAYER_H

#include "../Units/Verse.h"

namespace SPI {

    class MediaBinder {

        static MediaBinder* instance;

        Verse* verse = nullptr;
        std::vector<unsigned int> clipIndices;

    public:

        static MediaBinder& Get() {
            if (instance == nullptr) {
                instance = new MediaBinder();
            }
            return *instance;
        }

        MediaBinder();
        ~MediaBinder();

        void BindVerse(Verse* verse);
        void UnbindVerse();
        Verse* getVerse() const { return verse; }

        std::vector<Clip> DataToBind() const;

    };

}

#endif 
