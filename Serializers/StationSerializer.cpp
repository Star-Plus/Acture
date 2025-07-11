//
// Created by Ahmed Mustafa on 5/2/2025.
//

#include "StationSerializer.h"

#include "../Application.h"
#include "../Mappers/StationTypeMapper.h"
#include "../Mappers/TriggerMapper.h"

namespace SPI {

    StationSerializer::StationSerializer(std::ostream &out, std::istream &in, Application* context)
        : out(out), in(in), context(context)
    {}

    void StationSerializer::SerializeBase() const {

        const ID_T id = this->station->GetId();
        const itime_t timeLapse = this->station->GetTimelapse();
        const lifetime_t lifeTime = this->station->GetLifetime();
        const STATION_TYPE type = this->station->GetType();

        this->out.write(reinterpret_cast<const char*>(&type), sizeof(uint8_t));
        this->out.write(reinterpret_cast<const char*>(&id), sizeof(ID_T));
        this->out.write(reinterpret_cast<const char*>(&timeLapse), sizeof(timeLapse));
        this->out.write(reinterpret_cast<const char*>(&lifeTime), sizeof(lifeTime));

        const n_threads_t nThreads = station->getThreadCount();
        out.write(reinterpret_cast<const char*>(&nThreads), sizeof(nThreads));

        for (auto i = 0; i < this->station->getThreadCount(); i++) {
            const auto child = station->GetConnectedStation(i);
            out.write(reinterpret_cast<const char*>(&child), sizeof(ID_T));
        }

        const auto trigger = this->station->GetTrigger();

        if (trigger == nullptr) {
            constexpr auto triggerType = TRIGGER_TYPE::NONE;
            this->out.write(reinterpret_cast<const char*>(&triggerType), sizeof(TRIGGER_TYPE));
        }
        else {
            const auto triggerSerializer = TriggerMapper::CreateTriggerSerializer(trigger->GetType(), this->out, this->in, this->context);
            triggerSerializer->Serialize(trigger);
        }

    }

    void StationSerializer::DeserializeBase(const STATION_TYPE type, Application* context) {
        ID_T id;
        itime_t timeLapse;
        lifetime_t lifeTime;
        n_threads_t nThreads;

        this->in.read(reinterpret_cast<char*>(&id), sizeof(ID_T));

        this->in.read(reinterpret_cast<char*>(&timeLapse), sizeof(timeLapse));

        this->station = CreateStation(type, context);
        this->station->SetId(id);

        this->in.read(reinterpret_cast<char*>(&lifeTime), sizeof(lifeTime));

        this->station->SetLifetime(lifeTime);

        this->in.read(reinterpret_cast<char*>(&nThreads), sizeof(nThreads));

        for (auto i = 0; i < nThreads; i++) {
            ID_T childId;
            this->in.read(reinterpret_cast<char*>(&childId), sizeof(ID_T));
            this->station->PushId(childId);
        }

        TRIGGER_TYPE triggerType;
        this->in.read(reinterpret_cast<char*>(&triggerType), sizeof(TRIGGER_TYPE));

        if (triggerType == TRIGGER_TYPE::NONE) {
            this->station->SetTrigger(nullptr);
            return;
        }

        const auto triggerSerializer = TriggerMapper::CreateTriggerSerializer(triggerType, this->out, this->in, context);
        this->station->SetTrigger(triggerSerializer->Deserialize(triggerType));

    }

    void StationSerializer::Serialize(const StationPtr& station) {
        this->station = station;
        this->SerializeBase();
        this->SerializeBody();
    }

    StationPtr& StationSerializer::Deserialize(const STATION_TYPE type) {
        this->DeserializeBase(type, this->context);
        this->DeserializeBody();

        return this->station;
    }


}
