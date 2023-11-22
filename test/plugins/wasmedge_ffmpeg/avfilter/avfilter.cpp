#include "avfilter/avFilter.h"
#include "../utils.h"
#include "avfilter//avfilter_func.h"
#include "avfilter/module.h"

#include <gtest/gtest.h>

using WasmEdge::Host::WasmEdgeFFmpeg::ErrNo;

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {

TEST_F(FFmpegTest, AVFilterStructs) { ASSERT_TRUE(AVFilterMod != nullptr); }

} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge
