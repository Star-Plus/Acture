//
// Created by Ahmed Mustafa on 5/3/2025.
//

#include "VerseSerializer.h"

#include "../Core/Core.h"

namespace SPI {

    void VerseSerializer::Serialize(const Verse* verse, bool mode) {
        for (const auto track : verse->tracks) {
            const auto path = track->clips[0]->mediaPath;

            // Check if type of out is fstream or ostream
            if (mode) {

                // Read file from path
                std::ifstream videoFile(path, std::ios::binary);
                if (!videoFile.is_open()) {
                    std::cout << "Failed to open video file: " << path << std::endl;
                    throw std::runtime_error("Failed to open video file");
                }

                videoFile.seekg(0, std::ios::end);
                const location_t fileSize = videoFile.tellg();

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

                videoFile.close();

            }
            else {
                // Write the path length
                const uint32_t pathLength = path.length();
                out.write(reinterpret_cast<const char*>(&pathLength), sizeof(pathLength));

                // Write the path
                out.write(path.c_str(), pathLength);
            }

        }
    }

    void VerseSerializer::Deserialize() {
        // Implement deserialization logic here
    }

}
