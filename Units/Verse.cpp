//
// Created by am180 on 3/6/2025.
//

#include "Verse.h"

namespace SPI {

    Verse::Verse()
    {
    }

    Verse::~Verse()
    {
    }

    void Verse::CreateTrack()
    {
        Track newTrack;
        tracks.push_back(newTrack);
    }

    void Verse::DeleteTrack(unsigned int track){

        if (track >= tracks.size()) return;
        tracks.erase(tracks.begin() + track);
    }

    double Verse::CalculateLength()
    {
        return length;
    }
}