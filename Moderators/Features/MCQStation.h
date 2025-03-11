//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef MCQSTATION_H
#define MCQSTATION_H

#include "Core/Moderators/Station.h"

using str = std::string;

namespace SPI {

    class MCQStation : public Station {

        str question;
        std::vector<str> options;
        std::vector<unsigned int> links;

    public:
        explicit MCQStation(const double timelapse) : Station(STATION_TYPE::MCQ, timelapse) {}

        str getQuestion() const { return question; }
        void setQuestion(const str &question) { this->question = question; }

        std::vector<str> getOptions() { return options; }
        void setOption(const size_t idx, const str& newOption) { this->options[idx] = newOption; }

        std::vector<unsigned int> getLinks() { return links; }
        void setLink(const size_t idx, const unsigned int link) { this->links[idx] = link; }
    };

}

#endif //MCQSTATION_H
