//
// Created by am180 on 3/6/2025.
//

#include "Verse.h"

namespace SPI {

    Verse::Verse()
    = default;

    Verse::~Verse() {
        for (auto* track : tracks) {
            delete track;
        }
    }

    void Verse::CreateTrack()
    {
        auto* newTrack = new Track();
        tracks.emplace_back(newTrack);
    }

    void Verse::DeleteTrack(unsigned int idx){

        if (idx >= tracks.size()) return;
        delete tracks[idx];
        tracks.erase(tracks.begin() + idx);
    }

    double Verse::CalculateLength()
    {
        return length;
    }
}