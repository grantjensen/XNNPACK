// Auto-generated file. Do not edit!
//   Template: src/f32-velu/scalar-rr2-p6.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <math.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/vunary.h>


void xnn_f32_velu_ukernel__scalar_rr2_p6_x2(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_elu_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch % sizeof(float) == 0);

  const float vprescale = params->scalar_rr2_p6.prescale;
  const float valpha = params->scalar_rr2_p6.alpha;
  const float vbeta = params->scalar_rr2_p6.beta;
  const float vmagic_bias = params->scalar_rr2_p6.magic_bias;
  const float vlog2e = params->scalar_rr2_p6.log2e;
  const float vsat_cutoff = params->scalar_rr2_p6.sat_cutoff;
  const float vminus_ln2_hi = params->scalar_rr2_p6.minus_ln2_hi;
  const float vminus_ln2_lo = params->scalar_rr2_p6.minus_ln2_lo;
  const float vc6 = params->scalar_rr2_p6.c6;
  const float vc5 = params->scalar_rr2_p6.c5;
  const float vc4 = params->scalar_rr2_p6.c4;
  const float vc3 = params->scalar_rr2_p6.c3;
  const float vc2 = params->scalar_rr2_p6.c2;
  const float vone = params->scalar_rr2_p6.one;

  for (; batch >= 2 * sizeof(float); batch -= 2 * sizeof(float)) {
    float vx0 = input[0];
    float vx1 = input[1];
    input += 2;

    const float vz0 = vx0 * vprescale;
    const float vz1 = vx1 * vprescale;

    float vn0 = vz0 * vlog2e + vmagic_bias;
    float vn1 = vz1 * vlog2e + vmagic_bias;

    float vs0 = uint32_as_float(float_as_uint32(vn0) << 23);
    vn0 -= vmagic_bias;
    float vs1 = uint32_as_float(float_as_uint32(vn1) << 23);
    vn1 -= vmagic_bias;

    float vt0 = vn0 * vminus_ln2_hi + vz0;
    float vt1 = vn1 * vminus_ln2_hi + vz1;

    vt0 = vn0 * vminus_ln2_lo + vt0;
    vt1 = vn1 * vminus_ln2_lo + vt1;

    if XNN_UNPREDICTABLE(vz0 <= vsat_cutoff) {
      vs0 = 0.0f;
      vt0 = 0.0f;
    }
    if XNN_UNPREDICTABLE(vz1 <= vsat_cutoff) {
      vs1 = 0.0f;
      vt1 = 0.0f;
    }

    float vp0 = vc6 * vt0 + vc5;
    float vp1 = vc6 * vt1 + vc5;

    vp0 = vp0 * vt0 + vc4;
    vp1 = vp1 * vt1 + vc4;

    vp0 = vp0 * vt0 + vc3;
    vp1 = vp1 * vt1 + vc3;

    vp0 = vp0 * vt0 + vc2;
    vp1 = vp1 * vt1 + vc2;

    vp0 *= vt0;
    vp1 *= vt1;

    vt0 *= vs0;
    vs0 -= vone;
    vt1 *= vs1;
    vs1 -= vone;

    vp0 = vp0 * vt0 + vt0;
    vp1 = vp1 * vt1 + vt1;

    const float ve0 = (vp0 + vs0) * valpha;
    float vy0 = vx0 * vbeta;
    const float ve1 = (vp1 + vs1) * valpha;
    float vy1 = vx1 * vbeta;

    if XNN_UNPREDICTABLE(vx0 < 0.0f) {
      vy0 = ve0;
    }
    if XNN_UNPREDICTABLE(vx1 < 0.0f) {
      vy1 = ve1;
    }

    output[0] = vy0;
    output[1] = vy1;
    output += 2;
  }
  if XNN_UNLIKELY(batch != 0) {
    float vx = *input;

    const float vz = vx * vprescale;

    float vn = vz * vlog2e + vmagic_bias;
    float vs = uint32_as_float(float_as_uint32(vn) << 23);
    vn -= vmagic_bias;

    float vt = vn * vminus_ln2_hi + vz;
    vt = vn * vminus_ln2_lo + vt;

    if XNN_UNPREDICTABLE(vz <= vsat_cutoff) {
      vs = 0.0f;
      vt = 0.0f;
    }

    float vp = vc6 * vt + vc5;
    vp = vp * vt + vc4;
    vp = vp * vt + vc3;
    vp = vp * vt + vc2;
    vp *= vt;

    vt *= vs;
    vs -= vone;
    vp = vp * vt + vt;
    const float ve = (vp + vs) * valpha;

    float vy = vx * vbeta;
    if XNN_UNPREDICTABLE(vx < 0.0f) {
      vy = ve;
    }

    *output = vy;
  }
}
