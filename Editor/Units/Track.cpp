//
// Created by am180 on 3/4/2025.
//

#include "Track.h"

namespace SPI {

    unsigned short Track::addClip(const Clip &clip) {
        clips.push_back(clip);
        return clips.size() - 1;
    }

    void Track::removeClip(int idx) {
        clips.erase(clips.begin() + idx);
    }

    void Track::clearClips() {
        clips.clear();
    }

    const Clip &Track::getClip(unsigned short idx) const {
        return clips[idx];
    }

}