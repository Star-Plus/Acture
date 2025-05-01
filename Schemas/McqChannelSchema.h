//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef MCQCHANNELSCHEMA_H
#define MCQCHANNELSCHEMA_H

#include <string>
#include <vector>

#include "StationChannelSchema.h"

namespace SPI {
    struct McqChannelSchema : StationChannelSchema {
        std::string question;
        std::vector<std::string> options;
    };

    inline std::ostream& operator<<(std::ostream& os, const McqChannelSchema& schema) {
        os << "Does pause: " << schema.willPause << std::endl;
        os << "Question: " << schema.question << "\nOptions: ";
        for (const auto& option : schema.options) {
            os << option << " ";
        }
        return os;
    }
}

#endif //MCQCHANNELSCHEMA_H
