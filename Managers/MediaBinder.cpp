#include "MediaBinder.h"

#include "TimeService.h"

namespace SPI {

    void MediaBinder::BindVerse(Verse* verse) {
        this->verse = verse;
        this->clipIndices.clear();
    }

    void MediaBinder::UnbindVerse() {
        this->verse = nullptr;
        this->clipIndices.clear();
    }

    std::vector<Clip> MediaBinder::DataToBind() const {

        if (verse == nullptr) {
            return {};
        }

        auto tracks = verse->tracks;
        std::vector<Clip> clips;

        auto currentTime = TimeService::Get().GetPlayerTime();

        for (auto& track: tracks) {
            for (auto& clip: track.clips) {
                if (currentTime <= clip.first+clip.second.end-clip.second.start) {
                    clips.push_back(clip.second);
                    break;
                }
            }
        }

        return clips;

    }

}
