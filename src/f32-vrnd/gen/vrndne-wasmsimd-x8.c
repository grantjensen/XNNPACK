// Auto-generated file. Do not edit!
//   Template: src/f32-vrnd/wasmsimd.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/vunary.h>


void xnn_f32_vrndne_ukernel__wasmsimd_x8(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_rnd_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);

  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    const v128_t vx0123 = wasm_v128_load(input); input += 4;
    const v128_t vx4567 = wasm_v128_load(input); input += 4;

    const v128_t vy0123 = wasm_f32x4_nearest(vx0123);
    const v128_t vy4567 = wasm_f32x4_nearest(vx4567);

    wasm_v128_store(output, vy0123); output += 4;
    wasm_v128_store(output, vy4567); output += 4;
  }
  for (; batch >= 4 * sizeof(float); batch -= 4 * sizeof(float)) {
    const v128_t vx = wasm_v128_load(input); input += 4;
    const v128_t vy = wasm_f32x4_nearest(vx);
    wasm_v128_store(output, vy); output += 4;
  }
  if XNN_UNLIKELY(batch != 0) {
    const v128_t vx = wasm_v128_load(input);
    v128_t vy = wasm_f32x4_nearest(vx);

    if (batch & (2 * sizeof(float))) {
      *((double*) output) = wasm_f64x2_extract_lane(vy, 0);
      vy = wasm_v32x4_shuffle(vy, vy, 2, 3, 2, 3);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      *output = wasm_f32x4_extract_lane(vy, 0);
    }
  }
}
