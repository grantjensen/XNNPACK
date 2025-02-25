// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/vunary.h>


void xnn_u8_vclamp_ukernel__wasmsimd_x64(
    size_t batch,
    const uint8_t* input,
    uint8_t* output,
    const union xnn_u8_minmax_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);

  const v128_t voutput_max = wasm_v128_load64_splat(params->wasmsimd.max);
  const v128_t voutput_min = wasm_v128_load64_splat(params->wasmsimd.min);
  for (; batch >= 64; batch -= 64) {
    v128_t vacc0 = wasm_v128_load(input);
    v128_t vacc1 = wasm_v128_load(input + 16);
    v128_t vacc2 = wasm_v128_load(input + 32);
    v128_t vacc3 = wasm_v128_load(input + 48);
    input += 64;

    vacc0 = wasm_u8x16_max(vacc0, voutput_min);
    vacc1 = wasm_u8x16_max(vacc1, voutput_min);
    vacc2 = wasm_u8x16_max(vacc2, voutput_min);
    vacc3 = wasm_u8x16_max(vacc3, voutput_min);

    vacc0 = wasm_u8x16_min(vacc0, voutput_max);
    vacc1 = wasm_u8x16_min(vacc1, voutput_max);
    vacc2 = wasm_u8x16_min(vacc2, voutput_max);
    vacc3 = wasm_u8x16_min(vacc3, voutput_max);

    wasm_v128_store(output, vacc0);
    wasm_v128_store(output + 16, vacc1);
    wasm_v128_store(output + 32, vacc2);
    wasm_v128_store(output + 48, vacc3);
    output += 64;
  }
  for (; batch >= 16; batch -= 16) {
    v128_t vacc = wasm_v128_load(input);
    input += 16;

    vacc = wasm_u8x16_min(vacc, voutput_max);
    vacc = wasm_u8x16_max(vacc, voutput_min);

    wasm_v128_store(output, vacc);
    output += 16;
  }
  if XNN_UNLIKELY(batch != 0) {
    v128_t vacc = wasm_v128_load(input);

    vacc = wasm_u8x16_min(vacc, voutput_max);
    vacc = wasm_u8x16_max(vacc, voutput_min);

    if (batch & 8) {
      *((double*) output) = wasm_f64x2_extract_lane(vacc, 0);
      output += 8;
      vacc = wasm_v64x2_shuffle(vacc, vacc, 1, 1);
    }
    if (batch & 4) {
      *((float*) output) = wasm_f32x4_extract_lane(vacc, 0);
      output += 4;
      vacc = wasm_u64x2_shr(vacc, 32);
    }
    uint32_t vacc_lo = wasm_i32x4_extract_lane(vacc, 0);
    if (batch & 2) {
      *((uint16_t*) output) = (uint16_t) vacc_lo;
      vacc_lo >>= 16;
      output += 2;
    }
    if (batch & 1) {
      *output = (uint8_t) vacc_lo;
    }
  }
}
