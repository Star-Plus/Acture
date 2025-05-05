//
// Created by Ahmed Mustafa on 5/2/2025.
//

#include "StationSerializer.h"

#include <utility>

#include "../Mappers/StationTypeMapper.h"

namespace SPI {

    StationSerializer::StationSerializer(std::fstream &out)
        : out(out)
    {}

    void StationSerializer::SerializeBase() const {

        const timelapse_t timeLapse = this->station->GetTimelapse();
        const lifetime_t lifeTime = this->station->GetLifetime();
        const STATION_TYPE type = this->station->GetType();

        this->out.write(reinterpret_cast<const char*>(&type), sizeof(type));
        this->out.write(reinterpret_cast<const char*>(&timeLapse), sizeof(timeLapse));
        this->out.write(reinterpret_cast<const char*>(&lifeTime), sizeof(lifeTime));
    }

    void StationSerializer::DeserializeBase(const STATION_TYPE type) {
        timelapse_t timeLapse;
        lifetime_t lifeTime;

        this->out.read(reinterpret_cast<char*>(&timeLapse), sizeof(timeLapse));

        this->station = CreateStation(type, timeLapse);

        this->out.read(reinterpret_cast<char*>(&lifeTime), sizeof(lifeTime));

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
