//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_STATION_H
#define INTRASTATION_STATION_H

#include <memory>
#include <vector>

#include "../Types/STATION_TYPE.h"
#include "../Units/Verse.h"
#include "../Core/Core.h"

namespace SPI {

    class Station : public std::enable_shared_from_this<Station> {
    protected:

        STATION_TYPE type;
        timelapse_t timelapse;
        lifetime_t lifetime = 0.0;
        std::vector<Verse*> verses;
        std::vector<std::shared_ptr<Station>> stations;
        std::shared_ptr<Station> parent = nullptr;
        ID_T id = 0;
        thread_t threadId = 0;

        bool pause = true;

    public:
        Station(STATION_TYPE type, timelapse_t timelapse);
        virtual ~Station();

        virtual std::shared_ptr<Station> self() { return shared_from_this(); }
        std::shared_ptr<Station> GetParent() const { return parent; }

        ID_T GetId() const { return id; }
        void SetId(const ID_T id) { this->id = id; }

        thread_t GetThreadId() const { return threadId; }

        STATION_TYPE GetType() const { return type; }

        bool WillPause() const { return pause; }

        timelapse_t GetTimelapse() const { return timelapse; }
        void SetTimelapse(const timelapse_t timelapse) { this->timelapse = timelapse; }

        lifetime_t GetLifetime() const { return lifetime; }
        void SetLifetime(const lifetime_t lifetime) { this->lifetime = lifetime; }

        std::vector<std::shared_ptr<Station>> GetAllConnectedStations() const { return stations; }
        std::vector<Verse*> GetAllConnectedVerses() const { return verses; }

        std::shared_ptr<Station> GetConnectedStation(thread_t thread) const;
        Verse* GetConnectedVerse(thread_t idx) const;

        void ConnectStation(thread_t thread, const std::shared_ptr<Station>& station);
        void DisconnectStation(thread_t thread);
        void PushStation(const std::shared_ptr<Station>& station);

        unsigned int getThreadCount() const { return stations.size(); }

    };

}



#endif //INTRASTATION_STATION_H
