//
// Created by Ahmed Mustafa on 3/2/2025.
//

#ifndef MEDIASTORE_H
#define MEDIASTORE_H

#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


namespace SPI {

    class MediaStore {
        std::vector<fs::path> media;

    public:
        void addMedia(const std::string &mediaPath);

        void removeMedia(int index);

        const std::filesystem::path& getMedia(int index) const;

    private:
        void validateMediaType(const fs::path &path);
    };

}

#endif //MEDIASTORE_H
