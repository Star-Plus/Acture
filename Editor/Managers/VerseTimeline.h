//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_VERSETIMELINE_H
#define INTRASTATION_VERSETIMELINE_H

#include "Core/Editor/Units/Verse.h"

namespace SPI {

    class VerseTimeline {

        Verse* verse;
        double timer = 0;
        double duration;


    public:

        VerseTimeline(Verse* verse, double duration);

        void SetTimer(double time);

        double GetTimer() { return timer; }

        void RunTimer(double delta);

    };

}



#endif //INTRASTATION_VERSETIMELINE_H
