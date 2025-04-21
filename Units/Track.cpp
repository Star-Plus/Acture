//
// Created by am180 on 3/4/2025.
//

#include "Track.h"

#include <ranges>

namespace SPI {

    Track::Track() : length(0.0) {}

    void Track::AddClip(double position, const Clip &clip) {
        clips.insert(std::pair(position, clip));

        CalculateLength();
    }

    void Track::RemoveClip(double position) {
        if (auto it = clips.find(position); it != clips.end()) {
            clips.erase(it);
        }

        CalculateLength();
    }

    void Track::ClearClips() {
        clips.clear();

        CalculateLength();
    }

    const Clip &Track::GetClip(double position) const {
        auto it = clips.find(position);
        if (it != clips.end()) {
            return it->second;
        }
        throw std::out_of_range("Clip not found at the specified position.");
    }

    double Track::CalculateLength() {
        const auto lastClip = clips.rbegin();

        length = lastClip->first + lastClip->second.end - lastClip->second.start;

        return length;
    }

}
