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
        for (auto track : tracks) {
            delete track;
        }
    }

    void Verse::AddTrack(Track* track)
    {
        tracks.push_back(track);
    }

    void Verse::deleteTrack(unsigned int track){

        if (track >= tracks.size()) return;

        delete tracks[track];
        tracks.erase(tracks.begin() + track);
    }

    const Track& Verse::getTrack(unsigned int idx) const {
        return *tracks[idx];
    }
}