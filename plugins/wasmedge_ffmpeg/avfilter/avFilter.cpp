#include "avFilter.h"

extern "C" {
#include "libavfilter/avfilter.h"
}

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace AVFilter {

Expect<int32_t> AVFilterNameLength::body(const Runtime::CallingFrame &,
                                         uint32_t FilterId) {
  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  return strlen(Filter->name);
}

Expect<int32_t> AVFilterName::body(const Runtime::CallingFrame &Frame,
                                   uint32_t FilterId, uint32_t NamePtr,
                                   uint32_t NameLen) {

  MEMINST_CHECK(MemInst, Frame, 0);
  MEM_SPAN_CHECK(NameBuf, MemInst, char, NamePtr, NameLen, "");

  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  const char *Name = Filter->name;
  memmove(NameBuf.data(), Name, NameLen);
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<int32_t> AVFilterDescriptionLength::body(const Runtime::CallingFrame &,
                                                uint32_t FilterId) {
  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  return strlen(Filter->description);
}

Expect<int32_t> AVFilterDescription::body(const Runtime::CallingFrame &Frame,
                                          uint32_t FilterId, uint32_t DescPtr,
                                          uint32_t DescLen) {

  MEMINST_CHECK(MemInst, Frame, 0);
  MEM_SPAN_CHECK(DescBuf, MemInst, char, DescPtr, DescLen, "");

  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  const char *Desc = Filter->description;
  memmove(DescBuf.data(), Desc, DescLen);
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<uint32_t> AVFilterNbInputs::body(const Runtime::CallingFrame &,
                                        uint32_t FilterId) {
  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  return Filter->nb_inputs;
}

Expect<uint32_t> AVFilterNbOutputs::body(const Runtime::CallingFrame &,
                                         uint32_t FilterId) {
  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  return Filter->nb_outputs;
}

Expect<int32_t> AVFilterFlags::body(const Runtime::CallingFrame &,
                                    uint32_t FilterId) {

  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  return Filter->flags;
}

Expect<int32_t> AVFilterInoutSetName::body(const Runtime::CallingFrame &Frame,
                                           uint32_t InoutId, uint32_t NamePtr,
                                           uint32_t NameLen) {

  MEMINST_CHECK(MemInst, Frame, 0);
  MEM_SPAN_CHECK(NameBuf, MemInst, char, NamePtr, NameLen, "");

  FFMPEG_PTR_FETCH(Inout, InoutId, AVFilterInOut);

  std::string Name;
  std::copy_n(NameBuf.data(), NameLen, std::back_inserter(Name));
  char *CName = av_strdup(Name.c_str());
  if (CName == NULL)
    return static_cast<int32_t>(ErrNo::Success);
  Inout->name = CName;
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<int32_t> AVFilterInoutSetFilterCtx::body(const Runtime::CallingFrame &,
                                                uint32_t InoutId,
                                                uint32_t FilterCtxId) {

  FFMPEG_PTR_FETCH(Inout, InoutId, AVFilterInOut);
  FFMPEG_PTR_FETCH(FilterCtx, FilterCtxId, AVFilterContext);

  Inout->filter_ctx = FilterCtx;
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<int32_t> AVFilterInoutSetPadIdx::body(const Runtime::CallingFrame &,
                                             uint32_t InoutId, int32_t PadIdx) {

  FFMPEG_PTR_FETCH(Inout, InoutId, AVFilterInOut);
  Inout->pad_idx = PadIdx;
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<int32_t> AVFilterInoutSetNext::body(const Runtime::CallingFrame &,
                                           uint32_t InoutId,
                                           uint32_t NextInoutId) {

  FFMPEG_PTR_FETCH(Inout, InoutId, AVFilterInOut);
  FFMPEG_PTR_FETCH(NextInout, NextInoutId, AVFilterInOut);
  Inout->next = NextInout;
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<int32_t>
AVFilterGetInputsFilterPad::body(const Runtime::CallingFrame &Frame,
                                 uint32_t FilterId, uint32_t FilterPadPtr) {

  MEMINST_CHECK(MemInst, Frame, 0);
  MEM_PTR_CHECK(FilterPadId, MemInst, uint32_t, FilterPadPtr, "")

  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  const AVFilterPad *FilterPad = Filter->inputs;
  if (FilterPad == NULL)
    return static_cast<int32_t>(ErrNo::Success);
  FFMPEG_PTR_STORE((void *)FilterPad, FilterPadId);
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<int32_t>
AVFilterGetOutputsFilterPad::body(const Runtime::CallingFrame &Frame,
                                  uint32_t FilterId, uint32_t FilterPadPtr) {

  MEMINST_CHECK(MemInst, Frame, 0);
  MEM_PTR_CHECK(FilterPadId, MemInst, uint32_t, FilterPadPtr, "")

  FFMPEG_PTR_FETCH(Filter, FilterId, struct AVFilter);
  const AVFilterPad *FilterPad = Filter->outputs;
  if (FilterPad == NULL)
    return static_cast<int32_t>(ErrNo::Success);
  FFMPEG_PTR_STORE((void *)FilterPad, FilterPadId);
  return static_cast<int32_t>(ErrNo::Success);
}

} // namespace AVFilter
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge