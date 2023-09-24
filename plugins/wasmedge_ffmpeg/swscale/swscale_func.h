#pragma once

#include "swscale_base.h"
#include "runtime/callingframe.h"

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace SWScale{

class SwsGetContext : public WasmEdgeFFmpegSWScale<SwsGetContext> {
public:
  SwsGetContext(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsCtxPtr,uint32_t SrcW,uint32_t SrcH,uint32_t SrcAvPixFormatId,uint32_t DesW,uint32_t DesH,uint32_t DesAvPixFormatId,int32_t Flags,uint32_t SrcFilterId, uint32_t DesFilterId);
};

class SwsFreeContext : public WasmEdgeFFmpegSWScale<SwsFreeContext> {
public:
  SwsFreeContext(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsCtxId);
};

class SwsScale : public WasmEdgeFFmpegSWScale<SwsScale> {
public:
  SwsScale(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsCtxId,uint32_t InputFrameId,int32_t SrcSliceY,int32_t SrcSliceH,uint32_t OutputFrameId);
};

class SwsGetCachedContext : public WasmEdgeFFmpegSWScale<SwsGetCachedContext> {
public:
  SwsGetCachedContext(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsCachedCtxPtr,uint32_t SwsCtxPtr,uint32_t SrcW,uint32_t SrcH,uint32_t SrcAvPixFormatId,uint32_t DesW,uint32_t DesH,uint32_t DesAvPixFormatId,int32_t Flags,uint32_t SrcFilterId, uint32_t DesFilterId);
};

class SwsIsSupportedInput : public WasmEdgeFFmpegSWScale<SwsIsSupportedInput> {
public:
  SwsIsSupportedInput(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t AvPixFormatId);
};

class SwsIsSupportedOutput : public WasmEdgeFFmpegSWScale<SwsIsSupportedOutput> {
public:
  SwsIsSupportedOutput(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t AvPixFormatId);
};

class SwsIsSupportedEndiannessConversion  : public WasmEdgeFFmpegSWScale<SwsIsSupportedEndiannessConversion> {
public:
  SwsIsSupportedEndiannessConversion(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t AvPixFormatId);
};

class SwsGetDefaultFilter  : public WasmEdgeFFmpegSWScale<SwsGetDefaultFilter> {
public:
  SwsGetDefaultFilter(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsFilterPtr,float LumaGBlur,float ChromaGBlur,float LumaSharpen,float ChromaSharpen,float ChromaHShift,float ChromaVShift,int32_t Verbose);
};

class SwsFreeFilter  : public WasmEdgeFFmpegSWScale<SwsFreeFilter> {
public:
  SwsFreeFilter(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsFilterId);
};

class SwsAllocVec : public WasmEdgeFFmpegSWScale<SwsAllocVec> {
public:
  SwsAllocVec(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsVectorPtr,int32_t Length);
};

class SwsGetGaussianVec : public WasmEdgeFFmpegSWScale<SwsGetGaussianVec> {
public:
  SwsGetGaussianVec(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsVectorPtr,double Variance,double Quality);
};

class SwsScaleVec : public WasmEdgeFFmpegSWScale<SwsScaleVec> {
public:
  SwsScaleVec(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsVectorId,double Scalar);
};

class SwsNormalizeVec : public WasmEdgeFFmpegSWScale<SwsNormalizeVec> {
public:
  SwsNormalizeVec(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsVectorId,double Height);
};

class SwsFreeVec : public WasmEdgeFFmpegSWScale<SwsFreeVec> {
public:
  SwsFreeVec(std::shared_ptr<WasmEdgeFFmpegEnv> HostEnv)
      : WasmEdgeFFmpegSWScale(HostEnv) {}
  Expect<int32_t> body(const Runtime::CallingFrame &Frame,uint32_t SwsVectorId);
};

} // namespace SWScale
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge
