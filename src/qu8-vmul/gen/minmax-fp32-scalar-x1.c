// Auto-generated file. Do not edit!
//   Template: src/qs8-vmul/scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <xnnpack/math.h>
#include <xnnpack/vmul.h>


void xnn_qu8_vmul_minmax_fp32_ukernel__scalar_x1(
    size_t batch,
    const uint8_t* input_a,
    const uint8_t* input_b,
    uint8_t* output,
    const union xnn_qu8_mul_minmax_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  const int32_t va_zero_point = params->fp32_scalar.a_zero_point;
  const int32_t vb_zero_point = params->fp32_scalar.b_zero_point;
  const float vscale = params->fp32_scalar.scale;
  const float voutput_min_less_zero_point = params->fp32_scalar.output_min_less_zero_point;
  const float voutput_max_less_zero_point = params->fp32_scalar.output_max_less_zero_point;
  const float vmagic_bias = params->fp32_scalar.magic_bias;
  const int32_t vmagic_bias_less_output_zero_point = params->fp32_scalar.magic_bias_less_output_zero_point;

  do {
    const int32_t va = (int32_t) *input_a++ - va_zero_point;
    const int32_t vb = (int32_t) *input_b++ - vb_zero_point;
    const int32_t vacc = va * vb;

    float vfpacc = (float) vacc * vscale;
    vfpacc = math_max_f32(vfpacc, voutput_min_less_zero_point);
    vfpacc = math_min_f32(vfpacc, voutput_max_less_zero_point);
    vfpacc += vmagic_bias;
    const int32_t vout = (int32_t) float_as_uint32(vfpacc) - vmagic_bias_less_output_zero_point;
    *output++ = (uint8_t) vout;

    batch -= sizeof(uint8_t);
  } while (batch != 0);
}
