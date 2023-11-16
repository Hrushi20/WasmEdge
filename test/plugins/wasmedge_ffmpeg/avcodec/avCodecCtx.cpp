#include "../utils.h"
#include "avcodec/avCodecContext.h"
#include "avcodec/module.h"

#include <gtest/gtest.h>

using WasmEdge::Host::WasmEdgeFFmpeg::ErrNo;

// Testing all AVCodecCtxstruct
namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {

TEST_F(FFmpegTest, AVCodecCtx) {
  ASSERT_TRUE(AVCodecMod != nullptr);

  uint32_t AVCodecCtxPtr = UINT32_C(64);

  std::string FileName = "ffmpeg-assets/sample_video.mp4"; // 32 chars
  initAVCodec(UINT32_C(20), UINT32_C(24), UINT32_C(28), FileName, UINT32_C(60),
              AVCodecCtxPtr);
  uint32_t NumPtr = UINT32_C(64);
  uint32_t DenPtr = UINT32_C(68);

  uint32_t AVCodecCtxId = readUInt32(MemInst, AVCodecCtxPtr);

  auto *FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_codec_id");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxCodecID = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxCodecID &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxCodecID.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId},
        Result));
    EXPECT_EQ(Result[0].get<uint32_t>(), 27); // H264
  }

  uint32_t CodecType = 0; // MediaType Video
  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_codec_type");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxSetCodecType = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetCodecType &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxSetCodecType.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId, CodecType},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_codec_type");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxCodecType = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxCodecType &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxCodecType.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId},
        Result));
    EXPECT_EQ(Result[0].get<uint32_t>(), CodecType); // MediaType Video
  }

  int32_t Num = 5;
  int32_t Den = 10;
  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_time_base");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxSetTimebase = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetTimebase &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxSetTimebase.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId, Num, Den},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_time_base");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxTimeBase = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxTimeBase &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxTimeBase.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId, NumPtr,
                                                    DenPtr},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
    int32_t Numerator = readIInt32(MemInst, NumPtr);
    int32_t Denominator = readIInt32(MemInst, DenPtr);
    EXPECT_EQ(Numerator, Num);
    EXPECT_EQ(Denominator, Den);
  }

  int32_t Dimension = 200;
  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_width");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxSetWidth = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetWidth &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxSetWidth.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId, Dimension},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_width");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxWidth =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxWidth &>(
          FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxWidth.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), Dimension);
  }

  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_height");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxSetHeight = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetHeight &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxSetHeight.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId, Dimension},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_height");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxHeight =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxHeight &>(
          FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxHeight.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), Dimension);
  }

  Num = 10;
  Den = 20;
  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_sample_aspect_ratio");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxSetSampleAspectRatio = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSampleAspectRatio
          &>(FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxSetSampleAspectRatio.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId, Num, Den},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVCodecMod->findFuncExports(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_sample_aspect_ratio");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVCodecCtxSampleAspectRatio = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSampleAspectRatio &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVCodecCtxSampleAspectRatio.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId, NumPtr,
                                                    DenPtr},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    int32_t Numerator = readIInt32(MemInst, NumPtr);
    int32_t Denominator = readIInt32(MemInst, DenPtr);
    EXPECT_EQ(Numerator, Num);
    EXPECT_EQ(Denominator, Den);
  }

  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_channel_layout");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxChannelLayout = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxChannelLayout &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxChannelLayout.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_channel_layout");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetChannelLayout = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetChannelLayout
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetChannelLayout.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_pix_fmt");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxPixFormat = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxPixFormat &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxPixFormat.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_pix_fmt");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetPixFormat = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetPixFormat &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetPixFormat.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_sample_format");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSampleFormat = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSampleFormat &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSampleFormat.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_sample_format");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSampleFormat = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSampleFormat &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSampleFormat.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_sample_rate");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSampleRate = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSampleRate &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSampleRate.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_sample_rate");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSampleRate = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSampleRate &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSampleRate.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_gop_size");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetGopSize = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetGopSize &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetGopSize.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_max_b_frames");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMaxBFrames = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMaxBFrames &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMaxBFrames.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_b_quant_factor");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetBQuantFactor = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetBQuantFactor &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetBQuantFactor.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_b_quant_offset");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetBQuantOffset = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetBQuantOffset &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetBQuantOffset.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_i_quant_factor");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetIQuantFactor = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetIQuantFactor &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetIQuantFactor.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_i_quant_offset");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetIQuantOffset = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetIQuantOffset &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFunc.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_lumi_masking");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetLumiMasking = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetLumiMasking &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetLumiMasking.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_temporal_cplx_masking");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetTemporalCplxMasking = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetTemporalCplxMasking
  //          &>(FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetTemporalCplxMasking.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_spatial_cplx_masking");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSpatialCplxMasking = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSpatialCplxMasking
  //          &>(FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSpatialCplxMasking.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_p_masking");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetPMasking = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetPMasking &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetPMasking.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_dark_masking");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetDarkMasking = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetDarkMasking &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetDarkMasking.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_cmp");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMeCmp = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMeCmp &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMeCmp.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_sub_cmp");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMeSubCmp = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMeSubCmp &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMeSubCmp.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_mb_cmp");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMbCmp = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMbCmp &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMbCmp.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_ildct_cmp");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetIldctCmp = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetIldctCmp &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetIldctCmp.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_dia_size");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetDiaSize = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetDiaSize &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFunc.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_last_predictor_count");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetLastPredictorsCount = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetLastPredictorsCount
  //          &>(FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetLastPredictorsCount.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_pre_cmp");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMePreCmp = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMePreCmp &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMePreCmp.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_pre_dia_size");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetPreDiaSize = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetPreDiaSize &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetPreDiaSize.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_subpel_quality");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMeSubpelQuality = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMeSubpelQuality
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMeSubpelQuality.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_range");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMeRange = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMeRange &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMeRange.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_mb_decision");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMbDecision = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMbDecision &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMbDecision.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_mb_lmin");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMbLMin = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMbLMin &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMbLMin.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_mb_lmax");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetMbLMax = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetMbLMax &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetMbLMax.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_intra_dc_precision");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxIntraDcPrecision = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxIntraDcPrecision
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxIntraDcPrecision.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_intra_dc_precision");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxIntraDcPrecision = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxIntraDcPrecision
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxIntraDcPrecision.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_qmin");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetQMin = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetQMin &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetQMin.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_qmax");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetQMax = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetQMax &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetQMax.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_global_quality");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetGlobalQuality = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetGlobalQuality
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetGlobalQuality.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_colorspace");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetColorspace = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetColorspace &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetColorspace.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_colorspace");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxColorspace = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxColorspace &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxColorspace.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_color_range");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetColorRange = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetColorRange &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetColorRange.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_color_range");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxColorRange = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxColorRange &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxColorRange.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_frame_size");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxFrameSize = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxFrameSize &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxFrameSize.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_bit_rate");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxBitRate = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxBitRate &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxBitRate.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_bit_rate");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetBitRate = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetBitRate &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetBitRate.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_rc_max_rate");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxRcMaxRate = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxRcMaxRate &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxRcMaxRate.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_rc_max_rate");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetRcMaxRate = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetRcMaxRate &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetRcMaxRate.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_bit_rate_tolerance");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetBitRateTolerance = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetBitRateTolerance
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetBitRateTolerance.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_compression_level");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetCompressionLevel = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetCompressionLevel
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetCompressionLevel.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_framerate");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxFrameRate = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxFrameRate &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxFrameRate.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_framerate");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetFrameRate = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetFrameRate &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetFrameRate.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_flags");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetFlags = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetFlags &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetFlags.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_strict_std_compliance");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetStrictStdCompliance = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetStrictStdCompliance
  //          &>(FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetStrictStdCompliance.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_debug");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetDebug = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetDebug &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetDebug.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_codec");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxCodec =
  //      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxCodec
  //      &>(
  //          FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxCodec.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_channels");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxChannels = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxChannels &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxChannels.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_channels");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetChannels = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetChannels &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetChannels.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_loop_filter");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSkipLoopFilter = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSkipLoopFilter
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSkipLoopFilter.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_frame");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSkipFrame = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSkipFrame &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSkipFrame.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_idct");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSkipIdct = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSkipIdct &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSkipIdct.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_error_concealment");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetErrorConcealment = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetErrorConcealment
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFunc.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_err_recognition");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetErrorRecognition = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetErrorRecognition
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetErrorRecognition.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_delay");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxDelay =
  //      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxDelay
  //      &>(
  //          FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxDelay.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_top");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSkipTop = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSkipTop &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSkipTop.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_bottom");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSkipBottom = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSkipBottom &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSkipBottom.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_refs");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxRefs =
  //      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxRefs
  //      &>(
  //          FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxRefs.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_slice_flags");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSliceFlags = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSliceFlags &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSliceFlags.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_slice_count");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetSliceCount = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetSliceCount &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetSliceCount.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_field_order");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetFieldOrder = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetFieldOrder &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetFieldOrder.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_color_trc");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxColorTrc = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxColorTrc &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxColorTrc.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_chroma_sample_location");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxChromaSampleLocation = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxChromaSampleLocation
  //          &>(FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxChromaSampleLocation.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_frame_number");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxFrameNumber = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxFrameNumber &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxFrameNumber.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_block_align");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxBlockAlign = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxBlockAlign &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxBlockAlign.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_request_sample_fmt");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetRequestSampleFmt = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetRequestSampleFmt
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetRequestSampleFmt.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_audio_service_type");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxAudioServiceType = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxAudioServiceType
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxAudioServiceType.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_has_b_frames");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxHasBFrames = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxHasBFrames &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxHasBFrames.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_request_channel_layout");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetRequestChannelLayout = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetRequestChannelLayout
  //          &>(FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetRequestChannelLayout.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_active_thread_type");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxActiveThreadType = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxActiveThreadType
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxActiveThreadType.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_thread_type");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetThreadType = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetThreadType &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetThreadType.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_thread_count");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxThreadCount = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxThreadCount &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxThreadCount.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_thread_count");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxSetThreadCount = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxSetThreadCount &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxSetThreadCount.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVCodecMod->findFuncExports(
  //      "wasmedge_ffmpeg_avcodec_avcodeccontext_color_primaries");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVCodecCtxColorPrimaries = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::AVCodecCtxColorPrimaries &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVCodecCtxColorPrimaries.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //  FuncInst = AVCodecMod->findFuncExports("");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFunc = dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVcodec::&>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFunc.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AVCodecCtxId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
}

} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge
