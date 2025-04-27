//
// Created by Ahmed Mustafa on 4/25/2025.
//

#include "Editor.h"

#include "../Mappers/StationTypeMapper.h"

namespace SPI {
    Editor::Editor(Application& app) : app(app) {
        // Constructor implementation
    }

    ID_T Editor::AddStation(const ID_T id, const STATION_TYPE type, const double timelapse) const {
        const ID_T createdId = app.stationManager.getNetwork()->PushStation(id, CreateStation(type, timelapse));

        if (app.GetCurrentState() == EngineState::EMPTY){
            app.TranslateState(EngineState::PAUSED);
        }

        return createdId;
    }

    void Editor::InitializeVerse(Verse* verse, const std::string& mediaPath, const float duration) const {
        verse->CreateTrack();
        const Clip clip{mediaPath, 0, duration};
        verse->tracks[0].AddClip(0, clip);
    }
}
