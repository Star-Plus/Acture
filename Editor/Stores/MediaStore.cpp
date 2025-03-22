//
// Created by Ahmed Mustafa on 3/2/2025.
//

#include "MediaStore.h"

namespace SPI {

    void MediaStore::addMedia(const std::string &mediaPath) {
        fs::path path(mediaPath);
        validateMediaType(path);
        this->media.push_back(path);
    }

    void MediaStore::removeMedia(int index) {
        media.erase(media.begin() + index);
    }

    const std::filesystem::path &MediaStore::getMedia(int index) const {
        return media[index];
    }

    const std::vector<std::string> MediaStore::listAllMedia_string() const
    {
        std::vector<std::string> result;

        for (const auto& p : media) {
            result.push_back(p.string());
        }

        return result;
    }

    const std::string MediaStore::getMedia_string(int index) const
    {
        return media[index].string();
    }

    void MediaStore::validateMediaType(const fs::path &path) {
        if (path.extension() != ".mp4") {
            throw std::invalid_argument("Invalid media type");
        }
    }

    const std::vector<fs::path> MediaStore::listAllMedia() const {
        return this->media;
    }


}