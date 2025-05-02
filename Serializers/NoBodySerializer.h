//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef NOBODYSERIALIZER_H
#define NOBODYSERIALIZER_H
#include "StationSerializer.h"

namespace SPI {

    class NoBodySerializer final : public StationSerializer{
    public:
        NoBodySerializer(StationPtr station, std::fstream &out) : StationSerializer(std::move(station), out) {}

        void SerializeBody() override {
        }
    };

} // namespace SPI

#endif //NOBODYSERIALIZER_H
