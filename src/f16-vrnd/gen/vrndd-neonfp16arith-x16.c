// Auto-generated file. Do not edit!
//   Template: src/f16-vrnd/neonfp16arith.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/vunary.h>


void xnn_f16_vrndd_ukernel__neonfp16arith_x16(
    size_t batch,
    const void* input,
    void* output,
    const union xnn_f16_rnd_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(__fp16) == 0);

  const __fp16* i = (const __fp16*) input;
  __fp16* o = (__fp16*) output;
  for (; batch >= 16 * sizeof(__fp16); batch -= 16 * sizeof(__fp16)) {
    float16x8_t vacc0 = vld1q_f16(i); i += 8;
    float16x8_t vacc1 = vld1q_f16(i); i += 8;

    vacc0 = vrndmq_f16(vacc0);
    vacc1 = vrndmq_f16(vacc1);

    vst1q_f16(o, vacc0); o += 8;
    vst1q_f16(o, vacc1); o += 8;
  }
  for (; batch >= 8 * sizeof(__fp16); batch -= 8 * sizeof(__fp16)) {
    float16x8_t vacc = vld1q_f16(i); i += 8;
    vacc = vrndmq_f16(vacc);
    vst1q_f16(o, vacc); o += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    float16x8_t vacc = vld1q_f16(i);
    vacc = vrndmq_f16(vacc);
    float16x4_t vacc_lo = vget_low_f16(vacc);
    if (batch & (4 * sizeof(__fp16))) {
      vst1_f16(o, vacc_lo); o += 4;
      vacc_lo = vget_high_f16(vacc);
    }
    if (batch & (2 * sizeof(__fp16))) {
      vst1_lane_u32((void*) o, vreinterpret_u32_f16(vacc_lo), 0); o += 2;
      vacc_lo = vext_f16(vacc_lo, vacc_lo, 2);
    }
    if (batch & (1 * sizeof(__fp16))) {
      vst1_lane_f16(o, vacc_lo, 0);
    }
  }
}
