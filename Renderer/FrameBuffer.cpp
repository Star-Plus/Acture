#include "FrameBuffer.h"
#include <algorithm>
#include <cmath>

namespace SPI {

	FrameBuffer::FrameBuffer(size_t capacity) : maxSize(capacity) {}

	void FrameBuffer::push(Frame&& frame) {
		std::lock_guard<std::mutex> lock(mutex);

		if (buffer.size() >= maxSize) {
			buffer.erase(buffer.begin());
		}
		buffer.push_back(std::move(frame));
	}

	Frame FrameBuffer::get_closest(double timestamp) {
		std::lock_guard<std::mutex> lock(mutex);
		if (buffer.empty()) return Frame{};

		auto it = std::min_element(buffer.begin(), buffer.end(), [timestamp](const Frame& a, const Frame& b) {
			return std::abs(a.timestamp - timestamp) < std::abs(b.timestamp - timestamp);
		});

		return *it;
	}

	void FrameBuffer::clear() {
		std::lock_guard<std::mutex> lock(mutex);
		buffer.clear();
	}

}