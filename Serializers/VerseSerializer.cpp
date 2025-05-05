//
// Created by Ahmed Mustafa on 5/3/2025.
//

#include "VerseSerializer.h"

namespace SPI {

    void VerseSerializer::Serialize(const Verse* verse) {
        for (const auto track : verse->tracks) {
            const auto path = track->clips[0]->mediaPath;
            // Read file from path
            std::ifstream videoFile(path, std::ios::binary);
            if (!videoFile.is_open()) {
                throw std::runtime_error("Failed to open video file");
            }

            videoFile.seekg(0, std::ios::end);
            const auto fileSize = videoFile.tellg();


            if (fileSize == -1) {
                throw std::runtime_error("Failed to get video file size");
            }

            videoFile.seekg(0, std::ios::beg);

            out.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));

            std::vector<char> buffer(fileSize);
            if (!videoFile.read(buffer.data(), fileSize)) {
                throw std::runtime_error("Failed to read video file");
            }

            out.write(buffer.data(), fileSize);
            out.flush();

            videoFile.close();
        }
    }

    void VerseSerializer::Deserialize() {
        // Implement deserialization logic here
    }

}