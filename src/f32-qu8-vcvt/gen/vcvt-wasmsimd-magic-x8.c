// Auto-generated file. Do not edit!
//   Template: src/f32-qs8-vcvt/wasmsimd-magic.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/common.h>
#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/vcvt.h>


void xnn_f32_qu8_vcvt_ukernel__wasmsimd_magic_x8(
    size_t batch,
    const float* input,
    uint8_t* output,
    const union xnn_f32_qu8_cvt_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const v128_t vscale = wasm_v128_load64_splat(params->wasmsimd_magic.scale);
  const v128_t vmagic_bias = wasm_v128_load64_splat(params->wasmsimd_magic.magic_bias);
  const v128_t vmagic_min = wasm_v128_load64_splat(params->wasmsimd_magic.magic_min);
  const v128_t vmagic_bias_less_zero_point = wasm_v128_load64_splat(params->wasmsimd_magic.magic_bias_less_zero_point);
  const v128_t voutput_max = wasm_v128_load64_splat(params->wasmsimd_magic.output_max);
  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    v128_t vx_lo = wasm_v128_load(input);
    v128_t vx_hi = wasm_v128_load(input + 4);
    input += 8;

    vx_lo = wasm_f32x4_mul(vx_lo, vscale);
    vx_hi = wasm_f32x4_mul(vx_hi, vscale);

    vx_lo = wasm_f32x4_add(vx_lo, vmagic_bias);
    vx_hi = wasm_f32x4_add(vx_hi, vmagic_bias);

    v128_t vacc_lo = wasm_i32x4_max(vx_lo, vmagic_min);
    v128_t vacc_hi = wasm_i32x4_max(vx_hi, vmagic_min);

    vacc_lo = wasm_i32x4_sub(vacc_lo, vmagic_bias_less_zero_point);
    vacc_hi = wasm_i32x4_sub(vacc_hi, vmagic_bias_less_zero_point);

    const v128_t vacc = wasm_i16x8_narrow_i32x4(vacc_lo, vacc_hi);

    v128_t vy = wasm_u8x16_narrow_i16x8(vacc, vacc);
    vy = wasm_u8x16_min(vy, voutput_max);
    *((double*) output) = wasm_f64x2_extract_lane(vy, 0);
    output += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 7 * sizeof(float));
    v128_t vx_lo = wasm_v128_load(input);
    const float* x_hi = (const float*) ((uintptr_t) input + (batch & (4 * sizeof(float))));
    v128_t vx_hi = wasm_v128_load(x_hi);

    vx_lo = wasm_f32x4_mul(vx_lo, vscale);
    vx_hi = wasm_f32x4_mul(vx_hi, vscale);

    vx_lo = wasm_f32x4_add(vx_lo, vmagic_bias);
    vx_hi = wasm_f32x4_add(vx_hi, vmagic_bias);

    v128_t vacc_lo = wasm_i32x4_max(vx_lo, vmagic_min);
    v128_t vacc_hi = wasm_i32x4_max(vx_hi, vmagic_min);

    vacc_lo = wasm_i32x4_sub(vacc_lo, vmagic_bias_less_zero_point);
    vacc_hi = wasm_i32x4_sub(vacc_hi, vmagic_bias_less_zero_point);

    const v128_t vacc = wasm_i16x8_narrow_i32x4(vacc_lo, vacc_hi);

    v128_t vy = wasm_u8x16_narrow_i16x8(vacc, vacc);
    vy = wasm_u8x16_min(vy, voutput_max);

    if (batch & (4 * sizeof(float))) {
      *((float*) output) = wasm_f32x4_extract_lane(vy, 0);
      output += 4;
      vy = wasm_u64x2_shr(vy, 32);
    }
    uint32_t vy_lo = (uint32_t) wasm_i32x4_extract_lane(vy, 0);
    if (batch & (2 * sizeof(float))) {
      *((uint16_t*) output) = (uint16_t) vy_lo;
      output += 2;
      vy_lo >>= 16;
    }
    if (batch & (1 * sizeof(float))) {
      *output = (uint8_t) vy_lo;
    }
  }
}
