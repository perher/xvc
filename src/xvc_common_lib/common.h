/******************************************************************************
* Copyright (C) 2017, Divideon.
*
* Redistribution and use in source and binary form, with or without
* modifications is permitted only under the terms and conditions set forward
* in the xvc License Agreement. For commercial redistribution and use, you are
* required to send a signed copy of the xvc License Agreement to Divideon.
*
* Redistribution and use in source and binary form is permitted free of charge
* for non-commercial purposes. See definition of non-commercial in the xvc
* License Agreement.
*
* All redistribution of source code must retain this copyright notice
* unmodified.
*
* The xvc License Agreement is available at https://xvc.io/license/.
******************************************************************************/

#ifndef XVC_COMMON_LIB_COMMON_H_
#define XVC_COMMON_LIB_COMMON_H_

#include <stdint.h>
#include <cstddef>

#ifndef XVC_HIGH_BITDEPTH
#define XVC_HIGH_BITDEPTH 1
#endif

namespace xvc {

#if !XVC_HIGH_BITDEPTH
typedef uint8_t Sample;
#else
typedef uint16_t Sample;
#endif
typedef int16_t Coeff;
typedef int16_t Residual;
typedef uint64_t Cost;
typedef uint64_t Distortion;
typedef uint32_t Bits;
typedef uint64_t PicNum;
typedef uint8_t SegmentNum;

enum class ChromaFormat : uint8_t {
  kMonochrome = 0,
  k420 = 1,
  k422 = 2,
  k444 = 3,
  kArgb = 4,
  kUndefined = 255,
};

enum class ColorMatrix : uint8_t {
  kUndefined = 0,
  k601 = 1,
  k709 = 2,
  k2020 = 3,
};

enum YuvComponent {
  kY = 0,
  kU = 1,
  kV = 2,
};

enum class CuTree {
  Primary = 0,
  Secondary = 1,
};

namespace constants {

// xvc version
const uint32_t kXvcCodecIdentifier = 7894627;
const uint32_t kXvcMajorVersion = 2;
const uint32_t kXvcMinorVersion = 0;
static const uint32_t kSupportedOldBitstreamVersions[1][2] = { { 1, 0 } };

// Picture
const int kMaxYuvComponents = 3;
const int kMaxNumPlanes = 2;  // luma and chroma
const int kMaxNumCuTrees = 2;

// CU limits
const int kCtuSizeLog2 = 6;
const int kCtuSize = 1 << kCtuSizeLog2;
// CU size and depth for luma
const int kMaxCuDepth = 3;
const int kMaxCuDepthChroma = kMaxCuDepth + 1;
const int kMinCuSize = (kCtuSize >> kMaxCuDepth);
// Binary split
const int kMaxBinarySplitDepth = 3;
const int kMaxBinarySplitSizeInter = kCtuSize;
const int kMaxBinarySplitSizeIntra1 = 32;
const int kMaxBinarySplitSizeIntra2 = 16;
const int kMinBinarySplitSize = 4;

// Actual storage required (to allow for deeper chroma CU trees)
const int kMaxBlockSize = kCtuSize;
const int kMaxBlockDepthLuma = kMaxCuDepth + kMaxBinarySplitDepth;
const int kMaxBlockDepthChroma = kMaxCuDepthChroma + kMaxBinarySplitDepth;
const int kMaxBlockDepth = kMaxBlockDepthLuma > kMaxBlockDepthChroma ?
kMaxBlockDepthLuma : kMaxBlockDepthChroma;
const int kMinBlockSize = 4;
const int kMaxBlockSamples = kMaxBlockSize * kMaxBlockSize;

const int kQuadSplit = 4;

// Transform
const int kTransformSkipMaxArea = 4 * 4;
const int kTransformSelectMinSigCoeffs = 3;
const int kTransformZeroOutMinSize = 32;
const int kMaxTransformSelectIdx = 4;

// Prediction
const int kNumIntraMpm = 3;
const int kNumIntraMpmExt = 6;
const int kNumInterMvPredictors = 2;
const int kNumInterMergeCandidates = 5;
const bool kTemporalMvPrediction = true;

// Quant
const int kMaxTrDynamicRange = 15;
const int kMinAllowedQp = -64;
const int kMaxAllowedQp = 63;
const int kMaxQpDiff = 16;
const int kQpSignalBase = 64;
const int kChromaOffsetBits = 6;

// Residual coding
const int kMaxNumC1Flags = 8;
const int kMaxNumC2Flags = 1;
const int kSubblockShift = 2;
const uint32_t kCoeffRemainBinReduction = 3;
const int SignHidingThreshold = 3;

// Deblocking
const int kDeblockOffsetBits = 6;

// Maximum number of reference pictures per reference picture list
const int kMaxNumRefPics = 5;

// High-level syntax
const int kTimeScale = 90000;
const int kMaxTid = 8;
const int kFrameRateBitDepth = 24;
const int kPicSizeBits = 16;
const PicNum kMaxSubGopLength = 64;
const int kEncapsulationCode1 = 182;
const int kEncapsulationCode2 = 214;

// Min and Max
const int16_t kInt16Max = INT16_MAX;
const int16_t kInt16Min = INT16_MIN;

}   // namespace constants

}   // namespace xvc

#endif  // XVC_COMMON_LIB_COMMON_H_
