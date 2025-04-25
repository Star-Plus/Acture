//
// Created by Ahmed Mustafa on 4/25/2025.
//

#ifndef EDITOR_H
#define EDITOR_H
#include "../Application.h"


namespace SPI {
    class Editor {

        Application* app;

    public:
        Editor(Application* app);

        float AddStation(float id, STATION_TYPE type, double timelapse) const;
        void InitializeVerse(Verse* verse, const std::string& mediaPath, float duration) const;

    };
}

#endif //EDITOR_H
