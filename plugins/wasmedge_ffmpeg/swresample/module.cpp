#include "module.h"
#include "swresample_func.h"

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace SWResample {

WasmEdgeFFmpegSWResampleModule::
    WasmEdgeFFmpegSWResampleModule(std::shared_ptr<WasmEdgeFFmpegEnv> Env)
    : ModuleInstance("wasmedge_ffmpeg_swresample") {

    addHostFunc("wasmedge_ffmpeg_swresample_swresample_getVersion",std::make_unique<SWResampleVersion>(Env));
    addHostFunc("wasmedge_ffmpeg_swresample_swr_get_delay",std::make_unique<SWRGetDelay>(Env));
}


} // namespace SWResample
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge
