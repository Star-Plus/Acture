//
// Created by Ahmed Mustafa on 5/2/2025.
//

#include "StationSerializer.h"

#include <utility>

#include "../Mappers/StationTypeMapper.h"

namespace SPI {

    StationSerializer::StationSerializer(std::ostream &out, std::istream &in)
        : out(out), in(in)
    {}

    void StationSerializer::SerializeBase() const {

        const itime_t timeLapse = this->station->GetTimelapse();
        const lifetime_t lifeTime = this->station->GetLifetime();
        const STATION_TYPE type = this->station->GetType();

        this->out.write(reinterpret_cast<const char*>(&type), sizeof(uint8_t));
        this->out.write(reinterpret_cast<const char*>(&timeLapse), sizeof(timeLapse));
        this->out.write(reinterpret_cast<const char*>(&lifeTime), sizeof(lifeTime));
    }

    void StationSerializer::DeserializeBase(const STATION_TYPE type) {
        itime_t timeLapse;
        lifetime_t lifeTime;

        this->in.read(reinterpret_cast<char*>(&timeLapse), sizeof(timeLapse));

        std::cout << "Timelapse: " << timeLapse << std::endl;

        this->station = CreateStation(type);

        this->in.read(reinterpret_cast<char*>(&lifeTime), sizeof(lifeTime));

        std::cout << "Lifetime: " << lifeTime << std::endl;

        // this->station->SetLifetime(lifeTime);
    }

    void StationSerializer::Serialize(const StationPtr& station) {
        this->station = station;
        this->SerializeBase();
        this->SerializeBody();
    }

    StationPtr& StationSerializer::Deserialize(const STATION_TYPE type) {
        this->DeserializeBase(type);
        this->DeserializeBody();

        return this->station;
    }


}
