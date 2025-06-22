//
// Created by Ahmed Mustafa on 6/22/2025.
//

#include "Decoder.h"
extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h> 
}

namespace SPI {

	Decoder::Decoder(const std::string& path, double start, double end, FrameBuffer* buffer)
		: path(path), startSec(start), endSec(end), frameBuffer(buffer) {}

	void Decoder::decodeSegment() {

		avformat_network_init();
		AVFormatContext* fmtCtx = nullptr;

		if (avformat_open_input(&fmtCtx, path.c_str(), nullptr, nullptr) != 0) return;
		if (avformat_find_stream_info(fmtCtx, nullptr) < 0) return;

		int videoStream = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
		if (videoStream < 0) return;

		AVCodecParameters* codecPar = fmtCtx->streams[videoStream]->codecpar;
		AVCodecContext* codecCtx = avcodec_alloc_context3(nullptr);

		const AVCodec* codec = avcodec_find_decoder(codecPar->codec_id);
		avcodec_open2(codecCtx, codec, nullptr);

		AVPacket* pkt = av_packet_alloc();
		AVFrame* frame = av_frame_alloc();
		AVFrame* rgb = av_frame_alloc();

		SwsContext* sws = sws_getContext(
			codecCtx->width, codecCtx->height, codecCtx->pix_fmt,
			codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24,
			SWS_BILINEAR, 
			nullptr, nullptr, nullptr
		);

		int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, codecCtx->width, codecCtx->height, 1);
		uint8_t* buffer = (uint8_t*)av_malloc(numBytes);
		av_image_fill_arrays(rgb->data, rgb->linesize, buffer, AV_PIX_FMT_RGB24, codecCtx->width, codecCtx->height, 1);

		int64_t start_pts = startSec / av_q2d(fmtCtx->streams[videoStream]->time_base);
		av_seek_frame(fmtCtx, videoStream, start_pts, AVSEEK_FLAG_BACKWARD);

		while (av_read_frame(fmtCtx, pkt) >= 0) {
			if (pkt->stream_index != videoStream) {
				av_packet_unref(pkt);
				continue;
			}

			avcodec_send_packet(codecCtx, pkt);
			while (avcodec_receive_frame(codecCtx, frame) == 0) {
				double timestamp = frame->pts * av_q2d(fmtCtx->streams[videoStream]->time_base);
				if (timestamp < startSec) continue;
				if (timestamp > endSec) break;

				sws_scale(sws, frame->data, frame->linesize, 0, codecCtx->height, rgb->data, rgb->linesize);

				Frame outFrame = {
					timestamp,
					std::vector<uint8_t>(rgb->data[0], rgb->data[0] + numBytes),
					codecCtx->width,
					codecCtx->height
				};
			}

			av_packet_unref(pkt);
		}

		av_frame_free(&frame);
		av_frame_free(&rgb);
		av_packet_free(&pkt);
		avcodec_free_context(&codecCtx);
		avformat_close_input(&fmtCtx);
		sws_freeContext(sws);
	}

} // SPI