//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_VERSESTORE_H
#define INTRASTATION_VERSESTORE_H

#include <map>
#include "Core/Editor/Units/Verse.h"

namespace SPI {

    class VerseStore {

        static VerseStore* instance;
        std::map<std::string, Verse*> verses;

    public:
        static VerseStore& Get() { return *instance; }

        VerseStore();
        ~VerseStore();

        Verse* createNewVerse();
        void removeVerse(const std::string &VerseName);
        Verse& getVerse(const std::string &VerseName);
        void clearVerses();
        void editVerseName(const std::string &oldName, const std::string &newName);

    };

}


#endif //INTRASTATION_VERSESTORE_H
