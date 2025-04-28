//
// Created by Ahmed Mustafa on 4/25/2025.
//

#ifndef EDITOR_H
#define EDITOR_H
#include "../Application.h"
#include "../Core/Core.h"


namespace SPI {
    class Editor {

        Application& app;

    public:
        Editor(Application& app);

        ID_T AddStation(ID_T id, STATION_TYPE type, double timelapse) const;
        void InitializeVerse(Verse* verse, const std::string& mediaPath, float duration) const;

        ID_T AddStationInstance(ID_T parentId, const std::shared_ptr<Station>& station) const;

    };
}

#endif //EDITOR_H
