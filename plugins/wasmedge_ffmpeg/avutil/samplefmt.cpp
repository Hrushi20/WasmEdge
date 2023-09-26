#include "samplefmt.h"
extern "C"{
#include "libavutil/samplefmt.h"
}

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace AVUtil{

Expect<uint32_t> AVGetPlanarSampleFmt::body(const Runtime::CallingFrame &,uint32_t SampleFormatId){
  AVSampleFormat const AvSampleFormat = FFmpegUtils::SampleFmt::fromSampleID(SampleFormatId);
  AVSampleFormat const PlanarSampleFmt = av_get_planar_sample_fmt(AvSampleFormat);
  return FFmpegUtils::SampleFmt::toSampleID(PlanarSampleFmt);
}

Expect<uint32_t> AVGetPackedSampleFmt::body(const Runtime::CallingFrame &,uint32_t SampleFormatId){
  AVSampleFormat const AvSampleFormat = FFmpegUtils::SampleFmt::fromSampleID(SampleFormatId);
  AVSampleFormat const PackedSampleFmt = av_get_packed_sample_fmt(AvSampleFormat);
  return FFmpegUtils::SampleFmt::toSampleID(PackedSampleFmt);
}

Expect<uint32_t> AVSampleFmtIsPlanar::body(const Runtime::CallingFrame &,uint32_t SampleFormatId){
  AVSampleFormat const AvSampleFormat = FFmpegUtils::SampleFmt::fromSampleID(SampleFormatId);
  return av_sample_fmt_is_planar(AvSampleFormat);
}

Expect<int32_t> AVGetBytesPerSample::body(const Runtime::CallingFrame &,uint32_t SampleFormatId){
  AVSampleFormat const AvSampleFormat = FFmpegUtils::SampleFmt::fromSampleID(SampleFormatId);
  return av_get_bytes_per_sample(AvSampleFormat);
}

Expect<int32_t> AVGetSampleFmt::body(const Runtime::CallingFrame &Frame,uint32_t Str, uint32_t StrLen){

  MEMINST_CHECK(MemInst,Frame,0);
  MEM_PTR_CHECK(StrId,MemInst,char,Str,"");

  std::string TargetUrl;
  std::copy_n(StrId,StrLen,std::back_inserter(TargetUrl));

  AVSampleFormat const AvSampleFormat = av_get_sample_fmt(TargetUrl.c_str());
  return FFmpegUtils::SampleFmt::toSampleID(AvSampleFormat);
}

Expect<int32_t> AVSamplesGetBufferSize::body(const Runtime::CallingFrame &,int32_t NbChannels,int32_t NbSamples,uint32_t SampleFormatId,int32_t Align){
  AVSampleFormat const AvSampleFormat = FFmpegUtils::SampleFmt::fromSampleID(SampleFormatId);
  return av_samples_get_buffer_size(NULL,NbChannels,NbSamples,AvSampleFormat,Align); // linesize is NULL in RustSDK.
}

Expect<int32_t> AVSamplesAllocArrayAndSamples::body(const Runtime::CallingFrame &Frame,uint32_t BufferPtr,int32_t LinesizeValue,int32_t NbChannels,int32_t NbSamples,uint32_t SampleFmtId,int32_t Align){
  MEMINST_CHECK(MemInst,Frame,0);
  MEM_PTR_CHECK(BufId,MemInst,uint32_t,BufferPtr,"");

  FFMPEG_PTR_FETCH(Buf,*BufId,uint8_t*);
  int Linesize = LinesizeValue;
  AVSampleFormat const AvSampleFormat = FFmpegUtils::SampleFmt::fromSampleID(SampleFmtId);
  int Res = av_samples_alloc_array_and_samples(&Buf,&Linesize,NbChannels,NbSamples,AvSampleFormat,Align);
  FFMPEG_PTR_STORE(Buf,BufId);
  return Res;
}

//Expect<int32_t> AVSamplesCopy::body(const Runtime::CallingFrame &Frame,uint32_t DestBufPtr,uint32_t SrcBufId,int32_t DestOffset,int32_t SrcOffset,int32_t NbSamples,int32_t NbChannels,uint32_t SampleFmtId){
//  printf("Inside AVSample");
//  MEMINST_CHECK(MemInst,Frame,0);
//  MEM_PTR_CHECK(DestBufId,MemInst,uint32_t,DestBufPtr,"");
//
////  FFMPEG_PTR_FETCH(DestBuf,*DestBufId,uint8_t);
//  uint8_t* DestBuf = NULL;
//  FFMPEG_PTR_FETCH(SrcBuf,SrcBufId,uint8_t);
//  AVSampleFormat const AvSampleFormat = FFmpegUtils::SampleFmt::fromSampleID(SampleFmtId);
//  printf("I am here");
//  int Res = av_samples_copy(&DestBuf,&SrcBuf,DestOffset,SrcOffset,NbSamples,NbChannels,AvSampleFormat);
//  FFMPEG_PTR_STORE(DestBuf,DestBufId);
//  return Res;
//}

Expect<int32_t> AVSamplesGetBuffer::body(const Runtime::CallingFrame &Frame,uint32_t BufferID,uint32_t BufferPtr,uint32_t BufferSize){

  MEMINST_CHECK(MemInst,Frame,0)
  MEM_SPAN_CHECK(Buffer,MemInst,uint8_t,BufferPtr,BufferSize,"");
  FFMPEG_PTR_FETCH(Buf,BufferID,uint8_t);

  memmove(Buffer.data(),Buf,BufferSize);
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<int32_t> AVFreep::body(const Runtime::CallingFrame &,uint32_t BufferId){
  FFMPEG_PTR_FETCH(Buffer,BufferId,uint8_t*);
  av_freep(Buffer);
  FFMPEG_PTR_DELETE(BufferId);
  return static_cast<int32_t>(ErrNo::Success);
}

} // namespace AVUtil
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge