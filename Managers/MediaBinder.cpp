#include "MediaBinder.h"

#include "TimeService.h"

namespace SPI {

    MediaBinder* MediaBinder::instance = nullptr;

    MediaBinder::MediaBinder() {
        instance = this;
    }

    MediaBinder::~MediaBinder() {
        instance = nullptr;
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

        std::cout << "Binding verse" << std::endl;

        const auto tracks = verse->tracks;

        std::vector<Clip> clipsToBind(tracks.size());
        currentClips.resize(tracks.size(), -1);

        for (size_t i = 0; i < tracks.size(); i++) {
            const auto& track = tracks[i];
            for (auto clip: track.clips) {

                if (currentTime <= clip.first + clip.second.end - clip.second.start && currentTime >= clip.first + clip.second.start) {
                    if (currentClips[i] != clip.first) {
                        currentClips[i] = clip.first;
                        clipsToBind[i] = clip.second;
                    }
                    else
                        clipsToBind[i] = Clip();

                    break;
                }
            }
        }

        return clipsToBind;

    }

}
