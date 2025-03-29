#include "Engine.h"

namespace SPI {

    Engine::Engine() {
        verseStore = new VerseStore();
        versePlayer = new VersePlayer();
    }

    Engine::~Engine() {
    }

    void Engine::Run() {
    }

    void Engine::CreateVerse() {
        verseStore->CreateNewVerse();
    }

    void Engine::BindVerse(const std::string &verseName) {
        auto verse = verseStore->GetVerse(verseName);
        versePlayer->BindVerse(verse);
    }

}