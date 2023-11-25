#include "module.h"
#include "avCodec.h"
#include "avCodecContext.h"
#include "avCodecParameters.h"
#include "avPacket.h"
#include "avcodec_func.h"

namespace WasmEdge {
namespace Host {
namespace WasmEdgeFFmpeg {
namespace AVcodec {

WasmEdgeFFmpegAVCodecModule::WasmEdgeFFmpegAVCodecModule(
    std::shared_ptr<WasmEdgeFFmpegEnv> Env)
    : ModuleInstance("wasmedge_ffmpeg_avcodec") {

  // avcodec_func.h
  // Need to test
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_alloc_context3",
              std::make_unique<AVCodecAllocContext3>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_parameters_from_context",
              std::make_unique<AVCodecParametersFromContext>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_parameters_free",
              std::make_unique<AVCodecParametersFree>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_free_context",
              std::make_unique<AVCodecFreeContext>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_parameters_alloc",
              std::make_unique<AVCodecParametersAlloc>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_get_type",
              std::make_unique<AVCodecGetType>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_open2",
              std::make_unique<AVCodecOpen2>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_find_decoder",
              std::make_unique<AVCodecFindDecoder>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_codec_is_encoder",
              std::make_unique<AVCodecIsEncoder>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_codec_is_decoder",
              std::make_unique<AVCodecIsDecoder>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_close",
              std::make_unique<AVCodecClose>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_parameters_to_context",
              std::make_unique<AVCodecParametersToContext>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_receive_frame",
              std::make_unique<AVCodecReceiveFrame>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_send_packet",
              std::make_unique<AVCodecSendPacket>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_find_encoder",
              std::make_unique<AVCodecFindEncoder>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_receive_packet",
              std::make_unique<AVCodecReceivePacket>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_send_frame",
              std::make_unique<AVCodecSendFrame>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_find_decoder_by_name",
              std::make_unique<AVCodecFindDecoderByName>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_find_encoder_by_name",
              std::make_unique<AVCodecFindEncoderByName>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_rescale_ts",
              std::make_unique<AVPacketRescaleTs>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_make_writable",
              std::make_unique<AVPacketMakeWritable>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_parameters_copy", // test
              std::make_unique<AVCodecParametersCopy>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_version",
              std::make_unique<AVCodecVersion>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_flush_buffers",
              std::make_unique<AVCodecFlushBuffers>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_configuration_length",
              std::make_unique<AVCodecConfigurationLength>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_configuration",
              std::make_unique<AVCodecConfiguration>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_license_length",
              std::make_unique<AVCodecLicenseLength>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_license",
              std::make_unique<AVCodecLicense>(Env));

  // avCodecContext Struct fields access
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_codec_id",
              std::make_unique<AVCodecCtxCodecID>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_codec_type",
              std::make_unique<AVCodecCtxCodecType>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_codec_type",
              std::make_unique<AVCodecCtxSetCodecType>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_time_base",
              std::make_unique<AVCodecCtxSetTimebase>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_time_base",
              std::make_unique<AVCodecCtxTimeBase>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_width",
              std::make_unique<AVCodecCtxWidth>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_width",
              std::make_unique<AVCodecCtxSetWidth>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_height",
              std::make_unique<AVCodecCtxHeight>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_height",
              std::make_unique<AVCodecCtxSetHeight>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_sample_aspect_ratio",
              std::make_unique<AVCodecCtxSampleAspectRatio>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_sample_aspect_ratio",
              std::make_unique<AVCodecCtxSetSampleAspectRatio>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_channel_layout",
              std::make_unique<AVCodecCtxChannelLayout>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_channel_layout",
              std::make_unique<AVCodecCtxSetChannelLayout>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_pix_fmt",
              std::make_unique<AVCodecCtxPixFormat>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_pix_fmt",
              std::make_unique<AVCodecCtxSetPixFormat>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_sample_format",
              std::make_unique<AVCodecCtxSampleFormat>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_sample_format",
              std::make_unique<AVCodecCtxSetSampleFormat>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_sample_rate",
              std::make_unique<AVCodecCtxSampleRate>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_sample_rate",
              std::make_unique<AVCodecCtxSetSampleRate>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_gop_size",
              std::make_unique<AVCodecCtxSetGopSize>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_max_b_frames",
              std::make_unique<AVCodecCtxSetMaxBFrames>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_b_quant_factor",
              std::make_unique<AVCodecCtxSetBQuantFactor>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_b_quant_offset",
              std::make_unique<AVCodecCtxSetBQuantOffset>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_i_quant_factor",
              std::make_unique<AVCodecCtxSetIQuantFactor>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_i_quant_offset",
              std::make_unique<AVCodecCtxSetIQuantOffset>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_lumi_masking",
              std::make_unique<AVCodecCtxSetLumiMasking>(Env));
  addHostFunc(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_temporal_cplx_masking",
      std::make_unique<AVCodecCtxSetTemporalCplxMasking>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_spatial_cplx_masking",
              std::make_unique<AVCodecCtxSetSpatialCplxMasking>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_p_masking",
              std::make_unique<AVCodecCtxSetPMasking>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_dark_masking",
              std::make_unique<AVCodecCtxSetDarkMasking>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_cmp",
              std::make_unique<AVCodecCtxSetMeCmp>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_sub_cmp",
              std::make_unique<AVCodecCtxSetMeSubCmp>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_mb_cmp",
              std::make_unique<AVCodecCtxSetMbCmp>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_ildct_cmp",
              std::make_unique<AVCodecCtxSetIldctCmp>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_dia_size",
              std::make_unique<AVCodecCtxSetDiaSize>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_last_predictor_count",
              std::make_unique<AVCodecCtxSetLastPredictorsCount>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_pre_cmp",
              std::make_unique<AVCodecCtxSetMePreCmp>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_pre_dia_size",
              std::make_unique<AVCodecCtxSetPreDiaSize>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_subpel_quality",
              std::make_unique<AVCodecCtxSetMeSubpelQuality>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_me_range",
              std::make_unique<AVCodecCtxSetMeRange>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_mb_decision",
              std::make_unique<AVCodecCtxSetMbDecision>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_mb_lmin",
              std::make_unique<AVCodecCtxSetMbLMin>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_mb_lmax",
              std::make_unique<AVCodecCtxSetMbLMax>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_intra_dc_precision",
              std::make_unique<AVCodecCtxIntraDcPrecision>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_intra_dc_precision",
              std::make_unique<AVCodecCtxSetIntraDcPrecision>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_qmin",
              std::make_unique<AVCodecCtxSetQMin>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_qmax",
              std::make_unique<AVCodecCtxSetQMax>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_global_quality",
              std::make_unique<AVCodecCtxSetGlobalQuality>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_colorspace",
              std::make_unique<AVCodecCtxSetColorspace>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_colorspace",
              std::make_unique<AVCodecCtxColorspace>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_color_range",
              std::make_unique<AVCodecCtxSetColorRange>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_color_range",
              std::make_unique<AVCodecCtxColorRange>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_frame_size",
              std::make_unique<AVCodecCtxFrameSize>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_bit_rate",
              std::make_unique<AVCodecCtxBitRate>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_bit_rate",
              std::make_unique<AVCodecCtxSetBitRate>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_rc_max_rate",
              std::make_unique<AVCodecCtxRcMaxRate>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_rc_max_rate",
              std::make_unique<AVCodecCtxSetRcMaxRate>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_bit_rate_tolerance",
              std::make_unique<AVCodecCtxSetBitRateTolerance>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_compression_level",
              std::make_unique<AVCodecCtxSetCompressionLevel>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_framerate",
              std::make_unique<AVCodecCtxFrameRate>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_framerate",
              std::make_unique<AVCodecCtxSetFrameRate>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_flags",
              std::make_unique<AVCodecCtxSetFlags>(Env));
  addHostFunc(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_strict_std_compliance",
      std::make_unique<AVCodecCtxSetStrictStdCompliance>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_debug",
              std::make_unique<AVCodecCtxSetDebug>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_codec",
              std::make_unique<AVCodecCtxCodec>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_channels",
              std::make_unique<AVCodecCtxChannels>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_channels",
              std::make_unique<AVCodecCtxSetChannels>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_loop_filter",
              std::make_unique<AVCodecCtxSetSkipLoopFilter>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_frame",
              std::make_unique<AVCodecCtxSetSkipFrame>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_idct",
              std::make_unique<AVCodecCtxSetSkipIdct>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_error_concealment",
              std::make_unique<AVCodecCtxSetErrorConcealment>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_err_recognition",
              std::make_unique<AVCodecCtxSetErrorRecognition>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_delay",
              std::make_unique<AVCodecCtxDelay>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_top",
              std::make_unique<AVCodecCtxSetSkipTop>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_skip_bottom",
              std::make_unique<AVCodecCtxSetSkipBottom>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_refs",
              std::make_unique<AVCodecCtxRefs>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_slice_flags",
              std::make_unique<AVCodecCtxSetSliceFlags>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_slice_count",
              std::make_unique<AVCodecCtxSetSliceCount>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_field_order",
              std::make_unique<AVCodecCtxSetFieldOrder>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_color_trc",
              std::make_unique<AVCodecCtxColorTrc>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_chroma_sample_location",
              std::make_unique<AVCodecCtxChromaSampleLocation>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_frame_number",
              std::make_unique<AVCodecCtxFrameNumber>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_block_align",
              std::make_unique<AVCodecCtxBlockAlign>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_request_sample_fmt",
              std::make_unique<AVCodecCtxSetRequestSampleFmt>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_audio_service_type",
              std::make_unique<AVCodecCtxAudioServiceType>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_has_b_frames",
              std::make_unique<AVCodecCtxHasBFrames>(Env));
  addHostFunc(
      "wasmedge_ffmpeg_avcodec_avcodeccontext_set_request_channel_layout",
      std::make_unique<AVCodecCtxSetRequestChannelLayout>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_active_thread_type",
              std::make_unique<AVCodecCtxActiveThreadType>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_thread_type",
              std::make_unique<AVCodecCtxSetThreadType>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_thread_count",
              std::make_unique<AVCodecCtxThreadCount>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_set_thread_count",
              std::make_unique<AVCodecCtxSetThreadCount>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodeccontext_color_primaries",
              std::make_unique<AVCodecCtxColorPrimaries>(Env));

  // avCodec Struct fields access
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_id",
              std::make_unique<AVCodecID>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_type",
              std::make_unique<AVCodecType>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_max_lowres",
              std::make_unique<AVCodecMaxLowres>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_capabilities",
              std::make_unique<AVCodecCapabilities>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_get_name_len",
              std::make_unique<AVCodecGetNameLen>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_get_name",
              std::make_unique<AVCodecGetName>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_get_long_name_len",
              std::make_unique<AVCodecGetLongNameLen>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_get_long_name",
              std::make_unique<AVCodecGetLongName>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_profiles",
              std::make_unique<AVCodecProfiles>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_pix_fmts_is_null",
              std::make_unique<AVCodecPixFmtsIsNull>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_pix_fmts_iter",
              std::make_unique<AVCodecPixFmtsIter>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_supported_framerate_is_null",
              std::make_unique<AVCodecSupportedFrameratesIsNull>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_supported_framerate_iter",
              std::make_unique<AVCodecSupportedFrameratesIter>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_supported_samplerates_is_null",
              std::make_unique<AVCodecSupportedSampleRatesIsNull>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_supported_samplerates_iter",
              std::make_unique<AVCodecSupportedSampleRatesIter>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_channel_layouts_is_null",
              std::make_unique<AVCodecChannelLayoutIsNull>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_channel_layouts_iter",
              std::make_unique<AVCodecChannelLayoutIter>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_sample_fmts_is_null",
              std::make_unique<AVCodecSampleFmtsIsNull>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodec_sample_fmts_iter",
              std::make_unique<AVCodecSampleFmtsIter>(Env));

  // AVCodecParam Struct fields access.
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodecparam_codec_id",
              std::make_unique<AVCodecParamCodecId>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodecparam_codec_type",
              std::make_unique<AVCodecParamCodecType>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_avcodecparam_set_codec_tag",
              std::make_unique<AVCodecParamSetCodecTag>(Env));

  // AVPacket functions.
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_alloc",
              std::make_unique<AVPacketAlloc>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_new_packet",
              std::make_unique<AVNewPacket>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_ref",
              std::make_unique<AVPacketRef>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_unref",
              std::make_unique<AVPacketUnref>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_grow_packet",
              std::make_unique<AVGrowPacket>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_shrink_packet",
              std::make_unique<AVShrinkPacket>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_stream_index",
              std::make_unique<AVPacketStreamIndex>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_set_stream_index",
              std::make_unique<AVPacketSetStreamIndex>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_size",
              std::make_unique<AVPacketSize>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_flags",
              std::make_unique<AVPacketFlags>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_set_flags",
              std::make_unique<AVPacketSetFlags>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_pos",
              std::make_unique<AVPacketPos>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_set_pos",
              std::make_unique<AVPacketSetPos>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_duration",
              std::make_unique<AVPacketDuration>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_set_duration",
              std::make_unique<AVPacketSetDuration>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_dts",
              std::make_unique<AVPacketDts>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_set_dts",
              std::make_unique<AVPacketSetDts>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_pts",
              std::make_unique<AVPacketPts>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_set_pts",
              std::make_unique<AVPacketSetPts>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_is_data_null",
              std::make_unique<AVPacketIsDataNull>(Env));
  addHostFunc("wasmedge_ffmpeg_avcodec_av_packet_data",
              std::make_unique<AVPacketData>(Env));
}

} // namespace AVcodec
} // namespace WasmEdgeFFmpeg
} // namespace Host
} // namespace WasmEdge
