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

        const std::vector<fs::path> listAllMedia() const;
        const std::filesystem::path& getMedia(int index) const;

        const std::vector<std::string> listAllMedia_string() const;
        const std::string getMedia_string(int index) const;

    private:
        void validateMediaType(const fs::path &path);
    };

}

#endif //MEDIASTORE_H
