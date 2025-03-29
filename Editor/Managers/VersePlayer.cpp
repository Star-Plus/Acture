#include "VersePlayer.h"

namespace SPI {

    VersePlayer::VersePlayer(Verse* initialVerse) : playingVerse(initialVerse) {}

    void VersePlayer::BindVerse(Verse* verse) {
        playingVerse = verse;
    }

}