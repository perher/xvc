/******************************************************************************
* Copyright (C) 2017, Divideon. All rights reserved.
* No part of this code may be reproduced in any form
* without the written permission of the copyright holder.
******************************************************************************/

#ifndef XVC_ENC_LIB_PICTURE_ENCODER_H_
#define XVC_ENC_LIB_PICTURE_ENCODER_H_

#include <memory>
#include <string>
#include <vector>

#include "xvc_common_lib/checksum.h"
#include "xvc_common_lib/common.h"
#include "xvc_common_lib/picture_data.h"
#include "xvc_common_lib/segment_header.h"
#include "xvc_common_lib/yuv_pic.h"
#include "xvc_enc_lib/bit_writer.h"
#include "xvc_enc_lib/encoder_settings.h"
#include "xvc_enc_lib/syntax_writer.h"
#include "xvc_enc_lib/xvcenc.h"

namespace xvc {

class PictureEncoder {
public:
  PictureEncoder(ChromaFormat chroma_format, int width, int height,
                 int bitdepth);
  std::shared_ptr<YuvPicture> GetOrigPic() { return orig_pic_; }
  std::shared_ptr<const PictureData> GetPicData() const { return pic_data_; }
  std::shared_ptr<PictureData> GetPicData() { return pic_data_; }
  std::shared_ptr<const YuvPicture> GetRecPic() const { return rec_pic_; }
  std::shared_ptr<YuvPicture> GetRecPic() { return rec_pic_; }

  std::vector<uint8_t>* Encode(const SegmentHeader &segment, int segment_qp,
                               PicNum sub_gop_length, int buffer_flag,
                               bool flat_lambda,
                               const EncoderSettings &encoder_settings);
  std::vector<uint8_t> GetLastChecksum() const { return checksum_.GetHash(); }
  std::shared_ptr<YuvPicture> GetAlternativeRecPic(
    ChromaFormat chroma_format, int width, int height, int bitdepth) const;

private:
  void WriteHeader(const PictureData &pic_data, PicNum sub_gop_length,
                   int buffer_flag, BitWriter *bit_writer);
  void WriteChecksum(BitWriter *bit_writer, Checksum::Mode checksum_mode);
  int DerivePictureQp(const PictureData &pic_data, int segment_qp) const;

  BitWriter bit_writer_;
  Checksum checksum_;
  std::shared_ptr<YuvPicture> orig_pic_;
  std::shared_ptr<PictureData> pic_data_;
  std::shared_ptr<YuvPicture> rec_pic_;
};

}   // namespace xvc

#endif  // XVC_ENC_LIB_PICTURE_ENCODER_H_
