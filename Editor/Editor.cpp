//
// Created by Ahmed Mustafa on 4/25/2025.
//

#include "Editor.h"

#include "../Mappers/StationTypeMapper.h"

namespace SPI {
    Editor::Editor(Application* app) : app(app) {
        // Constructor implementation
    }

    void Editor::AddStation(const unsigned int id, const STATION_TYPE type, const double timelapse) const {
        app->stationManager.getNetwork().PushStation(id, CreateStation(type, timelapse));
    }
}
