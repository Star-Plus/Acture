//
// Created by am180 on 3/6/2025.
//

#include "Verse.h"

namespace SPI {

    Verse::Verse()
    = default;

    Verse::~Verse() {}

    void Verse::CreateTrack()
    {
        Track newTrack;
        tracks.emplace_back(std::make_shared<Track>(newTrack));
    }

    void Verse::DeleteTrack(const thread_t idx){

        if (idx >= tracks.size()) return;
        tracks[idx].reset();
        tracks.erase(tracks.begin() + idx);
    }

    itime_t Verse::CalculateLength()
    {
        itime_t length = 0;
        for (const auto& track : tracks) {
            if (track->GetLength() > length) {
                length = track->GetLength();
            }
        }

        this->length = length;

        return length;
    }
}