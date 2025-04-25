//
// Created by Ahmed Mustafa on 4/25/2025.
//

#include "Editor.h"

#include "../Mappers/StationTypeMapper.h"

namespace SPI {
    Editor::Editor(Application* app) : app(app) {
        // Constructor implementation
    }

    float Editor::AddStation(const float id, const STATION_TYPE type, const double timelapse) const {
        return app->stationManager.getNetwork().PushStation(id, CreateStation(type, timelapse));
    }
}
