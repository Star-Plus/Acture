//
// Created by Ahmed Mustafa on 5/2/2025.
//

#include "McqSerializer.h"

#include "../MCQStation.h"

namespace SPI {

    McqSerializer::McqSerializer(std::fstream& out)
        : StationSerializer(out) {}

    void McqSerializer::SerializeBody() {
        const auto& mcq = std::dynamic_pointer_cast<MCQStation>(station);

        const auto question = mcq->getQuestion();
        const uint32_t questionSize = question.size();

        out.write(reinterpret_cast<const char *>(&questionSize), sizeof(questionSize));
        out.write(question.c_str(), questionSize);

        const auto optionsCount = mcq->getOptions().size();
        out.write(reinterpret_cast<const char *>(&optionsCount), sizeof(optionsCount));

        for (int i = 0; i < optionsCount; ++i) {
            const auto& option = mcq->getOption(i);
            const auto optionSize = static_cast<uint32_t>(option.length());
            out.write(reinterpret_cast<const char *>(&optionSize), sizeof(optionSize));
            out.write(option.c_str(), optionSize);
        }
    }

    void McqSerializer::DeserializeBody() {
        const auto& mcq = std::dynamic_pointer_cast<MCQStation>(station);
        uint32_t questionSize;
        out.read(reinterpret_cast<char *>(&questionSize), sizeof(questionSize));
        std::string question(questionSize, '\0');
        out.read(question.data(), questionSize);

        std::cout << "Question: " << question << std::endl;

        mcq->setQuestion(question);

        size_t optionsCount;
        out.read(reinterpret_cast<char *>(&optionsCount), sizeof(optionsCount));

        for (uint32_t i = 0; i < optionsCount; ++i) {
            uint32_t optionSize;
            out.read(reinterpret_cast<char *>(&optionSize), sizeof(optionSize));

            std::string option(optionSize, '\0');
            out.read(&option[0], optionSize);

            std::cout << "Option " << i << ": " << option << std::endl;
            mcq->setOption(i, option);
        }

    }

}
