#include "avutil_func.h"

extern "C" {
#include "libavutil/avutil.h"
#include "libavutil/time.h"
}

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace AVUtil {

Expect<void> AVLogSetLevel::body(const Runtime::CallingFrame &,
                                 int32_t LogLevelId) {
  av_log_set_level(LogLevelId);
  return {};
}

Expect<int32_t> AVLogGetLevel::body(const Runtime::CallingFrame &) {
  return av_log_get_level();
}

Expect<int32_t> AVLogGetFlags::body(const Runtime::CallingFrame &) {
  return av_log_get_flags();
}

Expect<void> AVLogSetFlags::body(const Runtime::CallingFrame &,
                                 int32_t FlagId) {
  av_log_set_flags(FlagId);
  return {};
}

Expect<int64_t> AVRescaleQ::body(const Runtime::CallingFrame &, int64_t A,
                                 int32_t BNum, int32_t BDen, int32_t CNum,
                                 int32_t CDen) {

  AVRational const B = av_make_q(BNum, BDen);
  AVRational const C = av_make_q(CNum, CDen);
  return av_rescale_q(A, B, C);
}

Expect<int64_t> AVRescaleQRnd::body(const Runtime::CallingFrame &, int64_t A,
                                    int32_t BNum, int32_t BDen, int32_t CNum,
                                    int32_t CDen, int32_t RoundingId) {

  AVRational const B = av_make_q(BNum, BDen);
  AVRational const C = av_make_q(CNum, CDen);
  AVRounding const Rounding = FFmpegUtils::Rounding::intoAVRounding(RoundingId);
  return av_rescale_q_rnd(A, B, C, Rounding);
}

Expect<uint32_t> AVUtilVersion::body(const Runtime::CallingFrame &) {
  return avutil_version();
}

Expect<int32_t>
AVGetChannelLayoutNbChannels::body(const Runtime::CallingFrame &,
                                   uint64_t ChannelLayoutId) {
  uint64_t const ChannelLay =
      FFmpegUtils::ChannelLayout::fromChannelLayoutID(ChannelLayoutId);
  return av_get_channel_layout_nb_channels(ChannelLay);
}

Expect<uint64_t> AVGetDefaultChannelLayout::body(const Runtime::CallingFrame &,
                                                 int32_t Number) {
  uint64_t const ChannelLayout = av_get_default_channel_layout(Number);
  return FFmpegUtils::ChannelLayout::intoChannelLayoutID(ChannelLayout);
}

Expect<int32_t> AVUtilConfigurationLength::body(const Runtime::CallingFrame &) {
  const char *Config = avutil_configuration();
  return strlen(Config);
}

Expect<int32_t> AVUtilConfiguration::body(const Runtime::CallingFrame &Frame,
                                          uint32_t ConfigPtr,
                                          uint32_t ConfigLen) {

  MEMINST_CHECK(MemInst, Frame, 0);
  MEM_SPAN_CHECK(ConfigBuf, MemInst, char, ConfigPtr, ConfigLen, "");

  const char *Config = avutil_configuration();
  memmove(ConfigBuf.data(), Config, ConfigLen);
  return static_cast<int32_t>(ErrNo::Success);
}

Expect<int32_t> AVUtilLicenseLength::body(const Runtime::CallingFrame &) {

  const char *License = avutil_license();
  return strlen(License);
}

Expect<int32_t> AVUtilLicense::body(const Runtime::CallingFrame &Frame,
                                    uint32_t LicensePtr, uint32_t LicenseLen) {

  MEMINST_CHECK(MemInst, Frame, 0);
  MEM_SPAN_CHECK(LicenseBuf, MemInst, char, LicensePtr, LicenseLen, "");

  const char *License = avutil_license();
  memmove(LicenseBuf.data(), License, LicenseLen);
  return static_cast<int32_t>(ErrNo::Success);
}

} // namespace AVUtil
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge