//
// Created by am180 on 3/4/2025.
//

#include "VerseStore.h"
#include "../../Utils/LabelGenerator.h"


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

    Verse* VerseStore::CreateNewVerse() {
        const auto verse = new Verse();
        verses[LabelGenerator::generateLabel("Untitled_Verse#")] = verse;
        return verse;
    }

    void VerseStore::RemoveVerse(const std::string &VerseName) {
        delete verses[VerseName];
        verses.erase(VerseName);
    }

    Verse *VerseStore::GetVerse(const std::string &VerseName) {
        auto it = verses.find(VerseName);
        if (it == verses.end()) {
            throw std::invalid_argument("Verse not found");
        }
        return it->second;
    }

    void VerseStore::ClearVerses() {
        for (auto &Verse : verses) {
            delete Verse.second;
        }
        verses.clear();
    }

    void VerseStore::EditVerseName(const std::string &oldName, const std::string &newName) {
        verses[newName] = verses[oldName];
        verses.erase(oldName);
    }

}