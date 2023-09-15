#pragma once

#include "avutil_base.h"
#include "runtime/callingframe.h"

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace AVUtil{

class AVUtilAVStrError : public WasmEdgeFFmpegAVUtil<AVUtilAVStrError> {
public:
    AVUtilAVStrError(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVUtil(HostEnv) {}
    Expect<int32_t> body(const Runtime::CallingFrame &Frame, int32_t Errnum,uint32_t Errbuf,uint32_t BufLen);
};

class AVUtilAVError : public WasmEdgeFFmpegAVUtil<AVUtilAVError> {
public:
    AVUtilAVError(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVUtil(HostEnv) {}
    Expect<int32_t> body(const Runtime::CallingFrame &Frame, int32_t Errnum);
};

class AVUtilAVUNError : public WasmEdgeFFmpegAVUtil<AVUtilAVUNError> {
public:
    AVUtilAVUNError(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
            : WasmEdgeFFmpegAVUtil(HostEnv) {}
    Expect<int32_t> body(const Runtime::CallingFrame &Frame, int32_t Errnum);
};

} // namespace AVUtil
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge
