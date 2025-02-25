// Auto-generated file. Do not edit!
//   Template: src/f32-velu/wasmsimd-rr2-lut16-p3.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/vunary.h>
#include <xnnpack/common.h>


extern XNN_INTERNAL const float xnn_table_exp2minus_k_over_16[16];

void xnn_f32_velu_ukernel__wasmsimd_x86_rr2_lut16_p3_x8(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_elu_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const v128_t vprescale = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.prescale);
  const v128_t valpha = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.alpha);
  const v128_t vbeta = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.beta);
  const v128_t vsat_cutoff = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.sat_cutoff);
  const v128_t vmagic_bias = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.magic_bias);
  const v128_t vlog2e = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.log2e);
  const v128_t vindex_mask =  wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.index_mask);
  const v128_t vminus_ln2_hi = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.minus_ln2_hi);
  const v128_t vminus_ln2_lo = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.minus_ln2_lo);
  const v128_t vc3 = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.c3);
  const v128_t vc2 = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.c2);
  const v128_t vone = wasm_v128_load64_splat(params->wasmsimd_rr2_lut16_p3.one);

  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    v128_t vx0123 = wasm_v128_load(input);
    v128_t vx4567 = wasm_v128_load(input + 4);
    input += 8;

    const v128_t vz0123 = wasm_f32x4_mul(vx0123, vprescale);
    const v128_t vz4567 = wasm_f32x4_mul(vx4567, vprescale);

    v128_t vn0123 = wasm_f32x4_add(wasm_f32x4_mul(vz0123, vlog2e), vmagic_bias);
    v128_t vn4567 = wasm_f32x4_add(wasm_f32x4_mul(vz4567, vlog2e), vmagic_bias);

    const v128_t vidx0123 = wasm_i32x4_shl(wasm_v128_and(vn0123, vindex_mask), 2);
    const v128_t ven0123 = wasm_i32x4_shl(vn0123, 19);
    const v128_t vidx4567 = wasm_i32x4_shl(wasm_v128_and(vn4567, vindex_mask), 2);
    const v128_t ven4567 = wasm_i32x4_shl(vn4567, 19);

    const uint64_t vidx01 = wasm_i64x2_extract_lane(vidx0123, 0);
    const uint64_t vidx23 = wasm_i64x2_extract_lane(vidx0123, 1);
    const float vl0   = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx01));
    const float vl1 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx01 >> 32)));
    const float vl2 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx23));
    const float vl3 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx23 >> 32)));
    const v128_t vl0123 = wasm_f32x4_make(vl0, vl1, vl2, vl3);
    const uint64_t vidx45 = wasm_i64x2_extract_lane(vidx4567, 0);
    const uint64_t vidx67 = wasm_i64x2_extract_lane(vidx4567, 1);
    const float vl4   = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx45));
    const float vl5 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx45 >> 32)));
    const float vl6 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx67));
    const float vl7 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx67 >> 32)));
    const v128_t vl4567 = wasm_f32x4_make(vl4, vl5, vl6, vl7);

    vn0123 = wasm_f32x4_sub(vn0123, vmagic_bias);
    v128_t vs0123 = wasm_i32x4_add(vl0123, ven0123);
    vn4567 = wasm_f32x4_sub(vn4567, vmagic_bias);
    v128_t vs4567 = wasm_i32x4_add(vl4567, ven4567);

    v128_t vt0123 = wasm_f32x4_add(wasm_f32x4_mul(vn0123, vminus_ln2_hi), vz0123);
    const v128_t vsatm0123 = wasm_f32x4_le(vz0123, vsat_cutoff);
    v128_t vt4567 = wasm_f32x4_add(wasm_f32x4_mul(vn4567, vminus_ln2_hi), vz4567);
    const v128_t vsatm4567 = wasm_f32x4_le(vz4567, vsat_cutoff);

    vt0123 = wasm_f32x4_add(wasm_f32x4_mul(vn0123, vminus_ln2_lo), vt0123);
    vs0123 = wasm_v128_andnot(vs0123, vsatm0123);
    vt4567 = wasm_f32x4_add(wasm_f32x4_mul(vn4567, vminus_ln2_lo), vt4567);
    vs4567 = wasm_v128_andnot(vs4567, vsatm4567);

    vt0123 = wasm_v128_andnot(vt0123, vsatm0123);
    v128_t vp0123 = wasm_f32x4_add(wasm_f32x4_mul(vc3, vt0123), vc2);
    vt4567 = wasm_v128_andnot(vt4567, vsatm4567);
    v128_t vp4567 = wasm_f32x4_add(wasm_f32x4_mul(vc3, vt4567), vc2);

    vp0123 = wasm_f32x4_mul(vp0123, vt0123);
    vp4567 = wasm_f32x4_mul(vp4567, vt4567);

    vt0123 = wasm_f32x4_mul(vt0123, vs0123);
    vs0123 = wasm_f32x4_sub(vs0123, vone);
    vt4567 = wasm_f32x4_mul(vt4567, vs4567);
    vs4567 = wasm_f32x4_sub(vs4567, vone);

    vp0123 = wasm_f32x4_add(wasm_f32x4_mul(vp0123, vt0123), vt0123);
    vp4567 = wasm_f32x4_add(wasm_f32x4_mul(vp4567, vt4567), vt4567);

    const v128_t ve0123 = wasm_f32x4_mul(wasm_f32x4_add(vp0123, vs0123), valpha);
    const v128_t ve4567 = wasm_f32x4_mul(wasm_f32x4_add(vp4567, vs4567), valpha);

    const v128_t vsignm0123 = wasm_i32x4_shr(vx0123, 31);
    vx0123 = wasm_f32x4_mul(vx0123, vbeta);
    const v128_t vsignm4567 = wasm_i32x4_shr(vx4567, 31);
    vx4567 = wasm_f32x4_mul(vx4567, vbeta);

    const v128_t vy0123 = wasm_v128_bitselect(ve0123, vx0123, vsignm0123);
    const v128_t vy4567 = wasm_v128_bitselect(ve4567, vx4567, vsignm4567);

    wasm_v128_store(output, vy0123);
    wasm_v128_store(output + 4, vy4567);
    output += 8;
  }
  for (; batch >= 4 * sizeof(float); batch -= 4 * sizeof(float)) {
    v128_t vx = wasm_v128_load(input);
    input += 4;

    const v128_t vz = wasm_f32x4_mul(vx, vprescale);

    v128_t vn = wasm_f32x4_add(wasm_f32x4_mul(vz, vlog2e), vmagic_bias);
    const v128_t vidx = wasm_i32x4_shl(wasm_v128_and(vn, vindex_mask), 2);
    const v128_t ven = wasm_i32x4_shl(vn, 19);

    const uint64_t vidx_lo = wasm_i64x2_extract_lane(vidx, 0);
    const uint64_t vidx_hi = wasm_i64x2_extract_lane(vidx, 1);
    const float vl0 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx_lo));
    const float vl1 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx_lo >> 32)));
    const float vl2 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx_hi));
    const float vl3 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx_hi >> 32)));
    const v128_t vl = wasm_f32x4_make(vl0, vl1, vl2, vl3);

    v128_t vs = wasm_i32x4_add(vl, ven);
    vn = wasm_f32x4_sub(vn, vmagic_bias);

    v128_t vt = wasm_f32x4_add(wasm_f32x4_mul(vn, vminus_ln2_hi), vz);
    const v128_t vsatm = wasm_f32x4_le(vz, vsat_cutoff);
    vt = wasm_f32x4_add(wasm_f32x4_mul(vn, vminus_ln2_lo), vt);
    vs = wasm_v128_andnot(vs, vsatm);
    vt = wasm_v128_andnot(vt, vsatm);

    v128_t vp = wasm_f32x4_add(wasm_f32x4_mul(vc3, vt), vc2);
    vp = wasm_f32x4_mul(vp, vt);

    vt = wasm_f32x4_mul(vt, vs);
    vs = wasm_f32x4_sub(vs, vone);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vt);
    const v128_t ve = wasm_f32x4_mul(wasm_f32x4_add(vp, vs), valpha);

    const v128_t vsignm = wasm_i32x4_shr(vx, 31);
    vx = wasm_f32x4_mul(vx, vbeta);
    const v128_t vy = wasm_v128_bitselect(ve, vx, vsignm);

    wasm_v128_store(output, vy);
    output += 4;
  }
  if XNN_UNLIKELY(batch != 0) {
    v128_t vx = wasm_v128_load(input);

    const v128_t vz = wasm_f32x4_mul(vx, vprescale);

    v128_t vn = wasm_f32x4_add(wasm_f32x4_mul(vz, vlog2e), vmagic_bias);
    const v128_t vidx = wasm_i32x4_shl(wasm_v128_and(vn, vindex_mask), 2);
    const v128_t ven = wasm_i32x4_shl(vn, 19);

    const uint64_t vidx_lo = wasm_i64x2_extract_lane(vidx, 0);
    const uint64_t vidx_hi = wasm_i64x2_extract_lane(vidx, 1);
    const float vl0 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx_lo));
    const float vl1 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx_lo >> 32)));
    const float vl2 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) vidx_hi));
    const float vl3 = *((const float*) ((uintptr_t) xnn_table_exp2minus_k_over_16 + (uint32_t) (vidx_hi >> 32)));
    const v128_t vl = wasm_f32x4_make(vl0, vl1, vl2, vl3);

    v128_t vs = wasm_i32x4_add(vl, ven);
    vn = wasm_f32x4_sub(vn, vmagic_bias);

    v128_t vt = wasm_f32x4_add(wasm_f32x4_mul(vn, vminus_ln2_hi), vz);
    const v128_t vsatm = wasm_f32x4_le(vz, vsat_cutoff);
    vt = wasm_f32x4_add(wasm_f32x4_mul(vn, vminus_ln2_lo), vt);
    vs = wasm_v128_andnot(vs, vsatm);
    vt = wasm_v128_andnot(vt, vsatm);

    v128_t vp = wasm_f32x4_add(wasm_f32x4_mul(vc3, vt), vc2);
    vp = wasm_f32x4_mul(vp, vt);

    vt = wasm_f32x4_mul(vt, vs);
    vs = wasm_f32x4_sub(vs, vone);
    vp = wasm_f32x4_add(wasm_f32x4_mul(vp, vt), vt);
    const v128_t ve = wasm_f32x4_mul(wasm_f32x4_add(vp, vs), valpha);

    const v128_t vsignm = wasm_i32x4_shr(vx, 31);
    vx = wasm_f32x4_mul(vx, vbeta);
    v128_t vy = wasm_v128_bitselect(ve, vx, vsignm);

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
