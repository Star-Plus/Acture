cmake_minimum_required(VERSION 3.29)
project(Renderer)

# FFmpeg headers
include_directories(${CMAKE_SOURCE_DIR}/../Lib/ffmpeg/include)

# FFmpeg static libs
link_directories(${CMAKE_SOURCE_DIR}/../Lib/ffmpeg/lib)

# Your renderer source files
add_library(Renderer STATIC
        FrameBuffer.cpp
        FrameBuffer.h
        Decoder.cpp
        Decoder.h
        DecoderBridge.cpp
)

# Link FFmpeg libs (order matters!)
target_link_libraries(Renderer
        avformat
        avcodec
        avutil
        swscale
        swresample
)

# Optional if your FFmpeg build depends on it
find_package(Threads REQUIRED)
target_link_libraries(Renderer Threads::Threads z)
