//
// Created by Ahmed Mustafa on 4/25/2025.
//

#include "Editor.h"

#include <iostream>
#include <utility>

#include "../Mappers/StationTypeMapper.h"

namespace SPI {
    Editor::Editor(Application& app) : app(app) {
        // Constructor implementation
    }

    ID_T Editor::AddStation(const ID_T id, const STATION_TYPE type, const double timelapse) const {
        const auto createdStation = CreateStation(type, timelapse);
        const ID_T createdId = this->AddStationInstance(id, createdStation);

        return createdId;
    }

    void Editor::InitializeVerse(Verse* verse, const std::string& mediaPath, const float duration) const {
        verse->CreateTrack();
        Clip* clip = new Clip{mediaPath, 0, duration};
        verse->tracks[0]->AddClip(0, clip);
    }

    ID_T Editor::AddStationInstance(const ID_T parentId, const std::shared_ptr<Station>& station) const {
        const auto csId = app.stationManager.getNetwork()->PushStation(parentId, station);

        if (app.GetCurrentState() == EngineState::EMPTY){
            app.Travel(0);
            app.OnUpdate(0);
            app.TranslateState(EngineState::PAUSED);
        }

        return csId;
    }

    Clip* Editor::CreateClip(std::string mediaPath, const double start, const double end) {
        const auto clip = new Clip{std::move(mediaPath), start, end};
        return clip;
    }
}
