#include "avformat/avformat_func.h"
#include "../utils.h"
#include "avformat/module.h"

#include <gtest/gtest.h>

using WasmEdge::Host::WasmEdgeFFmpeg::ErrNo;

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {

// Testing all AVFormat_funcs.
TEST_F(FFmpegTest, AVInputFormatFunc) {

  uint32_t FormatCtxPtr = UINT32_C(4);
  uint32_t DictPtr = UINT32_C(16);
  uint32_t KeyPtr = UINT32_C(100);
  uint32_t ValuePtr = UINT32_C(200);

  initDict(DictPtr, KeyPtr, std::string("Key"), ValuePtr, std::string("Value"));
  uint32_t DictId = readUInt32(MemInst, DictPtr);

  uint32_t UrlStart = 300;
  uint32_t UrlSize = 30;
  fillMemContent(MemInst, UrlStart, UrlSize);
  fillMemContent(MemInst, UrlStart,
                 std::string("ffmpeg-assets/sample_video.mp4"));

  auto *FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_avformat_open_input");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatOpenInput = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatOpenInput &>(
      FuncInst->getHostFunc());

  {
    // AVDict only
    EXPECT_TRUE(HostFuncAVFormatOpenInput.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            FormatCtxPtr, UrlStart, UrlSize, UINT32_C(0), DictId},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
    EXPECT_TRUE(readUInt32(MemInst, FormatCtxPtr) > 0);

    // No AVDict, No AVInputFormat
    EXPECT_TRUE(HostFuncAVFormatOpenInput.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            FormatCtxPtr, UrlStart, UrlSize, UINT32_C(0), UINT32_C(0)},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
    EXPECT_TRUE(readUInt32(MemInst, FormatCtxPtr) > 0);

    // AVInputFormat is same as AvFormatCtx
    //    uint32_t AvInputFormatCtxId = readUInt32(MemInst, AvFormatCtxPtr);
    //    EXPECT_TRUE(HostFuncAVFormatOpenInput.run(
    //        CallFrame,
    //        std::initializer_list<WasmEdge::ValVariant>{
    //            AvFormatCtxPtr, UrlStart, UrlSize, AvInputFormatCtxId,
    //            UINT32_C(0)},
    //        Result));
    //    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
    //    EXPECT_TRUE(readUInt32(MemInst, AvFormatCtxPtr) > 0);

    // AVInputFormat && AVDictionary
    //    EXPECT_TRUE(HostFuncAVFormatOpenInput.run(
    //        CallFrame,
    //        std::initializer_list<WasmEdge::ValVariant>{
    //        AvFormatCtxPtr, INT32_C(1), UINT32_C(30), UINT32_C(0),
    //        UINT32_C(0)}, Result));
    //    EXPECT_EQ(Result[0].get<int32_t>() >= 0);
    //    EXPECT_TRUE(readUInt32(MemInst, AvFormatCtxPtr) > 0);
  }

  FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_avformat_find_stream_info");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatFindStreamInfo = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatFindStreamInfo &>(
      FuncInst->getHostFunc());

  {
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(HostFuncAVFormatFindStreamInfo.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId, UINT32_C(0)},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);

    // AVDictionaryID
    //    EXPECT_TRUE(HostFuncAVFormatFindStreamInfo.run(
    //        CallFrame,
    //        std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId,
    //        AVDictId}, Result));
    //    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  FuncInst =
      AVFormatMod->findFuncExports("wasmedge_ffmpeg_avformat_av_read_play");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatAVReadPlay =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVReadPlay &>(
          FuncInst->getHostFunc());

  {
    // Try a network Fetch.
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(HostFuncAVFormatAVReadPlay.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), -78);
  }

  FuncInst =
      AVFormatMod->findFuncExports("wasmedge_ffmpeg_avformat_av_read_pause");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatAVReadPause =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVReadPause &>(
          FuncInst->getHostFunc());
  {
    // Try a network Fetch.
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(HostFuncAVFormatAVReadPause.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), -78);
  }

  FuncInst =
      AVFormatMod->findFuncExports("wasmedge_ffmpeg_avformat_av_dump_format");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatAVDumpFormat =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVDumpFormat &>(
          FuncInst->getHostFunc());
  {
    // Try a network Fetch.
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(HostFuncAVFormatAVDumpFormat.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            AvFormatCtxId, 0, UINT32_C(100), UINT32_C(30), 0},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), 0);
  }

  //  FuncInst = AVFormatMod->findFuncExports(
  //      "wasmedge_ffmpeg_avformat_avformat_seek_file");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //  auto &HostFuncAVFormatSeekFile = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatSeekFile &>(
  //      FuncInst->getHostFunc());
  //  {
  //    // Try a network Fetch.
  //    uint32_t AvFormatCtxId = readUInt32(MemInst, AvFormatCtxPtr);
  //    EXPECT_TRUE(HostFuncAVFormatSeekFile.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{
  //            AvFormatCtxId, -1, INT64_C(-10), 0, INT64_C(10), 0},
  //        Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(), 0);
  //  }

  FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_av_find_best_stream");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFindBestStream = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFindBestStream &>(
      FuncInst->getHostFunc());
  {
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(HostFuncAVFindBestStream.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            AvFormatCtxId, UINT32_C(0), INT32_C(-1), INT32_C(-1), 0, 0},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  //  FuncInst = AVFormatMod->findFuncExports(
  //      "wasmedge_ffmpeg_avformat_avformat_write_header");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //  auto &HostFuncAVFormatWriteHeader = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatWriteHeader &>(
  //      FuncInst->getHostFunc());
  //  {
  //    uint32_t AvFormatCtxId = readUInt32(MemInst, AvFormatCtxPtr);
  //    EXPECT_TRUE(HostFuncAVFormatWriteHeader.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId,
  //        UINT32_C(0)}, Result));
  //    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  //  }

  //  FuncInst =
  //      AVFormatMod->findFuncExports("wasmedge_ffmpeg_avformat_av_read_frame");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //  auto &HostFuncAVReadFrame =
  //      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVReadFrame &>(
  //          FuncInst->getHostFunc());
  //  {
  //    uint32_t AvFormatCtxId = readUInt32(MemInst, AvFormatCtxPtr);
  //    EXPECT_TRUE(HostFuncAVReadFrame.run(
  //        CallFrame, std::initializer_list<WasmEdge::ValVariant>{}, Result));
  //    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  //  }
  FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_avformat_close_input");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatCloseInput = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatCloseInput &>(
      FuncInst->getHostFunc());
  {
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(HostFuncAVFormatCloseInput.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_avformat_free_context");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFreeContext = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatFreeContext &>(
      FuncInst->getHostFunc());
  {
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(HostFuncAVFreeContext.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_avformat_network_init");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatNetworkInit = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatNetworkInit &>(
      FuncInst->getHostFunc());
  {
    EXPECT_TRUE(HostFuncAVFormatNetworkInit.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{}, Result));

    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_avformat_network_deinit");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatNetworkDeInit = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatNetworkDeInit &>(
      FuncInst->getHostFunc());
  {
    EXPECT_TRUE(HostFuncAVFormatNetworkDeInit.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{}, Result));

    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }

  FuncInst =
      AVFormatMod->findFuncExports("wasmedge_ffmpeg_avformat_avformat_version");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatVersion =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatVersion &>(
          FuncInst->getHostFunc());
  {
    EXPECT_TRUE(HostFuncAVFormatVersion.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{}, Result));

    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  }
}

TEST_F(FFmpegTest, AVOutputFormatFunc) {

  uint32_t FormatCtxPtr = UINT32_C(4);
  uint32_t DictPtr = UINT32_C(16);
  uint32_t ChapterPtr = uint32_t(20);
  uint32_t KeyPtr = UINT32_C(100);
  uint32_t ValuePtr = UINT32_C(200);

  initDict(DictPtr, KeyPtr, std::string("Key"), ValuePtr, std::string("Value"));
  uint32_t DictId = readUInt32(MemInst, DictPtr);

  uint32_t FormatStart = 300;
  uint32_t FormatLen = 3;
  uint32_t FileStart = 350;
  uint32_t FileLen = 8;
  fillMemContent(MemInst, FormatStart, FormatLen + FileLen);

  fillMemContent(MemInst, FormatStart, std::string("mp4"));
  fillMemContent(MemInst, FileStart, std::string("test.mp4"));

  auto *FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_avformat_alloc_output_context2");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatAllocOutputContext2 = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFormatAllocOutputContext2 &>(
      FuncInst->getHostFunc());
  {
    EXPECT_TRUE(HostFuncAVFormatAllocOutputContext2.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            FormatCtxPtr, 0, FormatStart, FormatLen, FileStart, FileLen},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);

    EXPECT_TRUE(HostFuncAVFormatAllocOutputContext2.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{
            FormatCtxPtr, readUInt32(MemInst, FormatCtxPtr), FormatStart,
            FormatLen, FileStart, FileLen},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);

    EXPECT_TRUE(HostFuncAVFormatAllocOutputContext2.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{FormatCtxPtr, 0, 0, 0,
                                                    FileStart, FileLen},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  FuncInst = AVFormatMod->findFuncExports("wasmedge_ffmpeg_avformat_avio_open");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVIOOpen =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVIOOpen &>(
          FuncInst->getHostFunc());
  {
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(
        HostFuncAVIOOpen.run(CallFrame,
                             std::initializer_list<WasmEdge::ValVariant>{
                                 AvFormatCtxId, FileStart, FileLen, 2},
                             Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  FuncInst =
      AVFormatMod->findFuncExports("wasmedge_ffmpeg_avformat_avio_open2");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVIOOpen2 =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVIOOpen2 &>(
          FuncInst->getHostFunc());

  {
    uint32_t AvFormatCtxId = readUInt32(MemInst, FormatCtxPtr);
    EXPECT_TRUE(HostFuncAVIOOpen2.run(
        CallFrame,
        std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId, FileStart,
                                                    FileLen, 2, 0, DictId},
        Result));
    EXPECT_TRUE(Result[0].get<int32_t>() >= 0);
  }

  FuncInst = AVFormatMod->findFuncExports(
      "wasmedge_ffmpeg_avformat_avchapter_mallocz");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVIOClose = dynamic_cast<
      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVChapterMallocz &>(
      FuncInst->getHostFunc());
  {
    EXPECT_TRUE(HostFuncAVIOClose.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{ChapterPtr},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }
  // How to pass IntPtr
  //
  //  FuncInst = AVFormatMod->findFuncExports(
  //      "wasmedge_ffmpeg_avformat_avchapter_dynarray_add");
  //  EXPECT_NE(FuncInst, nullptr);
  //  EXPECT_TRUE(FuncInst->isHostFunction());
  //  auto &HostFuncAVChapterDynarrayAdd = dynamic_cast<
  //      WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVChapterDynarrayAdd &>(
  //      FuncInst->getHostFunc());
  //  // For the give input file, nb_chapter is 0;
  //  {
  //    uint32_t AvChapterId = readUInt32(MemInst, AvFormatCtxPtr);
  //    uint32_t AvFormatCtxId = readUInt32(MemInst, AvFormatCtxPtr);
  //    EXPECT_TRUE(HostFuncAVChapterDynarrayAdd.run(
  //        CallFrame,
  //        std::initializer_list<WasmEdge::ValVariant>{AvFormatCtxId,
  //        UINT32_C(0),
  //                                                    AvChapterId},
  //        Result));
  //    EXPECT_EQ(Result[0].get<int32_t>(),
  //    static_cast<int32_t>(ErrNo::Success));
  //  }

  FuncInst =
      AVFormatMod->findFuncExports("wasmedge_ffmpeg_avformat_avformat_avfreep");
  EXPECT_NE(FuncInst, nullptr);
  EXPECT_TRUE(FuncInst->isHostFunction());
  auto &HostFuncAVFormatAVFreep =
      dynamic_cast<WasmEdge::Host::WasmEdgeFFmpeg::AVFormat::AVFreeP &>(
          FuncInst->getHostFunc());

  {
    uint32_t ChapterId = readUInt32(MemInst, ChapterPtr);
    EXPECT_TRUE(HostFuncAVFormatAVFreep.run(
        CallFrame, std::initializer_list<WasmEdge::ValVariant>{ChapterId},
        Result));
    EXPECT_EQ(Result[0].get<int32_t>(), static_cast<int32_t>(ErrNo::Success));
  }
}

} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge