#include "DecoderBridge.h"
#include "Decoder.h"
#include <thread>
#include <memory>

static std::unique_ptr<SPI::FrameBuffer> g_frameBuffer;
static std::unique_ptr<SPI::Decoder> g_decoder;
static std::thread g_decodeThread;

extern "C" void preload_segment(const char* path, double start, double end) {
    if (g_decodeThread.joinable()) g_decodeThread.join();

    g_frameBuffer = std::make_unique<SPI::FrameBuffer>(300);
    g_decoder = std::make_unique<SPI::Decoder>(path, start, end, g_frameBuffer.get());

    g_decodeThread = std::thread([]() {
        g_decoder->decodeSegment();
        });
}

extern "C" SPI::Frame get_frame_at_time(double time) {
    if (!g_frameBuffer) return SPI::Frame{};
    return g_frameBuffer->get_closest(time);
}
