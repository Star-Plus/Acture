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

    int SMath::CantorFunction(const int k1, const int k2) {
        return (k1 + k2) * (k1 + k2 + 1) / 2 + k2;
    }

    uint32_t SMath::EncodeBitPack(const uint16_t k1, const uint16_t k2, const uint16_t k3) {
        return (static_cast<uint32_t>(k1) << 21) |
           (static_cast<uint32_t>(k2) << 10) |
           (static_cast<uint32_t>(k3));
    }

    std::vector<uint16_t> SMath::DecodeBitPack(const uint32_t id) {
        std::vector<uint16_t> result(3);
        result[0] = (id >> 21) & 0x7FF;
        result[1] = (id >> 10) & 0x7FF;
        result[2] = id & 0x3FF;
        return result;
    }

}