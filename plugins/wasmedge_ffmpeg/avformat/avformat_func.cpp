#include "avformat_func.h"

extern "C"{
  #include "libavformat/avformat.h"
}

namespace WasmEdge{
namespace Host{
namespace WasmEdgeFFmpeg {
namespace AVFormat {

Expect<int32_t>
AVFormatOpenInput::body(const Runtime::CallingFrame &Frame, uint32_t AvFormatCtxPtr,
                        uint32_t UrlPtr, uint32_t UrlSize,uint32_t AvInputFormatId,uint32_t AvDictionaryId){

  MEMINST_CHECK(MemInst,Frame,0);
  MEM_PTR_CHECK(urlId,MemInst,char,UrlPtr,"Failed when accessing the return URL memory",true);
  MEM_PTR_CHECK(AvFormatCtxId,MemInst,uint32_t,AvFormatCtxPtr,"Failed when accessing the return AVFormatContext Memory",true);

  std::string TargetUrl;
  std::copy_n(urlId,UrlSize,std::back_inserter(TargetUrl));

  AVFormatContext* AvFormatContext = NULL;
  FFMPEG_PTR_FETCH(AvDictionary,AvDictionaryId,AVDictionary*,"AVDictionary in Function AVFormatOpenInput",false);
  FFMPEG_PTR_FETCH(AvInputFormat,AvInputFormatId,AVInputFormat ,"AVInputFormat in Function AVFormatOpenInput",false);

  int Res =  avformat_open_input(&AvFormatContext,TargetUrl.c_str(),AvInputFormat,AvDictionary);
  FFMPEG_PTR_STORE(AvFormatContext,AvFormatCtxId);
  return Res;
}


Expect<int32_t>
AVFormatFindStreamInfo::body(const Runtime::CallingFrame &, uint32_t AvFormatCtxId,uint32_t AvDictionaryId){

  FFMPEG_PTR_FETCH(AvFormatContext,AvFormatCtxId,AVFormatContext ,"AVFormatContext in Function AVFormatFindStreamInfo",true);
  FFMPEG_PTR_FETCH(AvDictionary,AvDictionaryId,AVDictionary*,"AVDictionary",false);
  return avformat_find_stream_info(AvFormatContext,AvDictionary);
}

Expect<void>
AVFormatCloseInput::body(const Runtime::CallingFrame &, uint32_t avFormatCtxId) {
  if(!avFormatCtxId) {

  }

  WasmEdgeFFmpegEnv* ffmpegMemory = Env.get();
  AVFormatContext* avFormatContext =  static_cast<AVFormatContext*>(ffmpegMemory->fetchData(avFormatCtxId));
  avformat_close_input(&avFormatContext);
  ffmpegMemory->dealloc(avFormatCtxId);
  return {};
}

Expect<int32_t>
AVReadPause::body(const Runtime::CallingFrame &,uint32_t AvFormatCtxId) {

    FFMPEG_PTR_FETCH(AvFormatContext,AvFormatCtxId,AVFormatContext ,"AVFormatContext in Function AVReadPause",true);
    return av_read_pause(AvFormatContext);
}

Expect<int32_t>
AVReadPlay::body(const Runtime::CallingFrame &, uint32_t AvFormatCtxId) {

    FFMPEG_PTR_FETCH(AvFormatContext,AvFormatCtxId,AVFormatContext ,"AVFormatContext in Function AVReadPlay",true);
    return av_read_play(AvFormatContext);
}

Expect<int32_t> AVFormatSeekFile::body(const Runtime::CallingFrame &, uint32_t AvFormatCtxId,uint32_t StreamIdx,int64_t MinTs,int64_t Ts,int64_t MaxTs, int32_t Flags){

    FFMPEG_PTR_FETCH(AvFormatContext,AvFormatCtxId,AVFormatContext ,"AVFormatContext in Function AVFormatSeekFile",true);
    return avformat_seek_file(AvFormatContext,StreamIdx,MinTs,Ts,MaxTs,Flags);
}

Expect<void>
AVDumpFormat::body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxId,int32_t idx,uint32_t urlPtr,uint32_t urlSize,int32_t isOutput) {
    std::string targetUrl;

    auto* MemInst = Frame.getMemoryByIndex(0);
    char* buf = MemInst->getPointer<char*>(urlPtr);
    std::copy_n(buf,urlSize,std::back_inserter(targetUrl));
    auto* ffmpegMemory = Env.get();

    if(!avFormatCtxId){
        // Error handling...
    }

    AVFormatContext* avFormatContext = static_cast<AVFormatContext*>(ffmpegMemory->fetchData(avFormatCtxId));
    av_dump_format(avFormatContext,idx,targetUrl.c_str(),isOutput);
    return {};
}

Expect<void>
AVFormatFreeContext::body(const Runtime::CallingFrame &, uint32_t AvFormatCtxId) {

    auto* ffmpegMemory = Env.get();
    AVFormatContext* avFormatCtx = static_cast<AVFormatContext*>(ffmpegMemory->fetchData(AvFormatCtxId));
    avformat_free_context(avFormatCtx);
    ffmpegMemory->dealloc(AvFormatCtxId);
    return {};
}

Expect<int32_t> AVFindBestStream::body(const Runtime::CallingFrame &,uint32_t AvFormatCtxId,int32_t MediaTypeId,int32_t WantedStream,int32_t RelatedStream,uint32_t DecoderRetId,int32_t Flags){

    FFMPEG_PTR_FETCH(AvFormatContext,AvFormatCtxId,AVFormatContext ,"AVFormatContext in Function AVFindBestStream",true);
    FFMPEG_PTR_FETCH(DecoderRet,DecoderRetId,const AVCodec*,"AVCodec in Function AVFindBestStream",false);

    AVMediaType const AvMediaType = FFmpegUtils::MediaType::intoMediaType(MediaTypeId);
    return av_find_best_stream(AvFormatContext, AvMediaType,WantedStream,RelatedStream,DecoderRet,Flags);
}

}
}
}
}
