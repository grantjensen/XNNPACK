// Auto-generated file. Do not edit!
//   Template: src/f32-velu/avx-rr2-lut4-p4-perm.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/vunary.h>


void xnn_f32_velu_ukernel__avx_rr2_lut4_p4_perm_x8(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_elu_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch % sizeof(float) == 0);

  const __m256 vprescale = _mm256_load_ps(params->avx_rr2_lut4_p4.prescale);
  const __m256 valpha = _mm256_load_ps(params->avx_rr2_lut4_p4.alpha);
  const __m256 vbeta = _mm256_load_ps(params->avx_rr2_lut4_p4.beta);
  const __m256 vsat_cutoff = _mm256_load_ps(params->avx_rr2_lut4_p4.sat_cutoff);
  const __m256 vmagic_bias = _mm256_load_ps(params->avx_rr2_lut4_p4.magic_bias);
  const __m256 vlog2e = _mm256_load_ps(params->avx_rr2_lut4_p4.log2e);
  const __m256 vindex_mask = _mm256_load_ps((const float*) params->avx_rr2_lut4_p4.index_mask);
  const __m256 vtable = _mm256_load_ps(params->avx_rr2_lut4_p4.table);
  const __m256 vminus_ln2_hi = _mm256_load_ps(params->avx_rr2_lut4_p4.minus_ln2_hi);
  const __m256 vminus_ln2_lo = _mm256_load_ps(params->avx_rr2_lut4_p4.minus_ln2_lo);
  const __m256 vc4 = _mm256_load_ps(params->avx_rr2_lut4_p4.c4);
  const __m256 vc3 = _mm256_load_ps(params->avx_rr2_lut4_p4.c3);
  const __m256 vc2 = _mm256_load_ps(params->avx_rr2_lut4_p4.c2);
  const __m256 vone = _mm256_load_ps(params->avx_rr2_lut4_p4.one);

  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    __m256 vx = _mm256_loadu_ps(input);
    input += 8;

    const __m256 vz = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx, vprescale));

    __m256 vn = _mm256_add_ps(_mm256_mul_ps(vz, vlog2e), vmagic_bias);
    __m256 ven = _mm256_andnot_ps(vindex_mask, vn);
    const __m256 vl = _mm256_permutevar_ps(vtable, _mm256_castps_si256(vn));
    const __m128 ven_lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(ven)), 21));
    vn = _mm256_sub_ps(vn, vmagic_bias);
    const __m128 ven_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(ven, 1)), 21));

    __m256 vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_hi), vz);
    ven = _mm256_insertf128_ps(_mm256_castps128_ps256(ven_lo), ven_hi, 1);
    vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_lo), vt);
    __m256 vs = _mm256_mul_ps(vl, ven);

    __m256 vp = _mm256_add_ps(_mm256_mul_ps(vc4, vt), vc3);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc2);
    vp = _mm256_mul_ps(vp, vt);

    vt = _mm256_mul_ps(vt, vs);
    vs = _mm256_sub_ps(vs, vone);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vt);

    const __m256 ve = _mm256_mul_ps(_mm256_add_ps(vp, vs), valpha);
    vx = _mm256_mul_ps(vx, vbeta);
    const __m256 vy = _mm256_blendv_ps(vx, ve, vx);

    _mm256_storeu_ps(output, vy);
    output += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 7 * sizeof(float));
    const __m256i vmask = _mm256_loadu_si256((const __m256i*) ((uintptr_t) &params->avx_rr2_p6.mask_table[7] - batch));

    __m256 vx = _mm256_maskload_ps(input, vmask);

    const __m256 vz = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx, vprescale));

    __m256 vn = _mm256_add_ps(_mm256_mul_ps(vz, vlog2e), vmagic_bias);
    __m256 ven = _mm256_andnot_ps(vindex_mask, vn);
    const __m256 vl = _mm256_permutevar_ps(vtable, _mm256_castps_si256(vn));
    const __m128 ven_lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(ven)), 21));
    vn = _mm256_sub_ps(vn, vmagic_bias);
    const __m128 ven_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(ven, 1)), 21));

    __m256 vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_hi), vz);
    ven = _mm256_insertf128_ps(_mm256_castps128_ps256(ven_lo), ven_hi, 1);
    vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_lo), vt);
    __m256 vs = _mm256_mul_ps(vl, ven);

    __m256 vp = _mm256_add_ps(_mm256_mul_ps(vc4, vt), vc3);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc2);
    vp = _mm256_mul_ps(vp, vt);

    vt = _mm256_mul_ps(vt, vs);
    vs = _mm256_sub_ps(vs, vone);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vt);

    const __m256 ve = _mm256_mul_ps(_mm256_add_ps(vp, vs), valpha);
    vx = _mm256_mul_ps(vx, vbeta);
    const __m256 vy = _mm256_blendv_ps(vx, ve, vx);

    __m128 vy_lo = _mm256_castps256_ps128(vy);
    if (batch & (4 * sizeof(float))) {
      _mm_storeu_ps(output, vy_lo);
      vy_lo = _mm256_extractf128_ps(vy, 1);
      output += 4;
    }
    if (batch & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) output, vy_lo);
      vy_lo = _mm_movehl_ps(vy_lo, vy_lo);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      _mm_store_ss(output, vy_lo);
    }
  }
}
