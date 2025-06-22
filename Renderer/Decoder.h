//
// Created by Ahmed Mustafa on 6/22/2025.
//

#ifndef DECODER_H
#define DECODER_H

#include <string>
#include "FrameBuffer.h"

namespace SPI {

	class Decoder {

	public:
		Decoder(const std::string& path, double start, double end, FrameBuffer* buffer);
		void decodeSegment();

	private:
		std::string path;
		double startSec, endSec;
		FrameBuffer* frameBuffer;
	};

} // SPI

#endif //DECODER_H
