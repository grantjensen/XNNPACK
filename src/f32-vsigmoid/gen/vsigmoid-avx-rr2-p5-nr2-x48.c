// Auto-generated file. Do not edit!
//   Template: src/f32-vsigmoid/avx-rr2-p5.c.in
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


void xnn_f32_vsigmoid_ukernel__avx_rr2_p5_nr2_x48(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_sigmoid_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch % sizeof(float) == 0);

  const __m256 vsign_mask = _mm256_load_ps(params->avx_rr2_p5.sign_mask);
  const __m256 vmagic_bias = _mm256_load_ps(params->avx_rr2_p5.magic_bias);
  const __m256 vlog2e = _mm256_load_ps(params->avx_rr2_p5.log2e);
  const __m256 vminus_ln2_hi = _mm256_load_ps(params->avx_rr2_p5.minus_ln2_hi);
  const __m256 vminus_ln2_lo = _mm256_load_ps(params->avx_rr2_p5.minus_ln2_lo);
  const __m256 vc5 = _mm256_load_ps(params->avx_rr2_p5.c5);
  const __m256 vc4 = _mm256_load_ps(params->avx_rr2_p5.c4);
  const __m256 vc3 = _mm256_load_ps(params->avx_rr2_p5.c3);
  const __m256 vc2 = _mm256_load_ps(params->avx_rr2_p5.c2);
  const __m256 vc1 = _mm256_load_ps(params->avx_rr2_p5.c1);
  const __m256 vone = _mm256_load_ps(params->avx_rr2_p5.one);
  const __m256 vtwo = _mm256_load_ps(params->avx_rr2_p5.two);
  const __m256 vdenorm_cutoff = _mm256_load_ps(params->avx_rr2_p5.denorm_cutoff);

  for (; batch >= 48 * sizeof(float); batch -= 48 * sizeof(float)) {
    const __m256 vx0 = _mm256_loadu_ps(input);
    const __m256 vx1 = _mm256_loadu_ps(input + 8);
    const __m256 vx2 = _mm256_loadu_ps(input + 16);
    const __m256 vx3 = _mm256_loadu_ps(input + 24);
    const __m256 vx4 = _mm256_loadu_ps(input + 32);
    const __m256 vx5 = _mm256_loadu_ps(input + 40);
    input += 48;

    const __m256 vz0 = _mm256_or_ps(vx0, vsign_mask);
    const __m256 vz1 = _mm256_or_ps(vx1, vsign_mask);
    const __m256 vz2 = _mm256_or_ps(vx2, vsign_mask);
    const __m256 vz3 = _mm256_or_ps(vx3, vsign_mask);
    const __m256 vz4 = _mm256_or_ps(vx4, vsign_mask);
    const __m256 vz5 = _mm256_or_ps(vx5, vsign_mask);

    __m256 vn0 = _mm256_add_ps(_mm256_mul_ps(vz0, vlog2e), vmagic_bias);
    __m256 vn1 = _mm256_add_ps(_mm256_mul_ps(vz1, vlog2e), vmagic_bias);
    __m256 vn2 = _mm256_add_ps(_mm256_mul_ps(vz2, vlog2e), vmagic_bias);
    __m256 vn3 = _mm256_add_ps(_mm256_mul_ps(vz3, vlog2e), vmagic_bias);
    __m256 vn4 = _mm256_add_ps(_mm256_mul_ps(vz4, vlog2e), vmagic_bias);
    __m256 vn5 = _mm256_add_ps(_mm256_mul_ps(vz5, vlog2e), vmagic_bias);

    const __m128 vs_lo0 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn0)), 23));
    const __m128 vs_hi0 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(vn0, 1)), 23));
    const __m256 vs0 = _mm256_insertf128_ps(_mm256_castps128_ps256(vs_lo0), vs_hi0, 1);
    const __m128 vs_lo1 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn1)), 23));
    const __m128 vs_hi1 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(vn1, 1)), 23));
    const __m256 vs1 = _mm256_insertf128_ps(_mm256_castps128_ps256(vs_lo1), vs_hi1, 1);
    const __m128 vs_lo2 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn2)), 23));
    const __m128 vs_hi2 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(vn2, 1)), 23));
    const __m256 vs2 = _mm256_insertf128_ps(_mm256_castps128_ps256(vs_lo2), vs_hi2, 1);
    const __m128 vs_lo3 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn3)), 23));
    const __m128 vs_hi3 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(vn3, 1)), 23));
    const __m256 vs3 = _mm256_insertf128_ps(_mm256_castps128_ps256(vs_lo3), vs_hi3, 1);
    const __m128 vs_lo4 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn4)), 23));
    const __m128 vs_hi4 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(vn4, 1)), 23));
    const __m256 vs4 = _mm256_insertf128_ps(_mm256_castps128_ps256(vs_lo4), vs_hi4, 1);
    const __m128 vs_lo5 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn5)), 23));
    const __m128 vs_hi5 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(vn5, 1)), 23));
    const __m256 vs5 = _mm256_insertf128_ps(_mm256_castps128_ps256(vs_lo5), vs_hi5, 1);

    vn0 = _mm256_sub_ps(vn0, vmagic_bias);
    vn1 = _mm256_sub_ps(vn1, vmagic_bias);
    vn2 = _mm256_sub_ps(vn2, vmagic_bias);
    vn3 = _mm256_sub_ps(vn3, vmagic_bias);
    vn4 = _mm256_sub_ps(vn4, vmagic_bias);
    vn5 = _mm256_sub_ps(vn5, vmagic_bias);

    __m256 vt0 = _mm256_add_ps(_mm256_mul_ps(vn0, vminus_ln2_hi), vz0);
    __m256 vt1 = _mm256_add_ps(_mm256_mul_ps(vn1, vminus_ln2_hi), vz1);
    __m256 vt2 = _mm256_add_ps(_mm256_mul_ps(vn2, vminus_ln2_hi), vz2);
    __m256 vt3 = _mm256_add_ps(_mm256_mul_ps(vn3, vminus_ln2_hi), vz3);
    __m256 vt4 = _mm256_add_ps(_mm256_mul_ps(vn4, vminus_ln2_hi), vz4);
    __m256 vt5 = _mm256_add_ps(_mm256_mul_ps(vn5, vminus_ln2_hi), vz5);

    vt0 = _mm256_add_ps(_mm256_mul_ps(vn0, vminus_ln2_lo), vt0);
    vt1 = _mm256_add_ps(_mm256_mul_ps(vn1, vminus_ln2_lo), vt1);
    vt2 = _mm256_add_ps(_mm256_mul_ps(vn2, vminus_ln2_lo), vt2);
    vt3 = _mm256_add_ps(_mm256_mul_ps(vn3, vminus_ln2_lo), vt3);
    vt4 = _mm256_add_ps(_mm256_mul_ps(vn4, vminus_ln2_lo), vt4);
    vt5 = _mm256_add_ps(_mm256_mul_ps(vn5, vminus_ln2_lo), vt5);

    __m256 vp0 = _mm256_add_ps(_mm256_mul_ps(vc5, vt0), vc4);
    __m256 vp1 = _mm256_add_ps(_mm256_mul_ps(vc5, vt1), vc4);
    __m256 vp2 = _mm256_add_ps(_mm256_mul_ps(vc5, vt2), vc4);
    __m256 vp3 = _mm256_add_ps(_mm256_mul_ps(vc5, vt3), vc4);
    __m256 vp4 = _mm256_add_ps(_mm256_mul_ps(vc5, vt4), vc4);
    __m256 vp5 = _mm256_add_ps(_mm256_mul_ps(vc5, vt5), vc4);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc3);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc3);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc3);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc3);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc3);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc3);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc2);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc2);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc2);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc2);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc2);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc2);

    vp0 = _mm256_add_ps(_mm256_mul_ps(vp0, vt0), vc1);
    vp1 = _mm256_add_ps(_mm256_mul_ps(vp1, vt1), vc1);
    vp2 = _mm256_add_ps(_mm256_mul_ps(vp2, vt2), vc1);
    vp3 = _mm256_add_ps(_mm256_mul_ps(vp3, vt3), vc1);
    vp4 = _mm256_add_ps(_mm256_mul_ps(vp4, vt4), vc1);
    vp5 = _mm256_add_ps(_mm256_mul_ps(vp5, vt5), vc1);

    vt0 = _mm256_mul_ps(vt0, vs0);
    vt1 = _mm256_mul_ps(vt1, vs1);
    vt2 = _mm256_mul_ps(vt2, vs2);
    vt3 = _mm256_mul_ps(vt3, vs3);
    vt4 = _mm256_mul_ps(vt4, vs4);
    vt5 = _mm256_mul_ps(vt5, vs5);

    const __m256 ve0 = _mm256_add_ps(_mm256_mul_ps(vt0, vp0), vs0);
    const __m256 ve1 = _mm256_add_ps(_mm256_mul_ps(vt1, vp1), vs1);
    const __m256 ve2 = _mm256_add_ps(_mm256_mul_ps(vt2, vp2), vs2);
    const __m256 ve3 = _mm256_add_ps(_mm256_mul_ps(vt3, vp3), vs3);
    const __m256 ve4 = _mm256_add_ps(_mm256_mul_ps(vt4, vp4), vs4);
    const __m256 ve5 = _mm256_add_ps(_mm256_mul_ps(vt5, vp5), vs5);

    const __m256 vd0 = _mm256_add_ps(ve0, vone);
    const __m256 vd1 = _mm256_add_ps(ve1, vone);
    const __m256 vd2 = _mm256_add_ps(ve2, vone);
    const __m256 vd3 = _mm256_add_ps(ve3, vone);
    const __m256 vd4 = _mm256_add_ps(ve4, vone);
    const __m256 vd5 = _mm256_add_ps(ve5, vone);

    __m256 vr0 = _mm256_rcp_ps(vd0);
    __m256 vr1 = _mm256_rcp_ps(vd1);
    __m256 vr2 = _mm256_rcp_ps(vd2);
    __m256 vr3 = _mm256_rcp_ps(vd3);
    __m256 vr4 = _mm256_rcp_ps(vd4);
    __m256 vr5 = _mm256_rcp_ps(vd5);

    vr0 = _mm256_mul_ps(vr0, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr0, vd0)));
    vr0 = _mm256_mul_ps(vr0, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr0, vd0)));
    vr1 = _mm256_mul_ps(vr1, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr1, vd1)));
    vr1 = _mm256_mul_ps(vr1, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr1, vd1)));
    vr2 = _mm256_mul_ps(vr2, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr2, vd2)));
    vr2 = _mm256_mul_ps(vr2, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr2, vd2)));
    vr3 = _mm256_mul_ps(vr3, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr3, vd3)));
    vr3 = _mm256_mul_ps(vr3, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr3, vd3)));
    vr4 = _mm256_mul_ps(vr4, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr4, vd4)));
    vr4 = _mm256_mul_ps(vr4, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr4, vd4)));
    vr5 = _mm256_mul_ps(vr5, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr5, vd5)));
    vr5 = _mm256_mul_ps(vr5, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr5, vd5)));

    __m256 vf0 = _mm256_mul_ps(ve0, vr0);
    __m256 vf1 = _mm256_mul_ps(ve1, vr1);
    __m256 vf2 = _mm256_mul_ps(ve2, vr2);
    __m256 vf3 = _mm256_mul_ps(ve3, vr3);
    __m256 vf4 = _mm256_mul_ps(ve4, vr4);
    __m256 vf5 = _mm256_mul_ps(ve5, vr5);

    vf0 = _mm256_andnot_ps(_mm256_cmp_ps(vz0, vdenorm_cutoff, _CMP_LT_OS), vf0);
    vf1 = _mm256_andnot_ps(_mm256_cmp_ps(vz1, vdenorm_cutoff, _CMP_LT_OS), vf1);
    vf2 = _mm256_andnot_ps(_mm256_cmp_ps(vz2, vdenorm_cutoff, _CMP_LT_OS), vf2);
    vf3 = _mm256_andnot_ps(_mm256_cmp_ps(vz3, vdenorm_cutoff, _CMP_LT_OS), vf3);
    vf4 = _mm256_andnot_ps(_mm256_cmp_ps(vz4, vdenorm_cutoff, _CMP_LT_OS), vf4);
    vf5 = _mm256_andnot_ps(_mm256_cmp_ps(vz5, vdenorm_cutoff, _CMP_LT_OS), vf5);

    vf0 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf0), vf0, vx0);
    vf1 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf1), vf1, vx1);
    vf2 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf2), vf2, vx2);
    vf3 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf3), vf3, vx3);
    vf4 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf4), vf4, vx4);
    vf5 = _mm256_blendv_ps(_mm256_sub_ps(vone, vf5), vf5, vx5);

    _mm256_storeu_ps(output, vf0);
    _mm256_storeu_ps(output + 8, vf1);
    _mm256_storeu_ps(output + 16, vf2);
    _mm256_storeu_ps(output + 24, vf3);
    _mm256_storeu_ps(output + 32, vf4);
    _mm256_storeu_ps(output + 40, vf5);
    output += 48;
  }
  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    const __m256 vx = _mm256_loadu_ps(input);
    input += 8;

    const __m256 vz = _mm256_or_ps(vx, vsign_mask);

    __m256 vn = _mm256_add_ps(_mm256_mul_ps(vz, vlog2e), vmagic_bias);

    const __m128 vs_lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn)), 23));
    const __m128 vs_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(vn, 1)), 23));
    const __m256 vs = _mm256_insertf128_ps(_mm256_castps128_ps256(vs_lo), vs_hi, 1);

    vn = _mm256_sub_ps(vn, vmagic_bias);

    __m256 vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_hi), vz);
    vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_lo), vt);

    __m256 vp = _mm256_add_ps(_mm256_mul_ps(vc5, vt), vc4);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc3);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc2);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc1);

    vt = _mm256_mul_ps(vt, vs);
    const __m256 ve = _mm256_add_ps(_mm256_mul_ps(vt, vp), vs);

    const __m256 vd = _mm256_add_ps(ve, vone);
    __m256 vr = _mm256_rcp_ps(vd);
    vr = _mm256_mul_ps(vr, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr, vd)));
    vr = _mm256_mul_ps(vr, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr, vd)));
    __m256 vf = _mm256_mul_ps(ve, vr);

    vf = _mm256_andnot_ps(_mm256_cmp_ps(vz, vdenorm_cutoff, _CMP_LT_OS), vf);
    vf = _mm256_blendv_ps(_mm256_sub_ps(vone, vf), vf, vx);

    _mm256_storeu_ps(output, vf);
    output += 8;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 7 * sizeof(float));
    const __m256i vmask = _mm256_loadu_si256((const __m256i*) ((uintptr_t) &params->avx_rr2_p5.mask_table[7] - batch));

    const __m256 vx = _mm256_maskload_ps(input, vmask);

    const __m256 vz = _mm256_or_ps(vx, vsign_mask);

    __m256 vn = _mm256_add_ps(_mm256_mul_ps(vz, vlog2e), vmagic_bias);
    const __m128 vs_lo = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_castps256_ps128(vn)), 23));
    const __m128 vs_hi = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(_mm256_extractf128_ps(vn, 1)), 23));
    const __m256 vs = _mm256_insertf128_ps(_mm256_castps128_ps256(vs_lo), vs_hi, 1);

    vn = _mm256_sub_ps(vn, vmagic_bias);

    __m256 vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_hi), vz);
    vt = _mm256_add_ps(_mm256_mul_ps(vn, vminus_ln2_lo), vt);

    __m256 vp = _mm256_add_ps(_mm256_mul_ps(vc5, vt), vc4);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc3);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc2);
    vp = _mm256_add_ps(_mm256_mul_ps(vp, vt), vc1);

    vt = _mm256_mul_ps(vt, vs);
    const __m256 ve = _mm256_add_ps(_mm256_mul_ps(vt, vp), vs);

    const __m256 vd = _mm256_add_ps(ve, vone);
    __m256 vr = _mm256_rcp_ps(vd);
    vr = _mm256_mul_ps(vr, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr, vd)));
    vr = _mm256_mul_ps(vr, _mm256_sub_ps(vtwo, _mm256_mul_ps(vr, vd)));
    __m256 vf = _mm256_mul_ps(ve, vr);

    vf = _mm256_andnot_ps(_mm256_cmp_ps(vz, vdenorm_cutoff, _CMP_LT_OS), vf);
    vf = _mm256_blendv_ps(_mm256_sub_ps(vone, vf), vf, vx);

    __m128 vf_lo = _mm256_castps256_ps128(vf);
    if (batch & (4 * sizeof(float))) {
      _mm_storeu_ps(output, vf_lo);
      vf_lo = _mm256_extractf128_ps(vf, 1);
      output += 4;
    }
    if (batch & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) output, vf_lo);
      vf_lo = _mm_movehl_ps(vf_lo, vf_lo);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      _mm_store_ss(output, vf_lo);
    }
  }
}
