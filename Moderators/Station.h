//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_STATION_H
#define INTRASTATION_STATION_H

#include "STATION_TYPE.h"
#include "Core/Editor/Units/Verse.h"

namespace SPI {

    class Station {
    protected:
        STATION_TYPE type;
        double timelapse;
        std::vector<Verse*> verses;
        std::vector<Station*> stations;

    public:
        Station(STATION_TYPE type, double timelapse);
        ~Station();

        double getTimelapse() const { return timelapse; }

        void addVerse();
        void connectVerse(int idx, Verse* Verse);
        void removeVerse(int idx);
        Verse& moveVerse(int idx);

        void connectStation(unsigned int thread, Station* station);
        void disconnectStation(int thread);
        Station& getConnectedStation(unsigned int thread);
    };

}



#endif //INTRASTATION_STATION_H
