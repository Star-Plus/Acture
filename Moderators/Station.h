//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_STATION_H
#define INTRASTATION_STATION_H

#include "STATION_TYPE.h"
#include "../Editor/Units/Verse.h"

namespace SPI {

    class Station : public std::enable_shared_from_this<Station> {
    protected:
        STATION_TYPE type;
        double timelapse;
        std::vector<Verse*> verses;
        std::vector<std::shared_ptr<Station>> stations;

    public:
        Station(STATION_TYPE type, double timelapse);
        ~Station();

        virtual std::shared_ptr<Station> self() { return shared_from_this(); }

        double GetTimelapse() const { return timelapse; }
        void SetTimelapse(double timelapse) { this->timelapse = timelapse; }

        STATION_TYPE GetType() const { return type; }

        void AddVerse();
        void ConnectVerse(int idx, Verse* Verse);
        void RemoveVerse(int idx);
        Verse& MoveVerse(int idx);
        Verse* GetVerse(int idx);

        unsigned int getStationCount() const { return stations.size(); }
        unsigned int getVerseCount() const { return verses.size(); }

        void ConnectStation(unsigned int thread, std::shared_ptr<Station> station);
        void DisconnectStation(int thread);
        std::shared_ptr<Station> GetConnectedStation(unsigned int thread);
    };

}



#endif //INTRASTATION_STATION_H
