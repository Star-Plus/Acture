//
// Created by am180 on 3/4/2025.
//

#include "Track.h"

#include <iostream>
#include <ranges>
#include <functional>

namespace SPI {

    Track::Track() : length(0.0) {}
    Track::~Track() {
        for (auto& clip : clips) {
            delete clip.second;
        }
    }

    void Track::AddClip(double position, Clip *clip) {
        clips.insert({position, clip});
        CalculateLength();
    }

    void Track::RemoveClip(const double position) {
        if (auto it = clips.find(position); it != clips.end()) {
            clips.erase(it);
        }

        CalculateLength();
    }

    void Track::ClearClips() {
        clips.clear();

        CalculateLength();
    }

    Clip* Track::GetClip(const double position) const {
        auto it = clips.find(position);
        if (it != clips.end()) {
            return it->second;
        }
        throw std::out_of_range("Clip not found at the specified position.");
    }

    double Track::CalculateLength() {
        const auto lastClip = clips.rbegin();

        length = lastClip->first + lastClip->second->end - lastClip->second->start;

        return length;
    }

}
