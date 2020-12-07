#ifndef _PBGL_PUSH_H
#define _PBGL_PUSH_H

/* this push helper library is part of XGU */

#include <stdint.h>
#include <assert.h>
#include <pbkit/pbkit.h>

#define NV097_SET_SPECULAR_ENABLE 0x000003B8
#define NV097_SET_CONTROL0_TEXTUREPERSPECTIVE 0x100000

static inline uint32_t *push_command(uint32_t *p, uint32_t command, unsigned int parameter_count) {
  pb_push(p++, command, parameter_count);
  return p;
}

static inline uint32_t *push_parameter(uint32_t *p, uint32_t parameter) {
  *p++ = parameter;
  return p;
}

static inline uint32_t *push_parameters(uint32_t *p, const uint32_t *parameters, unsigned int count) {
  for(unsigned int i  =  0; i < count; i++)
    p = push_parameter(p, parameters[i]);
  return p;
}

static inline uint32_t *push_boolean(uint32_t *p, bool enabled) {
  return push_parameter(p, !!enabled);
}

static inline uint32_t *push_command_boolean(uint32_t *p, uint32_t command, bool enabled) {
  p = push_command(p, command, 1);
  p = push_boolean(p, enabled);
  return p;
}

static inline uint32_t *push_float(uint32_t *p, float f) {
  return push_parameter(p, *(uint32_t*)&f);
}

static inline uint32_t *push_floats(uint32_t *p, const float *f, unsigned int count) {
  return push_parameters(p, (const uint32_t*)f, count);
}

static inline uint32_t *push_matrix2x2(uint32_t *p, const float m[2 * 2]) {
  return push_floats(p, m, 2 * 2);
}

static inline uint32_t *push_matrix4x4(uint32_t *p, const float m[4 * 4]) {
  return push_floats(p, m, 4 * 4);
}

static inline uint32_t *push_matrix2x2_transposed(uint32_t *p, const float m[2 * 2]) {
  *((float *)p++) = m[0 * 2 + 0];
  *((float *)p++) = m[1 * 2 + 0];

  *((float *)p++) = m[0 * 2 + 1];
  *((float *)p++) = m[1 * 2 + 1];

  return p;
}

static inline uint32_t *push_matrix4x4_transposed(uint32_t *p, const float m[4 * 4]) {
  *((float *)p++) = m[0 * 4 + 0];
  *((float *)p++) = m[1 * 4 + 0];
  *((float *)p++) = m[2 * 4 + 0];
  *((float *)p++) = m[3 * 4 + 0];

  *((float *)p++) = m[0 * 4 + 1];
  *((float *)p++) = m[1 * 4 + 1];
  *((float *)p++) = m[2 * 4 + 1];
  *((float *)p++) = m[3 * 4 + 1];

  *((float *)p++) = m[0 * 4 + 2];
  *((float *)p++) = m[1 * 4 + 2];
  *((float *)p++) = m[2 * 4 + 2];
  *((float *)p++) = m[3 * 4 + 2];

  *((float *)p++) = m[0 * 4 + 3];
  *((float *)p++) = m[1 * 4 + 3];
  *((float *)p++) = m[2 * 4 + 3];
  *((float *)p++) = m[3 * 4 + 3];

  return p;
}

static inline uint32_t *push_command_matrix2x2(uint32_t *p, uint32_t command, const float m[2 * 2]) {
  p = push_command(p, command, 2 * 2);
  p = push_matrix2x2(p, m);
  return p;
}

static inline uint32_t *push_command_matrix4x4(uint32_t *p, uint32_t command, const float m[4 * 4]) {
  p = push_command(p, command, 4 * 4);
  p = push_matrix4x4(p, m);
  return p;
}

static inline uint32_t *push_command_matrix2x2_transposed(uint32_t *p, uint32_t command, const float m[2 * 2]) {
  p = push_command(p, command, 2 * 2);
  p = push_matrix2x2_transposed(p, m);
  return p;
}

static inline uint32_t *push_command_matrix4x4_transposed(uint32_t *p, uint32_t command, const float m[4 * 4]) {
  p = push_command(p, command, 4 * 4);
  p = push_matrix4x4_transposed(p, m);
  return p;
}

static inline uint32_t *push_command_parameter(uint32_t *p, uint32_t command, uint32_t parameter) {
  p = push_command(p, command, 1);
  p = push_parameter(p, parameter);
  return p;
}

static inline uint32_t *push_command_float(uint32_t *p, uint32_t command, float parameter) {
  p = push_command(p, command, 1);
  p = push_float(p, parameter);
  return p;
}

static inline uint32_t *push_command_float2(uint32_t *p, uint32_t command, float parameter1, float parameter2) {
  p = push_command(p, command, 2);
  p = push_float(p, parameter1);
  p = push_float(p, parameter2);
  return p;
}

#endif // _PBGL_PUSH_H
