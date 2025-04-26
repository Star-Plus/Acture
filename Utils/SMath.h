//
// Created by Ahmed Mustafa on 4/25/2025.
//

#ifndef SMATH_H
#define SMATH_H
#include <cstdint>
#include <vector>

namespace SPI {
    class SMath {
    public:
        static unsigned short GetFloatPart(float value);
        static int CantorFunction(int k1, int k2);
        static uint32_t EncodeBitPack(uint16_t k1, uint16_t k2, uint16_t k3);
        static std::vector<uint16_t> DecodeBitPack(uint32_t id);
    };
}

#endif //SMATH_H
