// Auto-generated file. Do not edit!
//   Template: src/s16-rabsmax/scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <xnnpack/math.h>
#include <xnnpack/rabsmax.h>


void xnn_s16_rabsmax_ukernel__scalar_x4(
    size_t channels,
    const int16_t* input,
    uint16_t* output) {

  assert(channels > 0);
  assert(input != NULL);
  assert(output != NULL);

  int32_t vmax0 = 0;
  int32_t vmax1 = 0;
  int32_t vmax2 = 0;
  int32_t vmax3 = 0;

  size_t c = channels;
  for (; c >= 4; c -= 4) {
    const int32_t vi0 = (int32_t) input[0];
    const int32_t vi1 = (int32_t) input[1];
    const int32_t vi2 = (int32_t) input[2];
    const int32_t vi3 = (int32_t) input[3];
    input += 4;

    const int32_t vabs0 = vi0 >= 0 ? vi0 : -vi0;
    const int32_t vabs1 = vi1 >= 0 ? vi1 : -vi1;
    const int32_t vabs2 = vi2 >= 0 ? vi2 : -vi2;
    const int32_t vabs3 = vi3 >= 0 ? vi3 : -vi3;

    vmax0 = math_max_s32(vmax0, vabs0);
    vmax1 = math_max_s32(vmax1, vabs1);
    vmax2 = math_max_s32(vmax2, vabs2);
    vmax3 = math_max_s32(vmax3, vabs3);
  }

  vmax0 = math_max_s32(vmax0, vmax1);
  vmax2 = math_max_s32(vmax2, vmax3);
  vmax0 = math_max_s32(vmax0, vmax2);

  if (c != 0) {
    do {
      const int32_t vi = (int32_t) *input++;
      const int32_t vabs = vi >= 0 ? vi : -vi;
      vmax0 = math_max_s32(vmax0, vabs);
    } while (--c != 0);
  }
  *output = (uint16_t) vmax0;
}
