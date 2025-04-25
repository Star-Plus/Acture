//
// Created by Ahmed Mustafa on 4/25/2025.
//

#include "SMath.h"

namespace SPI {
    unsigned short SMath::GetFloatPart(const float value) {
        float fractional = value - static_cast<int>(value);
        // Shift the fractional part to the right until it becomes an integer
        unsigned short result = 0;
        int multiplier = 1;

        while (fractional > 0.00001f && multiplier <= 10000) { // Prevent infinite loops on float errors
            fractional *= 10;
            int digit = static_cast<int>(fractional);
            result = result * 10 + digit;
            fractional -= digit;
        }

        return result;
    }

}