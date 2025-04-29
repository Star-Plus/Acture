//
// Created by am180 on 3/6/2025.
//

#include "Verse.h"

namespace SPI {

    Verse::Verse()
    = default;

    Verse::~Verse()
    = default;

    void Verse::CreateTrack()
    {
        const Track newTrack;
        tracks.push_back(newTrack);
    }

    void Verse::DeleteTrack(unsigned int idx){

        if (idx >= tracks.size()) return;
        tracks.erase(tracks.begin() + idx);
    }

    double Verse::CalculateLength()
    {
        return length;
    }
}