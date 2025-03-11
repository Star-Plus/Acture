//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef CUT_H
#define CUT_H
#include "Core/Editor/Units/Clip.h"

namespace SPI {

    class Cut {

        static Clip cut(Clip& clip, double position) {
            if (position < clip.start || position > clip.end) {
                throw std::invalid_argument("Cut range is out of bounds");
            }

            Clip newClip = clip;
            newClip.start = position;
            newClip.end = clip.end;

            clip.end = position;

            return newClip;
        }

        static void trim(Clip& clip, double start, double end) {
            if (start < clip.start || end > clip.end) {
                throw std::invalid_argument("Cut range is out of bounds");
            }

            clip.start = start;
            clip.end = end;
        }
    };

}

#endif //CUT_H
