//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_STATIONSTORE_H
#define INTRASTATION_STATIONSTORE_H

#include "Station.h"

namespace SPI {

        class StationStore {

            static StationStore* instance;
            std::vector<Station*> stations;

        public:
            StationStore(){
                instance = this;
            }

            StationStore& Get() { return *instance; }

            void AddStation(Station* station) {
                stations.push_back(station);
            }

            Station* GetStation(unsigned int idx) {
                return stations.at(idx);
            }

            void RemoveStation(Station* station) {
                try {
                    stations.erase(std::remove(stations.begin(), stations.end(), station), stations.end());
                }
                catch (std::out_of_range &e) {
                    return;
                }
            }

            void RemoveStationByIndex(unsigned int idx) {
                try {
                    stations.erase(stations.begin() + idx);
                }
                catch (std::out_of_range &e) {
                    return;
                }
            }

        };
}

#endif //INTRASTATION_STATIONSTORE_H
