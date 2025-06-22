#pragma once
#include "FrameBuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

	void preload_segment(const char* path, double start, double end);
	SPI::Frame get_frame_at_time(double time);

#ifdef __cplusplus
}
#endif
