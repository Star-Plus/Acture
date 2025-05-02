//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_TRACK_H
#define INTRASTATION_TRACK_H

#include <iostream>
#include <map>
#include "Clip.h"
#include "../Types/MEDIA_TYPE.h"

namespace SPI {

    class Track {

        MEDIA_TYPE mediaType = MEDIA_TYPE::NONE;
        double length;

        double CalculateLength();

    public:

        Track();
        ~Track();

        void AddClip(double position, Clip* clip);
        void RemoveClip(double position);
        void ClearClips();

        Clip* GetClip(double position) const;

        double GetLength() const {
            return length;
        }

        MEDIA_TYPE GetMediaType() const {
            return mediaType;
        }
        
        void SetMediaType(const MEDIA_TYPE type) {
            mediaType = type;
        }

        size_t GetClipCount() const {
            return clips.size();
        }


        std::map<double, Clip*> clips;
    };

}

#endif //INTRASTATION_TRACK_H
