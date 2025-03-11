//
// Created by Ahmed Mustafa on 3/2/2025.
//

#include "MediaStore.h"

namespace SPI {

    void MediaStore::addMedia(const std::string &mediaPath) {
        fs::path path(mediaPath);
        validateMediaType(path);
        media.push_back(path);
    }

    void MediaStore::removeMedia(int index) {
        media.erase(media.begin() + index);
    }

    const std::filesystem::path &MediaStore::getMedia(int index) const {
        return media[index];
    }

    void MediaStore::validateMediaType(const fs::path &path) {
        if (path.extension() != ".mp4") {
            throw std::invalid_argument("Invalid media type");
        }
    }

}