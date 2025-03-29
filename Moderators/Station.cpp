//
// Created by am180 on 3/4/2025.
//

#include "Station.h"
#include "../Editor/Stores/VerseStore.h"

namespace SPI {

    Station::Station(const STATION_TYPE type, const double timelapse) : type(type), timelapse(timelapse) {}

    Station::~Station() {
    }

    void Station::AddVerse() {
        if (&VerseStore::Get() == nullptr) throw std::runtime_error("VerseStore not initialized");
        auto Verse = VerseStore::Get().CreateNewVerse();
        verses.push_back(Verse);
    }

    void Station::ConnectVerse(int idx, Verse *Verse) {
        verses.insert(verses.cbegin() + idx, Verse);
    }

    void Station::RemoveVerse(int idx) {
        delete verses[idx];
        verses.erase(verses.begin() + idx);
    }

    Verse &Station::MoveVerse(int idx) {
        Verse *Verse = verses[idx];
        verses.erase(verses.begin() + idx);
        return *Verse;
    }

    Verse *Station::GetVerse(int idx) {
        if (idx >= verses.size()) return nullptr;
        return verses[idx];
    }

    void Station::ConnectStation(const unsigned int thread, std::shared_ptr<Station> station) {
        if (thread >= this->stations.size())
            stations.resize(thread + 1);

        stations[thread] = station;
    }

    void Station::DisconnectStation(int thread) {
        stations[thread] = nullptr;
    }

    std::shared_ptr<Station> Station::GetConnectedStation(unsigned int thread) {
        if (thread >= stations.size()) return nullptr;
        return stations[thread];
    }

}