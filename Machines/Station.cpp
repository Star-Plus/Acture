//
// Created by am180 on 3/4/2025.
//

#include "Station.h"

#include <iostream>
#include <utility>

namespace SPI {

    Station::Station(const STATION_TYPE type, const double timelapse) : type(type), timelapse(timelapse) {}

    Station::~Station() {
        verses.clear();
        for (auto &station : stations) {
            station.reset();
        }
        stations.clear();
    }

    Verse* Station::GetConnectedVerse(const unsigned int idx) const {
        if (idx >= verses.size()) {
            throw std::out_of_range("Index out of range");
        }
        return verses[idx];
    }

    void Station::ConnectStation(const unsigned int thread, const std::shared_ptr<Station>& station) {
        if (thread >= this->stations.size()) {
            stations.resize(thread + 1);
            verses.resize(thread + 1);
        }

        stations[thread] = station;
        station->parent = shared_from_this();
        station->threadId = thread;

        verses[thread] = new Verse();
    }

    void Station::DisconnectStation(const unsigned int thread) {
        stations[thread].reset();
        stations[thread] = nullptr;

        if (verses[thread] != nullptr) {
            delete verses[thread];
            verses[thread] = nullptr;
        }
    }

    std::shared_ptr<Station> Station::GetConnectedStation(const unsigned int thread) const {
        if (thread >= stations.size()) return nullptr;
        return stations[thread];
    }

    void Station::PushStation(const std::shared_ptr<Station>& station) {
        ConnectStation(stations.size(), station);
    }

}