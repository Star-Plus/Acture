#include "MediaBinder.h"

#include "TimeService.h"

namespace SPI {


    MediaBinder::MediaBinder() {
    }

    MediaBinder::~MediaBinder() {
    }

    void MediaBinder::BindVerse(Verse* verse) {
        this->verse = verse;
    }

    void MediaBinder::UnbindVerse() {
        this->verse = nullptr;
    }

    std::vector<Clip> MediaBinder::DataToBind(const double currentTime) {

        if (verse == nullptr) {
            std::cout << "No verse bound to MediaBinder" << std::endl;
            return {};
        }

        const auto tracks = verse->tracks;

        std::vector<Clip> clipsToBind(tracks.size());
        currentClips.resize(tracks.size());

        for (size_t i = 0; i < tracks.size(); i++) {
            const auto& track = tracks[i];
            for (auto clip: track->clips) {

                if (currentTime <= clip.first + clip.second->end - clip.second->start && currentTime >= clip.first + clip.second->start) {
                    if (currentClips[i] != clip.second) {
                        currentClips[i] = clip.second;
                        clipsToBind[i] = *clip.second;
                    }
                    else {
                        clipsToBind[i] = Clip();
                    }

                    break;
                }
            }
        }

        return clipsToBind;

    }

}
