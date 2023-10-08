#pragma once

#include "avformat_base.h"
#include "runtime/callingframe.h"

namespace WasmEdge{
namespace Host{
namespace WasmEdgeFFmpeg {
namespace AVFormat {

class AVFormatOpenInput : public WasmEdgeFFmpegAVFormat<AVFormatOpenInput> {
public:
  AVFormatOpenInput(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegAVFormat(HostEnv) {}
  Expect<int32_t > body(const Runtime::CallingFrame &Frame, uint32_t AvFormatCtxPtr,
                       uint32_t UrlPtr, uint32_t UrlSize,uint32_t AvInputFormatId,uint32_t AvDictionaryId);
};

class AVFormatFindStreamInfo : public WasmEdgeFFmpegAVFormat<AVFormatFindStreamInfo> {
public:
  AVFormatFindStreamInfo(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegAVFormat(HostEnv) {}
  Expect<int32_t > body(const Runtime::CallingFrame &, uint32_t AvFormatCtxId,uint32_t AvDictionaryId);
};

class AVFormatCloseInput : public WasmEdgeFFmpegAVFormat<AVFormatCloseInput> {
public:
    AVFormatCloseInput(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVFormat(HostEnv) {}
    Expect<void> body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxPtr);
};

class AVReadPause : public WasmEdgeFFmpegAVFormat<AVReadPause> {
public:
    AVReadPause(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVFormat(HostEnv) {}
    Expect<int32_t > body(const Runtime::CallingFrame &, uint32_t AvFormatCtxId);
};

class AVReadPlay : public WasmEdgeFFmpegAVFormat<AVReadPlay> {
public:
    AVReadPlay(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVFormat(HostEnv) {}
    Expect<int32_t > body(const Runtime::CallingFrame &, uint32_t AvFormatCtxId);
};

class AVFormatSeekFile : public WasmEdgeFFmpegAVFormat<AVFormatSeekFile> {
public:
    AVFormatSeekFile(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVFormat(HostEnv) {}
    Expect<int32_t > body(const Runtime::CallingFrame &, uint32_t AvFormatCtxId,uint32_t StreamIdx,int64_t MinTs,int64_t Ts,int64_t MaxTs, int32_t Flags);
};

class AVDumpFormat : public WasmEdgeFFmpegAVFormat<AVDumpFormat> {
public:
    AVDumpFormat(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVFormat(HostEnv) {}
    Expect<void > body(const Runtime::CallingFrame &Frame,uint32_t avFormatCtxPtr,int32_t idx,uint32_t urlPtr,uint32_t urlSize,int32_t isOutput);
};

class AVFormatFreeContext : public WasmEdgeFFmpegAVFormat<AVFormatFreeContext> {
public:
    AVFormatFreeContext(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVFormat(HostEnv) {}
    Expect<void > body(const Runtime::CallingFrame &Frame,uint32_t AvFormatCtxPtr);
};

class AVFindBestStream : public WasmEdgeFFmpegAVFormat<AVFindBestStream> {
public:
  AVFindBestStream(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegAVFormat(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &,uint32_t AvFormatCtxId,int32_t MediaTypeId,int32_t WantedStream,int32_t RelatedStream,uint32_t DecoderRetId,int32_t Flags);
};

}
}
}
}
