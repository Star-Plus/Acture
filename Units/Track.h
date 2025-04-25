//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_TRACK_H
#define INTRASTATION_TRACK_H

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

        void AddClip(double position, const Clip& clip);
        void RemoveClip(double position);
        void ClearClips();
        const Clip& GetClip(double position) const;

        double GetLength() const {
            return length;
        }

        MEDIA_TYPE GetMediaType() const {
            return mediaType;
        }
        
        void SetMediaType(const MEDIA_TYPE type) {
            mediaType = type;
        }


        std::map<double, Clip> clips;
    };

}

#endif //INTRASTATION_TRACK_H
