#pragma once

#include <vector>
#include <mutex>

namespace SPI {

	struct Frame {
		double timestamp;
		std::vector<uint8_t> data;
		int width;
		int height;
	};

	class FrameBuffer {
	public:
		FrameBuffer(size_t capacity);

		void push(Frame&& frame);
		Frame get_closest(double timestamp);
		void clear();

	private:
		std::vector<Frame> buffer;
		std::mutex mutex;
		size_t maxSize;
	};

}
