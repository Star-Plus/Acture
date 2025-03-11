//
// Created by am180 on 3/4/2025.
//

#include "Station.h"
#include "Core/Editor/Stores/VerseStore.h"

namespace SPI {

    Station::Station(const STATION_TYPE type, const double timelapse) : type(type), timelapse(timelapse) {
    }

    Station::~Station() {
    }

    void Station::addVerse() {
        if (&VerseStore::Get() == nullptr) throw std::runtime_error("VerseStore not initialized");
        auto Verse = VerseStore::Get().createNewVerse();
        verses.push_back(Verse);
    }

    void Station::connectVerse(int idx, Verse *Verse) {
        verses.insert(verses.cbegin() + idx, Verse);
    }

    void Station::removeVerse(int idx) {
        delete verses[idx];
        verses.erase(verses.begin() + idx);
    }

    Verse &Station::moveVerse(int idx) {
        Verse *Verse = verses[idx];
        verses.erase(verses.begin() + idx);
        return *Verse;
    }

    void Station::connectStation(const unsigned int thread, Station *station) {
        if (thread >= stations.size())
            stations.insert(stations.cbegin()+thread, station);
        else
            stations[thread] = station;
    }

    void Station::disconnectStation(int thread) {
        stations[thread] = nullptr;
    }

    Station &Station::getConnectedStation(unsigned int thread) {
        if (thread > stations.size()) throw std::out_of_range("Thread out of range");
        return *stations[thread];
    }

}