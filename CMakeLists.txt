cmake_minimum_required(VERSION 3.29)
project(Acture)

set(CMAKE_CXX_STANDARD 20)

# Create a shared library target for Engine code
add_library(ActureLib STATIC
        src/Units/Clip.cpp
        src/Units/Track.cpp
        src/Units/Verse.h
        src/Units/Verse.cpp
        src/Machines/Station.h
        src/Machines/Station.cpp
        src/Stores/StationNetwork.h
        src/Stores/StationNetwork.cpp
        src/Core/LeafStation.h
        src/Managers/StationManager.h
        src/Managers/StationManager.cpp
        src/Managers/TimeService.h
        src/Managers/TimeService.cpp
        src/Managers/MediaBinder.h
        src/Managers/MediaBinder.cpp
        src/States/EngineStateBase.h
        src/States/EngineRunningState.h
        src/States/EnginePausedState.h
        src/States/EngineEmptyState.h
        src/Application.h
        src/Application.cpp
        src/Mappers/EngineStateMapping.h
        src/States/EngineStationedPauseState.h
        src/States/EngineStationedRunState.h
        src/States/EngineTravellingState.h
        src/Editor/Editor.cpp
        src/Editor/Editor.h
        src/Mappers/StationTypeMapper.h
        src/Utils/SMath.cpp
        src/Utils/SMath.h
        src/Mappers/ExtentionMediaTypeMapper.h
        src/Core/Core.h
        src/Events/Event.h
        src/Schemas/StationChannelSchema.h
        src/Events/StationCallEvent.h
        src/Schemas/McqChannelSchema.h
        src/Mappers/SchemaGenerator.h
        src/States/EngineStationedState.h
        src/Channels/StationChannel.h
        src/Channels/Channel.h
        src/Schemas/LeafChannelSchema.h
        src/States/EngineRewindState.h
        src/Serializers/StationNetworkSerializer.cpp
        src/Serializers/StationNetworkSerializer.h
        src/Serializers/StationSerializer.cpp
        src/Serializers/StationSerializer.h
        src/Features/Mcq/McqSerializer.cpp
        src/Features/Mcq/McqSerializer.h
        src/Mappers/StationSerialzerMapper.h
        src/Serializers/NoBodySerializer.h
        src/Serializers/VerseSerializer.cpp
        src/Serializers/VerseSerializer.h
        src/Features/History/HistoryStation.h
        src/Features/History/HistoryStation.cpp
        src/Stores/StationHistory.cpp
        src/Stores/StationHistory.h
)

# Include headers for Engine
target_include_directories(ActureLib PUBLIC src)

# Main executable
add_executable(Acture main.cpp)

# Link Engine to the main executable
target_link_libraries(Acture PRIVATE ActureLib)