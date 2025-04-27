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
        double timelapse;
        double lifetime = 0.0;
        std::vector<Verse*> verses;
        std::vector<std::shared_ptr<Station>> stations;
        std::shared_ptr<Station> parent = nullptr;
        ID_T id = 0;
        unsigned int threadId = 0;

        bool pause = true;

    public:
        Station(STATION_TYPE type, double timelapse);
        virtual ~Station();

        virtual std::shared_ptr<Station> self() { return shared_from_this(); }
        std::shared_ptr<Station> GetParent() const { return parent; }

        ID_T GetId() const { return id; }
        void SetId(ID_T id) { this->id = id; }

        unsigned int GetThreadId() const { return threadId; }

        STATION_TYPE GetType() const { return type; }

        bool WillPause() const { return pause; }

        double GetTimelapse() const { return timelapse; }
        void SetTimelapse(const double timelapse) { this->timelapse = timelapse; }

        double GetLifetime() const { return lifetime; }
        void SetLifetime(const double lifetime) { this->lifetime = lifetime; }

        std::vector<std::shared_ptr<Station>> GetAllConnectedStations() const { return stations; }
        std::vector<Verse*> GetAllConnectedVerses() const { return verses; }

        std::shared_ptr<Station> GetConnectedStation(unsigned int thread) const;
        Verse* GetConnectedVerse(unsigned int idx) const;

        void ConnectStation(unsigned int thread, const std::shared_ptr<Station>& station);
        void DisconnectStation(unsigned int thread);
        void PushStation(const std::shared_ptr<Station>& station);

        unsigned int getThreadCount() const { return stations.size(); }

    };

}



#endif //INTRASTATION_STATION_H
