//
// Created by am180 on 3/4/2025.
//

#include "VerseStore.h"
#include "Utils/LabelGenerator.h"


namespace SPI {

    VerseStore* VerseStore::instance = nullptr;

    VerseStore::VerseStore() {
       instance = this;
    }

    VerseStore::~VerseStore() {
        for (auto &Verse : verses) {
            delete Verse.second;
        }
    }

    Verse* VerseStore::createNewVerse() {
        const auto verse = new Verse();
        verses[LabelGenerator::generateLabel("Untitled_Verse#")] = verse;
        return verse;
    }

    void VerseStore::removeVerse(const std::string &VerseName) {
        delete verses[VerseName];
        verses.erase(VerseName);
    }

    Verse &VerseStore::getVerse(const std::string &VerseName) {
        return *verses[VerseName];
    }

    void VerseStore::clearVerses() {
        for (auto &Verse : verses) {
            delete Verse.second;
        }
        verses.clear();
    }

    void VerseStore::editVerseName(const std::string &oldName, const std::string &newName) {
        verses[newName] = verses[oldName];
        verses.erase(oldName);
    }

}