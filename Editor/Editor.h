//
// Created by Ahmed Mustafa on 4/25/2025.
//

#ifndef EDITOR_H
#define EDITOR_H
#include "Application.h"


namespace SPI {
    class Editor {

        Application* app;

    public:
        Editor(Application* app);

        void AddStation(unsigned int id, STATION_TYPE type, double timelapse) const;

    };
}

#endif //EDITOR_H
