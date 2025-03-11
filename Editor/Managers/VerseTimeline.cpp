//
// Created by am180 on 3/6/2025.
//

#include "VerseTimeline.h"

namespace SPI {

    VerseTimeline::VerseTimeline(Verse *verse, double duration) {
        if (verse == nullptr) throw std::invalid_argument("Verse cannot be null");
        if (duration <= 0) throw std::invalid_argument("Duration must be greater than 0");

        this->verse = verse;
        this->duration = duration;
    }

    void VerseTimeline::SetTimer(double time){
        if (time < 0) throw std::invalid_argument("Time cannot be negative");

        this->timer = time;
    }

    void VerseTimeline::RunTimer(double delta){
        this->timer += delta;
    }

}