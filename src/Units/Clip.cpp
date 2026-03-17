//
// Created by Ahmed Mustafa on 4/20/2025.
//

#include "Clip.h"

namespace SPI {

    bool Clip::operator>(const Clip &other) const {
        return this->end - this->start > other.end - other.start;
    }

    bool Clip::operator!() const {
        return mediaPath.empty() && start == 0 && end == 0;
    }

}