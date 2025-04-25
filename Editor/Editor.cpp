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
        const float createdId = app->stationManager.getNetwork().PushStation(id, CreateStation(type, timelapse));
        return createdId;
    }

    void Editor::InitializeVerse(Verse* verse, const std::string& mediaPath, const float duration) const {
        verse->CreateTrack();
        const Clip clip{mediaPath, 0, duration};
        verse->tracks[0].AddClip(0, clip);
    }
}
