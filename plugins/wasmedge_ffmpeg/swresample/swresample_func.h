#pragma once

#include "runtime/instance/module.h"
#include "swresample_base.h"
#include "ffmpeg_env.h"

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace SWResample {

class SWResampleVersion : public WasmEdgeFFmpegSWResample<SWResampleVersion> {
public:
  SWResampleVersion(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWResample(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame);
};

class SWRGetDelay: public WasmEdgeFFmpegSWResample<SWRGetDelay> {
public:
  SWRGetDelay(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWResample(HostEnv) {}
  Expect<int64_t> body(const Runtime::CallingFrame &Frame,uint32_t SWRContextId,int64_t Base);
};

} // namespace SWResample
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge