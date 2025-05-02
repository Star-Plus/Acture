//
// Created by Ahmed Mustafa on 5/2/2025.
//

#include "McqSerializer.h"

#include <Features/MCQStation.h>

namespace SPI {

    McqSerializer::McqSerializer(const StationPtr &station, std::fstream& out)
        : StationSerializer(station, out) {}

    void McqSerializer::SerializeBody() {
        const auto& mcq = std::dynamic_pointer_cast<MCQStation>(station);

        const auto question = mcq->getQuestion();
        const auto questionSize = question.size();

        out.write(reinterpret_cast<const char *>(&questionSize), sizeof(question.size()));
        out.write(question.data(), questionSize);

        for (int i = 0; i < mcq->getOptions().size(); ++i) {
            const auto& option = mcq->getOptions()[i];
            const auto optionSize = option.size();
            out.write(reinterpret_cast<const char *>(&optionSize), sizeof(optionSize));
            out.write(option.data(), optionSize);
        }
    }

}
