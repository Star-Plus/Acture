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
            if (!videoFile) {
                throw std::runtime_error("Failed to open video file");
            }

            videoFile.seekg(0, std::ios::end);
            const auto fileSize = videoFile.tellg();
            videoFile.seekg(0, std::ios::beg);

            std::vector<char> buffer(fileSize);
            if (!videoFile.read(buffer.data(), fileSize)) {
                throw std::runtime_error("Failed to read video file");
            }

            out.write(buffer.data(), fileSize);
            videoFile.close();
        }
    }

    void VerseSerializer::Deserialize() {
        // Implement deserialization logic here
    }

}