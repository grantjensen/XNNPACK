// Auto-generated file. Do not edit!
//   Template: src/f16-vhswish/neonfp16arith.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/common.h>
#include <xnnpack/vunary.h>


void xnn_f16_vhswish_ukernel__neonfp16arith_x8(
    size_t batch,
    const void* restrict input,
    void* restrict output,
    const union xnn_f16_hswish_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(__fp16) == 0);

  const __fp16* i = (const __fp16*) input;
  __fp16* o = (__fp16*) output;

  const float16x8_t vsixth = vreinterpretq_f16_u16(vld1q_dup_u16(&params->fp16arith.sixth));
  const float16x8_t vthree = vreinterpretq_f16_u16(vld1q_dup_u16(&params->fp16arith.three));
  const int16x8_t vsix = vreinterpretq_s16_u16(vld1q_dup_u16(&params->fp16arith.six));
  const int16x8_t vzero = vdupq_n_s16(0);

  for (; batch >= 8 * sizeof(__fp16); batch -= 8 * sizeof(__fp16)) {
    float16x8_t vx = vld1q_f16(i); i += 8;
    float16x8_t vacc = vaddq_f16(vx, vthree);
    vx = vmulq_f16(vx, vsixth);
    vacc = vreinterpretq_f16_s16(vmaxq_s16(vreinterpretq_s16_f16(vacc), vzero));
    vacc = vreinterpretq_f16_s16(vminq_s16(vreinterpretq_s16_f16(vacc), vsix));
    vacc = vmulq_f16(vacc, vx);
    vst1q_f16(o, vacc); o += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    float16x8_t vx = vld1q_f16(i);
    float16x8_t vacc = vaddq_f16(vx, vthree);
    vx = vmulq_f16(vx, vsixth);
    vacc = vreinterpretq_f16_s16(vmaxq_s16(vreinterpretq_s16_f16(vacc), vzero));
    vacc = vreinterpretq_f16_s16(vminq_s16(vreinterpretq_s16_f16(vacc), vsix));
    vacc = vmulq_f16(vacc, vx);

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
