//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef MCQSERIALIZER_H
#define MCQSERIALIZER_H
#include "../../Serializers/StationSerializer.h"

namespace SPI {

    class McqSerializer final : public StationSerializer {
    public:
        explicit McqSerializer(const StationPtr &station, std::fstream& out);
        ~McqSerializer() override = default;
    protected:
        void SerializeBody() override;
    };

}




#endif //MCQSERIALIZER_H
