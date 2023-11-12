#include "avcodec/avCodecParameters.h"
#include "../utils.h"
#include "avcodec/module.h"

#include <gtest/gtest.h>

using WasmEdge::Host::WasmEdgeFFmpeg::ErrNo;

// Testing all AVCodecstruct

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {

TEST_F(FFmpegTest, AVCodecParameters) {
  ASSERT_TRUE(AVCodecMod != nullptr);

  // File name is 32 char long.
  uint32_t AVCodecParamPtr = UINT32_C(60);
  // Refactor code.
  initAVCodec(UINT32_C(20), UINT32_C(24), UINT32_C(28), AVCodecParamPtr,
              UINT32_C(64));

  uint32_t AVCodecParamId = readUInt32(MemInst, AVCodecParamPtr);

  auto *AVCodecMod = TestUtils::InitModules::createAVCodecModule();

  auto *FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodecparam_codec_id");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecParamCodecId = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecParamCodecId &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecParamCodecId.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AVCodecParamId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), 27); // H264
  }

  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodecparam_codec_type");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecParamCodecType = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecParamCodecType &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecParamCodecType.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AVCodecParamId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), 0); // MediaType Video
  }

  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodecparam_set_codec_tag");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecParamSetCodecTag = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecParamSetCodecTag &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecParamSetCodecTag.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AVCodecParamId, 20},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }
}
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge