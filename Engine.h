#pragma once

#include <memory.h>

#include "spich.h"

namespace SPI
{
    class Engine
    {

        VerseStore* verseStore;
        VersePlayer* versePlayer;

    public:
        Engine();
        ~Engine();

        VerseStore& GetVerseStore() { return *verseStore; }
        VersePlayer& GetVersePlayer() { return *versePlayer; }

        void CreateVerse();
        void BindVerse(const std::string &verse);

        void Run();
    };
}