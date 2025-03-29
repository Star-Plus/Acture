//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_VERSESTORE_H
#define INTRASTATION_VERSESTORE_H

#include <map>
#include "../Units/Verse.h"

namespace SPI {

    class VerseStore {

        static VerseStore* instance;
        std::map<std::string, Verse*> verses;

    public:
        static VerseStore& Get() { return *instance; }

        VerseStore();
        ~VerseStore();

        Verse* CreateNewVerse();
        void RemoveVerse(const std::string &VerseName);
        Verse* GetVerse(const std::string &VerseName);
        void ClearVerses();
        void EditVerseName(const std::string &oldName, const std::string &newName);

    };

}


#endif //INTRASTATION_VERSESTORE_H
