// Auto-generated file. Do not edit!
//   Template: src/f32-velu/avx2-rr1-lut8-p4-perm.c.in
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


void xnn_f32_velu_ukernel__avx2_rr1_lut8_p4_perm_x72(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_elu_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch % sizeof(float) == 0);

  const __m256 vprescale = _mm256_load_ps(params->avx2_rr1_lut8_p4.prescale);
  const __m256 valpha = _mm256_load_ps(params->avx2_rr1_lut8_p4.alpha);
  const __m256 vbeta = _mm256_load_ps(params->avx2_rr1_lut8_p4.beta);
  const __m256 vsat_cutoff = _mm256_load_ps(params->avx2_rr1_lut8_p4.sat_cutoff);
  const __m256 vmagic_bias = _mm256_load_ps(params->avx2_rr1_lut8_p4.magic_bias);
  const __m256 vlog2e = _mm256_load_ps(params->avx2_rr1_lut8_p4.log2e);
  const __m256i vtable = _mm256_load_si256((const __m256i*) params->avx2_rr1_lut8_p4.table);
  const __m256 vminus_ln2 = _mm256_load_ps(params->avx2_rr1_lut8_p4.minus_ln2);
  const __m256 vc4 = _mm256_load_ps(params->avx2_rr1_lut8_p4.c4);
  const __m256 vc3 = _mm256_load_ps(params->avx2_rr1_lut8_p4.c3);
  const __m256 vc2 = _mm256_load_ps(params->avx2_rr1_lut8_p4.c2);

  for (; batch >= 72 * sizeof(float); batch -= 72 * sizeof(float)) {
    __m256 vx0 = _mm256_loadu_ps(input);
    __m256 vx1 = _mm256_loadu_ps(input + 8);
    __m256 vx2 = _mm256_loadu_ps(input + 16);
    __m256 vx3 = _mm256_loadu_ps(input + 24);
    __m256 vx4 = _mm256_loadu_ps(input + 32);
    __m256 vx5 = _mm256_loadu_ps(input + 40);
    __m256 vx6 = _mm256_loadu_ps(input + 48);
    __m256 vx7 = _mm256_loadu_ps(input + 56);
    __m256 vx8 = _mm256_loadu_ps(input + 64);
    input += 72;

    const __m256 vz0 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx0, vprescale));
    const __m256 vz1 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx1, vprescale));
    const __m256 vz2 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx2, vprescale));
    const __m256 vz3 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx3, vprescale));
    const __m256 vz4 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx4, vprescale));
    const __m256 vz5 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx5, vprescale));
    const __m256 vz6 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx6, vprescale));
    const __m256 vz7 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx7, vprescale));
    const __m256 vz8 = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx8, vprescale));

    __m256 vn0 = _mm256_fmadd_ps(vz0, vlog2e, vmagic_bias);
    __m256 vn1 = _mm256_fmadd_ps(vz1, vlog2e, vmagic_bias);
    __m256 vn2 = _mm256_fmadd_ps(vz2, vlog2e, vmagic_bias);
    __m256 vn3 = _mm256_fmadd_ps(vz3, vlog2e, vmagic_bias);
    __m256 vn4 = _mm256_fmadd_ps(vz4, vlog2e, vmagic_bias);
    __m256 vn5 = _mm256_fmadd_ps(vz5, vlog2e, vmagic_bias);
    __m256 vn6 = _mm256_fmadd_ps(vz6, vlog2e, vmagic_bias);
    __m256 vn7 = _mm256_fmadd_ps(vz7, vlog2e, vmagic_bias);
    __m256 vn8 = _mm256_fmadd_ps(vz8, vlog2e, vmagic_bias);

    const __m256i ven0 = _mm256_slli_epi32(_mm256_castps_si256(vn0), 20);
    const __m256i vl0 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn0));
    vn0 = _mm256_sub_ps(vn0, vmagic_bias);
    const __m256i ven1 = _mm256_slli_epi32(_mm256_castps_si256(vn1), 20);
    const __m256i vl1 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn1));
    vn1 = _mm256_sub_ps(vn1, vmagic_bias);
    const __m256i ven2 = _mm256_slli_epi32(_mm256_castps_si256(vn2), 20);
    const __m256i vl2 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn2));
    vn2 = _mm256_sub_ps(vn2, vmagic_bias);
    const __m256i ven3 = _mm256_slli_epi32(_mm256_castps_si256(vn3), 20);
    const __m256i vl3 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn3));
    vn3 = _mm256_sub_ps(vn3, vmagic_bias);
    const __m256i ven4 = _mm256_slli_epi32(_mm256_castps_si256(vn4), 20);
    const __m256i vl4 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn4));
    vn4 = _mm256_sub_ps(vn4, vmagic_bias);
    const __m256i ven5 = _mm256_slli_epi32(_mm256_castps_si256(vn5), 20);
    const __m256i vl5 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn5));
    vn5 = _mm256_sub_ps(vn5, vmagic_bias);
    const __m256i ven6 = _mm256_slli_epi32(_mm256_castps_si256(vn6), 20);
    const __m256i vl6 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn6));
    vn6 = _mm256_sub_ps(vn6, vmagic_bias);
    const __m256i ven7 = _mm256_slli_epi32(_mm256_castps_si256(vn7), 20);
    const __m256i vl7 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn7));
    vn7 = _mm256_sub_ps(vn7, vmagic_bias);
    const __m256i ven8 = _mm256_slli_epi32(_mm256_castps_si256(vn8), 20);
    const __m256i vl8 = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn8));
    vn8 = _mm256_sub_ps(vn8, vmagic_bias);

    __m256 vs0 = _mm256_castsi256_ps(_mm256_add_epi32(vl0, ven0));
    __m256 vt0 = _mm256_fmadd_ps(vn0, vminus_ln2, vz0);
    __m256 vs1 = _mm256_castsi256_ps(_mm256_add_epi32(vl1, ven1));
    __m256 vt1 = _mm256_fmadd_ps(vn1, vminus_ln2, vz1);
    __m256 vs2 = _mm256_castsi256_ps(_mm256_add_epi32(vl2, ven2));
    __m256 vt2 = _mm256_fmadd_ps(vn2, vminus_ln2, vz2);
    __m256 vs3 = _mm256_castsi256_ps(_mm256_add_epi32(vl3, ven3));
    __m256 vt3 = _mm256_fmadd_ps(vn3, vminus_ln2, vz3);
    __m256 vs4 = _mm256_castsi256_ps(_mm256_add_epi32(vl4, ven4));
    __m256 vt4 = _mm256_fmadd_ps(vn4, vminus_ln2, vz4);
    __m256 vs5 = _mm256_castsi256_ps(_mm256_add_epi32(vl5, ven5));
    __m256 vt5 = _mm256_fmadd_ps(vn5, vminus_ln2, vz5);
    __m256 vs6 = _mm256_castsi256_ps(_mm256_add_epi32(vl6, ven6));
    __m256 vt6 = _mm256_fmadd_ps(vn6, vminus_ln2, vz6);
    __m256 vs7 = _mm256_castsi256_ps(_mm256_add_epi32(vl7, ven7));
    __m256 vt7 = _mm256_fmadd_ps(vn7, vminus_ln2, vz7);
    __m256 vs8 = _mm256_castsi256_ps(_mm256_add_epi32(vl8, ven8));
    __m256 vt8 = _mm256_fmadd_ps(vn8, vminus_ln2, vz8);

    __m256 vp0 = _mm256_fmadd_ps(vc4, vt0, vc3);
    __m256 vp1 = _mm256_fmadd_ps(vc4, vt1, vc3);
    __m256 vp2 = _mm256_fmadd_ps(vc4, vt2, vc3);
    __m256 vp3 = _mm256_fmadd_ps(vc4, vt3, vc3);
    __m256 vp4 = _mm256_fmadd_ps(vc4, vt4, vc3);
    __m256 vp5 = _mm256_fmadd_ps(vc4, vt5, vc3);
    __m256 vp6 = _mm256_fmadd_ps(vc4, vt6, vc3);
    __m256 vp7 = _mm256_fmadd_ps(vc4, vt7, vc3);
    __m256 vp8 = _mm256_fmadd_ps(vc4, vt8, vc3);

    vp0 = _mm256_fmadd_ps(vp0, vt0, vc2);
    vp1 = _mm256_fmadd_ps(vp1, vt1, vc2);
    vp2 = _mm256_fmadd_ps(vp2, vt2, vc2);
    vp3 = _mm256_fmadd_ps(vp3, vt3, vc2);
    vp4 = _mm256_fmadd_ps(vp4, vt4, vc2);
    vp5 = _mm256_fmadd_ps(vp5, vt5, vc2);
    vp6 = _mm256_fmadd_ps(vp6, vt6, vc2);
    vp7 = _mm256_fmadd_ps(vp7, vt7, vc2);
    vp8 = _mm256_fmadd_ps(vp8, vt8, vc2);

    vp0 = _mm256_mul_ps(vp0, vt0);
    vt0 = _mm256_mul_ps(vt0, vs0);
    vp1 = _mm256_mul_ps(vp1, vt1);
    vt1 = _mm256_mul_ps(vt1, vs1);
    vp2 = _mm256_mul_ps(vp2, vt2);
    vt2 = _mm256_mul_ps(vt2, vs2);
    vp3 = _mm256_mul_ps(vp3, vt3);
    vt3 = _mm256_mul_ps(vt3, vs3);
    vp4 = _mm256_mul_ps(vp4, vt4);
    vt4 = _mm256_mul_ps(vt4, vs4);
    vp5 = _mm256_mul_ps(vp5, vt5);
    vt5 = _mm256_mul_ps(vt5, vs5);
    vp6 = _mm256_mul_ps(vp6, vt6);
    vt6 = _mm256_mul_ps(vt6, vs6);
    vp7 = _mm256_mul_ps(vp7, vt7);
    vt7 = _mm256_mul_ps(vt7, vs7);
    vp8 = _mm256_mul_ps(vp8, vt8);
    vt8 = _mm256_mul_ps(vt8, vs8);

    vs0 = _mm256_fmsub_ps(vs0, valpha, valpha);
    vp0 = _mm256_fmadd_ps(vp0, vt0, vt0);
    vs1 = _mm256_fmsub_ps(vs1, valpha, valpha);
    vp1 = _mm256_fmadd_ps(vp1, vt1, vt1);
    vs2 = _mm256_fmsub_ps(vs2, valpha, valpha);
    vp2 = _mm256_fmadd_ps(vp2, vt2, vt2);
    vs3 = _mm256_fmsub_ps(vs3, valpha, valpha);
    vp3 = _mm256_fmadd_ps(vp3, vt3, vt3);
    vs4 = _mm256_fmsub_ps(vs4, valpha, valpha);
    vp4 = _mm256_fmadd_ps(vp4, vt4, vt4);
    vs5 = _mm256_fmsub_ps(vs5, valpha, valpha);
    vp5 = _mm256_fmadd_ps(vp5, vt5, vt5);
    vs6 = _mm256_fmsub_ps(vs6, valpha, valpha);
    vp6 = _mm256_fmadd_ps(vp6, vt6, vt6);
    vs7 = _mm256_fmsub_ps(vs7, valpha, valpha);
    vp7 = _mm256_fmadd_ps(vp7, vt7, vt7);
    vs8 = _mm256_fmsub_ps(vs8, valpha, valpha);
    vp8 = _mm256_fmadd_ps(vp8, vt8, vt8);

    const __m256 ve0 = _mm256_fmadd_ps(vp0, valpha, vs0);
    vx0 = _mm256_mul_ps(vx0, vbeta);
    const __m256 ve1 = _mm256_fmadd_ps(vp1, valpha, vs1);
    vx1 = _mm256_mul_ps(vx1, vbeta);
    const __m256 ve2 = _mm256_fmadd_ps(vp2, valpha, vs2);
    vx2 = _mm256_mul_ps(vx2, vbeta);
    const __m256 ve3 = _mm256_fmadd_ps(vp3, valpha, vs3);
    vx3 = _mm256_mul_ps(vx3, vbeta);
    const __m256 ve4 = _mm256_fmadd_ps(vp4, valpha, vs4);
    vx4 = _mm256_mul_ps(vx4, vbeta);
    const __m256 ve5 = _mm256_fmadd_ps(vp5, valpha, vs5);
    vx5 = _mm256_mul_ps(vx5, vbeta);
    const __m256 ve6 = _mm256_fmadd_ps(vp6, valpha, vs6);
    vx6 = _mm256_mul_ps(vx6, vbeta);
    const __m256 ve7 = _mm256_fmadd_ps(vp7, valpha, vs7);
    vx7 = _mm256_mul_ps(vx7, vbeta);
    const __m256 ve8 = _mm256_fmadd_ps(vp8, valpha, vs8);
    vx8 = _mm256_mul_ps(vx8, vbeta);

    const __m256 vy0 = _mm256_blendv_ps(vx0, ve0, vx0);
    const __m256 vy1 = _mm256_blendv_ps(vx1, ve1, vx1);
    const __m256 vy2 = _mm256_blendv_ps(vx2, ve2, vx2);
    const __m256 vy3 = _mm256_blendv_ps(vx3, ve3, vx3);
    const __m256 vy4 = _mm256_blendv_ps(vx4, ve4, vx4);
    const __m256 vy5 = _mm256_blendv_ps(vx5, ve5, vx5);
    const __m256 vy6 = _mm256_blendv_ps(vx6, ve6, vx6);
    const __m256 vy7 = _mm256_blendv_ps(vx7, ve7, vx7);
    const __m256 vy8 = _mm256_blendv_ps(vx8, ve8, vx8);

    _mm256_storeu_ps(output, vy0);
    _mm256_storeu_ps(output + 8, vy1);
    _mm256_storeu_ps(output + 16, vy2);
    _mm256_storeu_ps(output + 24, vy3);
    _mm256_storeu_ps(output + 32, vy4);
    _mm256_storeu_ps(output + 40, vy5);
    _mm256_storeu_ps(output + 48, vy6);
    _mm256_storeu_ps(output + 56, vy7);
    _mm256_storeu_ps(output + 64, vy8);
    output += 72;
  }
  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    __m256 vx = _mm256_loadu_ps(input);
    input += 8;

    const __m256 vz = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx, vprescale));

    __m256 vn = _mm256_fmadd_ps(vz, vlog2e, vmagic_bias);
    const __m256i ven = _mm256_slli_epi32(_mm256_castps_si256(vn), 20);
    const __m256i vl = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn));
    __m256 vs = _mm256_castsi256_ps(_mm256_add_epi32(vl, ven));
    vn = _mm256_sub_ps(vn, vmagic_bias);

    __m256 vt = _mm256_fmadd_ps(vn, vminus_ln2, vz);

    __m256 vp = _mm256_fmadd_ps(vc4, vt, vc3);
    vp = _mm256_fmadd_ps(vp, vt, vc2);
    vp = _mm256_mul_ps(vp, vt);

    vt = _mm256_mul_ps(vt, vs);
    vs = _mm256_fmsub_ps(vs, valpha, valpha);
    vp = _mm256_fmadd_ps(vp, vt, vt);
    const __m256 ve = _mm256_fmadd_ps(vp, valpha, vs);

    vx = _mm256_mul_ps(vx, vbeta);
    const __m256 vy = _mm256_blendv_ps(vx, ve, vx);

    _mm256_storeu_ps(output, vy);
    output += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 7 * sizeof(float));
    const __m256i vmask = _mm256_loadu_si256((const __m256i*) ((uintptr_t) &params->avx2_rr1_lut8_p4.mask_table[7] - batch));

    __m256 vx = _mm256_maskload_ps(input, vmask);

    const __m256 vz = _mm256_max_ps(vsat_cutoff, _mm256_mul_ps(vx, vprescale));

    __m256 vn = _mm256_fmadd_ps(vz, vlog2e, vmagic_bias);
    const __m256i ven = _mm256_slli_epi32(_mm256_castps_si256(vn), 20);
    const __m256i vl = _mm256_permutevar8x32_epi32(vtable, _mm256_castps_si256(vn));
    __m256 vs = _mm256_castsi256_ps(_mm256_add_epi32(vl, ven));
    vn = _mm256_sub_ps(vn, vmagic_bias);

    __m256 vt = _mm256_fmadd_ps(vn, vminus_ln2, vz);

    __m256 vp = _mm256_fmadd_ps(vc4, vt, vc3);
    vp = _mm256_fmadd_ps(vp, vt, vc2);
    vp = _mm256_mul_ps(vp, vt);

    vt = _mm256_mul_ps(vt, vs);
    vs = _mm256_fmsub_ps(vs, valpha, valpha);
    vp = _mm256_fmadd_ps(vp, vt, vt);
    const __m256 ve = _mm256_fmadd_ps(vp, valpha, vs);

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
