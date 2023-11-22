#include "avfilter//avfilter_func.h"
#include "../utils.h"
#include "avfilter/avFilter.h"
#include "avfilter/module.h"

#include <gtest/gtest.h>

using WasmEdge::Host::WasmEdgeFFmpeg::ErrNo;

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {

TEST_F(FFmpegTest, AVFilterFunc) {

  ASSERT_TRUE(AVFilterMod != nullptr);

  uint32_t FilterGraphPtr = UINT32_C(4);
  uint32_t FilterPtr = UINT32_C(8);
  uint32_t Filter2Ptr = UINT32_C(12);
  uint32_t FilterCtxPtr = UINT32_C(16);
  uint32_t Filter2CtxPtr = UINT32_C(20);
  uint32_t OutputFilterCtxPtr =
      UINT32_C(24);                          // Used with AVFilterGraphGetFilter
  uint32_t InputFilterCtxPtr = UINT32_C(28); // Used with AVFilterGraphGetFilter
  uint32_t InputInoutPtr = UINT32_C(32);
  uint32_t OutputInoutPtr = UINT32_C(36);
  uint32_t InputNamePtr = UINT32_C(100);
  uint32_t OutputNamePtr = UINT32_C(150);
  uint32_t InputFilterNamePtr = UINT32_C(200);
  uint32_t OutputFilterNamePtr = UINT32_C(250);
  uint32_t ArgsPtr = UINT32_C(300);
  uint32_t SpecPtr = UINT32_C(450);
  uint32_t StrPtr = UINT32_C(500);

  std::string InputName = std::string("abuffer");
  fillMemContent(MemInst, InputNamePtr, InputName);

  std::string OutputName = std::string("abuffersink");
  fillMemContent(MemInst, OutputNamePtr, OutputName);

  std::string InputFilterName = std::string("in");
  fillMemContent(MemInst, InputFilterNamePtr, InputFilterName);

  std::string OutputFilterName = std::string("out");
  fillMemContent(MemInst, OutputFilterNamePtr, OutputFilterName);

  std::string Args = std::string(
      "time_base=1/44100:sample_rate=44100:sample_fmt=fltp:channel_layout=0x3");
  fillMemContent(MemInst, ArgsPtr, Args);

  std::string SpecStr = std::string("anull");
  fillMemContent(MemInst, SpecPtr, SpecStr);

  auto *FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_graph_alloc");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGraphAlloc = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGraphAlloc &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterGraphAlloc.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{FilterGraphPtr},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  uint32_t FilterGraphId = readUInt32(MemInst, FilterGraphPtr);
  ASSERT_TRUE(FilterGraphId > 0);

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_get_by_name");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGetByName = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGetByName &>(
      FuncInst->getHostFunc());

  {
    int32_t Length = InputName.length();
    EXPECT_TRUE(HostFuncAVFilterGetByName.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{FilterPtr, InputNamePtr,
                                                    Length},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    Length = OutputName.length();
    EXPECT_TRUE(HostFuncAVFilterGetByName.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{Filter2Ptr, OutputNamePtr,
                                                    Length},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  uint32_t FilterId = readUInt32(MemInst, FilterPtr);
  uint32_t Filter2Id = readUInt32(MemInst, Filter2Ptr);
  ASSERT_TRUE(FilterId > 0);
  ASSERT_TRUE(Filter2Id > 0);

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_graph_create_filter");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGraphCreateFilter = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGraphCreateFilter &>(
      FuncInst->getHostFunc());

  {
    int32_t NameLen = InputFilterName.length();
    int32_t ArgsLen = Args.length();
    EXPECT_TRUE(HostFuncAVFilterGraphCreateFilter.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            FilterCtxPtr, FilterId, InputFilterNamePtr, NameLen, ArgsPtr,
            ArgsLen, FilterGraphId},
        Result));
    ASSERT_TRUE(Result[0].get<int32_t>() >= 0);

    NameLen = OutputFilterName.length();
    EXPECT_TRUE(HostFuncAVFilterGraphCreateFilter.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            Filter2CtxPtr, Filter2Id, OutputFilterNamePtr, NameLen, 0, 0,
            FilterGraphId},
        Result));
    ASSERT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  uint32_t FilterCtxId = readUInt32(MemInst, FilterCtxPtr);
  ASSERT_TRUE(FilterCtxId > 0);

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_inout_alloc");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterInoutAlloc = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterInoutAlloc &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterInoutAlloc.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{InputInoutPtr},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    EXPECT_TRUE(HostFuncAVFilterInoutAlloc.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{OutputInoutPtr},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  uint32_t InputInoutId = readUInt32(MemInst, InputInoutPtr);
  ASSERT_TRUE(InputInoutId > 0);

  uint32_t OutputInoutId = readUInt32(MemInst, OutputInoutPtr);
  ASSERT_TRUE(OutputInoutId > 0);

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_graph_get_filter");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGraphGetFilter = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGraphGetFilter &>(
      FuncInst->getHostFunc());

  {
    int32_t Length = OutputFilterName.length();
    EXPECT_TRUE(HostFuncAVFilterGraphGetFilter.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            OutputFilterCtxPtr, FilterGraphId, OutputFilterNamePtr, Length},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    Length = InputFilterName.length();
    EXPECT_TRUE(HostFuncAVFilterGraphGetFilter.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            InputFilterCtxPtr, FilterGraphId, InputFilterNamePtr, Length},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  uint32_t OutputFilterCtxId = readUInt32(MemInst, OutputFilterCtxPtr);
  ASSERT_TRUE(OutputFilterCtxId > 0);

  uint32_t InputFilterCtxId = readUInt32(MemInst, InputFilterCtxPtr);
  ASSERT_TRUE(InputFilterCtxId > 0);

  // ==================================================================
  //                  Setting InoutId Values for Filtering
  // ==================================================================

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_inout_set_name");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterInoutSetName = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterInoutSetName &>(
      FuncInst->getHostFunc());

  {
    int32_t Length = InputFilterName.length();
    EXPECT_TRUE(HostFuncAVFilterInoutSetName.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{OutputInoutId,
                                                    InputFilterNamePtr, Length},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    Length = OutputFilterName.length();
    EXPECT_TRUE(HostFuncAVFilterInoutSetName.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            InputInoutId, OutputFilterNamePtr, Length},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_inout_set_filter_ctx");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterInoutSetFilterCtx = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterInoutSetFilterCtx &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterInoutSetFilterCtx.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{OutputInoutId,
                                                    InputFilterCtxId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    EXPECT_TRUE(HostFuncAVFilterInoutSetFilterCtx.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{InputInoutId,
                                                    OutputFilterCtxId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_inout_set_pad_idx");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterInoutSetPadIdx = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterInoutSetPadIdx &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterInoutSetPadIdx.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{OutputInoutId, 0}, Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    EXPECT_TRUE(HostFuncAVFilterInoutSetPadIdx.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{InputInoutId, 0},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_inout_set_next");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterInoutSetNext = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterInoutSetNext &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterInoutSetNext.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{OutputInoutId, 0}, Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    EXPECT_TRUE(HostFuncAVFilterInoutSetNext.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{InputInoutId, 0},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  // ==================================================================
  //                  End Setting InoutId Values for Filtering
  // ==================================================================

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_graph_parse_ptr");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGraphParsePtr = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGraphParsePtr &>(
      FuncInst->getHostFunc());

  {
    int32_t Length = SpecStr.length();
    EXPECT_TRUE(HostFuncAVFilterGraphParsePtr.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            FilterGraphId, SpecPtr, Length, InputInoutId, OutputInoutId},
        Result));
    ASSERT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_graph_config");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGraphConfig = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGraphConfig &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterGraphConfig.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{FilterGraphId},
        Result));
    ASSERT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_graph_dump_length");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGraphDumpLength = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGraphDumpLength &>(
      FuncInst->getHostFunc());

  int32_t GraphStrLen;
  {
    EXPECT_TRUE(HostFuncAVFilterGraphDumpLength.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{FilterGraphId},
        Result));
    GraphStrLen = Result[0].get<int32_t>();
    ASSERT_TRUE(GraphStrLen > 0);
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_graph_dump");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGraphDump = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGraphDump &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterGraphDump.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{FilterGraphId, StrPtr,
                                                    GraphStrLen},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  // Crashing the program. Checked even from Rust side.
  //  FuncInst = AVFilterMod->findFuncExports(
  //      "wasmedge_ffmpeg_avfilter_avfilter_inout_free");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVFilterInOutFree = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterInOutFree &>(
  //      FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVFilterInOutFree.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{InputInoutId}, Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //
  //    EXPECT_TRUE(HostFuncAVFilterInOutFree.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{OutputInoutId},
  //        Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }

  FuncInst =
      AVFilterMod->findFuncExports("wasmedge_ffmpeg_avfilter_avfilter_version");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterVersion =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterVersion &>(
          FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterVersion.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{}, Result));
    ASSERT_TRUE(Result[0].get<int32_t>() > 0);
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_configuration_length");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterConfigurationLength = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterConfigurationLength &>(
      FuncInst->getHostFunc());

  int32_t Length;
  {
    EXPECT_TRUE(HostFuncAVFilterConfigurationLength.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{}, Result));
    Length = Result[0].get<int32_t>();
    ASSERT_TRUE(Length > 0);
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_configuration");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterConfiguration = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterConfiguration &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterConfiguration.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{StrPtr, Length},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_license_length");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterLicenseLength = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterLicenseLength &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterLicenseLength.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{}, Result));
    Length = Result[0].get<int32_t>();
    ASSERT_TRUE(Length > 0);
  }

  FuncInst =
      AVFilterMod->findFuncExports("wasmedge_ffmpeg_avfilter_avfilter_license");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterLicense =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterLicense &>(
          FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterLicense.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{StrPtr, Length},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }
  //  FuncInst = AVFilterMod->findFuncExports(
  //      "wasmedge_ffmpeg_avfilter_avfilter_pad_get_name_length");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVFilterPadGetNameLength = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterPadGetNameLength
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVFilterPadGetNameLength.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{FilterGraphId},
  //        Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVFilterMod->findFuncExports(
  //      "wasmedge_ffmpeg_avfilter_avfilter_pad_get_name");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVFilterPadGetName = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterPadGetName
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVFilterPadGetName.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{FilterGraphId},
  //        Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }
  //
  //  FuncInst = AVFilterMod->findFuncExports(
  //      "wasmedge_ffmpeg_avfilter_avfilter_pad_get_type");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVFilterPadGetType = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterPadGetType
  //      &>( FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVFilterPadGetType.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{FilterGraphId},
  //        Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }

  //  FuncInst = AVFilterMod->findFuncExports(
  //      "wasmedge_ffmpeg_avfilter_avfilter_pad_drop");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //
  //  auto &HostFuncAVFilterPadDrop =
  //      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterPadDrop
  //      &>(
  //          FuncInst->getHostFunc());
  //
  //  {
  //    EXPECT_TRUE(HostFuncAVFilterPadDrop.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{FilterGraphId},
  //        Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_free_graph_str");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterFreeGraphStr = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterFreeGraphStr &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterFreeGraphStr.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{FilterGraphId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst =
      AVFilterMod->findFuncExports("wasmedge_ffmpeg_avfilter_avfilter_drop");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterDrop =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterDrop &>(
          FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterDrop.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{FilterId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_context_drop");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterContextDrop = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterContextDrop &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterContextDrop.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{InputFilterCtxId}, Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));

    EXPECT_TRUE(HostFuncAVFilterContextDrop.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{OutputFilterCtxId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVFilterMod->findFuncExports(
      "wasmedge_ffmpeg_avfilter_avfilter_graph_free");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());

  auto &HostFuncAVFilterGraphFree = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFilter::AVFilterGraphFree &>(
      FuncInst->getHostFunc());

  {
    EXPECT_TRUE(HostFuncAVFilterGraphFree.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{FilterGraphId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }
}

} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge