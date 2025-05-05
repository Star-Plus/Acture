//
// Created by Ahmed Mustafa on 5/3/2025.
//

#ifndef VERSESERIALIZER_H
#define VERSESERIALIZER_H

#include <fstream>

#include "../Units/Verse.h"

namespace SPI {
    class VerseSerializer {

        std::fstream& out;

    public:
        explicit VerseSerializer(std::fstream& out) : out(out) {}
        ~VerseSerializer() = default;

        void Serialize(const Verse* verse);
        void Deserialize();
    };
}

#endif //VERSESERIALIZER_H
