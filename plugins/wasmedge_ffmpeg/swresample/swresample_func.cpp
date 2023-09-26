#include "swresample_func.h"

extern "C"{
  #include "libswresample/swresample.h"
}

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace SWResample {

Expect<int32_t> SWResampleVersion::body(const Runtime::CallingFrame &){
  return swresample_version();
}

Expect<int64_t> SWRGetDelay::body(const Runtime::CallingFrame &,uint32_t SWRContextId,int64_t Base){
  FFMPEG_PTR_FETCH(SWRContext,SWRContextId,SwrContext);
  return swr_get_delay(SWRContext,Base);
}

} // namespace SWResample
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge
