#include "avformatContext.h"

extern "C" {
    #include "libavformat/avformat.h"
}

namespace WasmEdge{
namespace Host{
namespace WasmEdgeFFmpeg {
namespace AVFormat {


Expect<int32_t> AVFormatCtxIFormat::body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxPtr,uint32_t avInputFormatPtr){

    MEMINST_CHECK(MemInst,Frame,0);
    MEM_PTR_CHECK(avFormatCtxId,MemInst,uint32_t,avFormatCtxPtr,"Failed when accessing the return AVFormatContext Memory",true);
    MEM_PTR_CHECK(avInputFormatId,MemInst,uint32_t,avInputFormatPtr,"Failed when accessing the return AVInputFormat Memory",true);

    auto ffmpegMemory = Env.get();

    AVFormatContext* avFormatCtx = static_cast<AVFormatContext *>(ffmpegMemory->fetchData(*avFormatCtxId));

    const AVInputFormat* avInputFormat = avFormatCtx->iformat;
    ffmpegMemory->alloc(const_cast<AVInputFormat*>(avInputFormat),avInputFormatId);

    // Think of strategy to return value.
    return 0;
}

Expect<int32_t> AVFormatCtxProbeScore::body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxPtr){

    MEMINST_CHECK(MemInst,Frame,0);
    MEM_PTR_CHECK(avFormatCtxId,MemInst,uint32_t,avFormatCtxPtr,"Failed when accessing the return AVFormatContext Memory",true);

    auto ffmpegMemory = Env.get();
    AVFormatContext* avFormatCtx = static_cast<AVFormatContext *>(ffmpegMemory->fetchData(*avFormatCtxId));
    int res = avFormatCtx->probe_score;

    return res;
}


Expect<uint32_t> AVFormatCtxNbStreams::body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxPtr){
    MEMINST_CHECK(MemInst,Frame,0);
    MEM_PTR_CHECK(avFormatCtxId,MemInst,uint32_t,avFormatCtxPtr,"Failed when accessing the return AVFormatContext Memory",true);

    auto ffmpegMemory = Env.get();
    AVFormatContext* avFormatCtx = static_cast<AVFormatContext *>(ffmpegMemory->fetchData(*avFormatCtxId));
    return avFormatCtx->nb_streams;
};


Expect<int64_t> AVFormatCtxBitRate::body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxPtr){
    MEMINST_CHECK(MemInst,Frame,0);
    MEM_PTR_CHECK(avFormatCtxId,MemInst,uint32_t,avFormatCtxPtr,"Failed when accessing the return AVFormatContext Memory",true);

    auto ffmpegMemory = Env.get();
    AVFormatContext* avFormatCtx = static_cast<AVFormatContext *>(ffmpegMemory->fetchData(*avFormatCtxId));
    return avFormatCtx->bit_rate;
}

Expect<int64_t> AVFormatCtxDuration::body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxPtr){
    MEMINST_CHECK(MemInst,Frame,0);
    MEM_PTR_CHECK(avFormatCtxId,MemInst,uint32_t,avFormatCtxPtr,"Failed when accessing the return AVFormatContext Memory",true);

    auto ffmpegMemory = Env.get();
    AVFormatContext* avFormatCtx = static_cast<AVFormatContext *>(ffmpegMemory->fetchData(*avFormatCtxId));
    return avFormatCtx->duration;
}

Expect<uint32_t> AVFormatCtxNbChapters::body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxPtr){

    MEMINST_CHECK(MemInst,Frame,0);
    MEM_PTR_CHECK(avFormatCtxId,MemInst,uint32_t,avFormatCtxPtr,"Failed when accessing the return AVFormatContext Memory",true);

    auto ffmpegMemory = Env.get();
    AVFormatContext* avFormatCtx = static_cast<AVFormatContext *>(ffmpegMemory->fetchData(*avFormatCtxId));
    return avFormatCtx->nb_chapters;
}
Expect<void> AVFormatCtxGetAVStream::body(const Runtime::CallingFrame &Frame, uint32_t avFormatCtxPtr,uint32_t avStreamPtr){

    auto* MemInst = Frame.getMemoryByIndex(0);

    uint32_t* avFormatCtxIdx = MemInst->getPointerOrNull<uint32_t*>(avFormatCtxPtr);
    uint32_t* avStreamIdx = MemInst->getPointerOrNull<uint32_t*>(avStreamPtr);

    if(avFormatCtxIdx == nullptr){
      // Error Management
    }

    auto ffmpegMemory = Env.get();
    AVFormatContext* avFormatCtx = static_cast<AVFormatContext *>(ffmpegMemory->fetchData(*avFormatCtxIdx));

    AVStream** streams = avFormatCtx->streams;
    ffmpegMemory->alloc(streams,avStreamIdx);
    return {};
}

}
}
}
}

