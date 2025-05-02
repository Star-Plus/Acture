//
// Created by Ahmed Mustafa on 5/2/2025.
//

#include "StationSerializer.h"

#include <utility>

namespace SPI {

    StationSerializer::StationSerializer(StationPtr station, std::fstream &out)
        : station(std::move(station)), out(out)
    {}

    void StationSerializer::SerializeBase() const {

        const timelapse_t timeLapse = this->station->GetTimelapse();
        const lifetime_t lifeTime = this->station->GetLifetime();
        const STATION_TYPE type = this->station->GetType();
        const n_threads_t nThreads = this->station->getThreadCount();

        this->out.write(reinterpret_cast<const char*>(&timeLapse), sizeof(timeLapse));
        this->out.write(reinterpret_cast<const char*>(&lifeTime), sizeof(lifeTime));
        this->out.write(reinterpret_cast<const char*>(&type), sizeof(type));
        this->out.write(reinterpret_cast<const char*>(&nThreads), sizeof(nThreads));
    }

    void StationSerializer::Perform() {
        this->SerializeBase();
        this->SerializeBody();
    }


}