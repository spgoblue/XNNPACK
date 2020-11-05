// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <stddef.h>
#include <stdint.h>

#include <xnnpack/params.h>
#include <xnnpack/common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DECLARE_X32_DEPTH_TO_SPACE_CHW2HWC_UKERNEL_FUNCTION(fn_name) \
  XNN_INTERNAL void fn_name(                                         \
      size_t output_channels,                                        \
      size_t input_height,                                           \
      size_t input_width,                                            \
      size_t block_size,                                             \
      const uint32_t* input,                                         \
      uint32_t* output,                                              \
      size_t input_channel_stride,                                   \
      size_t input_height_stride,                                    \
      size_t output_height_stride,                                   \
      size_t output_width_stride);

DECLARE_X32_DEPTH_TO_SPACE_CHW2HWC_UKERNEL_FUNCTION(xnn_x32_depth_to_space_chw2hwc_ukernel__scalar_c1)
DECLARE_X32_DEPTH_TO_SPACE_CHW2HWC_UKERNEL_FUNCTION(xnn_x32_depth_to_space_chw2hwc_ukernel__scalar_c2)
DECLARE_X32_DEPTH_TO_SPACE_CHW2HWC_UKERNEL_FUNCTION(xnn_x32_depth_to_space_chw2hwc_ukernel__scalar_c4)
DECLARE_X32_DEPTH_TO_SPACE_CHW2HWC_UKERNEL_FUNCTION(xnn_x32_depth_to_space_chw2hwc_ukernel__scalar_c1_ib2)
DECLARE_X32_DEPTH_TO_SPACE_CHW2HWC_UKERNEL_FUNCTION(xnn_x32_depth_to_space_chw2hwc_ukernel__scalar_c2_ib2)
DECLARE_X32_DEPTH_TO_SPACE_CHW2HWC_UKERNEL_FUNCTION(xnn_x32_depth_to_space_chw2hwc_ukernel__scalar_c4_ib2)

#ifdef __cplusplus
}  // extern "C"
#endif