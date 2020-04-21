/*===---- arm_mve.h - ARM MVE intrinsics -----------------------------------===
 *
 *
 * Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
 * See https://llvm.org/LICENSE.txt for license information.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __ARM_MVE_H
#define __ARM_MVE_H

#if !__ARM_FEATURE_MVE
#error "MVE support not enabled"
#endif

#include <stdint.h>

typedef uint16_t mve_pred16_t;
typedef __attribute__((neon_vector_type(8))) int16_t int16x8_t;
typedef struct { int16x8_t val[2]; } int16x8x2_t;
typedef struct { int16x8_t val[4]; } int16x8x4_t;
typedef __attribute__((neon_vector_type(4))) int32_t int32x4_t;
typedef struct { int32x4_t val[2]; } int32x4x2_t;
typedef struct { int32x4_t val[4]; } int32x4x4_t;
typedef __attribute__((neon_vector_type(2))) int64_t int64x2_t;
typedef struct { int64x2_t val[2]; } int64x2x2_t;
typedef struct { int64x2_t val[4]; } int64x2x4_t;
typedef __attribute__((neon_vector_type(16))) int8_t int8x16_t;
typedef struct { int8x16_t val[2]; } int8x16x2_t;
typedef struct { int8x16_t val[4]; } int8x16x4_t;
typedef __attribute__((neon_vector_type(8))) uint16_t uint16x8_t;
typedef struct { uint16x8_t val[2]; } uint16x8x2_t;
typedef struct { uint16x8_t val[4]; } uint16x8x4_t;
typedef __attribute__((neon_vector_type(4))) uint32_t uint32x4_t;
typedef struct { uint32x4_t val[2]; } uint32x4x2_t;
typedef struct { uint32x4_t val[4]; } uint32x4x4_t;
typedef __attribute__((neon_vector_type(2))) uint64_t uint64x2_t;
typedef struct { uint64x2_t val[2]; } uint64x2x2_t;
typedef struct { uint64x2_t val[4]; } uint64x2x4_t;
typedef __attribute__((neon_vector_type(16))) uint8_t uint8x16_t;
typedef struct { uint8x16_t val[2]; } uint8x16x2_t;
typedef struct { uint8x16_t val[4]; } uint8x16x4_t;

static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_asrl)))
int64_t __arm_asrl(int64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_lsll)))
uint64_t __arm_lsll(uint64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqrshr)))
int32_t __arm_sqrshr(int32_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqrshrl)))
int64_t __arm_sqrshrl(int64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqrshrl_sat48)))
int64_t __arm_sqrshrl_sat48(int64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqshl)))
int32_t __arm_sqshl(int32_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqshll)))
int64_t __arm_sqshll(int64_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_srshr)))
int32_t __arm_srshr(int32_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_srshrl)))
int64_t __arm_srshrl(int64_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqrshl)))
uint32_t __arm_uqrshl(uint32_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqrshll)))
uint64_t __arm_uqrshll(uint64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqrshll_sat48)))
uint64_t __arm_uqrshll_sat48(uint64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqshl)))
uint32_t __arm_uqshl(uint32_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqshll)))
uint64_t __arm_uqshll(uint64_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_urshr)))
uint32_t __arm_urshr(uint32_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_urshrl)))
uint64_t __arm_urshrl(uint64_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s16)))
uint32_t __arm_vabavq_p_s16(uint32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s16)))
uint32_t __arm_vabavq_p(uint32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s32)))
uint32_t __arm_vabavq_p_s32(uint32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s32)))
uint32_t __arm_vabavq_p(uint32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s8)))
uint32_t __arm_vabavq_p_s8(uint32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s8)))
uint32_t __arm_vabavq_p(uint32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u16)))
uint32_t __arm_vabavq_p_u16(uint32_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u16)))
uint32_t __arm_vabavq_p(uint32_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u32)))
uint32_t __arm_vabavq_p_u32(uint32_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u32)))
uint32_t __arm_vabavq_p(uint32_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u8)))
uint32_t __arm_vabavq_p_u8(uint32_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u8)))
uint32_t __arm_vabavq_p(uint32_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_s16)))
uint32_t __arm_vabavq_s16(uint32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_s16)))
uint32_t __arm_vabavq(uint32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_s32)))
uint32_t __arm_vabavq_s32(uint32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_s32)))
uint32_t __arm_vabavq(uint32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_s8)))
uint32_t __arm_vabavq_s8(uint32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_s8)))
uint32_t __arm_vabavq(uint32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_u16)))
uint32_t __arm_vabavq_u16(uint32_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_u16)))
uint32_t __arm_vabavq(uint32_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_u32)))
uint32_t __arm_vabavq_u32(uint32_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_u32)))
uint32_t __arm_vabavq(uint32_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_u8)))
uint32_t __arm_vabavq_u8(uint32_t, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_u8)))
uint32_t __arm_vabavq(uint32_t, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s16)))
int16x8_t __arm_vabdq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s16)))
int16x8_t __arm_vabdq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s32)))
int32x4_t __arm_vabdq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s32)))
int32x4_t __arm_vabdq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s8)))
int8x16_t __arm_vabdq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s8)))
int8x16_t __arm_vabdq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u16)))
uint16x8_t __arm_vabdq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u16)))
uint16x8_t __arm_vabdq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u32)))
uint32x4_t __arm_vabdq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u32)))
uint32x4_t __arm_vabdq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u8)))
uint8x16_t __arm_vabdq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u8)))
uint8x16_t __arm_vabdq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_s16)))
int16x8_t __arm_vabdq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_s16)))
int16x8_t __arm_vabdq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_s32)))
int32x4_t __arm_vabdq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_s32)))
int32x4_t __arm_vabdq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_s8)))
int8x16_t __arm_vabdq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_s8)))
int8x16_t __arm_vabdq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_u16)))
uint16x8_t __arm_vabdq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_u16)))
uint16x8_t __arm_vabdq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_u32)))
uint32x4_t __arm_vabdq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_u32)))
uint32x4_t __arm_vabdq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_u8)))
uint8x16_t __arm_vabdq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_u8)))
uint8x16_t __arm_vabdq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s16)))
int16x8_t __arm_vabdq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s16)))
int16x8_t __arm_vabdq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s32)))
int32x4_t __arm_vabdq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s32)))
int32x4_t __arm_vabdq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s8)))
int8x16_t __arm_vabdq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s8)))
int8x16_t __arm_vabdq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u16)))
uint16x8_t __arm_vabdq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u16)))
uint16x8_t __arm_vabdq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u32)))
uint32x4_t __arm_vabdq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u32)))
uint32x4_t __arm_vabdq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u8)))
uint8x16_t __arm_vabdq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u8)))
uint8x16_t __arm_vabdq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadciq_m_s32)))
int32x4_t __arm_vadciq_m_s32(int32x4_t, int32x4_t, int32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadciq_m_s32)))
int32x4_t __arm_vadciq_m(int32x4_t, int32x4_t, int32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadciq_m_u32)))
uint32x4_t __arm_vadciq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadciq_m_u32)))
uint32x4_t __arm_vadciq_m(uint32x4_t, uint32x4_t, uint32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadciq_s32)))
int32x4_t __arm_vadciq_s32(int32x4_t, int32x4_t, unsigned *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadciq_s32)))
int32x4_t __arm_vadciq(int32x4_t, int32x4_t, unsigned *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadciq_u32)))
uint32x4_t __arm_vadciq_u32(uint32x4_t, uint32x4_t, unsigned *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadciq_u32)))
uint32x4_t __arm_vadciq(uint32x4_t, uint32x4_t, unsigned *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadcq_m_s32)))
int32x4_t __arm_vadcq_m_s32(int32x4_t, int32x4_t, int32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadcq_m_s32)))
int32x4_t __arm_vadcq_m(int32x4_t, int32x4_t, int32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadcq_m_u32)))
uint32x4_t __arm_vadcq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadcq_m_u32)))
uint32x4_t __arm_vadcq_m(uint32x4_t, uint32x4_t, uint32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadcq_s32)))
int32x4_t __arm_vadcq_s32(int32x4_t, int32x4_t, unsigned *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadcq_s32)))
int32x4_t __arm_vadcq(int32x4_t, int32x4_t, unsigned *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadcq_u32)))
uint32x4_t __arm_vadcq_u32(uint32x4_t, uint32x4_t, unsigned *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadcq_u32)))
uint32x4_t __arm_vadcq(uint32x4_t, uint32x4_t, unsigned *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s16)))
int16x8_t __arm_vaddq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s16)))
int16x8_t __arm_vaddq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s32)))
int32x4_t __arm_vaddq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s32)))
int32x4_t __arm_vaddq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s8)))
int8x16_t __arm_vaddq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s8)))
int8x16_t __arm_vaddq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u16)))
uint16x8_t __arm_vaddq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u16)))
uint16x8_t __arm_vaddq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u32)))
uint32x4_t __arm_vaddq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u32)))
uint32x4_t __arm_vaddq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u8)))
uint8x16_t __arm_vaddq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u8)))
uint8x16_t __arm_vaddq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_s16)))
int16x8_t __arm_vaddq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_s16)))
int16x8_t __arm_vaddq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_s32)))
int32x4_t __arm_vaddq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_s32)))
int32x4_t __arm_vaddq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_s8)))
int8x16_t __arm_vaddq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_s8)))
int8x16_t __arm_vaddq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_u16)))
uint16x8_t __arm_vaddq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_u16)))
uint16x8_t __arm_vaddq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_u32)))
uint32x4_t __arm_vaddq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_u32)))
uint32x4_t __arm_vaddq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_u8)))
uint8x16_t __arm_vaddq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_u8)))
uint8x16_t __arm_vaddq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s16)))
int16x8_t __arm_vaddq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s16)))
int16x8_t __arm_vaddq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s32)))
int32x4_t __arm_vaddq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s32)))
int32x4_t __arm_vaddq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s8)))
int8x16_t __arm_vaddq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s8)))
int8x16_t __arm_vaddq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u16)))
uint16x8_t __arm_vaddq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u16)))
uint16x8_t __arm_vaddq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u32)))
uint32x4_t __arm_vaddq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u32)))
uint32x4_t __arm_vaddq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u8)))
uint8x16_t __arm_vaddq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u8)))
uint8x16_t __arm_vaddq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s16)))
int16x8_t __arm_vandq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s16)))
int16x8_t __arm_vandq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s32)))
int32x4_t __arm_vandq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s32)))
int32x4_t __arm_vandq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s8)))
int8x16_t __arm_vandq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s8)))
int8x16_t __arm_vandq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u16)))
uint16x8_t __arm_vandq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u16)))
uint16x8_t __arm_vandq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u32)))
uint32x4_t __arm_vandq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u32)))
uint32x4_t __arm_vandq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u8)))
uint8x16_t __arm_vandq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u8)))
uint8x16_t __arm_vandq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_s16)))
int16x8_t __arm_vandq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_s16)))
int16x8_t __arm_vandq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_s32)))
int32x4_t __arm_vandq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_s32)))
int32x4_t __arm_vandq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_s8)))
int8x16_t __arm_vandq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_s8)))
int8x16_t __arm_vandq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_u16)))
uint16x8_t __arm_vandq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_u16)))
uint16x8_t __arm_vandq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_u32)))
uint32x4_t __arm_vandq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_u32)))
uint32x4_t __arm_vandq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_u8)))
uint8x16_t __arm_vandq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_u8)))
uint8x16_t __arm_vandq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s16)))
int16x8_t __arm_vandq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s16)))
int16x8_t __arm_vandq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s32)))
int32x4_t __arm_vandq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s32)))
int32x4_t __arm_vandq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s8)))
int8x16_t __arm_vandq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s8)))
int8x16_t __arm_vandq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u16)))
uint16x8_t __arm_vandq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u16)))
uint16x8_t __arm_vandq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u32)))
uint32x4_t __arm_vandq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u32)))
uint32x4_t __arm_vandq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u8)))
uint8x16_t __arm_vandq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u8)))
uint8x16_t __arm_vandq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s16)))
int16x8_t __arm_vbicq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s16)))
int16x8_t __arm_vbicq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s32)))
int32x4_t __arm_vbicq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s32)))
int32x4_t __arm_vbicq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s8)))
int8x16_t __arm_vbicq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s8)))
int8x16_t __arm_vbicq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u16)))
uint16x8_t __arm_vbicq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u16)))
uint16x8_t __arm_vbicq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u32)))
uint32x4_t __arm_vbicq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u32)))
uint32x4_t __arm_vbicq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u8)))
uint8x16_t __arm_vbicq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u8)))
uint8x16_t __arm_vbicq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_s16)))
int16x8_t __arm_vbicq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_s16)))
int16x8_t __arm_vbicq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_s32)))
int32x4_t __arm_vbicq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_s32)))
int32x4_t __arm_vbicq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_s8)))
int8x16_t __arm_vbicq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_s8)))
int8x16_t __arm_vbicq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_u16)))
uint16x8_t __arm_vbicq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_u16)))
uint16x8_t __arm_vbicq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_u32)))
uint32x4_t __arm_vbicq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_u32)))
uint32x4_t __arm_vbicq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_u8)))
uint8x16_t __arm_vbicq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_u8)))
uint8x16_t __arm_vbicq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s16)))
int16x8_t __arm_vbicq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s16)))
int16x8_t __arm_vbicq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s32)))
int32x4_t __arm_vbicq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s32)))
int32x4_t __arm_vbicq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s8)))
int8x16_t __arm_vbicq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s8)))
int8x16_t __arm_vbicq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u16)))
uint16x8_t __arm_vbicq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u16)))
uint16x8_t __arm_vbicq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u32)))
uint32x4_t __arm_vbicq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u32)))
uint32x4_t __arm_vbicq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u8)))
uint8x16_t __arm_vbicq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u8)))
uint8x16_t __arm_vbicq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s16)))
int16x8_t __arm_vcaddq_rot270_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s16)))
int16x8_t __arm_vcaddq_rot270_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s32)))
int32x4_t __arm_vcaddq_rot270_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s32)))
int32x4_t __arm_vcaddq_rot270_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s8)))
int8x16_t __arm_vcaddq_rot270_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s8)))
int8x16_t __arm_vcaddq_rot270_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u16)))
uint16x8_t __arm_vcaddq_rot270_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u16)))
uint16x8_t __arm_vcaddq_rot270_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u32)))
uint32x4_t __arm_vcaddq_rot270_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u32)))
uint32x4_t __arm_vcaddq_rot270_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u8)))
uint8x16_t __arm_vcaddq_rot270_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u8)))
uint8x16_t __arm_vcaddq_rot270_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s16)))
int16x8_t __arm_vcaddq_rot270_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s16)))
int16x8_t __arm_vcaddq_rot270(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s32)))
int32x4_t __arm_vcaddq_rot270_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s32)))
int32x4_t __arm_vcaddq_rot270(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s8)))
int8x16_t __arm_vcaddq_rot270_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s8)))
int8x16_t __arm_vcaddq_rot270(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u16)))
uint16x8_t __arm_vcaddq_rot270_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u16)))
uint16x8_t __arm_vcaddq_rot270(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u32)))
uint32x4_t __arm_vcaddq_rot270_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u32)))
uint32x4_t __arm_vcaddq_rot270(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u8)))
uint8x16_t __arm_vcaddq_rot270_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u8)))
uint8x16_t __arm_vcaddq_rot270(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s16)))
int16x8_t __arm_vcaddq_rot270_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s16)))
int16x8_t __arm_vcaddq_rot270_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s32)))
int32x4_t __arm_vcaddq_rot270_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s32)))
int32x4_t __arm_vcaddq_rot270_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s8)))
int8x16_t __arm_vcaddq_rot270_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s8)))
int8x16_t __arm_vcaddq_rot270_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u16)))
uint16x8_t __arm_vcaddq_rot270_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u16)))
uint16x8_t __arm_vcaddq_rot270_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u32)))
uint32x4_t __arm_vcaddq_rot270_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u32)))
uint32x4_t __arm_vcaddq_rot270_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u8)))
uint8x16_t __arm_vcaddq_rot270_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u8)))
uint8x16_t __arm_vcaddq_rot270_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s16)))
int16x8_t __arm_vcaddq_rot90_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s16)))
int16x8_t __arm_vcaddq_rot90_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s32)))
int32x4_t __arm_vcaddq_rot90_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s32)))
int32x4_t __arm_vcaddq_rot90_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s8)))
int8x16_t __arm_vcaddq_rot90_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s8)))
int8x16_t __arm_vcaddq_rot90_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u16)))
uint16x8_t __arm_vcaddq_rot90_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u16)))
uint16x8_t __arm_vcaddq_rot90_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u32)))
uint32x4_t __arm_vcaddq_rot90_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u32)))
uint32x4_t __arm_vcaddq_rot90_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u8)))
uint8x16_t __arm_vcaddq_rot90_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u8)))
uint8x16_t __arm_vcaddq_rot90_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s16)))
int16x8_t __arm_vcaddq_rot90_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s16)))
int16x8_t __arm_vcaddq_rot90(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s32)))
int32x4_t __arm_vcaddq_rot90_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s32)))
int32x4_t __arm_vcaddq_rot90(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s8)))
int8x16_t __arm_vcaddq_rot90_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s8)))
int8x16_t __arm_vcaddq_rot90(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u16)))
uint16x8_t __arm_vcaddq_rot90_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u16)))
uint16x8_t __arm_vcaddq_rot90(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u32)))
uint32x4_t __arm_vcaddq_rot90_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u32)))
uint32x4_t __arm_vcaddq_rot90(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u8)))
uint8x16_t __arm_vcaddq_rot90_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u8)))
uint8x16_t __arm_vcaddq_rot90(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s16)))
int16x8_t __arm_vcaddq_rot90_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s16)))
int16x8_t __arm_vcaddq_rot90_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s32)))
int32x4_t __arm_vcaddq_rot90_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s32)))
int32x4_t __arm_vcaddq_rot90_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s8)))
int8x16_t __arm_vcaddq_rot90_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s8)))
int8x16_t __arm_vcaddq_rot90_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u16)))
uint16x8_t __arm_vcaddq_rot90_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u16)))
uint16x8_t __arm_vcaddq_rot90_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u32)))
uint32x4_t __arm_vcaddq_rot90_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u32)))
uint32x4_t __arm_vcaddq_rot90_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u8)))
uint8x16_t __arm_vcaddq_rot90_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u8)))
uint8x16_t __arm_vcaddq_rot90_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u16)))
mve_pred16_t __arm_vcmpcsq_m_n_u16(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u16)))
mve_pred16_t __arm_vcmpcsq_m(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u32)))
mve_pred16_t __arm_vcmpcsq_m_n_u32(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u32)))
mve_pred16_t __arm_vcmpcsq_m(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u8)))
mve_pred16_t __arm_vcmpcsq_m_n_u8(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u8)))
mve_pred16_t __arm_vcmpcsq_m(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u16)))
mve_pred16_t __arm_vcmpcsq_m_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u16)))
mve_pred16_t __arm_vcmpcsq_m(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u32)))
mve_pred16_t __arm_vcmpcsq_m_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u32)))
mve_pred16_t __arm_vcmpcsq_m(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u8)))
mve_pred16_t __arm_vcmpcsq_m_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u8)))
mve_pred16_t __arm_vcmpcsq_m(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u16)))
mve_pred16_t __arm_vcmpcsq_n_u16(uint16x8_t, uint16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u16)))
mve_pred16_t __arm_vcmpcsq(uint16x8_t, uint16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u32)))
mve_pred16_t __arm_vcmpcsq_n_u32(uint32x4_t, uint32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u32)))
mve_pred16_t __arm_vcmpcsq(uint32x4_t, uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u8)))
mve_pred16_t __arm_vcmpcsq_n_u8(uint8x16_t, uint8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u8)))
mve_pred16_t __arm_vcmpcsq(uint8x16_t, uint8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u16)))
mve_pred16_t __arm_vcmpcsq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u16)))
mve_pred16_t __arm_vcmpcsq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u32)))
mve_pred16_t __arm_vcmpcsq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u32)))
mve_pred16_t __arm_vcmpcsq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u8)))
mve_pred16_t __arm_vcmpcsq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u8)))
mve_pred16_t __arm_vcmpcsq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s16)))
mve_pred16_t __arm_vcmpeqq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s16)))
mve_pred16_t __arm_vcmpeqq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s32)))
mve_pred16_t __arm_vcmpeqq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s32)))
mve_pred16_t __arm_vcmpeqq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s8)))
mve_pred16_t __arm_vcmpeqq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s8)))
mve_pred16_t __arm_vcmpeqq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u16)))
mve_pred16_t __arm_vcmpeqq_m_n_u16(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u16)))
mve_pred16_t __arm_vcmpeqq_m(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u32)))
mve_pred16_t __arm_vcmpeqq_m_n_u32(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u32)))
mve_pred16_t __arm_vcmpeqq_m(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u8)))
mve_pred16_t __arm_vcmpeqq_m_n_u8(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u8)))
mve_pred16_t __arm_vcmpeqq_m(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s16)))
mve_pred16_t __arm_vcmpeqq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s16)))
mve_pred16_t __arm_vcmpeqq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s32)))
mve_pred16_t __arm_vcmpeqq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s32)))
mve_pred16_t __arm_vcmpeqq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s8)))
mve_pred16_t __arm_vcmpeqq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s8)))
mve_pred16_t __arm_vcmpeqq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u16)))
mve_pred16_t __arm_vcmpeqq_m_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u16)))
mve_pred16_t __arm_vcmpeqq_m(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u32)))
mve_pred16_t __arm_vcmpeqq_m_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u32)))
mve_pred16_t __arm_vcmpeqq_m(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u8)))
mve_pred16_t __arm_vcmpeqq_m_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u8)))
mve_pred16_t __arm_vcmpeqq_m(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s16)))
mve_pred16_t __arm_vcmpeqq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s16)))
mve_pred16_t __arm_vcmpeqq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s32)))
mve_pred16_t __arm_vcmpeqq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s32)))
mve_pred16_t __arm_vcmpeqq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s8)))
mve_pred16_t __arm_vcmpeqq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s8)))
mve_pred16_t __arm_vcmpeqq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u16)))
mve_pred16_t __arm_vcmpeqq_n_u16(uint16x8_t, uint16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u16)))
mve_pred16_t __arm_vcmpeqq(uint16x8_t, uint16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u32)))
mve_pred16_t __arm_vcmpeqq_n_u32(uint32x4_t, uint32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u32)))
mve_pred16_t __arm_vcmpeqq(uint32x4_t, uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u8)))
mve_pred16_t __arm_vcmpeqq_n_u8(uint8x16_t, uint8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u8)))
mve_pred16_t __arm_vcmpeqq(uint8x16_t, uint8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s16)))
mve_pred16_t __arm_vcmpeqq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s16)))
mve_pred16_t __arm_vcmpeqq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s32)))
mve_pred16_t __arm_vcmpeqq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s32)))
mve_pred16_t __arm_vcmpeqq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s8)))
mve_pred16_t __arm_vcmpeqq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s8)))
mve_pred16_t __arm_vcmpeqq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u16)))
mve_pred16_t __arm_vcmpeqq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u16)))
mve_pred16_t __arm_vcmpeqq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u32)))
mve_pred16_t __arm_vcmpeqq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u32)))
mve_pred16_t __arm_vcmpeqq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u8)))
mve_pred16_t __arm_vcmpeqq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u8)))
mve_pred16_t __arm_vcmpeqq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s16)))
mve_pred16_t __arm_vcmpgeq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s16)))
mve_pred16_t __arm_vcmpgeq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s32)))
mve_pred16_t __arm_vcmpgeq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s32)))
mve_pred16_t __arm_vcmpgeq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s8)))
mve_pred16_t __arm_vcmpgeq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s8)))
mve_pred16_t __arm_vcmpgeq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s16)))
mve_pred16_t __arm_vcmpgeq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s16)))
mve_pred16_t __arm_vcmpgeq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s32)))
mve_pred16_t __arm_vcmpgeq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s32)))
mve_pred16_t __arm_vcmpgeq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s8)))
mve_pred16_t __arm_vcmpgeq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s8)))
mve_pred16_t __arm_vcmpgeq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s16)))
mve_pred16_t __arm_vcmpgeq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s16)))
mve_pred16_t __arm_vcmpgeq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s32)))
mve_pred16_t __arm_vcmpgeq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s32)))
mve_pred16_t __arm_vcmpgeq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s8)))
mve_pred16_t __arm_vcmpgeq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s8)))
mve_pred16_t __arm_vcmpgeq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s16)))
mve_pred16_t __arm_vcmpgeq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s16)))
mve_pred16_t __arm_vcmpgeq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s32)))
mve_pred16_t __arm_vcmpgeq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s32)))
mve_pred16_t __arm_vcmpgeq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s8)))
mve_pred16_t __arm_vcmpgeq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s8)))
mve_pred16_t __arm_vcmpgeq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s16)))
mve_pred16_t __arm_vcmpgtq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s16)))
mve_pred16_t __arm_vcmpgtq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s32)))
mve_pred16_t __arm_vcmpgtq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s32)))
mve_pred16_t __arm_vcmpgtq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s8)))
mve_pred16_t __arm_vcmpgtq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s8)))
mve_pred16_t __arm_vcmpgtq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s16)))
mve_pred16_t __arm_vcmpgtq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s16)))
mve_pred16_t __arm_vcmpgtq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s32)))
mve_pred16_t __arm_vcmpgtq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s32)))
mve_pred16_t __arm_vcmpgtq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s8)))
mve_pred16_t __arm_vcmpgtq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s8)))
mve_pred16_t __arm_vcmpgtq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s16)))
mve_pred16_t __arm_vcmpgtq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s16)))
mve_pred16_t __arm_vcmpgtq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s32)))
mve_pred16_t __arm_vcmpgtq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s32)))
mve_pred16_t __arm_vcmpgtq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s8)))
mve_pred16_t __arm_vcmpgtq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s8)))
mve_pred16_t __arm_vcmpgtq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s16)))
mve_pred16_t __arm_vcmpgtq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s16)))
mve_pred16_t __arm_vcmpgtq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s32)))
mve_pred16_t __arm_vcmpgtq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s32)))
mve_pred16_t __arm_vcmpgtq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s8)))
mve_pred16_t __arm_vcmpgtq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s8)))
mve_pred16_t __arm_vcmpgtq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u16)))
mve_pred16_t __arm_vcmphiq_m_n_u16(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u16)))
mve_pred16_t __arm_vcmphiq_m(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u32)))
mve_pred16_t __arm_vcmphiq_m_n_u32(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u32)))
mve_pred16_t __arm_vcmphiq_m(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u8)))
mve_pred16_t __arm_vcmphiq_m_n_u8(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u8)))
mve_pred16_t __arm_vcmphiq_m(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u16)))
mve_pred16_t __arm_vcmphiq_m_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u16)))
mve_pred16_t __arm_vcmphiq_m(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u32)))
mve_pred16_t __arm_vcmphiq_m_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u32)))
mve_pred16_t __arm_vcmphiq_m(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u8)))
mve_pred16_t __arm_vcmphiq_m_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u8)))
mve_pred16_t __arm_vcmphiq_m(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u16)))
mve_pred16_t __arm_vcmphiq_n_u16(uint16x8_t, uint16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u16)))
mve_pred16_t __arm_vcmphiq(uint16x8_t, uint16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u32)))
mve_pred16_t __arm_vcmphiq_n_u32(uint32x4_t, uint32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u32)))
mve_pred16_t __arm_vcmphiq(uint32x4_t, uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u8)))
mve_pred16_t __arm_vcmphiq_n_u8(uint8x16_t, uint8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u8)))
mve_pred16_t __arm_vcmphiq(uint8x16_t, uint8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u16)))
mve_pred16_t __arm_vcmphiq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u16)))
mve_pred16_t __arm_vcmphiq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u32)))
mve_pred16_t __arm_vcmphiq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u32)))
mve_pred16_t __arm_vcmphiq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u8)))
mve_pred16_t __arm_vcmphiq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u8)))
mve_pred16_t __arm_vcmphiq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s16)))
mve_pred16_t __arm_vcmpleq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s16)))
mve_pred16_t __arm_vcmpleq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s32)))
mve_pred16_t __arm_vcmpleq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s32)))
mve_pred16_t __arm_vcmpleq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s8)))
mve_pred16_t __arm_vcmpleq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s8)))
mve_pred16_t __arm_vcmpleq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s16)))
mve_pred16_t __arm_vcmpleq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s16)))
mve_pred16_t __arm_vcmpleq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s32)))
mve_pred16_t __arm_vcmpleq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s32)))
mve_pred16_t __arm_vcmpleq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s8)))
mve_pred16_t __arm_vcmpleq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s8)))
mve_pred16_t __arm_vcmpleq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s16)))
mve_pred16_t __arm_vcmpleq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s16)))
mve_pred16_t __arm_vcmpleq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s32)))
mve_pred16_t __arm_vcmpleq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s32)))
mve_pred16_t __arm_vcmpleq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s8)))
mve_pred16_t __arm_vcmpleq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s8)))
mve_pred16_t __arm_vcmpleq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s16)))
mve_pred16_t __arm_vcmpleq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s16)))
mve_pred16_t __arm_vcmpleq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s32)))
mve_pred16_t __arm_vcmpleq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s32)))
mve_pred16_t __arm_vcmpleq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s8)))
mve_pred16_t __arm_vcmpleq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s8)))
mve_pred16_t __arm_vcmpleq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s16)))
mve_pred16_t __arm_vcmpltq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s16)))
mve_pred16_t __arm_vcmpltq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s32)))
mve_pred16_t __arm_vcmpltq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s32)))
mve_pred16_t __arm_vcmpltq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s8)))
mve_pred16_t __arm_vcmpltq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s8)))
mve_pred16_t __arm_vcmpltq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s16)))
mve_pred16_t __arm_vcmpltq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s16)))
mve_pred16_t __arm_vcmpltq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s32)))
mve_pred16_t __arm_vcmpltq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s32)))
mve_pred16_t __arm_vcmpltq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s8)))
mve_pred16_t __arm_vcmpltq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s8)))
mve_pred16_t __arm_vcmpltq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s16)))
mve_pred16_t __arm_vcmpltq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s16)))
mve_pred16_t __arm_vcmpltq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s32)))
mve_pred16_t __arm_vcmpltq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s32)))
mve_pred16_t __arm_vcmpltq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s8)))
mve_pred16_t __arm_vcmpltq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s8)))
mve_pred16_t __arm_vcmpltq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s16)))
mve_pred16_t __arm_vcmpltq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s16)))
mve_pred16_t __arm_vcmpltq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s32)))
mve_pred16_t __arm_vcmpltq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s32)))
mve_pred16_t __arm_vcmpltq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s8)))
mve_pred16_t __arm_vcmpltq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s8)))
mve_pred16_t __arm_vcmpltq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s16)))
mve_pred16_t __arm_vcmpneq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s16)))
mve_pred16_t __arm_vcmpneq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s32)))
mve_pred16_t __arm_vcmpneq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s32)))
mve_pred16_t __arm_vcmpneq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s8)))
mve_pred16_t __arm_vcmpneq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s8)))
mve_pred16_t __arm_vcmpneq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u16)))
mve_pred16_t __arm_vcmpneq_m_n_u16(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u16)))
mve_pred16_t __arm_vcmpneq_m(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u32)))
mve_pred16_t __arm_vcmpneq_m_n_u32(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u32)))
mve_pred16_t __arm_vcmpneq_m(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u8)))
mve_pred16_t __arm_vcmpneq_m_n_u8(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u8)))
mve_pred16_t __arm_vcmpneq_m(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s16)))
mve_pred16_t __arm_vcmpneq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s16)))
mve_pred16_t __arm_vcmpneq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s32)))
mve_pred16_t __arm_vcmpneq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s32)))
mve_pred16_t __arm_vcmpneq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s8)))
mve_pred16_t __arm_vcmpneq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s8)))
mve_pred16_t __arm_vcmpneq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u16)))
mve_pred16_t __arm_vcmpneq_m_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u16)))
mve_pred16_t __arm_vcmpneq_m(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u32)))
mve_pred16_t __arm_vcmpneq_m_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u32)))
mve_pred16_t __arm_vcmpneq_m(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u8)))
mve_pred16_t __arm_vcmpneq_m_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u8)))
mve_pred16_t __arm_vcmpneq_m(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s16)))
mve_pred16_t __arm_vcmpneq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s16)))
mve_pred16_t __arm_vcmpneq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s32)))
mve_pred16_t __arm_vcmpneq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s32)))
mve_pred16_t __arm_vcmpneq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s8)))
mve_pred16_t __arm_vcmpneq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s8)))
mve_pred16_t __arm_vcmpneq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u16)))
mve_pred16_t __arm_vcmpneq_n_u16(uint16x8_t, uint16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u16)))
mve_pred16_t __arm_vcmpneq(uint16x8_t, uint16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u32)))
mve_pred16_t __arm_vcmpneq_n_u32(uint32x4_t, uint32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u32)))
mve_pred16_t __arm_vcmpneq(uint32x4_t, uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u8)))
mve_pred16_t __arm_vcmpneq_n_u8(uint8x16_t, uint8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u8)))
mve_pred16_t __arm_vcmpneq(uint8x16_t, uint8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s16)))
mve_pred16_t __arm_vcmpneq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s16)))
mve_pred16_t __arm_vcmpneq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s32)))
mve_pred16_t __arm_vcmpneq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s32)))
mve_pred16_t __arm_vcmpneq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s8)))
mve_pred16_t __arm_vcmpneq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s8)))
mve_pred16_t __arm_vcmpneq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u16)))
mve_pred16_t __arm_vcmpneq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u16)))
mve_pred16_t __arm_vcmpneq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u32)))
mve_pred16_t __arm_vcmpneq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u32)))
mve_pred16_t __arm_vcmpneq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u8)))
mve_pred16_t __arm_vcmpneq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u8)))
mve_pred16_t __arm_vcmpneq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_s16)))
int16x8_t __arm_vcreateq_s16(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_s32)))
int32x4_t __arm_vcreateq_s32(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_s64)))
int64x2_t __arm_vcreateq_s64(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_s8)))
int8x16_t __arm_vcreateq_s8(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_u16)))
uint16x8_t __arm_vcreateq_u16(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_u32)))
uint32x4_t __arm_vcreateq_u32(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_u64)))
uint64x2_t __arm_vcreateq_u64(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_u8)))
uint8x16_t __arm_vcreateq_u8(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp16q)))
mve_pred16_t __arm_vctp16q(uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp16q_m)))
mve_pred16_t __arm_vctp16q_m(uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp32q)))
mve_pred16_t __arm_vctp32q(uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp32q_m)))
mve_pred16_t __arm_vctp32q_m(uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp64q)))
mve_pred16_t __arm_vctp64q(uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp64q_m)))
mve_pred16_t __arm_vctp64q_m(uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp8q)))
mve_pred16_t __arm_vctp8q(uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp8q_m)))
mve_pred16_t __arm_vctp8q_m(uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s16)))
int16x8_t __arm_veorq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s16)))
int16x8_t __arm_veorq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s32)))
int32x4_t __arm_veorq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s32)))
int32x4_t __arm_veorq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s8)))
int8x16_t __arm_veorq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s8)))
int8x16_t __arm_veorq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u16)))
uint16x8_t __arm_veorq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u16)))
uint16x8_t __arm_veorq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u32)))
uint32x4_t __arm_veorq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u32)))
uint32x4_t __arm_veorq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u8)))
uint8x16_t __arm_veorq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u8)))
uint8x16_t __arm_veorq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_s16)))
int16x8_t __arm_veorq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_s16)))
int16x8_t __arm_veorq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_s32)))
int32x4_t __arm_veorq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_s32)))
int32x4_t __arm_veorq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_s8)))
int8x16_t __arm_veorq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_s8)))
int8x16_t __arm_veorq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_u16)))
uint16x8_t __arm_veorq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_u16)))
uint16x8_t __arm_veorq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_u32)))
uint32x4_t __arm_veorq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_u32)))
uint32x4_t __arm_veorq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_u8)))
uint8x16_t __arm_veorq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_u8)))
uint8x16_t __arm_veorq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s16)))
int16x8_t __arm_veorq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s16)))
int16x8_t __arm_veorq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s32)))
int32x4_t __arm_veorq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s32)))
int32x4_t __arm_veorq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s8)))
int8x16_t __arm_veorq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s8)))
int8x16_t __arm_veorq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u16)))
uint16x8_t __arm_veorq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u16)))
uint16x8_t __arm_veorq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u32)))
uint32x4_t __arm_veorq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u32)))
uint32x4_t __arm_veorq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u8)))
uint8x16_t __arm_veorq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u8)))
uint8x16_t __arm_veorq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s16)))
int16_t __arm_vgetq_lane_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s16)))
int16_t __arm_vgetq_lane(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s32)))
int32_t __arm_vgetq_lane_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s32)))
int32_t __arm_vgetq_lane(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s64)))
int64_t __arm_vgetq_lane_s64(int64x2_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s64)))
int64_t __arm_vgetq_lane(int64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s8)))
int8_t __arm_vgetq_lane_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s8)))
int8_t __arm_vgetq_lane(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u16)))
uint16_t __arm_vgetq_lane_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u16)))
uint16_t __arm_vgetq_lane(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u32)))
uint32_t __arm_vgetq_lane_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u32)))
uint32_t __arm_vgetq_lane(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u64)))
uint64_t __arm_vgetq_lane_u64(uint64x2_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u64)))
uint64_t __arm_vgetq_lane(uint64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u8)))
uint8_t __arm_vgetq_lane_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u8)))
uint8_t __arm_vgetq_lane(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s16)))
int16x8_t __arm_vhaddq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s16)))
int16x8_t __arm_vhaddq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s32)))
int32x4_t __arm_vhaddq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s32)))
int32x4_t __arm_vhaddq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s8)))
int8x16_t __arm_vhaddq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s8)))
int8x16_t __arm_vhaddq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u16)))
uint16x8_t __arm_vhaddq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u16)))
uint16x8_t __arm_vhaddq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u32)))
uint32x4_t __arm_vhaddq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u32)))
uint32x4_t __arm_vhaddq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u8)))
uint8x16_t __arm_vhaddq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u8)))
uint8x16_t __arm_vhaddq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s16)))
int16x8_t __arm_vhaddq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s16)))
int16x8_t __arm_vhaddq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s32)))
int32x4_t __arm_vhaddq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s32)))
int32x4_t __arm_vhaddq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s8)))
int8x16_t __arm_vhaddq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s8)))
int8x16_t __arm_vhaddq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u16)))
uint16x8_t __arm_vhaddq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u16)))
uint16x8_t __arm_vhaddq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u32)))
uint32x4_t __arm_vhaddq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u32)))
uint32x4_t __arm_vhaddq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u8)))
uint8x16_t __arm_vhaddq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u8)))
uint8x16_t __arm_vhaddq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s16)))
int16x8_t __arm_vhaddq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s16)))
int16x8_t __arm_vhaddq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s32)))
int32x4_t __arm_vhaddq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s32)))
int32x4_t __arm_vhaddq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s8)))
int8x16_t __arm_vhaddq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s8)))
int8x16_t __arm_vhaddq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u16)))
uint16x8_t __arm_vhaddq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u16)))
uint16x8_t __arm_vhaddq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u32)))
uint32x4_t __arm_vhaddq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u32)))
uint32x4_t __arm_vhaddq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u8)))
uint8x16_t __arm_vhaddq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u8)))
uint8x16_t __arm_vhaddq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s16)))
int16x8_t __arm_vhcaddq_rot270_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s16)))
int16x8_t __arm_vhcaddq_rot270_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s32)))
int32x4_t __arm_vhcaddq_rot270_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s32)))
int32x4_t __arm_vhcaddq_rot270_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s8)))
int8x16_t __arm_vhcaddq_rot270_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s8)))
int8x16_t __arm_vhcaddq_rot270_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s16)))
int16x8_t __arm_vhcaddq_rot270_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s16)))
int16x8_t __arm_vhcaddq_rot270(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s32)))
int32x4_t __arm_vhcaddq_rot270_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s32)))
int32x4_t __arm_vhcaddq_rot270(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s8)))
int8x16_t __arm_vhcaddq_rot270_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s8)))
int8x16_t __arm_vhcaddq_rot270(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s16)))
int16x8_t __arm_vhcaddq_rot270_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s16)))
int16x8_t __arm_vhcaddq_rot270_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s32)))
int32x4_t __arm_vhcaddq_rot270_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s32)))
int32x4_t __arm_vhcaddq_rot270_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s8)))
int8x16_t __arm_vhcaddq_rot270_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s8)))
int8x16_t __arm_vhcaddq_rot270_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s16)))
int16x8_t __arm_vhcaddq_rot90_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s16)))
int16x8_t __arm_vhcaddq_rot90_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s32)))
int32x4_t __arm_vhcaddq_rot90_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s32)))
int32x4_t __arm_vhcaddq_rot90_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s8)))
int8x16_t __arm_vhcaddq_rot90_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s8)))
int8x16_t __arm_vhcaddq_rot90_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s16)))
int16x8_t __arm_vhcaddq_rot90_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s16)))
int16x8_t __arm_vhcaddq_rot90(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s32)))
int32x4_t __arm_vhcaddq_rot90_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s32)))
int32x4_t __arm_vhcaddq_rot90(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s8)))
int8x16_t __arm_vhcaddq_rot90_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s8)))
int8x16_t __arm_vhcaddq_rot90(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s16)))
int16x8_t __arm_vhcaddq_rot90_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s16)))
int16x8_t __arm_vhcaddq_rot90_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s32)))
int32x4_t __arm_vhcaddq_rot90_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s32)))
int32x4_t __arm_vhcaddq_rot90_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s8)))
int8x16_t __arm_vhcaddq_rot90_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s8)))
int8x16_t __arm_vhcaddq_rot90_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s16)))
int16x8_t __arm_vhsubq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s16)))
int16x8_t __arm_vhsubq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s32)))
int32x4_t __arm_vhsubq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s32)))
int32x4_t __arm_vhsubq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s8)))
int8x16_t __arm_vhsubq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s8)))
int8x16_t __arm_vhsubq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u16)))
uint16x8_t __arm_vhsubq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u16)))
uint16x8_t __arm_vhsubq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u32)))
uint32x4_t __arm_vhsubq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u32)))
uint32x4_t __arm_vhsubq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u8)))
uint8x16_t __arm_vhsubq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u8)))
uint8x16_t __arm_vhsubq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s16)))
int16x8_t __arm_vhsubq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s16)))
int16x8_t __arm_vhsubq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s32)))
int32x4_t __arm_vhsubq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s32)))
int32x4_t __arm_vhsubq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s8)))
int8x16_t __arm_vhsubq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s8)))
int8x16_t __arm_vhsubq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u16)))
uint16x8_t __arm_vhsubq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u16)))
uint16x8_t __arm_vhsubq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u32)))
uint32x4_t __arm_vhsubq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u32)))
uint32x4_t __arm_vhsubq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u8)))
uint8x16_t __arm_vhsubq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u8)))
uint8x16_t __arm_vhsubq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s16)))
int16x8_t __arm_vhsubq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s16)))
int16x8_t __arm_vhsubq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s32)))
int32x4_t __arm_vhsubq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s32)))
int32x4_t __arm_vhsubq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s8)))
int8x16_t __arm_vhsubq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s8)))
int8x16_t __arm_vhsubq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u16)))
uint16x8_t __arm_vhsubq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u16)))
uint16x8_t __arm_vhsubq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u32)))
uint32x4_t __arm_vhsubq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u32)))
uint32x4_t __arm_vhsubq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u8)))
uint8x16_t __arm_vhsubq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u8)))
uint8x16_t __arm_vhsubq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_s16)))
int16x8_t __arm_vld1q_s16(const int16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_s16)))
int16x8_t __arm_vld1q(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_s32)))
int32x4_t __arm_vld1q_s32(const int32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_s32)))
int32x4_t __arm_vld1q(const int32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_s8)))
int8x16_t __arm_vld1q_s8(const int8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_s8)))
int8x16_t __arm_vld1q(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_u16)))
uint16x8_t __arm_vld1q_u16(const uint16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_u16)))
uint16x8_t __arm_vld1q(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_u32)))
uint32x4_t __arm_vld1q_u32(const uint32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_u32)))
uint32x4_t __arm_vld1q(const uint32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_u8)))
uint8x16_t __arm_vld1q_u8(const uint8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_u8)))
uint8x16_t __arm_vld1q(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s16)))
int16x8_t __arm_vld1q_z_s16(const int16_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s16)))
int16x8_t __arm_vld1q_z(const int16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s32)))
int32x4_t __arm_vld1q_z_s32(const int32_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s32)))
int32x4_t __arm_vld1q_z(const int32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s8)))
int8x16_t __arm_vld1q_z_s8(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s8)))
int8x16_t __arm_vld1q_z(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u16)))
uint16x8_t __arm_vld1q_z_u16(const uint16_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u16)))
uint16x8_t __arm_vld1q_z(const uint16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u32)))
uint32x4_t __arm_vld1q_z_u32(const uint32_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u32)))
uint32x4_t __arm_vld1q_z(const uint32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u8)))
uint8x16_t __arm_vld1q_z_u8(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u8)))
uint8x16_t __arm_vld1q_z(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_s16)))
int16x8x2_t __arm_vld2q_s16(const int16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_s16)))
int16x8x2_t __arm_vld2q(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_s32)))
int32x4x2_t __arm_vld2q_s32(const int32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_s32)))
int32x4x2_t __arm_vld2q(const int32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_s8)))
int8x16x2_t __arm_vld2q_s8(const int8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_s8)))
int8x16x2_t __arm_vld2q(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_u16)))
uint16x8x2_t __arm_vld2q_u16(const uint16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_u16)))
uint16x8x2_t __arm_vld2q(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_u32)))
uint32x4x2_t __arm_vld2q_u32(const uint32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_u32)))
uint32x4x2_t __arm_vld2q(const uint32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_u8)))
uint8x16x2_t __arm_vld2q_u8(const uint8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_u8)))
uint8x16x2_t __arm_vld2q(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_s16)))
int16x8x4_t __arm_vld4q_s16(const int16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_s16)))
int16x8x4_t __arm_vld4q(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_s32)))
int32x4x4_t __arm_vld4q_s32(const int32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_s32)))
int32x4x4_t __arm_vld4q(const int32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_s8)))
int8x16x4_t __arm_vld4q_s8(const int8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_s8)))
int8x16x4_t __arm_vld4q(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_u16)))
uint16x8x4_t __arm_vld4q_u16(const uint16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_u16)))
uint16x8x4_t __arm_vld4q(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_u32)))
uint32x4x4_t __arm_vld4q_u32(const uint32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_u32)))
uint32x4x4_t __arm_vld4q(const uint32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_u8)))
uint8x16x4_t __arm_vld4q_u8(const uint8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_u8)))
uint8x16x4_t __arm_vld4q(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s16)))
int16x8_t __arm_vldrbq_gather_offset_s16(const int8_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s16)))
int16x8_t __arm_vldrbq_gather_offset(const int8_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s32)))
int32x4_t __arm_vldrbq_gather_offset_s32(const int8_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s32)))
int32x4_t __arm_vldrbq_gather_offset(const int8_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s8)))
int8x16_t __arm_vldrbq_gather_offset_s8(const int8_t *, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s8)))
int8x16_t __arm_vldrbq_gather_offset(const int8_t *, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u16)))
uint16x8_t __arm_vldrbq_gather_offset_u16(const uint8_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u16)))
uint16x8_t __arm_vldrbq_gather_offset(const uint8_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u32)))
uint32x4_t __arm_vldrbq_gather_offset_u32(const uint8_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u32)))
uint32x4_t __arm_vldrbq_gather_offset(const uint8_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u8)))
uint8x16_t __arm_vldrbq_gather_offset_u8(const uint8_t *, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u8)))
uint8x16_t __arm_vldrbq_gather_offset(const uint8_t *, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s16)))
int16x8_t __arm_vldrbq_gather_offset_z_s16(const int8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s16)))
int16x8_t __arm_vldrbq_gather_offset_z(const int8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s32)))
int32x4_t __arm_vldrbq_gather_offset_z_s32(const int8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s32)))
int32x4_t __arm_vldrbq_gather_offset_z(const int8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s8)))
int8x16_t __arm_vldrbq_gather_offset_z_s8(const int8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s8)))
int8x16_t __arm_vldrbq_gather_offset_z(const int8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u16)))
uint16x8_t __arm_vldrbq_gather_offset_z_u16(const uint8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u16)))
uint16x8_t __arm_vldrbq_gather_offset_z(const uint8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u32)))
uint32x4_t __arm_vldrbq_gather_offset_z_u32(const uint8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u32)))
uint32x4_t __arm_vldrbq_gather_offset_z(const uint8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u8)))
uint8x16_t __arm_vldrbq_gather_offset_z_u8(const uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u8)))
uint8x16_t __arm_vldrbq_gather_offset_z(const uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_s16)))
int16x8_t __arm_vldrbq_s16(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_s32)))
int32x4_t __arm_vldrbq_s32(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_s8)))
int8x16_t __arm_vldrbq_s8(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_u16)))
uint16x8_t __arm_vldrbq_u16(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_u32)))
uint32x4_t __arm_vldrbq_u32(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_u8)))
uint8x16_t __arm_vldrbq_u8(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_s16)))
int16x8_t __arm_vldrbq_z_s16(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_s32)))
int32x4_t __arm_vldrbq_z_s32(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_s8)))
int8x16_t __arm_vldrbq_z_s8(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_u16)))
uint16x8_t __arm_vldrbq_z_u16(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_u32)))
uint32x4_t __arm_vldrbq_z_u32(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_u8)))
uint8x16_t __arm_vldrbq_z_u8(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_s64)))
int64x2_t __arm_vldrdq_gather_base_s64(uint64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_u64)))
uint64x2_t __arm_vldrdq_gather_base_u64(uint64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_wb_s64)))
int64x2_t __arm_vldrdq_gather_base_wb_s64(uint64x2_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_wb_u64)))
uint64x2_t __arm_vldrdq_gather_base_wb_u64(uint64x2_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_wb_z_s64)))
int64x2_t __arm_vldrdq_gather_base_wb_z_s64(uint64x2_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_wb_z_u64)))
uint64x2_t __arm_vldrdq_gather_base_wb_z_u64(uint64x2_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_z_s64)))
int64x2_t __arm_vldrdq_gather_base_z_s64(uint64x2_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_z_u64)))
uint64x2_t __arm_vldrdq_gather_base_z_u64(uint64x2_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_s64)))
int64x2_t __arm_vldrdq_gather_offset_s64(const int64_t *, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_s64)))
int64x2_t __arm_vldrdq_gather_offset(const int64_t *, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_u64)))
uint64x2_t __arm_vldrdq_gather_offset_u64(const uint64_t *, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_u64)))
uint64x2_t __arm_vldrdq_gather_offset(const uint64_t *, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_z_s64)))
int64x2_t __arm_vldrdq_gather_offset_z_s64(const int64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_z_s64)))
int64x2_t __arm_vldrdq_gather_offset_z(const int64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_z_u64)))
uint64x2_t __arm_vldrdq_gather_offset_z_u64(const uint64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_z_u64)))
uint64x2_t __arm_vldrdq_gather_offset_z(const uint64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_s64)))
int64x2_t __arm_vldrdq_gather_shifted_offset_s64(const int64_t *, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_s64)))
int64x2_t __arm_vldrdq_gather_shifted_offset(const int64_t *, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_u64)))
uint64x2_t __arm_vldrdq_gather_shifted_offset_u64(const uint64_t *, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_u64)))
uint64x2_t __arm_vldrdq_gather_shifted_offset(const uint64_t *, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_z_s64)))
int64x2_t __arm_vldrdq_gather_shifted_offset_z_s64(const int64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_z_s64)))
int64x2_t __arm_vldrdq_gather_shifted_offset_z(const int64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_z_u64)))
uint64x2_t __arm_vldrdq_gather_shifted_offset_z_u64(const uint64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_z_u64)))
uint64x2_t __arm_vldrdq_gather_shifted_offset_z(const uint64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_s16)))
int16x8_t __arm_vldrhq_gather_offset_s16(const int16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_s16)))
int16x8_t __arm_vldrhq_gather_offset(const int16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_s32)))
int32x4_t __arm_vldrhq_gather_offset_s32(const int16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_s32)))
int32x4_t __arm_vldrhq_gather_offset(const int16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_u16)))
uint16x8_t __arm_vldrhq_gather_offset_u16(const uint16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_u16)))
uint16x8_t __arm_vldrhq_gather_offset(const uint16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_u32)))
uint32x4_t __arm_vldrhq_gather_offset_u32(const uint16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_u32)))
uint32x4_t __arm_vldrhq_gather_offset(const uint16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_s16)))
int16x8_t __arm_vldrhq_gather_offset_z_s16(const int16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_s16)))
int16x8_t __arm_vldrhq_gather_offset_z(const int16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_s32)))
int32x4_t __arm_vldrhq_gather_offset_z_s32(const int16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_s32)))
int32x4_t __arm_vldrhq_gather_offset_z(const int16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_u16)))
uint16x8_t __arm_vldrhq_gather_offset_z_u16(const uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_u16)))
uint16x8_t __arm_vldrhq_gather_offset_z(const uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_u32)))
uint32x4_t __arm_vldrhq_gather_offset_z_u32(const uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_u32)))
uint32x4_t __arm_vldrhq_gather_offset_z(const uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_s16)))
int16x8_t __arm_vldrhq_gather_shifted_offset_s16(const int16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_s16)))
int16x8_t __arm_vldrhq_gather_shifted_offset(const int16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_s32)))
int32x4_t __arm_vldrhq_gather_shifted_offset_s32(const int16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_s32)))
int32x4_t __arm_vldrhq_gather_shifted_offset(const int16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_u16)))
uint16x8_t __arm_vldrhq_gather_shifted_offset_u16(const uint16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_u16)))
uint16x8_t __arm_vldrhq_gather_shifted_offset(const uint16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_u32)))
uint32x4_t __arm_vldrhq_gather_shifted_offset_u32(const uint16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_u32)))
uint32x4_t __arm_vldrhq_gather_shifted_offset(const uint16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_s16)))
int16x8_t __arm_vldrhq_gather_shifted_offset_z_s16(const int16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_s16)))
int16x8_t __arm_vldrhq_gather_shifted_offset_z(const int16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_s32)))
int32x4_t __arm_vldrhq_gather_shifted_offset_z_s32(const int16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_s32)))
int32x4_t __arm_vldrhq_gather_shifted_offset_z(const int16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_u16)))
uint16x8_t __arm_vldrhq_gather_shifted_offset_z_u16(const uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_u16)))
uint16x8_t __arm_vldrhq_gather_shifted_offset_z(const uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_u32)))
uint32x4_t __arm_vldrhq_gather_shifted_offset_z_u32(const uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_u32)))
uint32x4_t __arm_vldrhq_gather_shifted_offset_z(const uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_s16)))
int16x8_t __arm_vldrhq_s16(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_s32)))
int32x4_t __arm_vldrhq_s32(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_u16)))
uint16x8_t __arm_vldrhq_u16(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_u32)))
uint32x4_t __arm_vldrhq_u32(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_s16)))
int16x8_t __arm_vldrhq_z_s16(const int16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_s32)))
int32x4_t __arm_vldrhq_z_s32(const int16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_u16)))
uint16x8_t __arm_vldrhq_z_u16(const uint16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_u32)))
uint32x4_t __arm_vldrhq_z_u32(const uint16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_s32)))
int32x4_t __arm_vldrwq_gather_base_s32(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_u32)))
uint32x4_t __arm_vldrwq_gather_base_u32(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_s32)))
int32x4_t __arm_vldrwq_gather_base_wb_s32(uint32x4_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_u32)))
uint32x4_t __arm_vldrwq_gather_base_wb_u32(uint32x4_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_z_s32)))
int32x4_t __arm_vldrwq_gather_base_wb_z_s32(uint32x4_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_z_u32)))
uint32x4_t __arm_vldrwq_gather_base_wb_z_u32(uint32x4_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_z_s32)))
int32x4_t __arm_vldrwq_gather_base_z_s32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_z_u32)))
uint32x4_t __arm_vldrwq_gather_base_z_u32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_s32)))
int32x4_t __arm_vldrwq_gather_offset_s32(const int32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_s32)))
int32x4_t __arm_vldrwq_gather_offset(const int32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_u32)))
uint32x4_t __arm_vldrwq_gather_offset_u32(const uint32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_u32)))
uint32x4_t __arm_vldrwq_gather_offset(const uint32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_s32)))
int32x4_t __arm_vldrwq_gather_offset_z_s32(const int32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_s32)))
int32x4_t __arm_vldrwq_gather_offset_z(const int32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_u32)))
uint32x4_t __arm_vldrwq_gather_offset_z_u32(const uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_u32)))
uint32x4_t __arm_vldrwq_gather_offset_z(const uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_s32)))
int32x4_t __arm_vldrwq_gather_shifted_offset_s32(const int32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_s32)))
int32x4_t __arm_vldrwq_gather_shifted_offset(const int32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_u32)))
uint32x4_t __arm_vldrwq_gather_shifted_offset_u32(const uint32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_u32)))
uint32x4_t __arm_vldrwq_gather_shifted_offset(const uint32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_s32)))
int32x4_t __arm_vldrwq_gather_shifted_offset_z_s32(const int32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_s32)))
int32x4_t __arm_vldrwq_gather_shifted_offset_z(const int32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_u32)))
uint32x4_t __arm_vldrwq_gather_shifted_offset_z_u32(const uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_u32)))
uint32x4_t __arm_vldrwq_gather_shifted_offset_z(const uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_s32)))
int32x4_t __arm_vldrwq_s32(const int32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_u32)))
uint32x4_t __arm_vldrwq_u32(const uint32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_z_s32)))
int32x4_t __arm_vldrwq_z_s32(const int32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_z_u32)))
uint32x4_t __arm_vldrwq_z_u32(const uint32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s16)))
int16x8_t __arm_vmaxq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s16)))
int16x8_t __arm_vmaxq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s32)))
int32x4_t __arm_vmaxq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s32)))
int32x4_t __arm_vmaxq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s8)))
int8x16_t __arm_vmaxq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s8)))
int8x16_t __arm_vmaxq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u16)))
uint16x8_t __arm_vmaxq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u16)))
uint16x8_t __arm_vmaxq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u32)))
uint32x4_t __arm_vmaxq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u32)))
uint32x4_t __arm_vmaxq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u8)))
uint8x16_t __arm_vmaxq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u8)))
uint8x16_t __arm_vmaxq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s16)))
int16x8_t __arm_vmaxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s16)))
int16x8_t __arm_vmaxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s32)))
int32x4_t __arm_vmaxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s32)))
int32x4_t __arm_vmaxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s8)))
int8x16_t __arm_vmaxq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s8)))
int8x16_t __arm_vmaxq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u16)))
uint16x8_t __arm_vmaxq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u16)))
uint16x8_t __arm_vmaxq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u32)))
uint32x4_t __arm_vmaxq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u32)))
uint32x4_t __arm_vmaxq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u8)))
uint8x16_t __arm_vmaxq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u8)))
uint8x16_t __arm_vmaxq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s16)))
int16x8_t __arm_vmaxq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s16)))
int16x8_t __arm_vmaxq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s32)))
int32x4_t __arm_vmaxq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s32)))
int32x4_t __arm_vmaxq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s8)))
int8x16_t __arm_vmaxq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s8)))
int8x16_t __arm_vmaxq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u16)))
uint16x8_t __arm_vmaxq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u16)))
uint16x8_t __arm_vmaxq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u32)))
uint32x4_t __arm_vmaxq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u32)))
uint32x4_t __arm_vmaxq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u8)))
uint8x16_t __arm_vmaxq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u8)))
uint8x16_t __arm_vmaxq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s16)))
int16_t __arm_vmaxvq_s16(int16_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s16)))
int16_t __arm_vmaxvq(int16_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s32)))
int32_t __arm_vmaxvq_s32(int32_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s32)))
int32_t __arm_vmaxvq(int32_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s8)))
int8_t __arm_vmaxvq_s8(int8_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s8)))
int8_t __arm_vmaxvq(int8_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u16)))
uint16_t __arm_vmaxvq_u16(uint16_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u16)))
uint16_t __arm_vmaxvq(uint16_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u32)))
uint32_t __arm_vmaxvq_u32(uint32_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u32)))
uint32_t __arm_vmaxvq(uint32_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u8)))
uint8_t __arm_vmaxvq_u8(uint8_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u8)))
uint8_t __arm_vmaxvq(uint8_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s16)))
int16x8_t __arm_vminq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s16)))
int16x8_t __arm_vminq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s32)))
int32x4_t __arm_vminq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s32)))
int32x4_t __arm_vminq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s8)))
int8x16_t __arm_vminq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s8)))
int8x16_t __arm_vminq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u16)))
uint16x8_t __arm_vminq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u16)))
uint16x8_t __arm_vminq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u32)))
uint32x4_t __arm_vminq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u32)))
uint32x4_t __arm_vminq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u8)))
uint8x16_t __arm_vminq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u8)))
uint8x16_t __arm_vminq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_s16)))
int16x8_t __arm_vminq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_s16)))
int16x8_t __arm_vminq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_s32)))
int32x4_t __arm_vminq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_s32)))
int32x4_t __arm_vminq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_s8)))
int8x16_t __arm_vminq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_s8)))
int8x16_t __arm_vminq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_u16)))
uint16x8_t __arm_vminq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_u16)))
uint16x8_t __arm_vminq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_u32)))
uint32x4_t __arm_vminq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_u32)))
uint32x4_t __arm_vminq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_u8)))
uint8x16_t __arm_vminq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_u8)))
uint8x16_t __arm_vminq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s16)))
int16x8_t __arm_vminq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s16)))
int16x8_t __arm_vminq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s32)))
int32x4_t __arm_vminq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s32)))
int32x4_t __arm_vminq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s8)))
int8x16_t __arm_vminq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s8)))
int8x16_t __arm_vminq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u16)))
uint16x8_t __arm_vminq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u16)))
uint16x8_t __arm_vminq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u32)))
uint32x4_t __arm_vminq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u32)))
uint32x4_t __arm_vminq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u8)))
uint8x16_t __arm_vminq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u8)))
uint8x16_t __arm_vminq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_s16)))
int16_t __arm_vminvq_s16(int16_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_s16)))
int16_t __arm_vminvq(int16_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_s32)))
int32_t __arm_vminvq_s32(int32_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_s32)))
int32_t __arm_vminvq(int32_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_s8)))
int8_t __arm_vminvq_s8(int8_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_s8)))
int8_t __arm_vminvq(int8_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_u16)))
uint16_t __arm_vminvq_u16(uint16_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_u16)))
uint16_t __arm_vminvq(uint16_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_u32)))
uint32_t __arm_vminvq_u32(uint32_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_u32)))
uint32_t __arm_vminvq(uint32_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_u8)))
uint8_t __arm_vminvq_u8(uint8_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_u8)))
uint8_t __arm_vminvq(uint8_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s16)))
int32_t __arm_vmladavaq_p_s16(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s16)))
int32_t __arm_vmladavaq_p(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s32)))
int32_t __arm_vmladavaq_p_s32(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s32)))
int32_t __arm_vmladavaq_p(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s8)))
int32_t __arm_vmladavaq_p_s8(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s8)))
int32_t __arm_vmladavaq_p(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u16)))
uint32_t __arm_vmladavaq_p_u16(uint32_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u16)))
uint32_t __arm_vmladavaq_p(uint32_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u32)))
uint32_t __arm_vmladavaq_p_u32(uint32_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u32)))
uint32_t __arm_vmladavaq_p(uint32_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u8)))
uint32_t __arm_vmladavaq_p_u8(uint32_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u8)))
uint32_t __arm_vmladavaq_p(uint32_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s16)))
int32_t __arm_vmladavaq_s16(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s16)))
int32_t __arm_vmladavaq(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s32)))
int32_t __arm_vmladavaq_s32(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s32)))
int32_t __arm_vmladavaq(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s8)))
int32_t __arm_vmladavaq_s8(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s8)))
int32_t __arm_vmladavaq(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u16)))
uint32_t __arm_vmladavaq_u16(uint32_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u16)))
uint32_t __arm_vmladavaq(uint32_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u32)))
uint32_t __arm_vmladavaq_u32(uint32_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u32)))
uint32_t __arm_vmladavaq(uint32_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u8)))
uint32_t __arm_vmladavaq_u8(uint32_t, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u8)))
uint32_t __arm_vmladavaq(uint32_t, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s16)))
int32_t __arm_vmladavaxq_p_s16(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s16)))
int32_t __arm_vmladavaxq_p(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s32)))
int32_t __arm_vmladavaxq_p_s32(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s32)))
int32_t __arm_vmladavaxq_p(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s8)))
int32_t __arm_vmladavaxq_p_s8(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s8)))
int32_t __arm_vmladavaxq_p(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s16)))
int32_t __arm_vmladavaxq_s16(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s16)))
int32_t __arm_vmladavaxq(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s32)))
int32_t __arm_vmladavaxq_s32(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s32)))
int32_t __arm_vmladavaxq(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s8)))
int32_t __arm_vmladavaxq_s8(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s8)))
int32_t __arm_vmladavaxq(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s16)))
int32_t __arm_vmladavq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s16)))
int32_t __arm_vmladavq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s32)))
int32_t __arm_vmladavq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s32)))
int32_t __arm_vmladavq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s8)))
int32_t __arm_vmladavq_p_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s8)))
int32_t __arm_vmladavq_p(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u16)))
uint32_t __arm_vmladavq_p_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u16)))
uint32_t __arm_vmladavq_p(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u32)))
uint32_t __arm_vmladavq_p_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u32)))
uint32_t __arm_vmladavq_p(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u8)))
uint32_t __arm_vmladavq_p_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u8)))
uint32_t __arm_vmladavq_p(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s16)))
int32_t __arm_vmladavq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s16)))
int32_t __arm_vmladavq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s32)))
int32_t __arm_vmladavq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s32)))
int32_t __arm_vmladavq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s8)))
int32_t __arm_vmladavq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s8)))
int32_t __arm_vmladavq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u16)))
uint32_t __arm_vmladavq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u16)))
uint32_t __arm_vmladavq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u32)))
uint32_t __arm_vmladavq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u32)))
uint32_t __arm_vmladavq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u8)))
uint32_t __arm_vmladavq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u8)))
uint32_t __arm_vmladavq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s16)))
int32_t __arm_vmladavxq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s16)))
int32_t __arm_vmladavxq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s32)))
int32_t __arm_vmladavxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s32)))
int32_t __arm_vmladavxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s8)))
int32_t __arm_vmladavxq_p_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s8)))
int32_t __arm_vmladavxq_p(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s16)))
int32_t __arm_vmladavxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s16)))
int32_t __arm_vmladavxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s32)))
int32_t __arm_vmladavxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s32)))
int32_t __arm_vmladavxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s8)))
int32_t __arm_vmladavxq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s8)))
int32_t __arm_vmladavxq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_s16)))
int64_t __arm_vmlaldavaq_p_s16(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_s16)))
int64_t __arm_vmlaldavaq_p(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_s32)))
int64_t __arm_vmlaldavaq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_s32)))
int64_t __arm_vmlaldavaq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_u16)))
uint64_t __arm_vmlaldavaq_p_u16(uint64_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_u16)))
uint64_t __arm_vmlaldavaq_p(uint64_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_u32)))
uint64_t __arm_vmlaldavaq_p_u32(uint64_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_u32)))
uint64_t __arm_vmlaldavaq_p(uint64_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_s16)))
int64_t __arm_vmlaldavaq_s16(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_s16)))
int64_t __arm_vmlaldavaq(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_s32)))
int64_t __arm_vmlaldavaq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_s32)))
int64_t __arm_vmlaldavaq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_u16)))
uint64_t __arm_vmlaldavaq_u16(uint64_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_u16)))
uint64_t __arm_vmlaldavaq(uint64_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_u32)))
uint64_t __arm_vmlaldavaq_u32(uint64_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_u32)))
uint64_t __arm_vmlaldavaq(uint64_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_p_s16)))
int64_t __arm_vmlaldavaxq_p_s16(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_p_s16)))
int64_t __arm_vmlaldavaxq_p(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_p_s32)))
int64_t __arm_vmlaldavaxq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_p_s32)))
int64_t __arm_vmlaldavaxq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_s16)))
int64_t __arm_vmlaldavaxq_s16(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_s16)))
int64_t __arm_vmlaldavaxq(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_s32)))
int64_t __arm_vmlaldavaxq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_s32)))
int64_t __arm_vmlaldavaxq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_s16)))
int64_t __arm_vmlaldavq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_s16)))
int64_t __arm_vmlaldavq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_s32)))
int64_t __arm_vmlaldavq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_s32)))
int64_t __arm_vmlaldavq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_u16)))
uint64_t __arm_vmlaldavq_p_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_u16)))
uint64_t __arm_vmlaldavq_p(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_u32)))
uint64_t __arm_vmlaldavq_p_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_u32)))
uint64_t __arm_vmlaldavq_p(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_s16)))
int64_t __arm_vmlaldavq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_s16)))
int64_t __arm_vmlaldavq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_s32)))
int64_t __arm_vmlaldavq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_s32)))
int64_t __arm_vmlaldavq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_u16)))
uint64_t __arm_vmlaldavq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_u16)))
uint64_t __arm_vmlaldavq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_u32)))
uint64_t __arm_vmlaldavq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_u32)))
uint64_t __arm_vmlaldavq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_p_s16)))
int64_t __arm_vmlaldavxq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_p_s16)))
int64_t __arm_vmlaldavxq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_p_s32)))
int64_t __arm_vmlaldavxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_p_s32)))
int64_t __arm_vmlaldavxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_s16)))
int64_t __arm_vmlaldavxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_s16)))
int64_t __arm_vmlaldavxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_s32)))
int64_t __arm_vmlaldavxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_s32)))
int64_t __arm_vmlaldavxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s16)))
int32_t __arm_vmlsdavaq_p_s16(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s16)))
int32_t __arm_vmlsdavaq_p(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s32)))
int32_t __arm_vmlsdavaq_p_s32(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s32)))
int32_t __arm_vmlsdavaq_p(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s8)))
int32_t __arm_vmlsdavaq_p_s8(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s8)))
int32_t __arm_vmlsdavaq_p(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s16)))
int32_t __arm_vmlsdavaq_s16(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s16)))
int32_t __arm_vmlsdavaq(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s32)))
int32_t __arm_vmlsdavaq_s32(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s32)))
int32_t __arm_vmlsdavaq(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s8)))
int32_t __arm_vmlsdavaq_s8(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s8)))
int32_t __arm_vmlsdavaq(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s16)))
int32_t __arm_vmlsdavaxq_p_s16(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s16)))
int32_t __arm_vmlsdavaxq_p(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s32)))
int32_t __arm_vmlsdavaxq_p_s32(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s32)))
int32_t __arm_vmlsdavaxq_p(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s8)))
int32_t __arm_vmlsdavaxq_p_s8(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s8)))
int32_t __arm_vmlsdavaxq_p(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s16)))
int32_t __arm_vmlsdavaxq_s16(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s16)))
int32_t __arm_vmlsdavaxq(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s32)))
int32_t __arm_vmlsdavaxq_s32(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s32)))
int32_t __arm_vmlsdavaxq(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s8)))
int32_t __arm_vmlsdavaxq_s8(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s8)))
int32_t __arm_vmlsdavaxq(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s16)))
int32_t __arm_vmlsdavq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s16)))
int32_t __arm_vmlsdavq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s32)))
int32_t __arm_vmlsdavq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s32)))
int32_t __arm_vmlsdavq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s8)))
int32_t __arm_vmlsdavq_p_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s8)))
int32_t __arm_vmlsdavq_p(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s16)))
int32_t __arm_vmlsdavq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s16)))
int32_t __arm_vmlsdavq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s32)))
int32_t __arm_vmlsdavq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s32)))
int32_t __arm_vmlsdavq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s8)))
int32_t __arm_vmlsdavq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s8)))
int32_t __arm_vmlsdavq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s16)))
int32_t __arm_vmlsdavxq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s16)))
int32_t __arm_vmlsdavxq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s32)))
int32_t __arm_vmlsdavxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s32)))
int32_t __arm_vmlsdavxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s8)))
int32_t __arm_vmlsdavxq_p_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s8)))
int32_t __arm_vmlsdavxq_p(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s16)))
int32_t __arm_vmlsdavxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s16)))
int32_t __arm_vmlsdavxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s32)))
int32_t __arm_vmlsdavxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s32)))
int32_t __arm_vmlsdavxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s8)))
int32_t __arm_vmlsdavxq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s8)))
int32_t __arm_vmlsdavxq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_p_s16)))
int64_t __arm_vmlsldavaq_p_s16(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_p_s16)))
int64_t __arm_vmlsldavaq_p(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_p_s32)))
int64_t __arm_vmlsldavaq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_p_s32)))
int64_t __arm_vmlsldavaq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_s16)))
int64_t __arm_vmlsldavaq_s16(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_s16)))
int64_t __arm_vmlsldavaq(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_s32)))
int64_t __arm_vmlsldavaq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_s32)))
int64_t __arm_vmlsldavaq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_p_s16)))
int64_t __arm_vmlsldavaxq_p_s16(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_p_s16)))
int64_t __arm_vmlsldavaxq_p(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_p_s32)))
int64_t __arm_vmlsldavaxq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_p_s32)))
int64_t __arm_vmlsldavaxq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_s16)))
int64_t __arm_vmlsldavaxq_s16(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_s16)))
int64_t __arm_vmlsldavaxq(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_s32)))
int64_t __arm_vmlsldavaxq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_s32)))
int64_t __arm_vmlsldavaxq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_p_s16)))
int64_t __arm_vmlsldavq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_p_s16)))
int64_t __arm_vmlsldavq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_p_s32)))
int64_t __arm_vmlsldavq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_p_s32)))
int64_t __arm_vmlsldavq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_s16)))
int64_t __arm_vmlsldavq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_s16)))
int64_t __arm_vmlsldavq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_s32)))
int64_t __arm_vmlsldavq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_s32)))
int64_t __arm_vmlsldavq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_p_s16)))
int64_t __arm_vmlsldavxq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_p_s16)))
int64_t __arm_vmlsldavxq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_p_s32)))
int64_t __arm_vmlsldavxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_p_s32)))
int64_t __arm_vmlsldavxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_s16)))
int64_t __arm_vmlsldavxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_s16)))
int64_t __arm_vmlsldavxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_s32)))
int64_t __arm_vmlsldavxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_s32)))
int64_t __arm_vmlsldavxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s16)))
int16x8_t __arm_vmulhq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s16)))
int16x8_t __arm_vmulhq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s32)))
int32x4_t __arm_vmulhq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s32)))
int32x4_t __arm_vmulhq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s8)))
int8x16_t __arm_vmulhq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s8)))
int8x16_t __arm_vmulhq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u16)))
uint16x8_t __arm_vmulhq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u16)))
uint16x8_t __arm_vmulhq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u32)))
uint32x4_t __arm_vmulhq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u32)))
uint32x4_t __arm_vmulhq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u8)))
uint8x16_t __arm_vmulhq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u8)))
uint8x16_t __arm_vmulhq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s16)))
int16x8_t __arm_vmulhq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s16)))
int16x8_t __arm_vmulhq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s32)))
int32x4_t __arm_vmulhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s32)))
int32x4_t __arm_vmulhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s8)))
int8x16_t __arm_vmulhq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s8)))
int8x16_t __arm_vmulhq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u16)))
uint16x8_t __arm_vmulhq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u16)))
uint16x8_t __arm_vmulhq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u32)))
uint32x4_t __arm_vmulhq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u32)))
uint32x4_t __arm_vmulhq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u8)))
uint8x16_t __arm_vmulhq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u8)))
uint8x16_t __arm_vmulhq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s16)))
int16x8_t __arm_vmulhq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s16)))
int16x8_t __arm_vmulhq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s32)))
int32x4_t __arm_vmulhq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s32)))
int32x4_t __arm_vmulhq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s8)))
int8x16_t __arm_vmulhq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s8)))
int8x16_t __arm_vmulhq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u16)))
uint16x8_t __arm_vmulhq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u16)))
uint16x8_t __arm_vmulhq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u32)))
uint32x4_t __arm_vmulhq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u32)))
uint32x4_t __arm_vmulhq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u8)))
uint8x16_t __arm_vmulhq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u8)))
uint8x16_t __arm_vmulhq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s16)))
int32x4_t __arm_vmullbq_int_m_s16(int32x4_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s16)))
int32x4_t __arm_vmullbq_int_m(int32x4_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s32)))
int64x2_t __arm_vmullbq_int_m_s32(int64x2_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s32)))
int64x2_t __arm_vmullbq_int_m(int64x2_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s8)))
int16x8_t __arm_vmullbq_int_m_s8(int16x8_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s8)))
int16x8_t __arm_vmullbq_int_m(int16x8_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u16)))
uint32x4_t __arm_vmullbq_int_m_u16(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u16)))
uint32x4_t __arm_vmullbq_int_m(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u32)))
uint64x2_t __arm_vmullbq_int_m_u32(uint64x2_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u32)))
uint64x2_t __arm_vmullbq_int_m(uint64x2_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u8)))
uint16x8_t __arm_vmullbq_int_m_u8(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u8)))
uint16x8_t __arm_vmullbq_int_m(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s16)))
int32x4_t __arm_vmullbq_int_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s16)))
int32x4_t __arm_vmullbq_int(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s32)))
int64x2_t __arm_vmullbq_int_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s32)))
int64x2_t __arm_vmullbq_int(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s8)))
int16x8_t __arm_vmullbq_int_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s8)))
int16x8_t __arm_vmullbq_int(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u16)))
uint32x4_t __arm_vmullbq_int_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u16)))
uint32x4_t __arm_vmullbq_int(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u32)))
uint64x2_t __arm_vmullbq_int_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u32)))
uint64x2_t __arm_vmullbq_int(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u8)))
uint16x8_t __arm_vmullbq_int_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u8)))
uint16x8_t __arm_vmullbq_int(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s16)))
int32x4_t __arm_vmullbq_int_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s16)))
int32x4_t __arm_vmullbq_int_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s32)))
int64x2_t __arm_vmullbq_int_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s32)))
int64x2_t __arm_vmullbq_int_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s8)))
int16x8_t __arm_vmullbq_int_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s8)))
int16x8_t __arm_vmullbq_int_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u16)))
uint32x4_t __arm_vmullbq_int_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u16)))
uint32x4_t __arm_vmullbq_int_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u32)))
uint64x2_t __arm_vmullbq_int_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u32)))
uint64x2_t __arm_vmullbq_int_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u8)))
uint16x8_t __arm_vmullbq_int_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u8)))
uint16x8_t __arm_vmullbq_int_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_m_p16)))
uint32x4_t __arm_vmullbq_poly_m_p16(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_m_p16)))
uint32x4_t __arm_vmullbq_poly_m(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_m_p8)))
uint16x8_t __arm_vmullbq_poly_m_p8(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_m_p8)))
uint16x8_t __arm_vmullbq_poly_m(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_p16)))
uint32x4_t __arm_vmullbq_poly_p16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_p16)))
uint32x4_t __arm_vmullbq_poly(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_p8)))
uint16x8_t __arm_vmullbq_poly_p8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_p8)))
uint16x8_t __arm_vmullbq_poly(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_x_p16)))
uint32x4_t __arm_vmullbq_poly_x_p16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_x_p16)))
uint32x4_t __arm_vmullbq_poly_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_x_p8)))
uint16x8_t __arm_vmullbq_poly_x_p8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_x_p8)))
uint16x8_t __arm_vmullbq_poly_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s16)))
int32x4_t __arm_vmulltq_int_m_s16(int32x4_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s16)))
int32x4_t __arm_vmulltq_int_m(int32x4_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s32)))
int64x2_t __arm_vmulltq_int_m_s32(int64x2_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s32)))
int64x2_t __arm_vmulltq_int_m(int64x2_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s8)))
int16x8_t __arm_vmulltq_int_m_s8(int16x8_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s8)))
int16x8_t __arm_vmulltq_int_m(int16x8_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u16)))
uint32x4_t __arm_vmulltq_int_m_u16(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u16)))
uint32x4_t __arm_vmulltq_int_m(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u32)))
uint64x2_t __arm_vmulltq_int_m_u32(uint64x2_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u32)))
uint64x2_t __arm_vmulltq_int_m(uint64x2_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u8)))
uint16x8_t __arm_vmulltq_int_m_u8(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u8)))
uint16x8_t __arm_vmulltq_int_m(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s16)))
int32x4_t __arm_vmulltq_int_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s16)))
int32x4_t __arm_vmulltq_int(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s32)))
int64x2_t __arm_vmulltq_int_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s32)))
int64x2_t __arm_vmulltq_int(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s8)))
int16x8_t __arm_vmulltq_int_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s8)))
int16x8_t __arm_vmulltq_int(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u16)))
uint32x4_t __arm_vmulltq_int_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u16)))
uint32x4_t __arm_vmulltq_int(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u32)))
uint64x2_t __arm_vmulltq_int_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u32)))
uint64x2_t __arm_vmulltq_int(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u8)))
uint16x8_t __arm_vmulltq_int_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u8)))
uint16x8_t __arm_vmulltq_int(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s16)))
int32x4_t __arm_vmulltq_int_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s16)))
int32x4_t __arm_vmulltq_int_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s32)))
int64x2_t __arm_vmulltq_int_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s32)))
int64x2_t __arm_vmulltq_int_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s8)))
int16x8_t __arm_vmulltq_int_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s8)))
int16x8_t __arm_vmulltq_int_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u16)))
uint32x4_t __arm_vmulltq_int_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u16)))
uint32x4_t __arm_vmulltq_int_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u32)))
uint64x2_t __arm_vmulltq_int_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u32)))
uint64x2_t __arm_vmulltq_int_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u8)))
uint16x8_t __arm_vmulltq_int_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u8)))
uint16x8_t __arm_vmulltq_int_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_m_p16)))
uint32x4_t __arm_vmulltq_poly_m_p16(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_m_p16)))
uint32x4_t __arm_vmulltq_poly_m(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_m_p8)))
uint16x8_t __arm_vmulltq_poly_m_p8(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_m_p8)))
uint16x8_t __arm_vmulltq_poly_m(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_p16)))
uint32x4_t __arm_vmulltq_poly_p16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_p16)))
uint32x4_t __arm_vmulltq_poly(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_p8)))
uint16x8_t __arm_vmulltq_poly_p8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_p8)))
uint16x8_t __arm_vmulltq_poly(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_x_p16)))
uint32x4_t __arm_vmulltq_poly_x_p16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_x_p16)))
uint32x4_t __arm_vmulltq_poly_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_x_p8)))
uint16x8_t __arm_vmulltq_poly_x_p8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_x_p8)))
uint16x8_t __arm_vmulltq_poly_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s16)))
int16x8_t __arm_vmulq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s16)))
int16x8_t __arm_vmulq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s32)))
int32x4_t __arm_vmulq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s32)))
int32x4_t __arm_vmulq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s8)))
int8x16_t __arm_vmulq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s8)))
int8x16_t __arm_vmulq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u16)))
uint16x8_t __arm_vmulq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u16)))
uint16x8_t __arm_vmulq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u32)))
uint32x4_t __arm_vmulq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u32)))
uint32x4_t __arm_vmulq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u8)))
uint8x16_t __arm_vmulq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u8)))
uint8x16_t __arm_vmulq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_s16)))
int16x8_t __arm_vmulq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_s16)))
int16x8_t __arm_vmulq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_s32)))
int32x4_t __arm_vmulq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_s32)))
int32x4_t __arm_vmulq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_s8)))
int8x16_t __arm_vmulq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_s8)))
int8x16_t __arm_vmulq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_u16)))
uint16x8_t __arm_vmulq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_u16)))
uint16x8_t __arm_vmulq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_u32)))
uint32x4_t __arm_vmulq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_u32)))
uint32x4_t __arm_vmulq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_u8)))
uint8x16_t __arm_vmulq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_u8)))
uint8x16_t __arm_vmulq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s16)))
int16x8_t __arm_vmulq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s16)))
int16x8_t __arm_vmulq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s32)))
int32x4_t __arm_vmulq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s32)))
int32x4_t __arm_vmulq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s8)))
int8x16_t __arm_vmulq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s8)))
int8x16_t __arm_vmulq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u16)))
uint16x8_t __arm_vmulq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u16)))
uint16x8_t __arm_vmulq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u32)))
uint32x4_t __arm_vmulq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u32)))
uint32x4_t __arm_vmulq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u8)))
uint8x16_t __arm_vmulq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u8)))
uint8x16_t __arm_vmulq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s16)))
int16x8_t __arm_vornq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s16)))
int16x8_t __arm_vornq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s32)))
int32x4_t __arm_vornq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s32)))
int32x4_t __arm_vornq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s8)))
int8x16_t __arm_vornq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s8)))
int8x16_t __arm_vornq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u16)))
uint16x8_t __arm_vornq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u16)))
uint16x8_t __arm_vornq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u32)))
uint32x4_t __arm_vornq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u32)))
uint32x4_t __arm_vornq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u8)))
uint8x16_t __arm_vornq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u8)))
uint8x16_t __arm_vornq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_s16)))
int16x8_t __arm_vornq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_s16)))
int16x8_t __arm_vornq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_s32)))
int32x4_t __arm_vornq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_s32)))
int32x4_t __arm_vornq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_s8)))
int8x16_t __arm_vornq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_s8)))
int8x16_t __arm_vornq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_u16)))
uint16x8_t __arm_vornq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_u16)))
uint16x8_t __arm_vornq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_u32)))
uint32x4_t __arm_vornq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_u32)))
uint32x4_t __arm_vornq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_u8)))
uint8x16_t __arm_vornq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_u8)))
uint8x16_t __arm_vornq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s16)))
int16x8_t __arm_vornq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s16)))
int16x8_t __arm_vornq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s32)))
int32x4_t __arm_vornq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s32)))
int32x4_t __arm_vornq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s8)))
int8x16_t __arm_vornq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s8)))
int8x16_t __arm_vornq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u16)))
uint16x8_t __arm_vornq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u16)))
uint16x8_t __arm_vornq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u32)))
uint32x4_t __arm_vornq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u32)))
uint32x4_t __arm_vornq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u8)))
uint8x16_t __arm_vornq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u8)))
uint8x16_t __arm_vornq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s16)))
int16x8_t __arm_vorrq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s16)))
int16x8_t __arm_vorrq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s32)))
int32x4_t __arm_vorrq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s32)))
int32x4_t __arm_vorrq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s8)))
int8x16_t __arm_vorrq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s8)))
int8x16_t __arm_vorrq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u16)))
uint16x8_t __arm_vorrq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u16)))
uint16x8_t __arm_vorrq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u32)))
uint32x4_t __arm_vorrq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u32)))
uint32x4_t __arm_vorrq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u8)))
uint8x16_t __arm_vorrq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u8)))
uint8x16_t __arm_vorrq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_s16)))
int16x8_t __arm_vorrq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_s16)))
int16x8_t __arm_vorrq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_s32)))
int32x4_t __arm_vorrq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_s32)))
int32x4_t __arm_vorrq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_s8)))
int8x16_t __arm_vorrq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_s8)))
int8x16_t __arm_vorrq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_u16)))
uint16x8_t __arm_vorrq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_u16)))
uint16x8_t __arm_vorrq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_u32)))
uint32x4_t __arm_vorrq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_u32)))
uint32x4_t __arm_vorrq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_u8)))
uint8x16_t __arm_vorrq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_u8)))
uint8x16_t __arm_vorrq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s16)))
int16x8_t __arm_vorrq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s16)))
int16x8_t __arm_vorrq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s32)))
int32x4_t __arm_vorrq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s32)))
int32x4_t __arm_vorrq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s8)))
int8x16_t __arm_vorrq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s8)))
int8x16_t __arm_vorrq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u16)))
uint16x8_t __arm_vorrq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u16)))
uint16x8_t __arm_vorrq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u32)))
uint32x4_t __arm_vorrq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u32)))
uint32x4_t __arm_vorrq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u8)))
uint8x16_t __arm_vorrq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u8)))
uint8x16_t __arm_vorrq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpnot)))
mve_pred16_t __arm_vpnot(mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_s16)))
int16x8_t __arm_vpselq_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_s16)))
int16x8_t __arm_vpselq(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_s32)))
int32x4_t __arm_vpselq_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_s32)))
int32x4_t __arm_vpselq(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_s64)))
int64x2_t __arm_vpselq_s64(int64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_s64)))
int64x2_t __arm_vpselq(int64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_s8)))
int8x16_t __arm_vpselq_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_s8)))
int8x16_t __arm_vpselq(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_u16)))
uint16x8_t __arm_vpselq_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_u16)))
uint16x8_t __arm_vpselq(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_u32)))
uint32x4_t __arm_vpselq_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_u32)))
uint32x4_t __arm_vpselq(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_u64)))
uint64x2_t __arm_vpselq_u64(uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_u64)))
uint64x2_t __arm_vpselq(uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_u8)))
uint8x16_t __arm_vpselq_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_u8)))
uint8x16_t __arm_vpselq(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s16)))
int16x8_t __arm_vqaddq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s16)))
int16x8_t __arm_vqaddq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s32)))
int32x4_t __arm_vqaddq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s32)))
int32x4_t __arm_vqaddq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s8)))
int8x16_t __arm_vqaddq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s8)))
int8x16_t __arm_vqaddq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u16)))
uint16x8_t __arm_vqaddq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u16)))
uint16x8_t __arm_vqaddq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u32)))
uint32x4_t __arm_vqaddq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u32)))
uint32x4_t __arm_vqaddq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u8)))
uint8x16_t __arm_vqaddq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u8)))
uint8x16_t __arm_vqaddq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s16)))
int16x8_t __arm_vqaddq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s16)))
int16x8_t __arm_vqaddq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s32)))
int32x4_t __arm_vqaddq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s32)))
int32x4_t __arm_vqaddq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s8)))
int8x16_t __arm_vqaddq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s8)))
int8x16_t __arm_vqaddq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u16)))
uint16x8_t __arm_vqaddq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u16)))
uint16x8_t __arm_vqaddq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u32)))
uint32x4_t __arm_vqaddq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u32)))
uint32x4_t __arm_vqaddq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u8)))
uint8x16_t __arm_vqaddq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u8)))
uint8x16_t __arm_vqaddq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s16)))
int16x8_t __arm_vqdmulhq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s16)))
int16x8_t __arm_vqdmulhq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s32)))
int32x4_t __arm_vqdmulhq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s32)))
int32x4_t __arm_vqdmulhq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s8)))
int8x16_t __arm_vqdmulhq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s8)))
int8x16_t __arm_vqdmulhq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s16)))
int16x8_t __arm_vqdmulhq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s16)))
int16x8_t __arm_vqdmulhq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s32)))
int32x4_t __arm_vqdmulhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s32)))
int32x4_t __arm_vqdmulhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s8)))
int8x16_t __arm_vqdmulhq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s8)))
int8x16_t __arm_vqdmulhq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s16)))
int16x8_t __arm_vqrdmulhq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s16)))
int16x8_t __arm_vqrdmulhq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s32)))
int32x4_t __arm_vqrdmulhq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s32)))
int32x4_t __arm_vqrdmulhq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s8)))
int8x16_t __arm_vqrdmulhq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s8)))
int8x16_t __arm_vqrdmulhq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s16)))
int16x8_t __arm_vqrdmulhq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s16)))
int16x8_t __arm_vqrdmulhq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s32)))
int32x4_t __arm_vqrdmulhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s32)))
int32x4_t __arm_vqrdmulhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s8)))
int8x16_t __arm_vqrdmulhq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s8)))
int8x16_t __arm_vqrdmulhq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s16)))
int16x8_t __arm_vqrshlq_m_n_s16(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s16)))
int16x8_t __arm_vqrshlq_m_n(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s32)))
int32x4_t __arm_vqrshlq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s32)))
int32x4_t __arm_vqrshlq_m_n(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s8)))
int8x16_t __arm_vqrshlq_m_n_s8(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s8)))
int8x16_t __arm_vqrshlq_m_n(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u16)))
uint16x8_t __arm_vqrshlq_m_n_u16(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u16)))
uint16x8_t __arm_vqrshlq_m_n(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u32)))
uint32x4_t __arm_vqrshlq_m_n_u32(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u32)))
uint32x4_t __arm_vqrshlq_m_n(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u8)))
uint8x16_t __arm_vqrshlq_m_n_u8(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u8)))
uint8x16_t __arm_vqrshlq_m_n(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s16)))
int16x8_t __arm_vqrshlq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s16)))
int16x8_t __arm_vqrshlq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s32)))
int32x4_t __arm_vqrshlq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s32)))
int32x4_t __arm_vqrshlq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s8)))
int8x16_t __arm_vqrshlq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s8)))
int8x16_t __arm_vqrshlq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u16)))
uint16x8_t __arm_vqrshlq_m_u16(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u16)))
uint16x8_t __arm_vqrshlq_m(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u32)))
uint32x4_t __arm_vqrshlq_m_u32(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u32)))
uint32x4_t __arm_vqrshlq_m(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u8)))
uint8x16_t __arm_vqrshlq_m_u8(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u8)))
uint8x16_t __arm_vqrshlq_m(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s16)))
int16x8_t __arm_vqrshlq_n_s16(int16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s16)))
int16x8_t __arm_vqrshlq(int16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s32)))
int32x4_t __arm_vqrshlq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s32)))
int32x4_t __arm_vqrshlq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s8)))
int8x16_t __arm_vqrshlq_n_s8(int8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s8)))
int8x16_t __arm_vqrshlq(int8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u16)))
uint16x8_t __arm_vqrshlq_n_u16(uint16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u16)))
uint16x8_t __arm_vqrshlq(uint16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u32)))
uint32x4_t __arm_vqrshlq_n_u32(uint32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u32)))
uint32x4_t __arm_vqrshlq(uint32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u8)))
uint8x16_t __arm_vqrshlq_n_u8(uint8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u8)))
uint8x16_t __arm_vqrshlq(uint8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s16)))
int16x8_t __arm_vqrshlq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s16)))
int16x8_t __arm_vqrshlq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s32)))
int32x4_t __arm_vqrshlq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s32)))
int32x4_t __arm_vqrshlq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s8)))
int8x16_t __arm_vqrshlq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s8)))
int8x16_t __arm_vqrshlq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u16)))
uint16x8_t __arm_vqrshlq_u16(uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u16)))
uint16x8_t __arm_vqrshlq(uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u32)))
uint32x4_t __arm_vqrshlq_u32(uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u32)))
uint32x4_t __arm_vqrshlq(uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u8)))
uint8x16_t __arm_vqrshlq_u8(uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u8)))
uint8x16_t __arm_vqrshlq(uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_s16)))
int8x16_t __arm_vqrshrnbq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_s16)))
int8x16_t __arm_vqrshrnbq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_s32)))
int16x8_t __arm_vqrshrnbq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_s32)))
int16x8_t __arm_vqrshrnbq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_u16)))
uint8x16_t __arm_vqrshrnbq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_u16)))
uint8x16_t __arm_vqrshrnbq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_u32)))
uint16x8_t __arm_vqrshrnbq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_u32)))
uint16x8_t __arm_vqrshrnbq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_s16)))
int8x16_t __arm_vqrshrnbq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_s16)))
int8x16_t __arm_vqrshrnbq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_s32)))
int16x8_t __arm_vqrshrnbq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_s32)))
int16x8_t __arm_vqrshrnbq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_u16)))
uint8x16_t __arm_vqrshrnbq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_u16)))
uint8x16_t __arm_vqrshrnbq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_u32)))
uint16x8_t __arm_vqrshrnbq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_u32)))
uint16x8_t __arm_vqrshrnbq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_s16)))
int8x16_t __arm_vqrshrntq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_s16)))
int8x16_t __arm_vqrshrntq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_s32)))
int16x8_t __arm_vqrshrntq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_s32)))
int16x8_t __arm_vqrshrntq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_u16)))
uint8x16_t __arm_vqrshrntq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_u16)))
uint8x16_t __arm_vqrshrntq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_u32)))
uint16x8_t __arm_vqrshrntq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_u32)))
uint16x8_t __arm_vqrshrntq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_s16)))
int8x16_t __arm_vqrshrntq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_s16)))
int8x16_t __arm_vqrshrntq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_s32)))
int16x8_t __arm_vqrshrntq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_s32)))
int16x8_t __arm_vqrshrntq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_u16)))
uint8x16_t __arm_vqrshrntq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_u16)))
uint8x16_t __arm_vqrshrntq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_u32)))
uint16x8_t __arm_vqrshrntq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_u32)))
uint16x8_t __arm_vqrshrntq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_m_n_s16)))
uint8x16_t __arm_vqrshrunbq_m_n_s16(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_m_n_s16)))
uint8x16_t __arm_vqrshrunbq_m(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_m_n_s32)))
uint16x8_t __arm_vqrshrunbq_m_n_s32(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_m_n_s32)))
uint16x8_t __arm_vqrshrunbq_m(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_n_s16)))
uint8x16_t __arm_vqrshrunbq_n_s16(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_n_s16)))
uint8x16_t __arm_vqrshrunbq(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_n_s32)))
uint16x8_t __arm_vqrshrunbq_n_s32(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_n_s32)))
uint16x8_t __arm_vqrshrunbq(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_m_n_s16)))
uint8x16_t __arm_vqrshruntq_m_n_s16(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_m_n_s16)))
uint8x16_t __arm_vqrshruntq_m(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_m_n_s32)))
uint16x8_t __arm_vqrshruntq_m_n_s32(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_m_n_s32)))
uint16x8_t __arm_vqrshruntq_m(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_n_s16)))
uint8x16_t __arm_vqrshruntq_n_s16(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_n_s16)))
uint8x16_t __arm_vqrshruntq(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_n_s32)))
uint16x8_t __arm_vqrshruntq_n_s32(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_n_s32)))
uint16x8_t __arm_vqrshruntq(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s16)))
int16x8_t __arm_vqshlq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s16)))
int16x8_t __arm_vqshlq_m_n(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s32)))
int32x4_t __arm_vqshlq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s32)))
int32x4_t __arm_vqshlq_m_n(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s8)))
int8x16_t __arm_vqshlq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s8)))
int8x16_t __arm_vqshlq_m_n(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u16)))
uint16x8_t __arm_vqshlq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u16)))
uint16x8_t __arm_vqshlq_m_n(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u32)))
uint32x4_t __arm_vqshlq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u32)))
uint32x4_t __arm_vqshlq_m_n(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u8)))
uint8x16_t __arm_vqshlq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u8)))
uint8x16_t __arm_vqshlq_m_n(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s16)))
int16x8_t __arm_vqshlq_m_r_s16(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s16)))
int16x8_t __arm_vqshlq_m_r(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s32)))
int32x4_t __arm_vqshlq_m_r_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s32)))
int32x4_t __arm_vqshlq_m_r(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s8)))
int8x16_t __arm_vqshlq_m_r_s8(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s8)))
int8x16_t __arm_vqshlq_m_r(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u16)))
uint16x8_t __arm_vqshlq_m_r_u16(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u16)))
uint16x8_t __arm_vqshlq_m_r(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u32)))
uint32x4_t __arm_vqshlq_m_r_u32(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u32)))
uint32x4_t __arm_vqshlq_m_r(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u8)))
uint8x16_t __arm_vqshlq_m_r_u8(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u8)))
uint8x16_t __arm_vqshlq_m_r(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s16)))
int16x8_t __arm_vqshlq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s16)))
int16x8_t __arm_vqshlq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s32)))
int32x4_t __arm_vqshlq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s32)))
int32x4_t __arm_vqshlq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s8)))
int8x16_t __arm_vqshlq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s8)))
int8x16_t __arm_vqshlq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u16)))
uint16x8_t __arm_vqshlq_m_u16(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u16)))
uint16x8_t __arm_vqshlq_m(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u32)))
uint32x4_t __arm_vqshlq_m_u32(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u32)))
uint32x4_t __arm_vqshlq_m(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u8)))
uint8x16_t __arm_vqshlq_m_u8(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u8)))
uint8x16_t __arm_vqshlq_m(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s16)))
int16x8_t __arm_vqshlq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s16)))
int16x8_t __arm_vqshlq_n(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s32)))
int32x4_t __arm_vqshlq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s32)))
int32x4_t __arm_vqshlq_n(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s8)))
int8x16_t __arm_vqshlq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s8)))
int8x16_t __arm_vqshlq_n(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u16)))
uint16x8_t __arm_vqshlq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u16)))
uint16x8_t __arm_vqshlq_n(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u32)))
uint32x4_t __arm_vqshlq_n_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u32)))
uint32x4_t __arm_vqshlq_n(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u8)))
uint8x16_t __arm_vqshlq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u8)))
uint8x16_t __arm_vqshlq_n(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s16)))
int16x8_t __arm_vqshlq_r_s16(int16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s16)))
int16x8_t __arm_vqshlq_r(int16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s32)))
int32x4_t __arm_vqshlq_r_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s32)))
int32x4_t __arm_vqshlq_r(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s8)))
int8x16_t __arm_vqshlq_r_s8(int8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s8)))
int8x16_t __arm_vqshlq_r(int8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u16)))
uint16x8_t __arm_vqshlq_r_u16(uint16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u16)))
uint16x8_t __arm_vqshlq_r(uint16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u32)))
uint32x4_t __arm_vqshlq_r_u32(uint32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u32)))
uint32x4_t __arm_vqshlq_r(uint32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u8)))
uint8x16_t __arm_vqshlq_r_u8(uint8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u8)))
uint8x16_t __arm_vqshlq_r(uint8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s16)))
int16x8_t __arm_vqshlq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s16)))
int16x8_t __arm_vqshlq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s32)))
int32x4_t __arm_vqshlq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s32)))
int32x4_t __arm_vqshlq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s8)))
int8x16_t __arm_vqshlq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s8)))
int8x16_t __arm_vqshlq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u16)))
uint16x8_t __arm_vqshlq_u16(uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u16)))
uint16x8_t __arm_vqshlq(uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u32)))
uint32x4_t __arm_vqshlq_u32(uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u32)))
uint32x4_t __arm_vqshlq(uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u8)))
uint8x16_t __arm_vqshlq_u8(uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u8)))
uint8x16_t __arm_vqshlq(uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s16)))
uint16x8_t __arm_vqshluq_m_n_s16(uint16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s16)))
uint16x8_t __arm_vqshluq_m(uint16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s32)))
uint32x4_t __arm_vqshluq_m_n_s32(uint32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s32)))
uint32x4_t __arm_vqshluq_m(uint32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s8)))
uint8x16_t __arm_vqshluq_m_n_s8(uint8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s8)))
uint8x16_t __arm_vqshluq_m(uint8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s16)))
uint16x8_t __arm_vqshluq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s16)))
uint16x8_t __arm_vqshluq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s32)))
uint32x4_t __arm_vqshluq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s32)))
uint32x4_t __arm_vqshluq(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s8)))
uint8x16_t __arm_vqshluq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s8)))
uint8x16_t __arm_vqshluq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_s16)))
int8x16_t __arm_vqshrnbq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_s16)))
int8x16_t __arm_vqshrnbq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_s32)))
int16x8_t __arm_vqshrnbq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_s32)))
int16x8_t __arm_vqshrnbq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_u16)))
uint8x16_t __arm_vqshrnbq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_u16)))
uint8x16_t __arm_vqshrnbq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_u32)))
uint16x8_t __arm_vqshrnbq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_u32)))
uint16x8_t __arm_vqshrnbq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_s16)))
int8x16_t __arm_vqshrnbq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_s16)))
int8x16_t __arm_vqshrnbq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_s32)))
int16x8_t __arm_vqshrnbq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_s32)))
int16x8_t __arm_vqshrnbq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_u16)))
uint8x16_t __arm_vqshrnbq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_u16)))
uint8x16_t __arm_vqshrnbq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_u32)))
uint16x8_t __arm_vqshrnbq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_u32)))
uint16x8_t __arm_vqshrnbq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_s16)))
int8x16_t __arm_vqshrntq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_s16)))
int8x16_t __arm_vqshrntq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_s32)))
int16x8_t __arm_vqshrntq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_s32)))
int16x8_t __arm_vqshrntq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_u16)))
uint8x16_t __arm_vqshrntq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_u16)))
uint8x16_t __arm_vqshrntq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_u32)))
uint16x8_t __arm_vqshrntq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_u32)))
uint16x8_t __arm_vqshrntq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_s16)))
int8x16_t __arm_vqshrntq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_s16)))
int8x16_t __arm_vqshrntq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_s32)))
int16x8_t __arm_vqshrntq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_s32)))
int16x8_t __arm_vqshrntq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_u16)))
uint8x16_t __arm_vqshrntq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_u16)))
uint8x16_t __arm_vqshrntq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_u32)))
uint16x8_t __arm_vqshrntq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_u32)))
uint16x8_t __arm_vqshrntq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_m_n_s16)))
uint8x16_t __arm_vqshrunbq_m_n_s16(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_m_n_s16)))
uint8x16_t __arm_vqshrunbq_m(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_m_n_s32)))
uint16x8_t __arm_vqshrunbq_m_n_s32(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_m_n_s32)))
uint16x8_t __arm_vqshrunbq_m(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_n_s16)))
uint8x16_t __arm_vqshrunbq_n_s16(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_n_s16)))
uint8x16_t __arm_vqshrunbq(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_n_s32)))
uint16x8_t __arm_vqshrunbq_n_s32(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_n_s32)))
uint16x8_t __arm_vqshrunbq(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_m_n_s16)))
uint8x16_t __arm_vqshruntq_m_n_s16(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_m_n_s16)))
uint8x16_t __arm_vqshruntq_m(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_m_n_s32)))
uint16x8_t __arm_vqshruntq_m_n_s32(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_m_n_s32)))
uint16x8_t __arm_vqshruntq_m(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_n_s16)))
uint8x16_t __arm_vqshruntq_n_s16(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_n_s16)))
uint8x16_t __arm_vqshruntq(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_n_s32)))
uint16x8_t __arm_vqshruntq_n_s32(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_n_s32)))
uint16x8_t __arm_vqshruntq(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s16)))
int16x8_t __arm_vqsubq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s16)))
int16x8_t __arm_vqsubq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s32)))
int32x4_t __arm_vqsubq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s32)))
int32x4_t __arm_vqsubq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s8)))
int8x16_t __arm_vqsubq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s8)))
int8x16_t __arm_vqsubq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u16)))
uint16x8_t __arm_vqsubq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u16)))
uint16x8_t __arm_vqsubq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u32)))
uint32x4_t __arm_vqsubq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u32)))
uint32x4_t __arm_vqsubq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u8)))
uint8x16_t __arm_vqsubq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u8)))
uint8x16_t __arm_vqsubq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s16)))
int16x8_t __arm_vqsubq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s16)))
int16x8_t __arm_vqsubq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s32)))
int32x4_t __arm_vqsubq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s32)))
int32x4_t __arm_vqsubq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s8)))
int8x16_t __arm_vqsubq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s8)))
int8x16_t __arm_vqsubq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u16)))
uint16x8_t __arm_vqsubq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u16)))
uint16x8_t __arm_vqsubq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u32)))
uint32x4_t __arm_vqsubq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u32)))
uint32x4_t __arm_vqsubq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u8)))
uint8x16_t __arm_vqsubq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u8)))
uint8x16_t __arm_vqsubq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s32)))
int16x8_t __arm_vreinterpretq_s16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s32)))
int16x8_t __arm_vreinterpretq_s16(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s64)))
int16x8_t __arm_vreinterpretq_s16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s64)))
int16x8_t __arm_vreinterpretq_s16(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s8)))
int16x8_t __arm_vreinterpretq_s16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s8)))
int16x8_t __arm_vreinterpretq_s16(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u16)))
int16x8_t __arm_vreinterpretq_s16_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u16)))
int16x8_t __arm_vreinterpretq_s16(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u32)))
int16x8_t __arm_vreinterpretq_s16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u32)))
int16x8_t __arm_vreinterpretq_s16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u64)))
int16x8_t __arm_vreinterpretq_s16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u64)))
int16x8_t __arm_vreinterpretq_s16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u8)))
int16x8_t __arm_vreinterpretq_s16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u8)))
int16x8_t __arm_vreinterpretq_s16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s16)))
int32x4_t __arm_vreinterpretq_s32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s16)))
int32x4_t __arm_vreinterpretq_s32(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s64)))
int32x4_t __arm_vreinterpretq_s32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s64)))
int32x4_t __arm_vreinterpretq_s32(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s8)))
int32x4_t __arm_vreinterpretq_s32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s8)))
int32x4_t __arm_vreinterpretq_s32(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u16)))
int32x4_t __arm_vreinterpretq_s32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u16)))
int32x4_t __arm_vreinterpretq_s32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u32)))
int32x4_t __arm_vreinterpretq_s32_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u32)))
int32x4_t __arm_vreinterpretq_s32(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u64)))
int32x4_t __arm_vreinterpretq_s32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u64)))
int32x4_t __arm_vreinterpretq_s32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u8)))
int32x4_t __arm_vreinterpretq_s32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u8)))
int32x4_t __arm_vreinterpretq_s32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s16)))
int64x2_t __arm_vreinterpretq_s64_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s16)))
int64x2_t __arm_vreinterpretq_s64(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s32)))
int64x2_t __arm_vreinterpretq_s64_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s32)))
int64x2_t __arm_vreinterpretq_s64(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s8)))
int64x2_t __arm_vreinterpretq_s64_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s8)))
int64x2_t __arm_vreinterpretq_s64(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u16)))
int64x2_t __arm_vreinterpretq_s64_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u16)))
int64x2_t __arm_vreinterpretq_s64(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u32)))
int64x2_t __arm_vreinterpretq_s64_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u32)))
int64x2_t __arm_vreinterpretq_s64(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u64)))
int64x2_t __arm_vreinterpretq_s64_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u64)))
int64x2_t __arm_vreinterpretq_s64(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u8)))
int64x2_t __arm_vreinterpretq_s64_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u8)))
int64x2_t __arm_vreinterpretq_s64(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s16)))
int8x16_t __arm_vreinterpretq_s8_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s16)))
int8x16_t __arm_vreinterpretq_s8(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s32)))
int8x16_t __arm_vreinterpretq_s8_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s32)))
int8x16_t __arm_vreinterpretq_s8(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s64)))
int8x16_t __arm_vreinterpretq_s8_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s64)))
int8x16_t __arm_vreinterpretq_s8(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u16)))
int8x16_t __arm_vreinterpretq_s8_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u16)))
int8x16_t __arm_vreinterpretq_s8(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u32)))
int8x16_t __arm_vreinterpretq_s8_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u32)))
int8x16_t __arm_vreinterpretq_s8(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u64)))
int8x16_t __arm_vreinterpretq_s8_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u64)))
int8x16_t __arm_vreinterpretq_s8(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u8)))
int8x16_t __arm_vreinterpretq_s8_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u8)))
int8x16_t __arm_vreinterpretq_s8(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s16)))
uint16x8_t __arm_vreinterpretq_u16_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s16)))
uint16x8_t __arm_vreinterpretq_u16(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s32)))
uint16x8_t __arm_vreinterpretq_u16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s32)))
uint16x8_t __arm_vreinterpretq_u16(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s64)))
uint16x8_t __arm_vreinterpretq_u16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s64)))
uint16x8_t __arm_vreinterpretq_u16(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s8)))
uint16x8_t __arm_vreinterpretq_u16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s8)))
uint16x8_t __arm_vreinterpretq_u16(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u32)))
uint16x8_t __arm_vreinterpretq_u16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u32)))
uint16x8_t __arm_vreinterpretq_u16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u64)))
uint16x8_t __arm_vreinterpretq_u16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u64)))
uint16x8_t __arm_vreinterpretq_u16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u8)))
uint16x8_t __arm_vreinterpretq_u16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u8)))
uint16x8_t __arm_vreinterpretq_u16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s16)))
uint32x4_t __arm_vreinterpretq_u32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s16)))
uint32x4_t __arm_vreinterpretq_u32(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s32)))
uint32x4_t __arm_vreinterpretq_u32_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s32)))
uint32x4_t __arm_vreinterpretq_u32(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s64)))
uint32x4_t __arm_vreinterpretq_u32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s64)))
uint32x4_t __arm_vreinterpretq_u32(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s8)))
uint32x4_t __arm_vreinterpretq_u32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s8)))
uint32x4_t __arm_vreinterpretq_u32(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u16)))
uint32x4_t __arm_vreinterpretq_u32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u16)))
uint32x4_t __arm_vreinterpretq_u32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u64)))
uint32x4_t __arm_vreinterpretq_u32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u64)))
uint32x4_t __arm_vreinterpretq_u32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u8)))
uint32x4_t __arm_vreinterpretq_u32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u8)))
uint32x4_t __arm_vreinterpretq_u32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s16)))
uint64x2_t __arm_vreinterpretq_u64_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s16)))
uint64x2_t __arm_vreinterpretq_u64(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s32)))
uint64x2_t __arm_vreinterpretq_u64_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s32)))
uint64x2_t __arm_vreinterpretq_u64(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s64)))
uint64x2_t __arm_vreinterpretq_u64_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s64)))
uint64x2_t __arm_vreinterpretq_u64(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s8)))
uint64x2_t __arm_vreinterpretq_u64_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s8)))
uint64x2_t __arm_vreinterpretq_u64(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u16)))
uint64x2_t __arm_vreinterpretq_u64_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u16)))
uint64x2_t __arm_vreinterpretq_u64(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u32)))
uint64x2_t __arm_vreinterpretq_u64_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u32)))
uint64x2_t __arm_vreinterpretq_u64(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u8)))
uint64x2_t __arm_vreinterpretq_u64_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u8)))
uint64x2_t __arm_vreinterpretq_u64(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s16)))
uint8x16_t __arm_vreinterpretq_u8_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s16)))
uint8x16_t __arm_vreinterpretq_u8(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s32)))
uint8x16_t __arm_vreinterpretq_u8_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s32)))
uint8x16_t __arm_vreinterpretq_u8(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s64)))
uint8x16_t __arm_vreinterpretq_u8_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s64)))
uint8x16_t __arm_vreinterpretq_u8(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s8)))
uint8x16_t __arm_vreinterpretq_u8_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s8)))
uint8x16_t __arm_vreinterpretq_u8(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u16)))
uint8x16_t __arm_vreinterpretq_u8_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u16)))
uint8x16_t __arm_vreinterpretq_u8(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u32)))
uint8x16_t __arm_vreinterpretq_u8_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u32)))
uint8x16_t __arm_vreinterpretq_u8(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u64)))
uint8x16_t __arm_vreinterpretq_u8_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u64)))
uint8x16_t __arm_vreinterpretq_u8(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s16)))
int16x8_t __arm_vrhaddq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s16)))
int16x8_t __arm_vrhaddq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s32)))
int32x4_t __arm_vrhaddq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s32)))
int32x4_t __arm_vrhaddq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s8)))
int8x16_t __arm_vrhaddq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s8)))
int8x16_t __arm_vrhaddq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u16)))
uint16x8_t __arm_vrhaddq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u16)))
uint16x8_t __arm_vrhaddq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u32)))
uint32x4_t __arm_vrhaddq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u32)))
uint32x4_t __arm_vrhaddq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u8)))
uint8x16_t __arm_vrhaddq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u8)))
uint8x16_t __arm_vrhaddq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s16)))
int16x8_t __arm_vrhaddq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s16)))
int16x8_t __arm_vrhaddq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s32)))
int32x4_t __arm_vrhaddq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s32)))
int32x4_t __arm_vrhaddq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s8)))
int8x16_t __arm_vrhaddq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s8)))
int8x16_t __arm_vrhaddq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u16)))
uint16x8_t __arm_vrhaddq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u16)))
uint16x8_t __arm_vrhaddq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u32)))
uint32x4_t __arm_vrhaddq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u32)))
uint32x4_t __arm_vrhaddq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u8)))
uint8x16_t __arm_vrhaddq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u8)))
uint8x16_t __arm_vrhaddq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s16)))
int16x8_t __arm_vrhaddq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s16)))
int16x8_t __arm_vrhaddq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s32)))
int32x4_t __arm_vrhaddq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s32)))
int32x4_t __arm_vrhaddq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s8)))
int8x16_t __arm_vrhaddq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s8)))
int8x16_t __arm_vrhaddq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u16)))
uint16x8_t __arm_vrhaddq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u16)))
uint16x8_t __arm_vrhaddq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u32)))
uint32x4_t __arm_vrhaddq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u32)))
uint32x4_t __arm_vrhaddq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u8)))
uint8x16_t __arm_vrhaddq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u8)))
uint8x16_t __arm_vrhaddq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_p_s32)))
int64_t __arm_vrmlaldavhaq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_p_s32)))
int64_t __arm_vrmlaldavhaq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_p_u32)))
uint64_t __arm_vrmlaldavhaq_p_u32(uint64_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_p_u32)))
uint64_t __arm_vrmlaldavhaq_p(uint64_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_s32)))
int64_t __arm_vrmlaldavhaq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_s32)))
int64_t __arm_vrmlaldavhaq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_u32)))
uint64_t __arm_vrmlaldavhaq_u32(uint64_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_u32)))
uint64_t __arm_vrmlaldavhaq(uint64_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaxq_p_s32)))
int64_t __arm_vrmlaldavhaxq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaxq_p_s32)))
int64_t __arm_vrmlaldavhaxq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaxq_s32)))
int64_t __arm_vrmlaldavhaxq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaxq_s32)))
int64_t __arm_vrmlaldavhaxq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_p_s32)))
int64_t __arm_vrmlaldavhq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_p_s32)))
int64_t __arm_vrmlaldavhq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_p_u32)))
uint64_t __arm_vrmlaldavhq_p_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_p_u32)))
uint64_t __arm_vrmlaldavhq_p(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_s32)))
int64_t __arm_vrmlaldavhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_s32)))
int64_t __arm_vrmlaldavhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_u32)))
uint64_t __arm_vrmlaldavhq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_u32)))
uint64_t __arm_vrmlaldavhq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhxq_p_s32)))
int64_t __arm_vrmlaldavhxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhxq_p_s32)))
int64_t __arm_vrmlaldavhxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhxq_s32)))
int64_t __arm_vrmlaldavhxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhxq_s32)))
int64_t __arm_vrmlaldavhxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaq_p_s32)))
int64_t __arm_vrmlsldavhaq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaq_p_s32)))
int64_t __arm_vrmlsldavhaq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaq_s32)))
int64_t __arm_vrmlsldavhaq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaq_s32)))
int64_t __arm_vrmlsldavhaq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaxq_p_s32)))
int64_t __arm_vrmlsldavhaxq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaxq_p_s32)))
int64_t __arm_vrmlsldavhaxq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaxq_s32)))
int64_t __arm_vrmlsldavhaxq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaxq_s32)))
int64_t __arm_vrmlsldavhaxq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhq_p_s32)))
int64_t __arm_vrmlsldavhq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhq_p_s32)))
int64_t __arm_vrmlsldavhq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhq_s32)))
int64_t __arm_vrmlsldavhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhq_s32)))
int64_t __arm_vrmlsldavhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhxq_p_s32)))
int64_t __arm_vrmlsldavhxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhxq_p_s32)))
int64_t __arm_vrmlsldavhxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhxq_s32)))
int64_t __arm_vrmlsldavhxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhxq_s32)))
int64_t __arm_vrmlsldavhxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s16)))
int16x8_t __arm_vrmulhq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s16)))
int16x8_t __arm_vrmulhq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s32)))
int32x4_t __arm_vrmulhq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s32)))
int32x4_t __arm_vrmulhq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s8)))
int8x16_t __arm_vrmulhq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s8)))
int8x16_t __arm_vrmulhq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u16)))
uint16x8_t __arm_vrmulhq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u16)))
uint16x8_t __arm_vrmulhq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u32)))
uint32x4_t __arm_vrmulhq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u32)))
uint32x4_t __arm_vrmulhq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u8)))
uint8x16_t __arm_vrmulhq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u8)))
uint8x16_t __arm_vrmulhq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s16)))
int16x8_t __arm_vrmulhq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s16)))
int16x8_t __arm_vrmulhq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s32)))
int32x4_t __arm_vrmulhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s32)))
int32x4_t __arm_vrmulhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s8)))
int8x16_t __arm_vrmulhq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s8)))
int8x16_t __arm_vrmulhq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u16)))
uint16x8_t __arm_vrmulhq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u16)))
uint16x8_t __arm_vrmulhq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u32)))
uint32x4_t __arm_vrmulhq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u32)))
uint32x4_t __arm_vrmulhq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u8)))
uint8x16_t __arm_vrmulhq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u8)))
uint8x16_t __arm_vrmulhq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s16)))
int16x8_t __arm_vrmulhq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s16)))
int16x8_t __arm_vrmulhq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s32)))
int32x4_t __arm_vrmulhq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s32)))
int32x4_t __arm_vrmulhq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s8)))
int8x16_t __arm_vrmulhq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s8)))
int8x16_t __arm_vrmulhq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u16)))
uint16x8_t __arm_vrmulhq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u16)))
uint16x8_t __arm_vrmulhq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u32)))
uint32x4_t __arm_vrmulhq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u32)))
uint32x4_t __arm_vrmulhq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u8)))
uint8x16_t __arm_vrmulhq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u8)))
uint8x16_t __arm_vrmulhq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s16)))
int16x8_t __arm_vrshlq_m_n_s16(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s16)))
int16x8_t __arm_vrshlq_m_n(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s32)))
int32x4_t __arm_vrshlq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s32)))
int32x4_t __arm_vrshlq_m_n(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s8)))
int8x16_t __arm_vrshlq_m_n_s8(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s8)))
int8x16_t __arm_vrshlq_m_n(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u16)))
uint16x8_t __arm_vrshlq_m_n_u16(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u16)))
uint16x8_t __arm_vrshlq_m_n(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u32)))
uint32x4_t __arm_vrshlq_m_n_u32(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u32)))
uint32x4_t __arm_vrshlq_m_n(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u8)))
uint8x16_t __arm_vrshlq_m_n_u8(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u8)))
uint8x16_t __arm_vrshlq_m_n(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s16)))
int16x8_t __arm_vrshlq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s16)))
int16x8_t __arm_vrshlq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s32)))
int32x4_t __arm_vrshlq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s32)))
int32x4_t __arm_vrshlq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s8)))
int8x16_t __arm_vrshlq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s8)))
int8x16_t __arm_vrshlq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u16)))
uint16x8_t __arm_vrshlq_m_u16(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u16)))
uint16x8_t __arm_vrshlq_m(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u32)))
uint32x4_t __arm_vrshlq_m_u32(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u32)))
uint32x4_t __arm_vrshlq_m(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u8)))
uint8x16_t __arm_vrshlq_m_u8(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u8)))
uint8x16_t __arm_vrshlq_m(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s16)))
int16x8_t __arm_vrshlq_n_s16(int16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s16)))
int16x8_t __arm_vrshlq(int16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s32)))
int32x4_t __arm_vrshlq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s32)))
int32x4_t __arm_vrshlq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s8)))
int8x16_t __arm_vrshlq_n_s8(int8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s8)))
int8x16_t __arm_vrshlq(int8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u16)))
uint16x8_t __arm_vrshlq_n_u16(uint16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u16)))
uint16x8_t __arm_vrshlq(uint16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u32)))
uint32x4_t __arm_vrshlq_n_u32(uint32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u32)))
uint32x4_t __arm_vrshlq(uint32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u8)))
uint8x16_t __arm_vrshlq_n_u8(uint8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u8)))
uint8x16_t __arm_vrshlq(uint8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s16)))
int16x8_t __arm_vrshlq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s16)))
int16x8_t __arm_vrshlq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s32)))
int32x4_t __arm_vrshlq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s32)))
int32x4_t __arm_vrshlq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s8)))
int8x16_t __arm_vrshlq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s8)))
int8x16_t __arm_vrshlq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u16)))
uint16x8_t __arm_vrshlq_u16(uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u16)))
uint16x8_t __arm_vrshlq(uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u32)))
uint32x4_t __arm_vrshlq_u32(uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u32)))
uint32x4_t __arm_vrshlq(uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u8)))
uint8x16_t __arm_vrshlq_u8(uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u8)))
uint8x16_t __arm_vrshlq(uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s16)))
int16x8_t __arm_vrshlq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s16)))
int16x8_t __arm_vrshlq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s32)))
int32x4_t __arm_vrshlq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s32)))
int32x4_t __arm_vrshlq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s8)))
int8x16_t __arm_vrshlq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s8)))
int8x16_t __arm_vrshlq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u16)))
uint16x8_t __arm_vrshlq_x_u16(uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u16)))
uint16x8_t __arm_vrshlq_x(uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u32)))
uint32x4_t __arm_vrshlq_x_u32(uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u32)))
uint32x4_t __arm_vrshlq_x(uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u8)))
uint8x16_t __arm_vrshlq_x_u8(uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u8)))
uint8x16_t __arm_vrshlq_x(uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_s16)))
int8x16_t __arm_vrshrnbq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_s16)))
int8x16_t __arm_vrshrnbq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_s32)))
int16x8_t __arm_vrshrnbq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_s32)))
int16x8_t __arm_vrshrnbq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_u16)))
uint8x16_t __arm_vrshrnbq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_u16)))
uint8x16_t __arm_vrshrnbq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_u32)))
uint16x8_t __arm_vrshrnbq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_u32)))
uint16x8_t __arm_vrshrnbq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_s16)))
int8x16_t __arm_vrshrnbq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_s16)))
int8x16_t __arm_vrshrnbq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_s32)))
int16x8_t __arm_vrshrnbq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_s32)))
int16x8_t __arm_vrshrnbq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_u16)))
uint8x16_t __arm_vrshrnbq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_u16)))
uint8x16_t __arm_vrshrnbq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_u32)))
uint16x8_t __arm_vrshrnbq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_u32)))
uint16x8_t __arm_vrshrnbq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_s16)))
int8x16_t __arm_vrshrntq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_s16)))
int8x16_t __arm_vrshrntq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_s32)))
int16x8_t __arm_vrshrntq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_s32)))
int16x8_t __arm_vrshrntq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_u16)))
uint8x16_t __arm_vrshrntq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_u16)))
uint8x16_t __arm_vrshrntq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_u32)))
uint16x8_t __arm_vrshrntq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_u32)))
uint16x8_t __arm_vrshrntq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_s16)))
int8x16_t __arm_vrshrntq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_s16)))
int8x16_t __arm_vrshrntq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_s32)))
int16x8_t __arm_vrshrntq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_s32)))
int16x8_t __arm_vrshrntq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_u16)))
uint8x16_t __arm_vrshrntq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_u16)))
uint8x16_t __arm_vrshrntq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_u32)))
uint16x8_t __arm_vrshrntq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_u32)))
uint16x8_t __arm_vrshrntq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s16)))
int16x8_t __arm_vrshrq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s16)))
int16x8_t __arm_vrshrq_m(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s32)))
int32x4_t __arm_vrshrq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s32)))
int32x4_t __arm_vrshrq_m(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s8)))
int8x16_t __arm_vrshrq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s8)))
int8x16_t __arm_vrshrq_m(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u16)))
uint16x8_t __arm_vrshrq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u16)))
uint16x8_t __arm_vrshrq_m(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u32)))
uint32x4_t __arm_vrshrq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u32)))
uint32x4_t __arm_vrshrq_m(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u8)))
uint8x16_t __arm_vrshrq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u8)))
uint8x16_t __arm_vrshrq_m(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s16)))
int16x8_t __arm_vrshrq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s16)))
int16x8_t __arm_vrshrq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s32)))
int32x4_t __arm_vrshrq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s32)))
int32x4_t __arm_vrshrq(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s8)))
int8x16_t __arm_vrshrq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s8)))
int8x16_t __arm_vrshrq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u16)))
uint16x8_t __arm_vrshrq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u16)))
uint16x8_t __arm_vrshrq(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u32)))
uint32x4_t __arm_vrshrq_n_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u32)))
uint32x4_t __arm_vrshrq(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u8)))
uint8x16_t __arm_vrshrq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u8)))
uint8x16_t __arm_vrshrq(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s16)))
int16x8_t __arm_vrshrq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s16)))
int16x8_t __arm_vrshrq_x(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s32)))
int32x4_t __arm_vrshrq_x_n_s32(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s32)))
int32x4_t __arm_vrshrq_x(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s8)))
int8x16_t __arm_vrshrq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s8)))
int8x16_t __arm_vrshrq_x(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u16)))
uint16x8_t __arm_vrshrq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u16)))
uint16x8_t __arm_vrshrq_x(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u32)))
uint32x4_t __arm_vrshrq_x_n_u32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u32)))
uint32x4_t __arm_vrshrq_x(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u8)))
uint8x16_t __arm_vrshrq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u8)))
uint8x16_t __arm_vrshrq_x(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s16)))
int16x8_t __arm_vsetq_lane_s16(int16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s16)))
int16x8_t __arm_vsetq_lane(int16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s32)))
int32x4_t __arm_vsetq_lane_s32(int32_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s32)))
int32x4_t __arm_vsetq_lane(int32_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s64)))
int64x2_t __arm_vsetq_lane_s64(int64_t, int64x2_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s64)))
int64x2_t __arm_vsetq_lane(int64_t, int64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s8)))
int8x16_t __arm_vsetq_lane_s8(int8_t, int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s8)))
int8x16_t __arm_vsetq_lane(int8_t, int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u16)))
uint16x8_t __arm_vsetq_lane_u16(uint16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u16)))
uint16x8_t __arm_vsetq_lane(uint16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u32)))
uint32x4_t __arm_vsetq_lane_u32(uint32_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u32)))
uint32x4_t __arm_vsetq_lane(uint32_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u64)))
uint64x2_t __arm_vsetq_lane_u64(uint64_t, uint64x2_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u64)))
uint64x2_t __arm_vsetq_lane(uint64_t, uint64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u8)))
uint8x16_t __arm_vsetq_lane_u8(uint8_t, uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u8)))
uint8x16_t __arm_vsetq_lane(uint8_t, uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_s16)))
int32x4_t __arm_vshllbq_m_n_s16(int32x4_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_s16)))
int32x4_t __arm_vshllbq_m(int32x4_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_s8)))
int16x8_t __arm_vshllbq_m_n_s8(int16x8_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_s8)))
int16x8_t __arm_vshllbq_m(int16x8_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_u16)))
uint32x4_t __arm_vshllbq_m_n_u16(uint32x4_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_u16)))
uint32x4_t __arm_vshllbq_m(uint32x4_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_u8)))
uint16x8_t __arm_vshllbq_m_n_u8(uint16x8_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_u8)))
uint16x8_t __arm_vshllbq_m(uint16x8_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_s16)))
int32x4_t __arm_vshllbq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_s16)))
int32x4_t __arm_vshllbq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_s8)))
int16x8_t __arm_vshllbq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_s8)))
int16x8_t __arm_vshllbq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_u16)))
uint32x4_t __arm_vshllbq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_u16)))
uint32x4_t __arm_vshllbq(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_u8)))
uint16x8_t __arm_vshllbq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_u8)))
uint16x8_t __arm_vshllbq(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_s16)))
int32x4_t __arm_vshllbq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_s16)))
int32x4_t __arm_vshllbq_x(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_s8)))
int16x8_t __arm_vshllbq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_s8)))
int16x8_t __arm_vshllbq_x(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_u16)))
uint32x4_t __arm_vshllbq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_u16)))
uint32x4_t __arm_vshllbq_x(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_u8)))
uint16x8_t __arm_vshllbq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_u8)))
uint16x8_t __arm_vshllbq_x(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_s16)))
int32x4_t __arm_vshlltq_m_n_s16(int32x4_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_s16)))
int32x4_t __arm_vshlltq_m(int32x4_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_s8)))
int16x8_t __arm_vshlltq_m_n_s8(int16x8_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_s8)))
int16x8_t __arm_vshlltq_m(int16x8_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_u16)))
uint32x4_t __arm_vshlltq_m_n_u16(uint32x4_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_u16)))
uint32x4_t __arm_vshlltq_m(uint32x4_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_u8)))
uint16x8_t __arm_vshlltq_m_n_u8(uint16x8_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_u8)))
uint16x8_t __arm_vshlltq_m(uint16x8_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_s16)))
int32x4_t __arm_vshlltq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_s16)))
int32x4_t __arm_vshlltq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_s8)))
int16x8_t __arm_vshlltq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_s8)))
int16x8_t __arm_vshlltq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_u16)))
uint32x4_t __arm_vshlltq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_u16)))
uint32x4_t __arm_vshlltq(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_u8)))
uint16x8_t __arm_vshlltq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_u8)))
uint16x8_t __arm_vshlltq(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_s16)))
int32x4_t __arm_vshlltq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_s16)))
int32x4_t __arm_vshlltq_x(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_s8)))
int16x8_t __arm_vshlltq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_s8)))
int16x8_t __arm_vshlltq_x(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_u16)))
uint32x4_t __arm_vshlltq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_u16)))
uint32x4_t __arm_vshlltq_x(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_u8)))
uint16x8_t __arm_vshlltq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_u8)))
uint16x8_t __arm_vshlltq_x(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s16)))
int16x8_t __arm_vshlq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s16)))
int16x8_t __arm_vshlq_m_n(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s32)))
int32x4_t __arm_vshlq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s32)))
int32x4_t __arm_vshlq_m_n(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s8)))
int8x16_t __arm_vshlq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s8)))
int8x16_t __arm_vshlq_m_n(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u16)))
uint16x8_t __arm_vshlq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u16)))
uint16x8_t __arm_vshlq_m_n(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u32)))
uint32x4_t __arm_vshlq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u32)))
uint32x4_t __arm_vshlq_m_n(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u8)))
uint8x16_t __arm_vshlq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u8)))
uint8x16_t __arm_vshlq_m_n(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s16)))
int16x8_t __arm_vshlq_m_r_s16(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s16)))
int16x8_t __arm_vshlq_m_r(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s32)))
int32x4_t __arm_vshlq_m_r_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s32)))
int32x4_t __arm_vshlq_m_r(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s8)))
int8x16_t __arm_vshlq_m_r_s8(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s8)))
int8x16_t __arm_vshlq_m_r(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u16)))
uint16x8_t __arm_vshlq_m_r_u16(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u16)))
uint16x8_t __arm_vshlq_m_r(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u32)))
uint32x4_t __arm_vshlq_m_r_u32(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u32)))
uint32x4_t __arm_vshlq_m_r(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u8)))
uint8x16_t __arm_vshlq_m_r_u8(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u8)))
uint8x16_t __arm_vshlq_m_r(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s16)))
int16x8_t __arm_vshlq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s16)))
int16x8_t __arm_vshlq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s32)))
int32x4_t __arm_vshlq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s32)))
int32x4_t __arm_vshlq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s8)))
int8x16_t __arm_vshlq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s8)))
int8x16_t __arm_vshlq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u16)))
uint16x8_t __arm_vshlq_m_u16(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u16)))
uint16x8_t __arm_vshlq_m(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u32)))
uint32x4_t __arm_vshlq_m_u32(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u32)))
uint32x4_t __arm_vshlq_m(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u8)))
uint8x16_t __arm_vshlq_m_u8(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u8)))
uint8x16_t __arm_vshlq_m(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s16)))
int16x8_t __arm_vshlq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s16)))
int16x8_t __arm_vshlq_n(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s32)))
int32x4_t __arm_vshlq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s32)))
int32x4_t __arm_vshlq_n(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s8)))
int8x16_t __arm_vshlq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s8)))
int8x16_t __arm_vshlq_n(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u16)))
uint16x8_t __arm_vshlq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u16)))
uint16x8_t __arm_vshlq_n(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u32)))
uint32x4_t __arm_vshlq_n_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u32)))
uint32x4_t __arm_vshlq_n(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u8)))
uint8x16_t __arm_vshlq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u8)))
uint8x16_t __arm_vshlq_n(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s16)))
int16x8_t __arm_vshlq_r_s16(int16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s16)))
int16x8_t __arm_vshlq_r(int16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s32)))
int32x4_t __arm_vshlq_r_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s32)))
int32x4_t __arm_vshlq_r(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s8)))
int8x16_t __arm_vshlq_r_s8(int8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s8)))
int8x16_t __arm_vshlq_r(int8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u16)))
uint16x8_t __arm_vshlq_r_u16(uint16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u16)))
uint16x8_t __arm_vshlq_r(uint16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u32)))
uint32x4_t __arm_vshlq_r_u32(uint32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u32)))
uint32x4_t __arm_vshlq_r(uint32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u8)))
uint8x16_t __arm_vshlq_r_u8(uint8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u8)))
uint8x16_t __arm_vshlq_r(uint8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_s16)))
int16x8_t __arm_vshlq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_s16)))
int16x8_t __arm_vshlq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_s32)))
int32x4_t __arm_vshlq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_s32)))
int32x4_t __arm_vshlq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_s8)))
int8x16_t __arm_vshlq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_s8)))
int8x16_t __arm_vshlq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_u16)))
uint16x8_t __arm_vshlq_u16(uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_u16)))
uint16x8_t __arm_vshlq(uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_u32)))
uint32x4_t __arm_vshlq_u32(uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_u32)))
uint32x4_t __arm_vshlq(uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_u8)))
uint8x16_t __arm_vshlq_u8(uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_u8)))
uint8x16_t __arm_vshlq(uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s16)))
int16x8_t __arm_vshlq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s16)))
int16x8_t __arm_vshlq_x_n(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s32)))
int32x4_t __arm_vshlq_x_n_s32(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s32)))
int32x4_t __arm_vshlq_x_n(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s8)))
int8x16_t __arm_vshlq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s8)))
int8x16_t __arm_vshlq_x_n(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u16)))
uint16x8_t __arm_vshlq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u16)))
uint16x8_t __arm_vshlq_x_n(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u32)))
uint32x4_t __arm_vshlq_x_n_u32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u32)))
uint32x4_t __arm_vshlq_x_n(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u8)))
uint8x16_t __arm_vshlq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u8)))
uint8x16_t __arm_vshlq_x_n(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s16)))
int16x8_t __arm_vshlq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s16)))
int16x8_t __arm_vshlq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s32)))
int32x4_t __arm_vshlq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s32)))
int32x4_t __arm_vshlq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s8)))
int8x16_t __arm_vshlq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s8)))
int8x16_t __arm_vshlq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u16)))
uint16x8_t __arm_vshlq_x_u16(uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u16)))
uint16x8_t __arm_vshlq_x(uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u32)))
uint32x4_t __arm_vshlq_x_u32(uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u32)))
uint32x4_t __arm_vshlq_x(uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u8)))
uint8x16_t __arm_vshlq_x_u8(uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u8)))
uint8x16_t __arm_vshlq_x(uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_s16)))
int8x16_t __arm_vshrnbq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_s16)))
int8x16_t __arm_vshrnbq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_s32)))
int16x8_t __arm_vshrnbq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_s32)))
int16x8_t __arm_vshrnbq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_u16)))
uint8x16_t __arm_vshrnbq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_u16)))
uint8x16_t __arm_vshrnbq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_u32)))
uint16x8_t __arm_vshrnbq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_u32)))
uint16x8_t __arm_vshrnbq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_s16)))
int8x16_t __arm_vshrnbq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_s16)))
int8x16_t __arm_vshrnbq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_s32)))
int16x8_t __arm_vshrnbq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_s32)))
int16x8_t __arm_vshrnbq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_u16)))
uint8x16_t __arm_vshrnbq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_u16)))
uint8x16_t __arm_vshrnbq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_u32)))
uint16x8_t __arm_vshrnbq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_u32)))
uint16x8_t __arm_vshrnbq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_s16)))
int8x16_t __arm_vshrntq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_s16)))
int8x16_t __arm_vshrntq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_s32)))
int16x8_t __arm_vshrntq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_s32)))
int16x8_t __arm_vshrntq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_u16)))
uint8x16_t __arm_vshrntq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_u16)))
uint8x16_t __arm_vshrntq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_u32)))
uint16x8_t __arm_vshrntq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_u32)))
uint16x8_t __arm_vshrntq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_s16)))
int8x16_t __arm_vshrntq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_s16)))
int8x16_t __arm_vshrntq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_s32)))
int16x8_t __arm_vshrntq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_s32)))
int16x8_t __arm_vshrntq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_u16)))
uint8x16_t __arm_vshrntq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_u16)))
uint8x16_t __arm_vshrntq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_u32)))
uint16x8_t __arm_vshrntq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_u32)))
uint16x8_t __arm_vshrntq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s16)))
int16x8_t __arm_vshrq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s16)))
int16x8_t __arm_vshrq_m(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s32)))
int32x4_t __arm_vshrq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s32)))
int32x4_t __arm_vshrq_m(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s8)))
int8x16_t __arm_vshrq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s8)))
int8x16_t __arm_vshrq_m(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u16)))
uint16x8_t __arm_vshrq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u16)))
uint16x8_t __arm_vshrq_m(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u32)))
uint32x4_t __arm_vshrq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u32)))
uint32x4_t __arm_vshrq_m(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u8)))
uint8x16_t __arm_vshrq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u8)))
uint8x16_t __arm_vshrq_m(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s16)))
int16x8_t __arm_vshrq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s16)))
int16x8_t __arm_vshrq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s32)))
int32x4_t __arm_vshrq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s32)))
int32x4_t __arm_vshrq(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s8)))
int8x16_t __arm_vshrq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s8)))
int8x16_t __arm_vshrq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u16)))
uint16x8_t __arm_vshrq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u16)))
uint16x8_t __arm_vshrq(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u32)))
uint32x4_t __arm_vshrq_n_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u32)))
uint32x4_t __arm_vshrq(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u8)))
uint8x16_t __arm_vshrq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u8)))
uint8x16_t __arm_vshrq(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s16)))
int16x8_t __arm_vshrq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s16)))
int16x8_t __arm_vshrq_x(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s32)))
int32x4_t __arm_vshrq_x_n_s32(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s32)))
int32x4_t __arm_vshrq_x(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s8)))
int8x16_t __arm_vshrq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s8)))
int8x16_t __arm_vshrq_x(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u16)))
uint16x8_t __arm_vshrq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u16)))
uint16x8_t __arm_vshrq_x(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u32)))
uint32x4_t __arm_vshrq_x_n_u32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u32)))
uint32x4_t __arm_vshrq_x(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u8)))
uint8x16_t __arm_vshrq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u8)))
uint8x16_t __arm_vshrq_x(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s16)))
int16x8_t __arm_vsliq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s16)))
int16x8_t __arm_vsliq_m(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s32)))
int32x4_t __arm_vsliq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s32)))
int32x4_t __arm_vsliq_m(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s8)))
int8x16_t __arm_vsliq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s8)))
int8x16_t __arm_vsliq_m(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u16)))
uint16x8_t __arm_vsliq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u16)))
uint16x8_t __arm_vsliq_m(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u32)))
uint32x4_t __arm_vsliq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u32)))
uint32x4_t __arm_vsliq_m(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u8)))
uint8x16_t __arm_vsliq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u8)))
uint8x16_t __arm_vsliq_m(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s16)))
int16x8_t __arm_vsliq_n_s16(int16x8_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s16)))
int16x8_t __arm_vsliq(int16x8_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s32)))
int32x4_t __arm_vsliq_n_s32(int32x4_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s32)))
int32x4_t __arm_vsliq(int32x4_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s8)))
int8x16_t __arm_vsliq_n_s8(int8x16_t, int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s8)))
int8x16_t __arm_vsliq(int8x16_t, int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u16)))
uint16x8_t __arm_vsliq_n_u16(uint16x8_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u16)))
uint16x8_t __arm_vsliq(uint16x8_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u32)))
uint32x4_t __arm_vsliq_n_u32(uint32x4_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u32)))
uint32x4_t __arm_vsliq(uint32x4_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u8)))
uint8x16_t __arm_vsliq_n_u8(uint8x16_t, uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u8)))
uint8x16_t __arm_vsliq(uint8x16_t, uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s16)))
int16x8_t __arm_vsriq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s16)))
int16x8_t __arm_vsriq_m(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s32)))
int32x4_t __arm_vsriq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s32)))
int32x4_t __arm_vsriq_m(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s8)))
int8x16_t __arm_vsriq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s8)))
int8x16_t __arm_vsriq_m(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u16)))
uint16x8_t __arm_vsriq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u16)))
uint16x8_t __arm_vsriq_m(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u32)))
uint32x4_t __arm_vsriq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u32)))
uint32x4_t __arm_vsriq_m(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u8)))
uint8x16_t __arm_vsriq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u8)))
uint8x16_t __arm_vsriq_m(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s16)))
int16x8_t __arm_vsriq_n_s16(int16x8_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s16)))
int16x8_t __arm_vsriq(int16x8_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s32)))
int32x4_t __arm_vsriq_n_s32(int32x4_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s32)))
int32x4_t __arm_vsriq(int32x4_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s8)))
int8x16_t __arm_vsriq_n_s8(int8x16_t, int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s8)))
int8x16_t __arm_vsriq(int8x16_t, int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u16)))
uint16x8_t __arm_vsriq_n_u16(uint16x8_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u16)))
uint16x8_t __arm_vsriq(uint16x8_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u32)))
uint32x4_t __arm_vsriq_n_u32(uint32x4_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u32)))
uint32x4_t __arm_vsriq(uint32x4_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u8)))
uint8x16_t __arm_vsriq_n_u8(uint8x16_t, uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u8)))
uint8x16_t __arm_vsriq(uint8x16_t, uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s16)))
void __arm_vst1q_p_s16(int16_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s16)))
void __arm_vst1q_p(int16_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s32)))
void __arm_vst1q_p_s32(int32_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s32)))
void __arm_vst1q_p(int32_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s8)))
void __arm_vst1q_p_s8(int8_t *, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s8)))
void __arm_vst1q_p(int8_t *, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u16)))
void __arm_vst1q_p_u16(uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u16)))
void __arm_vst1q_p(uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u32)))
void __arm_vst1q_p_u32(uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u32)))
void __arm_vst1q_p(uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u8)))
void __arm_vst1q_p_u8(uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u8)))
void __arm_vst1q_p(uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_s16)))
void __arm_vst1q_s16(int16_t *, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_s16)))
void __arm_vst1q(int16_t *, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_s32)))
void __arm_vst1q_s32(int32_t *, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_s32)))
void __arm_vst1q(int32_t *, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_s8)))
void __arm_vst1q_s8(int8_t *, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_s8)))
void __arm_vst1q(int8_t *, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_u16)))
void __arm_vst1q_u16(uint16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_u16)))
void __arm_vst1q(uint16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_u32)))
void __arm_vst1q_u32(uint32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_u32)))
void __arm_vst1q(uint32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_u8)))
void __arm_vst1q_u8(uint8_t *, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_u8)))
void __arm_vst1q(uint8_t *, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_s16)))
void __arm_vst2q_s16(int16_t *, int16x8x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_s16)))
void __arm_vst2q(int16_t *, int16x8x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_s32)))
void __arm_vst2q_s32(int32_t *, int32x4x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_s32)))
void __arm_vst2q(int32_t *, int32x4x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_s8)))
void __arm_vst2q_s8(int8_t *, int8x16x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_s8)))
void __arm_vst2q(int8_t *, int8x16x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_u16)))
void __arm_vst2q_u16(uint16_t *, uint16x8x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_u16)))
void __arm_vst2q(uint16_t *, uint16x8x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_u32)))
void __arm_vst2q_u32(uint32_t *, uint32x4x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_u32)))
void __arm_vst2q(uint32_t *, uint32x4x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_u8)))
void __arm_vst2q_u8(uint8_t *, uint8x16x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_u8)))
void __arm_vst2q(uint8_t *, uint8x16x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_s16)))
void __arm_vst4q_s16(int16_t *, int16x8x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_s16)))
void __arm_vst4q(int16_t *, int16x8x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_s32)))
void __arm_vst4q_s32(int32_t *, int32x4x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_s32)))
void __arm_vst4q(int32_t *, int32x4x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_s8)))
void __arm_vst4q_s8(int8_t *, int8x16x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_s8)))
void __arm_vst4q(int8_t *, int8x16x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_u16)))
void __arm_vst4q_u16(uint16_t *, uint16x8x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_u16)))
void __arm_vst4q(uint16_t *, uint16x8x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_u32)))
void __arm_vst4q_u32(uint32_t *, uint32x4x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_u32)))
void __arm_vst4q(uint32_t *, uint32x4x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_u8)))
void __arm_vst4q_u8(uint8_t *, uint8x16x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_u8)))
void __arm_vst4q(uint8_t *, uint8x16x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s16)))
void __arm_vstrbq_p_s16(int8_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s16)))
void __arm_vstrbq_p(int8_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s32)))
void __arm_vstrbq_p_s32(int8_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s32)))
void __arm_vstrbq_p(int8_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s8)))
void __arm_vstrbq_p_s8(int8_t *, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s8)))
void __arm_vstrbq_p(int8_t *, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u16)))
void __arm_vstrbq_p_u16(uint8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u16)))
void __arm_vstrbq_p(uint8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u32)))
void __arm_vstrbq_p_u32(uint8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u32)))
void __arm_vstrbq_p(uint8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u8)))
void __arm_vstrbq_p_u8(uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u8)))
void __arm_vstrbq_p(uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s16)))
void __arm_vstrbq_s16(int8_t *, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s16)))
void __arm_vstrbq(int8_t *, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s32)))
void __arm_vstrbq_s32(int8_t *, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s32)))
void __arm_vstrbq(int8_t *, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s8)))
void __arm_vstrbq_s8(int8_t *, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s8)))
void __arm_vstrbq(int8_t *, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s16)))
void __arm_vstrbq_scatter_offset_p_s16(int8_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s16)))
void __arm_vstrbq_scatter_offset_p(int8_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s32)))
void __arm_vstrbq_scatter_offset_p_s32(int8_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s32)))
void __arm_vstrbq_scatter_offset_p(int8_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s8)))
void __arm_vstrbq_scatter_offset_p_s8(int8_t *, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s8)))
void __arm_vstrbq_scatter_offset_p(int8_t *, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u16)))
void __arm_vstrbq_scatter_offset_p_u16(uint8_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u16)))
void __arm_vstrbq_scatter_offset_p(uint8_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u32)))
void __arm_vstrbq_scatter_offset_p_u32(uint8_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u32)))
void __arm_vstrbq_scatter_offset_p(uint8_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u8)))
void __arm_vstrbq_scatter_offset_p_u8(uint8_t *, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u8)))
void __arm_vstrbq_scatter_offset_p(uint8_t *, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s16)))
void __arm_vstrbq_scatter_offset_s16(int8_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s16)))
void __arm_vstrbq_scatter_offset(int8_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s32)))
void __arm_vstrbq_scatter_offset_s32(int8_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s32)))
void __arm_vstrbq_scatter_offset(int8_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s8)))
void __arm_vstrbq_scatter_offset_s8(int8_t *, uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s8)))
void __arm_vstrbq_scatter_offset(int8_t *, uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u16)))
void __arm_vstrbq_scatter_offset_u16(uint8_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u16)))
void __arm_vstrbq_scatter_offset(uint8_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u32)))
void __arm_vstrbq_scatter_offset_u32(uint8_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u32)))
void __arm_vstrbq_scatter_offset(uint8_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u8)))
void __arm_vstrbq_scatter_offset_u8(uint8_t *, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u8)))
void __arm_vstrbq_scatter_offset(uint8_t *, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u16)))
void __arm_vstrbq_u16(uint8_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u16)))
void __arm_vstrbq(uint8_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u32)))
void __arm_vstrbq_u32(uint8_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u32)))
void __arm_vstrbq(uint8_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u8)))
void __arm_vstrbq_u8(uint8_t *, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u8)))
void __arm_vstrbq(uint8_t *, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_p_s64)))
void __arm_vstrdq_scatter_base_p_s64(uint64x2_t, int, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_p_s64)))
void __arm_vstrdq_scatter_base_p(uint64x2_t, int, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_p_u64)))
void __arm_vstrdq_scatter_base_p_u64(uint64x2_t, int, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_p_u64)))
void __arm_vstrdq_scatter_base_p(uint64x2_t, int, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_s64)))
void __arm_vstrdq_scatter_base_s64(uint64x2_t, int, int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_s64)))
void __arm_vstrdq_scatter_base(uint64x2_t, int, int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_u64)))
void __arm_vstrdq_scatter_base_u64(uint64x2_t, int, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_u64)))
void __arm_vstrdq_scatter_base(uint64x2_t, int, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_p_s64)))
void __arm_vstrdq_scatter_base_wb_p_s64(uint64x2_t *, int, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_p_s64)))
void __arm_vstrdq_scatter_base_wb_p(uint64x2_t *, int, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_p_u64)))
void __arm_vstrdq_scatter_base_wb_p_u64(uint64x2_t *, int, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_p_u64)))
void __arm_vstrdq_scatter_base_wb_p(uint64x2_t *, int, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_s64)))
void __arm_vstrdq_scatter_base_wb_s64(uint64x2_t *, int, int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_s64)))
void __arm_vstrdq_scatter_base_wb(uint64x2_t *, int, int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_u64)))
void __arm_vstrdq_scatter_base_wb_u64(uint64x2_t *, int, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_u64)))
void __arm_vstrdq_scatter_base_wb(uint64x2_t *, int, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_p_s64)))
void __arm_vstrdq_scatter_offset_p_s64(int64_t *, uint64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_p_s64)))
void __arm_vstrdq_scatter_offset_p(int64_t *, uint64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_p_u64)))
void __arm_vstrdq_scatter_offset_p_u64(uint64_t *, uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_p_u64)))
void __arm_vstrdq_scatter_offset_p(uint64_t *, uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_s64)))
void __arm_vstrdq_scatter_offset_s64(int64_t *, uint64x2_t, int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_s64)))
void __arm_vstrdq_scatter_offset(int64_t *, uint64x2_t, int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_u64)))
void __arm_vstrdq_scatter_offset_u64(uint64_t *, uint64x2_t, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_u64)))
void __arm_vstrdq_scatter_offset(uint64_t *, uint64x2_t, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_p_s64)))
void __arm_vstrdq_scatter_shifted_offset_p_s64(int64_t *, uint64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_p_s64)))
void __arm_vstrdq_scatter_shifted_offset_p(int64_t *, uint64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_p_u64)))
void __arm_vstrdq_scatter_shifted_offset_p_u64(uint64_t *, uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_p_u64)))
void __arm_vstrdq_scatter_shifted_offset_p(uint64_t *, uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_s64)))
void __arm_vstrdq_scatter_shifted_offset_s64(int64_t *, uint64x2_t, int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_s64)))
void __arm_vstrdq_scatter_shifted_offset(int64_t *, uint64x2_t, int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_u64)))
void __arm_vstrdq_scatter_shifted_offset_u64(uint64_t *, uint64x2_t, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_u64)))
void __arm_vstrdq_scatter_shifted_offset(uint64_t *, uint64x2_t, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_s16)))
void __arm_vstrhq_p_s16(int16_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_s16)))
void __arm_vstrhq_p(int16_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_s32)))
void __arm_vstrhq_p_s32(int16_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_s32)))
void __arm_vstrhq_p(int16_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_u16)))
void __arm_vstrhq_p_u16(uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_u16)))
void __arm_vstrhq_p(uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_u32)))
void __arm_vstrhq_p_u32(uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_u32)))
void __arm_vstrhq_p(uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_s16)))
void __arm_vstrhq_s16(int16_t *, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_s16)))
void __arm_vstrhq(int16_t *, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_s32)))
void __arm_vstrhq_s32(int16_t *, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_s32)))
void __arm_vstrhq(int16_t *, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_s16)))
void __arm_vstrhq_scatter_offset_p_s16(int16_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_s16)))
void __arm_vstrhq_scatter_offset_p(int16_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_s32)))
void __arm_vstrhq_scatter_offset_p_s32(int16_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_s32)))
void __arm_vstrhq_scatter_offset_p(int16_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_u16)))
void __arm_vstrhq_scatter_offset_p_u16(uint16_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_u16)))
void __arm_vstrhq_scatter_offset_p(uint16_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_u32)))
void __arm_vstrhq_scatter_offset_p_u32(uint16_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_u32)))
void __arm_vstrhq_scatter_offset_p(uint16_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_s16)))
void __arm_vstrhq_scatter_offset_s16(int16_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_s16)))
void __arm_vstrhq_scatter_offset(int16_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_s32)))
void __arm_vstrhq_scatter_offset_s32(int16_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_s32)))
void __arm_vstrhq_scatter_offset(int16_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_u16)))
void __arm_vstrhq_scatter_offset_u16(uint16_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_u16)))
void __arm_vstrhq_scatter_offset(uint16_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_u32)))
void __arm_vstrhq_scatter_offset_u32(uint16_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_u32)))
void __arm_vstrhq_scatter_offset(uint16_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_s16)))
void __arm_vstrhq_scatter_shifted_offset_p_s16(int16_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_s16)))
void __arm_vstrhq_scatter_shifted_offset_p(int16_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_s32)))
void __arm_vstrhq_scatter_shifted_offset_p_s32(int16_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_s32)))
void __arm_vstrhq_scatter_shifted_offset_p(int16_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_u16)))
void __arm_vstrhq_scatter_shifted_offset_p_u16(uint16_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_u16)))
void __arm_vstrhq_scatter_shifted_offset_p(uint16_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_u32)))
void __arm_vstrhq_scatter_shifted_offset_p_u32(uint16_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_u32)))
void __arm_vstrhq_scatter_shifted_offset_p(uint16_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_s16)))
void __arm_vstrhq_scatter_shifted_offset_s16(int16_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_s16)))
void __arm_vstrhq_scatter_shifted_offset(int16_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_s32)))
void __arm_vstrhq_scatter_shifted_offset_s32(int16_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_s32)))
void __arm_vstrhq_scatter_shifted_offset(int16_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_u16)))
void __arm_vstrhq_scatter_shifted_offset_u16(uint16_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_u16)))
void __arm_vstrhq_scatter_shifted_offset(uint16_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_u32)))
void __arm_vstrhq_scatter_shifted_offset_u32(uint16_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_u32)))
void __arm_vstrhq_scatter_shifted_offset(uint16_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_u16)))
void __arm_vstrhq_u16(uint16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_u16)))
void __arm_vstrhq(uint16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_u32)))
void __arm_vstrhq_u32(uint16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_u32)))
void __arm_vstrhq(uint16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_s32)))
void __arm_vstrwq_p_s32(int32_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_s32)))
void __arm_vstrwq_p(int32_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_u32)))
void __arm_vstrwq_p_u32(uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_u32)))
void __arm_vstrwq_p(uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_s32)))
void __arm_vstrwq_s32(int32_t *, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_s32)))
void __arm_vstrwq(int32_t *, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_s32)))
void __arm_vstrwq_scatter_base_p_s32(uint32x4_t, int, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_s32)))
void __arm_vstrwq_scatter_base_p(uint32x4_t, int, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_u32)))
void __arm_vstrwq_scatter_base_p_u32(uint32x4_t, int, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_u32)))
void __arm_vstrwq_scatter_base_p(uint32x4_t, int, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_s32)))
void __arm_vstrwq_scatter_base_s32(uint32x4_t, int, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_s32)))
void __arm_vstrwq_scatter_base(uint32x4_t, int, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_u32)))
void __arm_vstrwq_scatter_base_u32(uint32x4_t, int, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_u32)))
void __arm_vstrwq_scatter_base(uint32x4_t, int, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_s32)))
void __arm_vstrwq_scatter_base_wb_p_s32(uint32x4_t *, int, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_s32)))
void __arm_vstrwq_scatter_base_wb_p(uint32x4_t *, int, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_u32)))
void __arm_vstrwq_scatter_base_wb_p_u32(uint32x4_t *, int, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_u32)))
void __arm_vstrwq_scatter_base_wb_p(uint32x4_t *, int, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_s32)))
void __arm_vstrwq_scatter_base_wb_s32(uint32x4_t *, int, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_s32)))
void __arm_vstrwq_scatter_base_wb(uint32x4_t *, int, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_u32)))
void __arm_vstrwq_scatter_base_wb_u32(uint32x4_t *, int, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_u32)))
void __arm_vstrwq_scatter_base_wb(uint32x4_t *, int, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_s32)))
void __arm_vstrwq_scatter_offset_p_s32(int32_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_s32)))
void __arm_vstrwq_scatter_offset_p(int32_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_u32)))
void __arm_vstrwq_scatter_offset_p_u32(uint32_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_u32)))
void __arm_vstrwq_scatter_offset_p(uint32_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_s32)))
void __arm_vstrwq_scatter_offset_s32(int32_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_s32)))
void __arm_vstrwq_scatter_offset(int32_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_u32)))
void __arm_vstrwq_scatter_offset_u32(uint32_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_u32)))
void __arm_vstrwq_scatter_offset(uint32_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_s32)))
void __arm_vstrwq_scatter_shifted_offset_p_s32(int32_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_s32)))
void __arm_vstrwq_scatter_shifted_offset_p(int32_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_u32)))
void __arm_vstrwq_scatter_shifted_offset_p_u32(uint32_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_u32)))
void __arm_vstrwq_scatter_shifted_offset_p(uint32_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_s32)))
void __arm_vstrwq_scatter_shifted_offset_s32(int32_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_s32)))
void __arm_vstrwq_scatter_shifted_offset(int32_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_u32)))
void __arm_vstrwq_scatter_shifted_offset_u32(uint32_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_u32)))
void __arm_vstrwq_scatter_shifted_offset(uint32_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_u32)))
void __arm_vstrwq_u32(uint32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_u32)))
void __arm_vstrwq(uint32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s16)))
int16x8_t __arm_vsubq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s16)))
int16x8_t __arm_vsubq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s32)))
int32x4_t __arm_vsubq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s32)))
int32x4_t __arm_vsubq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s8)))
int8x16_t __arm_vsubq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s8)))
int8x16_t __arm_vsubq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u16)))
uint16x8_t __arm_vsubq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u16)))
uint16x8_t __arm_vsubq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u32)))
uint32x4_t __arm_vsubq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u32)))
uint32x4_t __arm_vsubq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u8)))
uint8x16_t __arm_vsubq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u8)))
uint8x16_t __arm_vsubq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_s16)))
int16x8_t __arm_vsubq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_s16)))
int16x8_t __arm_vsubq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_s32)))
int32x4_t __arm_vsubq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_s32)))
int32x4_t __arm_vsubq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_s8)))
int8x16_t __arm_vsubq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_s8)))
int8x16_t __arm_vsubq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_u16)))
uint16x8_t __arm_vsubq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_u16)))
uint16x8_t __arm_vsubq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_u32)))
uint32x4_t __arm_vsubq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_u32)))
uint32x4_t __arm_vsubq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_u8)))
uint8x16_t __arm_vsubq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_u8)))
uint8x16_t __arm_vsubq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s16)))
int16x8_t __arm_vsubq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s16)))
int16x8_t __arm_vsubq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s32)))
int32x4_t __arm_vsubq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s32)))
int32x4_t __arm_vsubq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s8)))
int8x16_t __arm_vsubq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s8)))
int8x16_t __arm_vsubq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u16)))
uint16x8_t __arm_vsubq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u16)))
uint16x8_t __arm_vsubq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u32)))
uint32x4_t __arm_vsubq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u32)))
uint32x4_t __arm_vsubq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u8)))
uint8x16_t __arm_vsubq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u8)))
uint8x16_t __arm_vsubq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_s16)))
int16x8_t __arm_vuninitializedq(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_s32)))
int32x4_t __arm_vuninitializedq(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_s64)))
int64x2_t __arm_vuninitializedq(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_s8)))
int8x16_t __arm_vuninitializedq(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_u16)))
uint16x8_t __arm_vuninitializedq(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_u32)))
uint32x4_t __arm_vuninitializedq(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_u64)))
uint64x2_t __arm_vuninitializedq(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_u8)))
uint8x16_t __arm_vuninitializedq(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_s16)))
int16x8_t __arm_vuninitializedq_s16();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_s32)))
int32x4_t __arm_vuninitializedq_s32();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_s64)))
int64x2_t __arm_vuninitializedq_s64();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_s8)))
int8x16_t __arm_vuninitializedq_s8();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_u16)))
uint16x8_t __arm_vuninitializedq_u16();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_u32)))
uint32x4_t __arm_vuninitializedq_u32();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_u64)))
uint64x2_t __arm_vuninitializedq_u64();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_u8)))
uint8x16_t __arm_vuninitializedq_u8();

#if (__ARM_FEATURE_MVE & 2)

typedef __fp16 float16_t;
typedef float float32_t;
typedef __attribute__((neon_vector_type(8))) float16_t float16x8_t;
typedef struct { float16x8_t val[2]; } float16x8x2_t;
typedef struct { float16x8_t val[4]; } float16x8x4_t;
typedef __attribute__((neon_vector_type(4))) float32_t float32x4_t;
typedef struct { float32x4_t val[2]; } float32x4x2_t;
typedef struct { float32x4_t val[4]; } float32x4x4_t;

static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_f16)))
float16x8_t __arm_vabdq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_f16)))
float16x8_t __arm_vabdq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_f32)))
float32x4_t __arm_vabdq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_f32)))
float32x4_t __arm_vabdq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_f16)))
float16x8_t __arm_vabdq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_f16)))
float16x8_t __arm_vabdq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_f32)))
float32x4_t __arm_vabdq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_f32)))
float32x4_t __arm_vabdq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_f16)))
float16x8_t __arm_vabdq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_f16)))
float16x8_t __arm_vabdq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_f32)))
float32x4_t __arm_vabdq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_f32)))
float32x4_t __arm_vabdq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_f16)))
float16x8_t __arm_vaddq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_f16)))
float16x8_t __arm_vaddq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_f32)))
float32x4_t __arm_vaddq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_f32)))
float32x4_t __arm_vaddq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_f16)))
float16x8_t __arm_vaddq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_f16)))
float16x8_t __arm_vaddq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_f32)))
float32x4_t __arm_vaddq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_f32)))
float32x4_t __arm_vaddq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_f16)))
float16x8_t __arm_vaddq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_f16)))
float16x8_t __arm_vaddq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_f32)))
float32x4_t __arm_vaddq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_f32)))
float32x4_t __arm_vaddq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_f16)))
float16x8_t __arm_vandq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_f16)))
float16x8_t __arm_vandq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_f32)))
float32x4_t __arm_vandq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_f32)))
float32x4_t __arm_vandq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_f16)))
float16x8_t __arm_vandq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_f16)))
float16x8_t __arm_vandq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_f32)))
float32x4_t __arm_vandq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_f32)))
float32x4_t __arm_vandq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_f16)))
float16x8_t __arm_vandq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_f16)))
float16x8_t __arm_vandq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_f32)))
float32x4_t __arm_vandq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_f32)))
float32x4_t __arm_vandq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_f16)))
float16x8_t __arm_vbicq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_f16)))
float16x8_t __arm_vbicq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_f32)))
float32x4_t __arm_vbicq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_f32)))
float32x4_t __arm_vbicq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_f16)))
float16x8_t __arm_vbicq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_f16)))
float16x8_t __arm_vbicq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_f32)))
float32x4_t __arm_vbicq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_f32)))
float32x4_t __arm_vbicq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_f16)))
float16x8_t __arm_vbicq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_f16)))
float16x8_t __arm_vbicq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_f32)))
float32x4_t __arm_vbicq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_f32)))
float32x4_t __arm_vbicq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_f16)))
float16x8_t __arm_vcaddq_rot270_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_f16)))
float16x8_t __arm_vcaddq_rot270(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_f32)))
float32x4_t __arm_vcaddq_rot270_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_f32)))
float32x4_t __arm_vcaddq_rot270(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_f16)))
float16x8_t __arm_vcaddq_rot270_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_f16)))
float16x8_t __arm_vcaddq_rot270_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_f32)))
float32x4_t __arm_vcaddq_rot270_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_f32)))
float32x4_t __arm_vcaddq_rot270_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_f16)))
float16x8_t __arm_vcaddq_rot270_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_f16)))
float16x8_t __arm_vcaddq_rot270_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_f32)))
float32x4_t __arm_vcaddq_rot270_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_f32)))
float32x4_t __arm_vcaddq_rot270_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_f16)))
float16x8_t __arm_vcaddq_rot90_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_f16)))
float16x8_t __arm_vcaddq_rot90(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_f32)))
float32x4_t __arm_vcaddq_rot90_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_f32)))
float32x4_t __arm_vcaddq_rot90(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_f16)))
float16x8_t __arm_vcaddq_rot90_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_f16)))
float16x8_t __arm_vcaddq_rot90_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_f32)))
float32x4_t __arm_vcaddq_rot90_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_f32)))
float32x4_t __arm_vcaddq_rot90_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_f16)))
float16x8_t __arm_vcaddq_rot90_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_f16)))
float16x8_t __arm_vcaddq_rot90_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_f32)))
float32x4_t __arm_vcaddq_rot90_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_f32)))
float32x4_t __arm_vcaddq_rot90_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_f16)))
float16x8_t __arm_vcmlaq_f16(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_f16)))
float16x8_t __arm_vcmlaq(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_f32)))
float32x4_t __arm_vcmlaq_f32(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_f32)))
float32x4_t __arm_vcmlaq(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_m_f16)))
float16x8_t __arm_vcmlaq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_m_f16)))
float16x8_t __arm_vcmlaq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_m_f32)))
float32x4_t __arm_vcmlaq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_m_f32)))
float32x4_t __arm_vcmlaq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_f16)))
float16x8_t __arm_vcmlaq_rot180_f16(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_f16)))
float16x8_t __arm_vcmlaq_rot180(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_f32)))
float32x4_t __arm_vcmlaq_rot180_f32(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_f32)))
float32x4_t __arm_vcmlaq_rot180(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_m_f16)))
float16x8_t __arm_vcmlaq_rot180_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_m_f16)))
float16x8_t __arm_vcmlaq_rot180_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_m_f32)))
float32x4_t __arm_vcmlaq_rot180_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_m_f32)))
float32x4_t __arm_vcmlaq_rot180_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_f16)))
float16x8_t __arm_vcmlaq_rot270_f16(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_f16)))
float16x8_t __arm_vcmlaq_rot270(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_f32)))
float32x4_t __arm_vcmlaq_rot270_f32(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_f32)))
float32x4_t __arm_vcmlaq_rot270(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_m_f16)))
float16x8_t __arm_vcmlaq_rot270_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_m_f16)))
float16x8_t __arm_vcmlaq_rot270_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_m_f32)))
float32x4_t __arm_vcmlaq_rot270_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_m_f32)))
float32x4_t __arm_vcmlaq_rot270_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_f16)))
float16x8_t __arm_vcmlaq_rot90_f16(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_f16)))
float16x8_t __arm_vcmlaq_rot90(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_f32)))
float32x4_t __arm_vcmlaq_rot90_f32(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_f32)))
float32x4_t __arm_vcmlaq_rot90(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_m_f16)))
float16x8_t __arm_vcmlaq_rot90_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_m_f16)))
float16x8_t __arm_vcmlaq_rot90_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_m_f32)))
float32x4_t __arm_vcmlaq_rot90_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_m_f32)))
float32x4_t __arm_vcmlaq_rot90_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_f16)))
mve_pred16_t __arm_vcmpeqq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_f16)))
mve_pred16_t __arm_vcmpeqq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_f32)))
mve_pred16_t __arm_vcmpeqq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_f32)))
mve_pred16_t __arm_vcmpeqq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_f16)))
mve_pred16_t __arm_vcmpeqq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_f16)))
mve_pred16_t __arm_vcmpeqq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_f32)))
mve_pred16_t __arm_vcmpeqq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_f32)))
mve_pred16_t __arm_vcmpeqq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_f16)))
mve_pred16_t __arm_vcmpeqq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_f16)))
mve_pred16_t __arm_vcmpeqq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_f32)))
mve_pred16_t __arm_vcmpeqq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_f32)))
mve_pred16_t __arm_vcmpeqq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_f16)))
mve_pred16_t __arm_vcmpeqq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_f16)))
mve_pred16_t __arm_vcmpeqq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_f32)))
mve_pred16_t __arm_vcmpeqq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_f32)))
mve_pred16_t __arm_vcmpeqq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_f16)))
mve_pred16_t __arm_vcmpgeq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_f16)))
mve_pred16_t __arm_vcmpgeq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_f32)))
mve_pred16_t __arm_vcmpgeq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_f32)))
mve_pred16_t __arm_vcmpgeq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_f16)))
mve_pred16_t __arm_vcmpgeq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_f16)))
mve_pred16_t __arm_vcmpgeq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_f32)))
mve_pred16_t __arm_vcmpgeq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_f32)))
mve_pred16_t __arm_vcmpgeq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_f16)))
mve_pred16_t __arm_vcmpgeq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_f16)))
mve_pred16_t __arm_vcmpgeq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_f32)))
mve_pred16_t __arm_vcmpgeq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_f32)))
mve_pred16_t __arm_vcmpgeq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_f16)))
mve_pred16_t __arm_vcmpgeq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_f16)))
mve_pred16_t __arm_vcmpgeq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_f32)))
mve_pred16_t __arm_vcmpgeq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_f32)))
mve_pred16_t __arm_vcmpgeq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_f16)))
mve_pred16_t __arm_vcmpgtq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_f16)))
mve_pred16_t __arm_vcmpgtq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_f32)))
mve_pred16_t __arm_vcmpgtq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_f32)))
mve_pred16_t __arm_vcmpgtq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_f16)))
mve_pred16_t __arm_vcmpgtq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_f16)))
mve_pred16_t __arm_vcmpgtq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_f32)))
mve_pred16_t __arm_vcmpgtq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_f32)))
mve_pred16_t __arm_vcmpgtq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_f16)))
mve_pred16_t __arm_vcmpgtq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_f16)))
mve_pred16_t __arm_vcmpgtq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_f32)))
mve_pred16_t __arm_vcmpgtq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_f32)))
mve_pred16_t __arm_vcmpgtq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_f16)))
mve_pred16_t __arm_vcmpgtq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_f16)))
mve_pred16_t __arm_vcmpgtq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_f32)))
mve_pred16_t __arm_vcmpgtq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_f32)))
mve_pred16_t __arm_vcmpgtq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_f16)))
mve_pred16_t __arm_vcmpleq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_f16)))
mve_pred16_t __arm_vcmpleq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_f32)))
mve_pred16_t __arm_vcmpleq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_f32)))
mve_pred16_t __arm_vcmpleq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_f16)))
mve_pred16_t __arm_vcmpleq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_f16)))
mve_pred16_t __arm_vcmpleq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_f32)))
mve_pred16_t __arm_vcmpleq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_f32)))
mve_pred16_t __arm_vcmpleq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_f16)))
mve_pred16_t __arm_vcmpleq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_f16)))
mve_pred16_t __arm_vcmpleq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_f32)))
mve_pred16_t __arm_vcmpleq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_f32)))
mve_pred16_t __arm_vcmpleq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_f16)))
mve_pred16_t __arm_vcmpleq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_f16)))
mve_pred16_t __arm_vcmpleq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_f32)))
mve_pred16_t __arm_vcmpleq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_f32)))
mve_pred16_t __arm_vcmpleq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_f16)))
mve_pred16_t __arm_vcmpltq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_f16)))
mve_pred16_t __arm_vcmpltq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_f32)))
mve_pred16_t __arm_vcmpltq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_f32)))
mve_pred16_t __arm_vcmpltq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_f16)))
mve_pred16_t __arm_vcmpltq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_f16)))
mve_pred16_t __arm_vcmpltq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_f32)))
mve_pred16_t __arm_vcmpltq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_f32)))
mve_pred16_t __arm_vcmpltq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_f16)))
mve_pred16_t __arm_vcmpltq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_f16)))
mve_pred16_t __arm_vcmpltq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_f32)))
mve_pred16_t __arm_vcmpltq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_f32)))
mve_pred16_t __arm_vcmpltq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_f16)))
mve_pred16_t __arm_vcmpltq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_f16)))
mve_pred16_t __arm_vcmpltq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_f32)))
mve_pred16_t __arm_vcmpltq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_f32)))
mve_pred16_t __arm_vcmpltq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_f16)))
mve_pred16_t __arm_vcmpneq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_f16)))
mve_pred16_t __arm_vcmpneq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_f32)))
mve_pred16_t __arm_vcmpneq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_f32)))
mve_pred16_t __arm_vcmpneq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_f16)))
mve_pred16_t __arm_vcmpneq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_f16)))
mve_pred16_t __arm_vcmpneq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_f32)))
mve_pred16_t __arm_vcmpneq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_f32)))
mve_pred16_t __arm_vcmpneq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_f16)))
mve_pred16_t __arm_vcmpneq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_f16)))
mve_pred16_t __arm_vcmpneq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_f32)))
mve_pred16_t __arm_vcmpneq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_f32)))
mve_pred16_t __arm_vcmpneq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_f16)))
mve_pred16_t __arm_vcmpneq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_f16)))
mve_pred16_t __arm_vcmpneq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_f32)))
mve_pred16_t __arm_vcmpneq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_f32)))
mve_pred16_t __arm_vcmpneq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_f16)))
float16x8_t __arm_vcmulq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_f16)))
float16x8_t __arm_vcmulq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_f32)))
float32x4_t __arm_vcmulq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_f32)))
float32x4_t __arm_vcmulq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_m_f16)))
float16x8_t __arm_vcmulq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_m_f16)))
float16x8_t __arm_vcmulq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_m_f32)))
float32x4_t __arm_vcmulq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_m_f32)))
float32x4_t __arm_vcmulq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_f16)))
float16x8_t __arm_vcmulq_rot180_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_f16)))
float16x8_t __arm_vcmulq_rot180(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_f32)))
float32x4_t __arm_vcmulq_rot180_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_f32)))
float32x4_t __arm_vcmulq_rot180(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_m_f16)))
float16x8_t __arm_vcmulq_rot180_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_m_f16)))
float16x8_t __arm_vcmulq_rot180_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_m_f32)))
float32x4_t __arm_vcmulq_rot180_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_m_f32)))
float32x4_t __arm_vcmulq_rot180_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_x_f16)))
float16x8_t __arm_vcmulq_rot180_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_x_f16)))
float16x8_t __arm_vcmulq_rot180_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_x_f32)))
float32x4_t __arm_vcmulq_rot180_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_x_f32)))
float32x4_t __arm_vcmulq_rot180_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_f16)))
float16x8_t __arm_vcmulq_rot270_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_f16)))
float16x8_t __arm_vcmulq_rot270(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_f32)))
float32x4_t __arm_vcmulq_rot270_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_f32)))
float32x4_t __arm_vcmulq_rot270(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_m_f16)))
float16x8_t __arm_vcmulq_rot270_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_m_f16)))
float16x8_t __arm_vcmulq_rot270_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_m_f32)))
float32x4_t __arm_vcmulq_rot270_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_m_f32)))
float32x4_t __arm_vcmulq_rot270_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_x_f16)))
float16x8_t __arm_vcmulq_rot270_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_x_f16)))
float16x8_t __arm_vcmulq_rot270_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_x_f32)))
float32x4_t __arm_vcmulq_rot270_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_x_f32)))
float32x4_t __arm_vcmulq_rot270_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_f16)))
float16x8_t __arm_vcmulq_rot90_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_f16)))
float16x8_t __arm_vcmulq_rot90(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_f32)))
float32x4_t __arm_vcmulq_rot90_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_f32)))
float32x4_t __arm_vcmulq_rot90(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_m_f16)))
float16x8_t __arm_vcmulq_rot90_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_m_f16)))
float16x8_t __arm_vcmulq_rot90_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_m_f32)))
float32x4_t __arm_vcmulq_rot90_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_m_f32)))
float32x4_t __arm_vcmulq_rot90_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_x_f16)))
float16x8_t __arm_vcmulq_rot90_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_x_f16)))
float16x8_t __arm_vcmulq_rot90_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_x_f32)))
float32x4_t __arm_vcmulq_rot90_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_x_f32)))
float32x4_t __arm_vcmulq_rot90_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_x_f16)))
float16x8_t __arm_vcmulq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_x_f16)))
float16x8_t __arm_vcmulq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_x_f32)))
float32x4_t __arm_vcmulq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_x_f32)))
float32x4_t __arm_vcmulq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_f16)))
float16x8_t __arm_vcreateq_f16(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_f32)))
float32x4_t __arm_vcreateq_f32(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcvtbq_f16_f32)))
float16x8_t __arm_vcvtbq_f16_f32(float16x8_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcvtbq_m_f16_f32)))
float16x8_t __arm_vcvtbq_m_f16_f32(float16x8_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcvttq_f16_f32)))
float16x8_t __arm_vcvttq_f16_f32(float16x8_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcvttq_m_f16_f32)))
float16x8_t __arm_vcvttq_m_f16_f32(float16x8_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_f16)))
float16x8_t __arm_veorq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_f16)))
float16x8_t __arm_veorq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_f32)))
float32x4_t __arm_veorq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_f32)))
float32x4_t __arm_veorq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_f16)))
float16x8_t __arm_veorq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_f16)))
float16x8_t __arm_veorq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_f32)))
float32x4_t __arm_veorq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_f32)))
float32x4_t __arm_veorq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_f16)))
float16x8_t __arm_veorq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_f16)))
float16x8_t __arm_veorq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_f32)))
float32x4_t __arm_veorq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_f32)))
float32x4_t __arm_veorq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_f16)))
float16_t __arm_vgetq_lane_f16(float16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_f16)))
float16_t __arm_vgetq_lane(float16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_f32)))
float32_t __arm_vgetq_lane_f32(float32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_f32)))
float32_t __arm_vgetq_lane(float32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_f16)))
float16x8_t __arm_vld1q_f16(const float16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_f16)))
float16x8_t __arm_vld1q(const float16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_f32)))
float32x4_t __arm_vld1q_f32(const float32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_f32)))
float32x4_t __arm_vld1q(const float32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_f16)))
float16x8_t __arm_vld1q_z_f16(const float16_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_f16)))
float16x8_t __arm_vld1q_z(const float16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_f32)))
float32x4_t __arm_vld1q_z_f32(const float32_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_f32)))
float32x4_t __arm_vld1q_z(const float32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_f16)))
float16x8x2_t __arm_vld2q_f16(const float16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_f16)))
float16x8x2_t __arm_vld2q(const float16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_f32)))
float32x4x2_t __arm_vld2q_f32(const float32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_f32)))
float32x4x2_t __arm_vld2q(const float32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_f16)))
float16x8x4_t __arm_vld4q_f16(const float16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_f16)))
float16x8x4_t __arm_vld4q(const float16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_f32)))
float32x4x4_t __arm_vld4q_f32(const float32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_f32)))
float32x4x4_t __arm_vld4q(const float32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_f16)))
float16x8_t __arm_vldrhq_f16(const float16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_f16)))
float16x8_t __arm_vldrhq_gather_offset_f16(const float16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_f16)))
float16x8_t __arm_vldrhq_gather_offset(const float16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_f16)))
float16x8_t __arm_vldrhq_gather_offset_z_f16(const float16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_f16)))
float16x8_t __arm_vldrhq_gather_offset_z(const float16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_f16)))
float16x8_t __arm_vldrhq_gather_shifted_offset_f16(const float16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_f16)))
float16x8_t __arm_vldrhq_gather_shifted_offset(const float16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_f16)))
float16x8_t __arm_vldrhq_gather_shifted_offset_z_f16(const float16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_f16)))
float16x8_t __arm_vldrhq_gather_shifted_offset_z(const float16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_f16)))
float16x8_t __arm_vldrhq_z_f16(const float16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_f32)))
float32x4_t __arm_vldrwq_f32(const float32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_f32)))
float32x4_t __arm_vldrwq_gather_base_f32(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_f32)))
float32x4_t __arm_vldrwq_gather_base_wb_f32(uint32x4_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_z_f32)))
float32x4_t __arm_vldrwq_gather_base_wb_z_f32(uint32x4_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_z_f32)))
float32x4_t __arm_vldrwq_gather_base_z_f32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_f32)))
float32x4_t __arm_vldrwq_gather_offset_f32(const float32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_f32)))
float32x4_t __arm_vldrwq_gather_offset(const float32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_f32)))
float32x4_t __arm_vldrwq_gather_offset_z_f32(const float32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_f32)))
float32x4_t __arm_vldrwq_gather_offset_z(const float32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_f32)))
float32x4_t __arm_vldrwq_gather_shifted_offset_f32(const float32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_f32)))
float32x4_t __arm_vldrwq_gather_shifted_offset(const float32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_f32)))
float32x4_t __arm_vldrwq_gather_shifted_offset_z_f32(const float32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_f32)))
float32x4_t __arm_vldrwq_gather_shifted_offset_z(const float32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_z_f32)))
float32x4_t __arm_vldrwq_z_f32(const float32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_f16)))
float16x8_t __arm_vmaxnmq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_f16)))
float16x8_t __arm_vmaxnmq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_f32)))
float32x4_t __arm_vmaxnmq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_f32)))
float32x4_t __arm_vmaxnmq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_m_f16)))
float16x8_t __arm_vmaxnmq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_m_f16)))
float16x8_t __arm_vmaxnmq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_m_f32)))
float32x4_t __arm_vmaxnmq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_m_f32)))
float32x4_t __arm_vmaxnmq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_x_f16)))
float16x8_t __arm_vmaxnmq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_x_f16)))
float16x8_t __arm_vmaxnmq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_x_f32)))
float32x4_t __arm_vmaxnmq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_x_f32)))
float32x4_t __arm_vmaxnmq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_f16)))
float16x8_t __arm_vminnmq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_f16)))
float16x8_t __arm_vminnmq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_f32)))
float32x4_t __arm_vminnmq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_f32)))
float32x4_t __arm_vminnmq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_m_f16)))
float16x8_t __arm_vminnmq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_m_f16)))
float16x8_t __arm_vminnmq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_m_f32)))
float32x4_t __arm_vminnmq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_m_f32)))
float32x4_t __arm_vminnmq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_x_f16)))
float16x8_t __arm_vminnmq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_x_f16)))
float16x8_t __arm_vminnmq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_x_f32)))
float32x4_t __arm_vminnmq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_x_f32)))
float32x4_t __arm_vminnmq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_f16)))
float16x8_t __arm_vmulq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_f16)))
float16x8_t __arm_vmulq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_f32)))
float32x4_t __arm_vmulq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_f32)))
float32x4_t __arm_vmulq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_f16)))
float16x8_t __arm_vmulq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_f16)))
float16x8_t __arm_vmulq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_f32)))
float32x4_t __arm_vmulq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_f32)))
float32x4_t __arm_vmulq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_f16)))
float16x8_t __arm_vmulq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_f16)))
float16x8_t __arm_vmulq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_f32)))
float32x4_t __arm_vmulq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_f32)))
float32x4_t __arm_vmulq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_f16)))
float16x8_t __arm_vornq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_f16)))
float16x8_t __arm_vornq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_f32)))
float32x4_t __arm_vornq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_f32)))
float32x4_t __arm_vornq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_f16)))
float16x8_t __arm_vornq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_f16)))
float16x8_t __arm_vornq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_f32)))
float32x4_t __arm_vornq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_f32)))
float32x4_t __arm_vornq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_f16)))
float16x8_t __arm_vornq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_f16)))
float16x8_t __arm_vornq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_f32)))
float32x4_t __arm_vornq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_f32)))
float32x4_t __arm_vornq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_f16)))
float16x8_t __arm_vorrq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_f16)))
float16x8_t __arm_vorrq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_f32)))
float32x4_t __arm_vorrq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_f32)))
float32x4_t __arm_vorrq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_f16)))
float16x8_t __arm_vorrq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_f16)))
float16x8_t __arm_vorrq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_f32)))
float32x4_t __arm_vorrq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_f32)))
float32x4_t __arm_vorrq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_f16)))
float16x8_t __arm_vorrq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_f16)))
float16x8_t __arm_vorrq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_f32)))
float32x4_t __arm_vorrq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_f32)))
float32x4_t __arm_vorrq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_f16)))
float16x8_t __arm_vpselq_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_f16)))
float16x8_t __arm_vpselq(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_f32)))
float32x4_t __arm_vpselq_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_f32)))
float32x4_t __arm_vpselq(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_f32)))
float16x8_t __arm_vreinterpretq_f16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_f32)))
float16x8_t __arm_vreinterpretq_f16(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s16)))
float16x8_t __arm_vreinterpretq_f16_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s16)))
float16x8_t __arm_vreinterpretq_f16(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s32)))
float16x8_t __arm_vreinterpretq_f16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s32)))
float16x8_t __arm_vreinterpretq_f16(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s64)))
float16x8_t __arm_vreinterpretq_f16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s64)))
float16x8_t __arm_vreinterpretq_f16(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s8)))
float16x8_t __arm_vreinterpretq_f16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s8)))
float16x8_t __arm_vreinterpretq_f16(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u16)))
float16x8_t __arm_vreinterpretq_f16_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u16)))
float16x8_t __arm_vreinterpretq_f16(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u32)))
float16x8_t __arm_vreinterpretq_f16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u32)))
float16x8_t __arm_vreinterpretq_f16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u64)))
float16x8_t __arm_vreinterpretq_f16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u64)))
float16x8_t __arm_vreinterpretq_f16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u8)))
float16x8_t __arm_vreinterpretq_f16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u8)))
float16x8_t __arm_vreinterpretq_f16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_f16)))
float32x4_t __arm_vreinterpretq_f32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_f16)))
float32x4_t __arm_vreinterpretq_f32(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s16)))
float32x4_t __arm_vreinterpretq_f32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s16)))
float32x4_t __arm_vreinterpretq_f32(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s32)))
float32x4_t __arm_vreinterpretq_f32_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s32)))
float32x4_t __arm_vreinterpretq_f32(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s64)))
float32x4_t __arm_vreinterpretq_f32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s64)))
float32x4_t __arm_vreinterpretq_f32(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s8)))
float32x4_t __arm_vreinterpretq_f32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s8)))
float32x4_t __arm_vreinterpretq_f32(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u16)))
float32x4_t __arm_vreinterpretq_f32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u16)))
float32x4_t __arm_vreinterpretq_f32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u32)))
float32x4_t __arm_vreinterpretq_f32_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u32)))
float32x4_t __arm_vreinterpretq_f32(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u64)))
float32x4_t __arm_vreinterpretq_f32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u64)))
float32x4_t __arm_vreinterpretq_f32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u8)))
float32x4_t __arm_vreinterpretq_f32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u8)))
float32x4_t __arm_vreinterpretq_f32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_f16)))
int16x8_t __arm_vreinterpretq_s16_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_f16)))
int16x8_t __arm_vreinterpretq_s16(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_f32)))
int16x8_t __arm_vreinterpretq_s16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_f32)))
int16x8_t __arm_vreinterpretq_s16(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_f16)))
int32x4_t __arm_vreinterpretq_s32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_f16)))
int32x4_t __arm_vreinterpretq_s32(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_f32)))
int32x4_t __arm_vreinterpretq_s32_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_f32)))
int32x4_t __arm_vreinterpretq_s32(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_f16)))
int64x2_t __arm_vreinterpretq_s64_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_f16)))
int64x2_t __arm_vreinterpretq_s64(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_f32)))
int64x2_t __arm_vreinterpretq_s64_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_f32)))
int64x2_t __arm_vreinterpretq_s64(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_f16)))
int8x16_t __arm_vreinterpretq_s8_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_f16)))
int8x16_t __arm_vreinterpretq_s8(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_f32)))
int8x16_t __arm_vreinterpretq_s8_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_f32)))
int8x16_t __arm_vreinterpretq_s8(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_f16)))
uint16x8_t __arm_vreinterpretq_u16_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_f16)))
uint16x8_t __arm_vreinterpretq_u16(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_f32)))
uint16x8_t __arm_vreinterpretq_u16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_f32)))
uint16x8_t __arm_vreinterpretq_u16(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_f16)))
uint32x4_t __arm_vreinterpretq_u32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_f16)))
uint32x4_t __arm_vreinterpretq_u32(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_f32)))
uint32x4_t __arm_vreinterpretq_u32_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_f32)))
uint32x4_t __arm_vreinterpretq_u32(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_f16)))
uint64x2_t __arm_vreinterpretq_u64_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_f16)))
uint64x2_t __arm_vreinterpretq_u64(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_f32)))
uint64x2_t __arm_vreinterpretq_u64_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_f32)))
uint64x2_t __arm_vreinterpretq_u64(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_f16)))
uint8x16_t __arm_vreinterpretq_u8_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_f16)))
uint8x16_t __arm_vreinterpretq_u8(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_f32)))
uint8x16_t __arm_vreinterpretq_u8_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_f32)))
uint8x16_t __arm_vreinterpretq_u8(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_f16)))
float16x8_t __arm_vsetq_lane_f16(float16_t, float16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_f16)))
float16x8_t __arm_vsetq_lane(float16_t, float16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_f32)))
float32x4_t __arm_vsetq_lane_f32(float32_t, float32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_f32)))
float32x4_t __arm_vsetq_lane(float32_t, float32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_f16)))
void __arm_vst1q_f16(float16_t *, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_f16)))
void __arm_vst1q(float16_t *, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_f32)))
void __arm_vst1q_f32(float32_t *, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_f32)))
void __arm_vst1q(float32_t *, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_f16)))
void __arm_vst1q_p_f16(float16_t *, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_f16)))
void __arm_vst1q_p(float16_t *, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_f32)))
void __arm_vst1q_p_f32(float32_t *, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_f32)))
void __arm_vst1q_p(float32_t *, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_f16)))
void __arm_vst2q_f16(float16_t *, float16x8x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_f16)))
void __arm_vst2q(float16_t *, float16x8x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_f32)))
void __arm_vst2q_f32(float32_t *, float32x4x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_f32)))
void __arm_vst2q(float32_t *, float32x4x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_f16)))
void __arm_vst4q_f16(float16_t *, float16x8x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_f16)))
void __arm_vst4q(float16_t *, float16x8x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_f32)))
void __arm_vst4q_f32(float32_t *, float32x4x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_f32)))
void __arm_vst4q(float32_t *, float32x4x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_f16)))
void __arm_vstrhq_f16(float16_t *, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_f16)))
void __arm_vstrhq(float16_t *, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_f16)))
void __arm_vstrhq_p_f16(float16_t *, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_f16)))
void __arm_vstrhq_p(float16_t *, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_f16)))
void __arm_vstrhq_scatter_offset_f16(float16_t *, uint16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_f16)))
void __arm_vstrhq_scatter_offset(float16_t *, uint16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_f16)))
void __arm_vstrhq_scatter_offset_p_f16(float16_t *, uint16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_f16)))
void __arm_vstrhq_scatter_offset_p(float16_t *, uint16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_f16)))
void __arm_vstrhq_scatter_shifted_offset_f16(float16_t *, uint16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_f16)))
void __arm_vstrhq_scatter_shifted_offset(float16_t *, uint16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_f16)))
void __arm_vstrhq_scatter_shifted_offset_p_f16(float16_t *, uint16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_f16)))
void __arm_vstrhq_scatter_shifted_offset_p(float16_t *, uint16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_f32)))
void __arm_vstrwq_f32(float32_t *, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_f32)))
void __arm_vstrwq(float32_t *, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_f32)))
void __arm_vstrwq_p_f32(float32_t *, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_f32)))
void __arm_vstrwq_p(float32_t *, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_f32)))
void __arm_vstrwq_scatter_base_f32(uint32x4_t, int, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_f32)))
void __arm_vstrwq_scatter_base(uint32x4_t, int, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_f32)))
void __arm_vstrwq_scatter_base_p_f32(uint32x4_t, int, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_f32)))
void __arm_vstrwq_scatter_base_p(uint32x4_t, int, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_f32)))
void __arm_vstrwq_scatter_base_wb_f32(uint32x4_t *, int, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_f32)))
void __arm_vstrwq_scatter_base_wb(uint32x4_t *, int, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_f32)))
void __arm_vstrwq_scatter_base_wb_p_f32(uint32x4_t *, int, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_f32)))
void __arm_vstrwq_scatter_base_wb_p(uint32x4_t *, int, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_f32)))
void __arm_vstrwq_scatter_offset_f32(float32_t *, uint32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_f32)))
void __arm_vstrwq_scatter_offset(float32_t *, uint32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_f32)))
void __arm_vstrwq_scatter_offset_p_f32(float32_t *, uint32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_f32)))
void __arm_vstrwq_scatter_offset_p(float32_t *, uint32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_f32)))
void __arm_vstrwq_scatter_shifted_offset_f32(float32_t *, uint32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_f32)))
void __arm_vstrwq_scatter_shifted_offset(float32_t *, uint32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_f32)))
void __arm_vstrwq_scatter_shifted_offset_p_f32(float32_t *, uint32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_f32)))
void __arm_vstrwq_scatter_shifted_offset_p(float32_t *, uint32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_f16)))
float16x8_t __arm_vsubq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_f16)))
float16x8_t __arm_vsubq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_f32)))
float32x4_t __arm_vsubq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_f32)))
float32x4_t __arm_vsubq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_f16)))
float16x8_t __arm_vsubq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_f16)))
float16x8_t __arm_vsubq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_f32)))
float32x4_t __arm_vsubq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_f32)))
float32x4_t __arm_vsubq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_f16)))
float16x8_t __arm_vsubq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_f16)))
float16x8_t __arm_vsubq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_f32)))
float32x4_t __arm_vsubq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_f32)))
float32x4_t __arm_vsubq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_f16)))
float16x8_t __arm_vuninitializedq_f16();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_f32)))
float32x4_t __arm_vuninitializedq_f32();
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_f16)))
float16x8_t __arm_vuninitializedq(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_f32)))
float32x4_t __arm_vuninitializedq(float32x4_t);

#endif /* (__ARM_FEATURE_MVE & 2) */

#if (!defined __ARM_MVE_PRESERVE_USER_NAMESPACE)

static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_asrl)))
int64_t asrl(int64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_lsll)))
uint64_t lsll(uint64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqrshr)))
int32_t sqrshr(int32_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqrshrl)))
int64_t sqrshrl(int64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqrshrl_sat48)))
int64_t sqrshrl_sat48(int64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqshl)))
int32_t sqshl(int32_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_sqshll)))
int64_t sqshll(int64_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_srshr)))
int32_t srshr(int32_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_srshrl)))
int64_t srshrl(int64_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqrshl)))
uint32_t uqrshl(uint32_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqrshll)))
uint64_t uqrshll(uint64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqrshll_sat48)))
uint64_t uqrshll_sat48(uint64_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqshl)))
uint32_t uqshl(uint32_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_uqshll)))
uint64_t uqshll(uint64_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_urshr)))
uint32_t urshr(uint32_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_urshrl)))
uint64_t urshrl(uint64_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s16)))
uint32_t vabavq_p_s16(uint32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s16)))
uint32_t vabavq_p(uint32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s32)))
uint32_t vabavq_p_s32(uint32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s32)))
uint32_t vabavq_p(uint32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s8)))
uint32_t vabavq_p_s8(uint32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_s8)))
uint32_t vabavq_p(uint32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u16)))
uint32_t vabavq_p_u16(uint32_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u16)))
uint32_t vabavq_p(uint32_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u32)))
uint32_t vabavq_p_u32(uint32_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u32)))
uint32_t vabavq_p(uint32_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u8)))
uint32_t vabavq_p_u8(uint32_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_p_u8)))
uint32_t vabavq_p(uint32_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_s16)))
uint32_t vabavq_s16(uint32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_s16)))
uint32_t vabavq(uint32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_s32)))
uint32_t vabavq_s32(uint32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_s32)))
uint32_t vabavq(uint32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_s8)))
uint32_t vabavq_s8(uint32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_s8)))
uint32_t vabavq(uint32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_u16)))
uint32_t vabavq_u16(uint32_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_u16)))
uint32_t vabavq(uint32_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_u32)))
uint32_t vabavq_u32(uint32_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_u32)))
uint32_t vabavq(uint32_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabavq_u8)))
uint32_t vabavq_u8(uint32_t, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabavq_u8)))
uint32_t vabavq(uint32_t, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s16)))
int16x8_t vabdq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s16)))
int16x8_t vabdq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s32)))
int32x4_t vabdq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s32)))
int32x4_t vabdq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s8)))
int8x16_t vabdq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_s8)))
int8x16_t vabdq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u16)))
uint16x8_t vabdq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u16)))
uint16x8_t vabdq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u32)))
uint32x4_t vabdq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u32)))
uint32x4_t vabdq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u8)))
uint8x16_t vabdq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_u8)))
uint8x16_t vabdq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_s16)))
int16x8_t vabdq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_s16)))
int16x8_t vabdq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_s32)))
int32x4_t vabdq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_s32)))
int32x4_t vabdq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_s8)))
int8x16_t vabdq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_s8)))
int8x16_t vabdq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_u16)))
uint16x8_t vabdq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_u16)))
uint16x8_t vabdq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_u32)))
uint32x4_t vabdq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_u32)))
uint32x4_t vabdq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_u8)))
uint8x16_t vabdq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_u8)))
uint8x16_t vabdq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s16)))
int16x8_t vabdq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s16)))
int16x8_t vabdq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s32)))
int32x4_t vabdq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s32)))
int32x4_t vabdq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s8)))
int8x16_t vabdq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_s8)))
int8x16_t vabdq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u16)))
uint16x8_t vabdq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u16)))
uint16x8_t vabdq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u32)))
uint32x4_t vabdq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u32)))
uint32x4_t vabdq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u8)))
uint8x16_t vabdq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_u8)))
uint8x16_t vabdq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadciq_m_s32)))
int32x4_t vadciq_m_s32(int32x4_t, int32x4_t, int32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadciq_m_s32)))
int32x4_t vadciq_m(int32x4_t, int32x4_t, int32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadciq_m_u32)))
uint32x4_t vadciq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadciq_m_u32)))
uint32x4_t vadciq_m(uint32x4_t, uint32x4_t, uint32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadciq_s32)))
int32x4_t vadciq_s32(int32x4_t, int32x4_t, unsigned *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadciq_s32)))
int32x4_t vadciq(int32x4_t, int32x4_t, unsigned *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadciq_u32)))
uint32x4_t vadciq_u32(uint32x4_t, uint32x4_t, unsigned *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadciq_u32)))
uint32x4_t vadciq(uint32x4_t, uint32x4_t, unsigned *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadcq_m_s32)))
int32x4_t vadcq_m_s32(int32x4_t, int32x4_t, int32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadcq_m_s32)))
int32x4_t vadcq_m(int32x4_t, int32x4_t, int32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadcq_m_u32)))
uint32x4_t vadcq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadcq_m_u32)))
uint32x4_t vadcq_m(uint32x4_t, uint32x4_t, uint32x4_t, unsigned *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadcq_s32)))
int32x4_t vadcq_s32(int32x4_t, int32x4_t, unsigned *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadcq_s32)))
int32x4_t vadcq(int32x4_t, int32x4_t, unsigned *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vadcq_u32)))
uint32x4_t vadcq_u32(uint32x4_t, uint32x4_t, unsigned *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vadcq_u32)))
uint32x4_t vadcq(uint32x4_t, uint32x4_t, unsigned *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s16)))
int16x8_t vaddq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s16)))
int16x8_t vaddq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s32)))
int32x4_t vaddq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s32)))
int32x4_t vaddq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s8)))
int8x16_t vaddq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_s8)))
int8x16_t vaddq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u16)))
uint16x8_t vaddq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u16)))
uint16x8_t vaddq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u32)))
uint32x4_t vaddq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u32)))
uint32x4_t vaddq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u8)))
uint8x16_t vaddq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_u8)))
uint8x16_t vaddq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_s16)))
int16x8_t vaddq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_s16)))
int16x8_t vaddq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_s32)))
int32x4_t vaddq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_s32)))
int32x4_t vaddq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_s8)))
int8x16_t vaddq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_s8)))
int8x16_t vaddq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_u16)))
uint16x8_t vaddq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_u16)))
uint16x8_t vaddq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_u32)))
uint32x4_t vaddq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_u32)))
uint32x4_t vaddq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_u8)))
uint8x16_t vaddq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_u8)))
uint8x16_t vaddq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s16)))
int16x8_t vaddq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s16)))
int16x8_t vaddq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s32)))
int32x4_t vaddq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s32)))
int32x4_t vaddq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s8)))
int8x16_t vaddq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_s8)))
int8x16_t vaddq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u16)))
uint16x8_t vaddq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u16)))
uint16x8_t vaddq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u32)))
uint32x4_t vaddq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u32)))
uint32x4_t vaddq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u8)))
uint8x16_t vaddq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_u8)))
uint8x16_t vaddq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s16)))
int16x8_t vandq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s16)))
int16x8_t vandq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s32)))
int32x4_t vandq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s32)))
int32x4_t vandq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s8)))
int8x16_t vandq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_s8)))
int8x16_t vandq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u16)))
uint16x8_t vandq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u16)))
uint16x8_t vandq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u32)))
uint32x4_t vandq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u32)))
uint32x4_t vandq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u8)))
uint8x16_t vandq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_u8)))
uint8x16_t vandq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_s16)))
int16x8_t vandq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_s16)))
int16x8_t vandq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_s32)))
int32x4_t vandq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_s32)))
int32x4_t vandq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_s8)))
int8x16_t vandq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_s8)))
int8x16_t vandq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_u16)))
uint16x8_t vandq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_u16)))
uint16x8_t vandq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_u32)))
uint32x4_t vandq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_u32)))
uint32x4_t vandq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_u8)))
uint8x16_t vandq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_u8)))
uint8x16_t vandq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s16)))
int16x8_t vandq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s16)))
int16x8_t vandq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s32)))
int32x4_t vandq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s32)))
int32x4_t vandq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s8)))
int8x16_t vandq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_s8)))
int8x16_t vandq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u16)))
uint16x8_t vandq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u16)))
uint16x8_t vandq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u32)))
uint32x4_t vandq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u32)))
uint32x4_t vandq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u8)))
uint8x16_t vandq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_u8)))
uint8x16_t vandq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s16)))
int16x8_t vbicq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s16)))
int16x8_t vbicq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s32)))
int32x4_t vbicq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s32)))
int32x4_t vbicq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s8)))
int8x16_t vbicq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_s8)))
int8x16_t vbicq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u16)))
uint16x8_t vbicq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u16)))
uint16x8_t vbicq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u32)))
uint32x4_t vbicq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u32)))
uint32x4_t vbicq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u8)))
uint8x16_t vbicq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_u8)))
uint8x16_t vbicq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_s16)))
int16x8_t vbicq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_s16)))
int16x8_t vbicq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_s32)))
int32x4_t vbicq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_s32)))
int32x4_t vbicq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_s8)))
int8x16_t vbicq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_s8)))
int8x16_t vbicq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_u16)))
uint16x8_t vbicq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_u16)))
uint16x8_t vbicq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_u32)))
uint32x4_t vbicq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_u32)))
uint32x4_t vbicq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_u8)))
uint8x16_t vbicq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_u8)))
uint8x16_t vbicq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s16)))
int16x8_t vbicq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s16)))
int16x8_t vbicq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s32)))
int32x4_t vbicq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s32)))
int32x4_t vbicq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s8)))
int8x16_t vbicq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_s8)))
int8x16_t vbicq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u16)))
uint16x8_t vbicq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u16)))
uint16x8_t vbicq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u32)))
uint32x4_t vbicq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u32)))
uint32x4_t vbicq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u8)))
uint8x16_t vbicq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_u8)))
uint8x16_t vbicq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s16)))
int16x8_t vcaddq_rot270_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s16)))
int16x8_t vcaddq_rot270_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s32)))
int32x4_t vcaddq_rot270_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s32)))
int32x4_t vcaddq_rot270_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s8)))
int8x16_t vcaddq_rot270_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_s8)))
int8x16_t vcaddq_rot270_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u16)))
uint16x8_t vcaddq_rot270_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u16)))
uint16x8_t vcaddq_rot270_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u32)))
uint32x4_t vcaddq_rot270_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u32)))
uint32x4_t vcaddq_rot270_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u8)))
uint8x16_t vcaddq_rot270_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_u8)))
uint8x16_t vcaddq_rot270_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s16)))
int16x8_t vcaddq_rot270_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s16)))
int16x8_t vcaddq_rot270(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s32)))
int32x4_t vcaddq_rot270_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s32)))
int32x4_t vcaddq_rot270(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s8)))
int8x16_t vcaddq_rot270_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_s8)))
int8x16_t vcaddq_rot270(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u16)))
uint16x8_t vcaddq_rot270_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u16)))
uint16x8_t vcaddq_rot270(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u32)))
uint32x4_t vcaddq_rot270_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u32)))
uint32x4_t vcaddq_rot270(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u8)))
uint8x16_t vcaddq_rot270_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_u8)))
uint8x16_t vcaddq_rot270(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s16)))
int16x8_t vcaddq_rot270_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s16)))
int16x8_t vcaddq_rot270_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s32)))
int32x4_t vcaddq_rot270_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s32)))
int32x4_t vcaddq_rot270_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s8)))
int8x16_t vcaddq_rot270_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_s8)))
int8x16_t vcaddq_rot270_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u16)))
uint16x8_t vcaddq_rot270_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u16)))
uint16x8_t vcaddq_rot270_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u32)))
uint32x4_t vcaddq_rot270_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u32)))
uint32x4_t vcaddq_rot270_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u8)))
uint8x16_t vcaddq_rot270_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_u8)))
uint8x16_t vcaddq_rot270_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s16)))
int16x8_t vcaddq_rot90_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s16)))
int16x8_t vcaddq_rot90_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s32)))
int32x4_t vcaddq_rot90_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s32)))
int32x4_t vcaddq_rot90_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s8)))
int8x16_t vcaddq_rot90_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_s8)))
int8x16_t vcaddq_rot90_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u16)))
uint16x8_t vcaddq_rot90_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u16)))
uint16x8_t vcaddq_rot90_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u32)))
uint32x4_t vcaddq_rot90_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u32)))
uint32x4_t vcaddq_rot90_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u8)))
uint8x16_t vcaddq_rot90_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_u8)))
uint8x16_t vcaddq_rot90_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s16)))
int16x8_t vcaddq_rot90_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s16)))
int16x8_t vcaddq_rot90(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s32)))
int32x4_t vcaddq_rot90_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s32)))
int32x4_t vcaddq_rot90(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s8)))
int8x16_t vcaddq_rot90_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_s8)))
int8x16_t vcaddq_rot90(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u16)))
uint16x8_t vcaddq_rot90_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u16)))
uint16x8_t vcaddq_rot90(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u32)))
uint32x4_t vcaddq_rot90_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u32)))
uint32x4_t vcaddq_rot90(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u8)))
uint8x16_t vcaddq_rot90_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_u8)))
uint8x16_t vcaddq_rot90(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s16)))
int16x8_t vcaddq_rot90_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s16)))
int16x8_t vcaddq_rot90_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s32)))
int32x4_t vcaddq_rot90_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s32)))
int32x4_t vcaddq_rot90_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s8)))
int8x16_t vcaddq_rot90_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_s8)))
int8x16_t vcaddq_rot90_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u16)))
uint16x8_t vcaddq_rot90_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u16)))
uint16x8_t vcaddq_rot90_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u32)))
uint32x4_t vcaddq_rot90_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u32)))
uint32x4_t vcaddq_rot90_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u8)))
uint8x16_t vcaddq_rot90_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_u8)))
uint8x16_t vcaddq_rot90_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u16)))
mve_pred16_t vcmpcsq_m_n_u16(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u16)))
mve_pred16_t vcmpcsq_m(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u32)))
mve_pred16_t vcmpcsq_m_n_u32(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u32)))
mve_pred16_t vcmpcsq_m(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u8)))
mve_pred16_t vcmpcsq_m_n_u8(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_n_u8)))
mve_pred16_t vcmpcsq_m(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u16)))
mve_pred16_t vcmpcsq_m_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u16)))
mve_pred16_t vcmpcsq_m(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u32)))
mve_pred16_t vcmpcsq_m_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u32)))
mve_pred16_t vcmpcsq_m(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u8)))
mve_pred16_t vcmpcsq_m_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_m_u8)))
mve_pred16_t vcmpcsq_m(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u16)))
mve_pred16_t vcmpcsq_n_u16(uint16x8_t, uint16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u16)))
mve_pred16_t vcmpcsq(uint16x8_t, uint16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u32)))
mve_pred16_t vcmpcsq_n_u32(uint32x4_t, uint32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u32)))
mve_pred16_t vcmpcsq(uint32x4_t, uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u8)))
mve_pred16_t vcmpcsq_n_u8(uint8x16_t, uint8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_n_u8)))
mve_pred16_t vcmpcsq(uint8x16_t, uint8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u16)))
mve_pred16_t vcmpcsq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u16)))
mve_pred16_t vcmpcsq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u32)))
mve_pred16_t vcmpcsq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u32)))
mve_pred16_t vcmpcsq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u8)))
mve_pred16_t vcmpcsq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpcsq_u8)))
mve_pred16_t vcmpcsq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s16)))
mve_pred16_t vcmpeqq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s16)))
mve_pred16_t vcmpeqq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s32)))
mve_pred16_t vcmpeqq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s32)))
mve_pred16_t vcmpeqq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s8)))
mve_pred16_t vcmpeqq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_s8)))
mve_pred16_t vcmpeqq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u16)))
mve_pred16_t vcmpeqq_m_n_u16(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u16)))
mve_pred16_t vcmpeqq_m(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u32)))
mve_pred16_t vcmpeqq_m_n_u32(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u32)))
mve_pred16_t vcmpeqq_m(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u8)))
mve_pred16_t vcmpeqq_m_n_u8(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_u8)))
mve_pred16_t vcmpeqq_m(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s16)))
mve_pred16_t vcmpeqq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s16)))
mve_pred16_t vcmpeqq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s32)))
mve_pred16_t vcmpeqq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s32)))
mve_pred16_t vcmpeqq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s8)))
mve_pred16_t vcmpeqq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_s8)))
mve_pred16_t vcmpeqq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u16)))
mve_pred16_t vcmpeqq_m_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u16)))
mve_pred16_t vcmpeqq_m(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u32)))
mve_pred16_t vcmpeqq_m_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u32)))
mve_pred16_t vcmpeqq_m(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u8)))
mve_pred16_t vcmpeqq_m_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_u8)))
mve_pred16_t vcmpeqq_m(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s16)))
mve_pred16_t vcmpeqq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s16)))
mve_pred16_t vcmpeqq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s32)))
mve_pred16_t vcmpeqq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s32)))
mve_pred16_t vcmpeqq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s8)))
mve_pred16_t vcmpeqq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_s8)))
mve_pred16_t vcmpeqq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u16)))
mve_pred16_t vcmpeqq_n_u16(uint16x8_t, uint16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u16)))
mve_pred16_t vcmpeqq(uint16x8_t, uint16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u32)))
mve_pred16_t vcmpeqq_n_u32(uint32x4_t, uint32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u32)))
mve_pred16_t vcmpeqq(uint32x4_t, uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u8)))
mve_pred16_t vcmpeqq_n_u8(uint8x16_t, uint8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_u8)))
mve_pred16_t vcmpeqq(uint8x16_t, uint8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s16)))
mve_pred16_t vcmpeqq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s16)))
mve_pred16_t vcmpeqq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s32)))
mve_pred16_t vcmpeqq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s32)))
mve_pred16_t vcmpeqq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s8)))
mve_pred16_t vcmpeqq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_s8)))
mve_pred16_t vcmpeqq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u16)))
mve_pred16_t vcmpeqq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u16)))
mve_pred16_t vcmpeqq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u32)))
mve_pred16_t vcmpeqq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u32)))
mve_pred16_t vcmpeqq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u8)))
mve_pred16_t vcmpeqq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_u8)))
mve_pred16_t vcmpeqq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s16)))
mve_pred16_t vcmpgeq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s16)))
mve_pred16_t vcmpgeq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s32)))
mve_pred16_t vcmpgeq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s32)))
mve_pred16_t vcmpgeq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s8)))
mve_pred16_t vcmpgeq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_s8)))
mve_pred16_t vcmpgeq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s16)))
mve_pred16_t vcmpgeq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s16)))
mve_pred16_t vcmpgeq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s32)))
mve_pred16_t vcmpgeq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s32)))
mve_pred16_t vcmpgeq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s8)))
mve_pred16_t vcmpgeq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_s8)))
mve_pred16_t vcmpgeq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s16)))
mve_pred16_t vcmpgeq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s16)))
mve_pred16_t vcmpgeq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s32)))
mve_pred16_t vcmpgeq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s32)))
mve_pred16_t vcmpgeq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s8)))
mve_pred16_t vcmpgeq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_s8)))
mve_pred16_t vcmpgeq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s16)))
mve_pred16_t vcmpgeq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s16)))
mve_pred16_t vcmpgeq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s32)))
mve_pred16_t vcmpgeq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s32)))
mve_pred16_t vcmpgeq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s8)))
mve_pred16_t vcmpgeq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_s8)))
mve_pred16_t vcmpgeq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s16)))
mve_pred16_t vcmpgtq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s16)))
mve_pred16_t vcmpgtq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s32)))
mve_pred16_t vcmpgtq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s32)))
mve_pred16_t vcmpgtq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s8)))
mve_pred16_t vcmpgtq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_s8)))
mve_pred16_t vcmpgtq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s16)))
mve_pred16_t vcmpgtq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s16)))
mve_pred16_t vcmpgtq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s32)))
mve_pred16_t vcmpgtq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s32)))
mve_pred16_t vcmpgtq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s8)))
mve_pred16_t vcmpgtq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_s8)))
mve_pred16_t vcmpgtq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s16)))
mve_pred16_t vcmpgtq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s16)))
mve_pred16_t vcmpgtq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s32)))
mve_pred16_t vcmpgtq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s32)))
mve_pred16_t vcmpgtq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s8)))
mve_pred16_t vcmpgtq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_s8)))
mve_pred16_t vcmpgtq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s16)))
mve_pred16_t vcmpgtq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s16)))
mve_pred16_t vcmpgtq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s32)))
mve_pred16_t vcmpgtq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s32)))
mve_pred16_t vcmpgtq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s8)))
mve_pred16_t vcmpgtq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_s8)))
mve_pred16_t vcmpgtq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u16)))
mve_pred16_t vcmphiq_m_n_u16(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u16)))
mve_pred16_t vcmphiq_m(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u32)))
mve_pred16_t vcmphiq_m_n_u32(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u32)))
mve_pred16_t vcmphiq_m(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u8)))
mve_pred16_t vcmphiq_m_n_u8(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_n_u8)))
mve_pred16_t vcmphiq_m(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u16)))
mve_pred16_t vcmphiq_m_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u16)))
mve_pred16_t vcmphiq_m(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u32)))
mve_pred16_t vcmphiq_m_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u32)))
mve_pred16_t vcmphiq_m(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u8)))
mve_pred16_t vcmphiq_m_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_m_u8)))
mve_pred16_t vcmphiq_m(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u16)))
mve_pred16_t vcmphiq_n_u16(uint16x8_t, uint16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u16)))
mve_pred16_t vcmphiq(uint16x8_t, uint16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u32)))
mve_pred16_t vcmphiq_n_u32(uint32x4_t, uint32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u32)))
mve_pred16_t vcmphiq(uint32x4_t, uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u8)))
mve_pred16_t vcmphiq_n_u8(uint8x16_t, uint8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_n_u8)))
mve_pred16_t vcmphiq(uint8x16_t, uint8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u16)))
mve_pred16_t vcmphiq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u16)))
mve_pred16_t vcmphiq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u32)))
mve_pred16_t vcmphiq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u32)))
mve_pred16_t vcmphiq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u8)))
mve_pred16_t vcmphiq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmphiq_u8)))
mve_pred16_t vcmphiq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s16)))
mve_pred16_t vcmpleq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s16)))
mve_pred16_t vcmpleq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s32)))
mve_pred16_t vcmpleq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s32)))
mve_pred16_t vcmpleq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s8)))
mve_pred16_t vcmpleq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_s8)))
mve_pred16_t vcmpleq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s16)))
mve_pred16_t vcmpleq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s16)))
mve_pred16_t vcmpleq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s32)))
mve_pred16_t vcmpleq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s32)))
mve_pred16_t vcmpleq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s8)))
mve_pred16_t vcmpleq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_s8)))
mve_pred16_t vcmpleq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s16)))
mve_pred16_t vcmpleq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s16)))
mve_pred16_t vcmpleq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s32)))
mve_pred16_t vcmpleq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s32)))
mve_pred16_t vcmpleq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s8)))
mve_pred16_t vcmpleq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_s8)))
mve_pred16_t vcmpleq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s16)))
mve_pred16_t vcmpleq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s16)))
mve_pred16_t vcmpleq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s32)))
mve_pred16_t vcmpleq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s32)))
mve_pred16_t vcmpleq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s8)))
mve_pred16_t vcmpleq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_s8)))
mve_pred16_t vcmpleq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s16)))
mve_pred16_t vcmpltq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s16)))
mve_pred16_t vcmpltq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s32)))
mve_pred16_t vcmpltq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s32)))
mve_pred16_t vcmpltq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s8)))
mve_pred16_t vcmpltq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_s8)))
mve_pred16_t vcmpltq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s16)))
mve_pred16_t vcmpltq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s16)))
mve_pred16_t vcmpltq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s32)))
mve_pred16_t vcmpltq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s32)))
mve_pred16_t vcmpltq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s8)))
mve_pred16_t vcmpltq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_s8)))
mve_pred16_t vcmpltq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s16)))
mve_pred16_t vcmpltq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s16)))
mve_pred16_t vcmpltq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s32)))
mve_pred16_t vcmpltq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s32)))
mve_pred16_t vcmpltq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s8)))
mve_pred16_t vcmpltq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_s8)))
mve_pred16_t vcmpltq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s16)))
mve_pred16_t vcmpltq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s16)))
mve_pred16_t vcmpltq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s32)))
mve_pred16_t vcmpltq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s32)))
mve_pred16_t vcmpltq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s8)))
mve_pred16_t vcmpltq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_s8)))
mve_pred16_t vcmpltq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s16)))
mve_pred16_t vcmpneq_m_n_s16(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s16)))
mve_pred16_t vcmpneq_m(int16x8_t, int16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s32)))
mve_pred16_t vcmpneq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s32)))
mve_pred16_t vcmpneq_m(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s8)))
mve_pred16_t vcmpneq_m_n_s8(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_s8)))
mve_pred16_t vcmpneq_m(int8x16_t, int8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u16)))
mve_pred16_t vcmpneq_m_n_u16(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u16)))
mve_pred16_t vcmpneq_m(uint16x8_t, uint16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u32)))
mve_pred16_t vcmpneq_m_n_u32(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u32)))
mve_pred16_t vcmpneq_m(uint32x4_t, uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u8)))
mve_pred16_t vcmpneq_m_n_u8(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_u8)))
mve_pred16_t vcmpneq_m(uint8x16_t, uint8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s16)))
mve_pred16_t vcmpneq_m_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s16)))
mve_pred16_t vcmpneq_m(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s32)))
mve_pred16_t vcmpneq_m_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s32)))
mve_pred16_t vcmpneq_m(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s8)))
mve_pred16_t vcmpneq_m_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_s8)))
mve_pred16_t vcmpneq_m(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u16)))
mve_pred16_t vcmpneq_m_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u16)))
mve_pred16_t vcmpneq_m(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u32)))
mve_pred16_t vcmpneq_m_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u32)))
mve_pred16_t vcmpneq_m(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u8)))
mve_pred16_t vcmpneq_m_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_u8)))
mve_pred16_t vcmpneq_m(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s16)))
mve_pred16_t vcmpneq_n_s16(int16x8_t, int16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s16)))
mve_pred16_t vcmpneq(int16x8_t, int16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s32)))
mve_pred16_t vcmpneq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s32)))
mve_pred16_t vcmpneq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s8)))
mve_pred16_t vcmpneq_n_s8(int8x16_t, int8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_s8)))
mve_pred16_t vcmpneq(int8x16_t, int8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u16)))
mve_pred16_t vcmpneq_n_u16(uint16x8_t, uint16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u16)))
mve_pred16_t vcmpneq(uint16x8_t, uint16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u32)))
mve_pred16_t vcmpneq_n_u32(uint32x4_t, uint32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u32)))
mve_pred16_t vcmpneq(uint32x4_t, uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u8)))
mve_pred16_t vcmpneq_n_u8(uint8x16_t, uint8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_u8)))
mve_pred16_t vcmpneq(uint8x16_t, uint8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s16)))
mve_pred16_t vcmpneq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s16)))
mve_pred16_t vcmpneq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s32)))
mve_pred16_t vcmpneq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s32)))
mve_pred16_t vcmpneq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s8)))
mve_pred16_t vcmpneq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_s8)))
mve_pred16_t vcmpneq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u16)))
mve_pred16_t vcmpneq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u16)))
mve_pred16_t vcmpneq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u32)))
mve_pred16_t vcmpneq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u32)))
mve_pred16_t vcmpneq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u8)))
mve_pred16_t vcmpneq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_u8)))
mve_pred16_t vcmpneq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_s16)))
int16x8_t vcreateq_s16(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_s32)))
int32x4_t vcreateq_s32(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_s64)))
int64x2_t vcreateq_s64(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_s8)))
int8x16_t vcreateq_s8(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_u16)))
uint16x8_t vcreateq_u16(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_u32)))
uint32x4_t vcreateq_u32(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_u64)))
uint64x2_t vcreateq_u64(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_u8)))
uint8x16_t vcreateq_u8(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp16q)))
mve_pred16_t vctp16q(uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp16q_m)))
mve_pred16_t vctp16q_m(uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp32q)))
mve_pred16_t vctp32q(uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp32q_m)))
mve_pred16_t vctp32q_m(uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp64q)))
mve_pred16_t vctp64q(uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp64q_m)))
mve_pred16_t vctp64q_m(uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp8q)))
mve_pred16_t vctp8q(uint32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vctp8q_m)))
mve_pred16_t vctp8q_m(uint32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s16)))
int16x8_t veorq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s16)))
int16x8_t veorq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s32)))
int32x4_t veorq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s32)))
int32x4_t veorq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s8)))
int8x16_t veorq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_s8)))
int8x16_t veorq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u16)))
uint16x8_t veorq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u16)))
uint16x8_t veorq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u32)))
uint32x4_t veorq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u32)))
uint32x4_t veorq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u8)))
uint8x16_t veorq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_u8)))
uint8x16_t veorq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_s16)))
int16x8_t veorq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_s16)))
int16x8_t veorq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_s32)))
int32x4_t veorq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_s32)))
int32x4_t veorq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_s8)))
int8x16_t veorq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_s8)))
int8x16_t veorq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_u16)))
uint16x8_t veorq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_u16)))
uint16x8_t veorq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_u32)))
uint32x4_t veorq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_u32)))
uint32x4_t veorq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_u8)))
uint8x16_t veorq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_u8)))
uint8x16_t veorq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s16)))
int16x8_t veorq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s16)))
int16x8_t veorq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s32)))
int32x4_t veorq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s32)))
int32x4_t veorq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s8)))
int8x16_t veorq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_s8)))
int8x16_t veorq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u16)))
uint16x8_t veorq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u16)))
uint16x8_t veorq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u32)))
uint32x4_t veorq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u32)))
uint32x4_t veorq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u8)))
uint8x16_t veorq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_u8)))
uint8x16_t veorq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s16)))
int16_t vgetq_lane_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s16)))
int16_t vgetq_lane(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s32)))
int32_t vgetq_lane_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s32)))
int32_t vgetq_lane(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s64)))
int64_t vgetq_lane_s64(int64x2_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s64)))
int64_t vgetq_lane(int64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s8)))
int8_t vgetq_lane_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_s8)))
int8_t vgetq_lane(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u16)))
uint16_t vgetq_lane_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u16)))
uint16_t vgetq_lane(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u32)))
uint32_t vgetq_lane_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u32)))
uint32_t vgetq_lane(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u64)))
uint64_t vgetq_lane_u64(uint64x2_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u64)))
uint64_t vgetq_lane(uint64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u8)))
uint8_t vgetq_lane_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_u8)))
uint8_t vgetq_lane(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s16)))
int16x8_t vhaddq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s16)))
int16x8_t vhaddq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s32)))
int32x4_t vhaddq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s32)))
int32x4_t vhaddq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s8)))
int8x16_t vhaddq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_s8)))
int8x16_t vhaddq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u16)))
uint16x8_t vhaddq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u16)))
uint16x8_t vhaddq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u32)))
uint32x4_t vhaddq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u32)))
uint32x4_t vhaddq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u8)))
uint8x16_t vhaddq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_m_u8)))
uint8x16_t vhaddq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s16)))
int16x8_t vhaddq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s16)))
int16x8_t vhaddq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s32)))
int32x4_t vhaddq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s32)))
int32x4_t vhaddq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s8)))
int8x16_t vhaddq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_s8)))
int8x16_t vhaddq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u16)))
uint16x8_t vhaddq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u16)))
uint16x8_t vhaddq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u32)))
uint32x4_t vhaddq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u32)))
uint32x4_t vhaddq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u8)))
uint8x16_t vhaddq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_u8)))
uint8x16_t vhaddq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s16)))
int16x8_t vhaddq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s16)))
int16x8_t vhaddq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s32)))
int32x4_t vhaddq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s32)))
int32x4_t vhaddq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s8)))
int8x16_t vhaddq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_s8)))
int8x16_t vhaddq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u16)))
uint16x8_t vhaddq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u16)))
uint16x8_t vhaddq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u32)))
uint32x4_t vhaddq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u32)))
uint32x4_t vhaddq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u8)))
uint8x16_t vhaddq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhaddq_x_u8)))
uint8x16_t vhaddq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s16)))
int16x8_t vhcaddq_rot270_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s16)))
int16x8_t vhcaddq_rot270_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s32)))
int32x4_t vhcaddq_rot270_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s32)))
int32x4_t vhcaddq_rot270_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s8)))
int8x16_t vhcaddq_rot270_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_m_s8)))
int8x16_t vhcaddq_rot270_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s16)))
int16x8_t vhcaddq_rot270_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s16)))
int16x8_t vhcaddq_rot270(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s32)))
int32x4_t vhcaddq_rot270_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s32)))
int32x4_t vhcaddq_rot270(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s8)))
int8x16_t vhcaddq_rot270_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_s8)))
int8x16_t vhcaddq_rot270(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s16)))
int16x8_t vhcaddq_rot270_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s16)))
int16x8_t vhcaddq_rot270_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s32)))
int32x4_t vhcaddq_rot270_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s32)))
int32x4_t vhcaddq_rot270_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s8)))
int8x16_t vhcaddq_rot270_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot270_x_s8)))
int8x16_t vhcaddq_rot270_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s16)))
int16x8_t vhcaddq_rot90_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s16)))
int16x8_t vhcaddq_rot90_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s32)))
int32x4_t vhcaddq_rot90_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s32)))
int32x4_t vhcaddq_rot90_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s8)))
int8x16_t vhcaddq_rot90_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_m_s8)))
int8x16_t vhcaddq_rot90_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s16)))
int16x8_t vhcaddq_rot90_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s16)))
int16x8_t vhcaddq_rot90(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s32)))
int32x4_t vhcaddq_rot90_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s32)))
int32x4_t vhcaddq_rot90(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s8)))
int8x16_t vhcaddq_rot90_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_s8)))
int8x16_t vhcaddq_rot90(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s16)))
int16x8_t vhcaddq_rot90_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s16)))
int16x8_t vhcaddq_rot90_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s32)))
int32x4_t vhcaddq_rot90_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s32)))
int32x4_t vhcaddq_rot90_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s8)))
int8x16_t vhcaddq_rot90_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhcaddq_rot90_x_s8)))
int8x16_t vhcaddq_rot90_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s16)))
int16x8_t vhsubq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s16)))
int16x8_t vhsubq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s32)))
int32x4_t vhsubq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s32)))
int32x4_t vhsubq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s8)))
int8x16_t vhsubq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_s8)))
int8x16_t vhsubq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u16)))
uint16x8_t vhsubq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u16)))
uint16x8_t vhsubq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u32)))
uint32x4_t vhsubq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u32)))
uint32x4_t vhsubq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u8)))
uint8x16_t vhsubq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_m_u8)))
uint8x16_t vhsubq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s16)))
int16x8_t vhsubq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s16)))
int16x8_t vhsubq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s32)))
int32x4_t vhsubq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s32)))
int32x4_t vhsubq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s8)))
int8x16_t vhsubq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_s8)))
int8x16_t vhsubq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u16)))
uint16x8_t vhsubq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u16)))
uint16x8_t vhsubq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u32)))
uint32x4_t vhsubq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u32)))
uint32x4_t vhsubq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u8)))
uint8x16_t vhsubq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_u8)))
uint8x16_t vhsubq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s16)))
int16x8_t vhsubq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s16)))
int16x8_t vhsubq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s32)))
int32x4_t vhsubq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s32)))
int32x4_t vhsubq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s8)))
int8x16_t vhsubq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_s8)))
int8x16_t vhsubq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u16)))
uint16x8_t vhsubq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u16)))
uint16x8_t vhsubq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u32)))
uint32x4_t vhsubq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u32)))
uint32x4_t vhsubq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u8)))
uint8x16_t vhsubq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vhsubq_x_u8)))
uint8x16_t vhsubq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_s16)))
int16x8_t vld1q_s16(const int16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_s16)))
int16x8_t vld1q(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_s32)))
int32x4_t vld1q_s32(const int32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_s32)))
int32x4_t vld1q(const int32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_s8)))
int8x16_t vld1q_s8(const int8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_s8)))
int8x16_t vld1q(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_u16)))
uint16x8_t vld1q_u16(const uint16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_u16)))
uint16x8_t vld1q(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_u32)))
uint32x4_t vld1q_u32(const uint32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_u32)))
uint32x4_t vld1q(const uint32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_u8)))
uint8x16_t vld1q_u8(const uint8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_u8)))
uint8x16_t vld1q(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s16)))
int16x8_t vld1q_z_s16(const int16_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s16)))
int16x8_t vld1q_z(const int16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s32)))
int32x4_t vld1q_z_s32(const int32_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s32)))
int32x4_t vld1q_z(const int32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s8)))
int8x16_t vld1q_z_s8(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_s8)))
int8x16_t vld1q_z(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u16)))
uint16x8_t vld1q_z_u16(const uint16_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u16)))
uint16x8_t vld1q_z(const uint16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u32)))
uint32x4_t vld1q_z_u32(const uint32_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u32)))
uint32x4_t vld1q_z(const uint32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u8)))
uint8x16_t vld1q_z_u8(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_u8)))
uint8x16_t vld1q_z(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_s16)))
int16x8x2_t vld2q_s16(const int16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_s16)))
int16x8x2_t vld2q(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_s32)))
int32x4x2_t vld2q_s32(const int32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_s32)))
int32x4x2_t vld2q(const int32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_s8)))
int8x16x2_t vld2q_s8(const int8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_s8)))
int8x16x2_t vld2q(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_u16)))
uint16x8x2_t vld2q_u16(const uint16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_u16)))
uint16x8x2_t vld2q(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_u32)))
uint32x4x2_t vld2q_u32(const uint32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_u32)))
uint32x4x2_t vld2q(const uint32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_u8)))
uint8x16x2_t vld2q_u8(const uint8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_u8)))
uint8x16x2_t vld2q(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_s16)))
int16x8x4_t vld4q_s16(const int16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_s16)))
int16x8x4_t vld4q(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_s32)))
int32x4x4_t vld4q_s32(const int32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_s32)))
int32x4x4_t vld4q(const int32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_s8)))
int8x16x4_t vld4q_s8(const int8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_s8)))
int8x16x4_t vld4q(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_u16)))
uint16x8x4_t vld4q_u16(const uint16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_u16)))
uint16x8x4_t vld4q(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_u32)))
uint32x4x4_t vld4q_u32(const uint32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_u32)))
uint32x4x4_t vld4q(const uint32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_u8)))
uint8x16x4_t vld4q_u8(const uint8_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_u8)))
uint8x16x4_t vld4q(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s16)))
int16x8_t vldrbq_gather_offset_s16(const int8_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s16)))
int16x8_t vldrbq_gather_offset(const int8_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s32)))
int32x4_t vldrbq_gather_offset_s32(const int8_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s32)))
int32x4_t vldrbq_gather_offset(const int8_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s8)))
int8x16_t vldrbq_gather_offset_s8(const int8_t *, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_s8)))
int8x16_t vldrbq_gather_offset(const int8_t *, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u16)))
uint16x8_t vldrbq_gather_offset_u16(const uint8_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u16)))
uint16x8_t vldrbq_gather_offset(const uint8_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u32)))
uint32x4_t vldrbq_gather_offset_u32(const uint8_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u32)))
uint32x4_t vldrbq_gather_offset(const uint8_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u8)))
uint8x16_t vldrbq_gather_offset_u8(const uint8_t *, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_u8)))
uint8x16_t vldrbq_gather_offset(const uint8_t *, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s16)))
int16x8_t vldrbq_gather_offset_z_s16(const int8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s16)))
int16x8_t vldrbq_gather_offset_z(const int8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s32)))
int32x4_t vldrbq_gather_offset_z_s32(const int8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s32)))
int32x4_t vldrbq_gather_offset_z(const int8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s8)))
int8x16_t vldrbq_gather_offset_z_s8(const int8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_s8)))
int8x16_t vldrbq_gather_offset_z(const int8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u16)))
uint16x8_t vldrbq_gather_offset_z_u16(const uint8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u16)))
uint16x8_t vldrbq_gather_offset_z(const uint8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u32)))
uint32x4_t vldrbq_gather_offset_z_u32(const uint8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u32)))
uint32x4_t vldrbq_gather_offset_z(const uint8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u8)))
uint8x16_t vldrbq_gather_offset_z_u8(const uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrbq_gather_offset_z_u8)))
uint8x16_t vldrbq_gather_offset_z(const uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_s16)))
int16x8_t vldrbq_s16(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_s32)))
int32x4_t vldrbq_s32(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_s8)))
int8x16_t vldrbq_s8(const int8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_u16)))
uint16x8_t vldrbq_u16(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_u32)))
uint32x4_t vldrbq_u32(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_u8)))
uint8x16_t vldrbq_u8(const uint8_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_s16)))
int16x8_t vldrbq_z_s16(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_s32)))
int32x4_t vldrbq_z_s32(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_s8)))
int8x16_t vldrbq_z_s8(const int8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_u16)))
uint16x8_t vldrbq_z_u16(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_u32)))
uint32x4_t vldrbq_z_u32(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrbq_z_u8)))
uint8x16_t vldrbq_z_u8(const uint8_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_s64)))
int64x2_t vldrdq_gather_base_s64(uint64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_u64)))
uint64x2_t vldrdq_gather_base_u64(uint64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_wb_s64)))
int64x2_t vldrdq_gather_base_wb_s64(uint64x2_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_wb_u64)))
uint64x2_t vldrdq_gather_base_wb_u64(uint64x2_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_wb_z_s64)))
int64x2_t vldrdq_gather_base_wb_z_s64(uint64x2_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_wb_z_u64)))
uint64x2_t vldrdq_gather_base_wb_z_u64(uint64x2_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_z_s64)))
int64x2_t vldrdq_gather_base_z_s64(uint64x2_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_base_z_u64)))
uint64x2_t vldrdq_gather_base_z_u64(uint64x2_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_s64)))
int64x2_t vldrdq_gather_offset_s64(const int64_t *, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_s64)))
int64x2_t vldrdq_gather_offset(const int64_t *, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_u64)))
uint64x2_t vldrdq_gather_offset_u64(const uint64_t *, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_u64)))
uint64x2_t vldrdq_gather_offset(const uint64_t *, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_z_s64)))
int64x2_t vldrdq_gather_offset_z_s64(const int64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_z_s64)))
int64x2_t vldrdq_gather_offset_z(const int64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_z_u64)))
uint64x2_t vldrdq_gather_offset_z_u64(const uint64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_offset_z_u64)))
uint64x2_t vldrdq_gather_offset_z(const uint64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_s64)))
int64x2_t vldrdq_gather_shifted_offset_s64(const int64_t *, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_s64)))
int64x2_t vldrdq_gather_shifted_offset(const int64_t *, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_u64)))
uint64x2_t vldrdq_gather_shifted_offset_u64(const uint64_t *, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_u64)))
uint64x2_t vldrdq_gather_shifted_offset(const uint64_t *, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_z_s64)))
int64x2_t vldrdq_gather_shifted_offset_z_s64(const int64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_z_s64)))
int64x2_t vldrdq_gather_shifted_offset_z(const int64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_z_u64)))
uint64x2_t vldrdq_gather_shifted_offset_z_u64(const uint64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrdq_gather_shifted_offset_z_u64)))
uint64x2_t vldrdq_gather_shifted_offset_z(const uint64_t *, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_s16)))
int16x8_t vldrhq_gather_offset_s16(const int16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_s16)))
int16x8_t vldrhq_gather_offset(const int16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_s32)))
int32x4_t vldrhq_gather_offset_s32(const int16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_s32)))
int32x4_t vldrhq_gather_offset(const int16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_u16)))
uint16x8_t vldrhq_gather_offset_u16(const uint16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_u16)))
uint16x8_t vldrhq_gather_offset(const uint16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_u32)))
uint32x4_t vldrhq_gather_offset_u32(const uint16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_u32)))
uint32x4_t vldrhq_gather_offset(const uint16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_s16)))
int16x8_t vldrhq_gather_offset_z_s16(const int16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_s16)))
int16x8_t vldrhq_gather_offset_z(const int16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_s32)))
int32x4_t vldrhq_gather_offset_z_s32(const int16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_s32)))
int32x4_t vldrhq_gather_offset_z(const int16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_u16)))
uint16x8_t vldrhq_gather_offset_z_u16(const uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_u16)))
uint16x8_t vldrhq_gather_offset_z(const uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_u32)))
uint32x4_t vldrhq_gather_offset_z_u32(const uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_u32)))
uint32x4_t vldrhq_gather_offset_z(const uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_s16)))
int16x8_t vldrhq_gather_shifted_offset_s16(const int16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_s16)))
int16x8_t vldrhq_gather_shifted_offset(const int16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_s32)))
int32x4_t vldrhq_gather_shifted_offset_s32(const int16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_s32)))
int32x4_t vldrhq_gather_shifted_offset(const int16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_u16)))
uint16x8_t vldrhq_gather_shifted_offset_u16(const uint16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_u16)))
uint16x8_t vldrhq_gather_shifted_offset(const uint16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_u32)))
uint32x4_t vldrhq_gather_shifted_offset_u32(const uint16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_u32)))
uint32x4_t vldrhq_gather_shifted_offset(const uint16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_s16)))
int16x8_t vldrhq_gather_shifted_offset_z_s16(const int16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_s16)))
int16x8_t vldrhq_gather_shifted_offset_z(const int16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_s32)))
int32x4_t vldrhq_gather_shifted_offset_z_s32(const int16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_s32)))
int32x4_t vldrhq_gather_shifted_offset_z(const int16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_u16)))
uint16x8_t vldrhq_gather_shifted_offset_z_u16(const uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_u16)))
uint16x8_t vldrhq_gather_shifted_offset_z(const uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_u32)))
uint32x4_t vldrhq_gather_shifted_offset_z_u32(const uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_u32)))
uint32x4_t vldrhq_gather_shifted_offset_z(const uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_s16)))
int16x8_t vldrhq_s16(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_s32)))
int32x4_t vldrhq_s32(const int16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_u16)))
uint16x8_t vldrhq_u16(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_u32)))
uint32x4_t vldrhq_u32(const uint16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_s16)))
int16x8_t vldrhq_z_s16(const int16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_s32)))
int32x4_t vldrhq_z_s32(const int16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_u16)))
uint16x8_t vldrhq_z_u16(const uint16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_u32)))
uint32x4_t vldrhq_z_u32(const uint16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_s32)))
int32x4_t vldrwq_gather_base_s32(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_u32)))
uint32x4_t vldrwq_gather_base_u32(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_s32)))
int32x4_t vldrwq_gather_base_wb_s32(uint32x4_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_u32)))
uint32x4_t vldrwq_gather_base_wb_u32(uint32x4_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_z_s32)))
int32x4_t vldrwq_gather_base_wb_z_s32(uint32x4_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_z_u32)))
uint32x4_t vldrwq_gather_base_wb_z_u32(uint32x4_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_z_s32)))
int32x4_t vldrwq_gather_base_z_s32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_z_u32)))
uint32x4_t vldrwq_gather_base_z_u32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_s32)))
int32x4_t vldrwq_gather_offset_s32(const int32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_s32)))
int32x4_t vldrwq_gather_offset(const int32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_u32)))
uint32x4_t vldrwq_gather_offset_u32(const uint32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_u32)))
uint32x4_t vldrwq_gather_offset(const uint32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_s32)))
int32x4_t vldrwq_gather_offset_z_s32(const int32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_s32)))
int32x4_t vldrwq_gather_offset_z(const int32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_u32)))
uint32x4_t vldrwq_gather_offset_z_u32(const uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_u32)))
uint32x4_t vldrwq_gather_offset_z(const uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_s32)))
int32x4_t vldrwq_gather_shifted_offset_s32(const int32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_s32)))
int32x4_t vldrwq_gather_shifted_offset(const int32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_u32)))
uint32x4_t vldrwq_gather_shifted_offset_u32(const uint32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_u32)))
uint32x4_t vldrwq_gather_shifted_offset(const uint32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_s32)))
int32x4_t vldrwq_gather_shifted_offset_z_s32(const int32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_s32)))
int32x4_t vldrwq_gather_shifted_offset_z(const int32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_u32)))
uint32x4_t vldrwq_gather_shifted_offset_z_u32(const uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_u32)))
uint32x4_t vldrwq_gather_shifted_offset_z(const uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_s32)))
int32x4_t vldrwq_s32(const int32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_u32)))
uint32x4_t vldrwq_u32(const uint32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_z_s32)))
int32x4_t vldrwq_z_s32(const int32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_z_u32)))
uint32x4_t vldrwq_z_u32(const uint32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s16)))
int16x8_t vmaxq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s16)))
int16x8_t vmaxq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s32)))
int32x4_t vmaxq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s32)))
int32x4_t vmaxq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s8)))
int8x16_t vmaxq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_s8)))
int8x16_t vmaxq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u16)))
uint16x8_t vmaxq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u16)))
uint16x8_t vmaxq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u32)))
uint32x4_t vmaxq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u32)))
uint32x4_t vmaxq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u8)))
uint8x16_t vmaxq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_m_u8)))
uint8x16_t vmaxq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s16)))
int16x8_t vmaxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s16)))
int16x8_t vmaxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s32)))
int32x4_t vmaxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s32)))
int32x4_t vmaxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s8)))
int8x16_t vmaxq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_s8)))
int8x16_t vmaxq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u16)))
uint16x8_t vmaxq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u16)))
uint16x8_t vmaxq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u32)))
uint32x4_t vmaxq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u32)))
uint32x4_t vmaxq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u8)))
uint8x16_t vmaxq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_u8)))
uint8x16_t vmaxq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s16)))
int16x8_t vmaxq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s16)))
int16x8_t vmaxq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s32)))
int32x4_t vmaxq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s32)))
int32x4_t vmaxq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s8)))
int8x16_t vmaxq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_s8)))
int8x16_t vmaxq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u16)))
uint16x8_t vmaxq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u16)))
uint16x8_t vmaxq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u32)))
uint32x4_t vmaxq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u32)))
uint32x4_t vmaxq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u8)))
uint8x16_t vmaxq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxq_x_u8)))
uint8x16_t vmaxq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s16)))
int16_t vmaxvq_s16(int16_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s16)))
int16_t vmaxvq(int16_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s32)))
int32_t vmaxvq_s32(int32_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s32)))
int32_t vmaxvq(int32_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s8)))
int8_t vmaxvq_s8(int8_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_s8)))
int8_t vmaxvq(int8_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u16)))
uint16_t vmaxvq_u16(uint16_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u16)))
uint16_t vmaxvq(uint16_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u32)))
uint32_t vmaxvq_u32(uint32_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u32)))
uint32_t vmaxvq(uint32_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u8)))
uint8_t vmaxvq_u8(uint8_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxvq_u8)))
uint8_t vmaxvq(uint8_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s16)))
int16x8_t vminq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s16)))
int16x8_t vminq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s32)))
int32x4_t vminq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s32)))
int32x4_t vminq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s8)))
int8x16_t vminq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_s8)))
int8x16_t vminq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u16)))
uint16x8_t vminq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u16)))
uint16x8_t vminq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u32)))
uint32x4_t vminq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u32)))
uint32x4_t vminq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u8)))
uint8x16_t vminq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_m_u8)))
uint8x16_t vminq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_s16)))
int16x8_t vminq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_s16)))
int16x8_t vminq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_s32)))
int32x4_t vminq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_s32)))
int32x4_t vminq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_s8)))
int8x16_t vminq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_s8)))
int8x16_t vminq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_u16)))
uint16x8_t vminq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_u16)))
uint16x8_t vminq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_u32)))
uint32x4_t vminq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_u32)))
uint32x4_t vminq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_u8)))
uint8x16_t vminq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_u8)))
uint8x16_t vminq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s16)))
int16x8_t vminq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s16)))
int16x8_t vminq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s32)))
int32x4_t vminq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s32)))
int32x4_t vminq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s8)))
int8x16_t vminq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_s8)))
int8x16_t vminq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u16)))
uint16x8_t vminq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u16)))
uint16x8_t vminq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u32)))
uint32x4_t vminq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u32)))
uint32x4_t vminq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u8)))
uint8x16_t vminq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminq_x_u8)))
uint8x16_t vminq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_s16)))
int16_t vminvq_s16(int16_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_s16)))
int16_t vminvq(int16_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_s32)))
int32_t vminvq_s32(int32_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_s32)))
int32_t vminvq(int32_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_s8)))
int8_t vminvq_s8(int8_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_s8)))
int8_t vminvq(int8_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_u16)))
uint16_t vminvq_u16(uint16_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_u16)))
uint16_t vminvq(uint16_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_u32)))
uint32_t vminvq_u32(uint32_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_u32)))
uint32_t vminvq(uint32_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminvq_u8)))
uint8_t vminvq_u8(uint8_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminvq_u8)))
uint8_t vminvq(uint8_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s16)))
int32_t vmladavaq_p_s16(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s16)))
int32_t vmladavaq_p(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s32)))
int32_t vmladavaq_p_s32(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s32)))
int32_t vmladavaq_p(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s8)))
int32_t vmladavaq_p_s8(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_s8)))
int32_t vmladavaq_p(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u16)))
uint32_t vmladavaq_p_u16(uint32_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u16)))
uint32_t vmladavaq_p(uint32_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u32)))
uint32_t vmladavaq_p_u32(uint32_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u32)))
uint32_t vmladavaq_p(uint32_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u8)))
uint32_t vmladavaq_p_u8(uint32_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_p_u8)))
uint32_t vmladavaq_p(uint32_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s16)))
int32_t vmladavaq_s16(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s16)))
int32_t vmladavaq(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s32)))
int32_t vmladavaq_s32(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s32)))
int32_t vmladavaq(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s8)))
int32_t vmladavaq_s8(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_s8)))
int32_t vmladavaq(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u16)))
uint32_t vmladavaq_u16(uint32_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u16)))
uint32_t vmladavaq(uint32_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u32)))
uint32_t vmladavaq_u32(uint32_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u32)))
uint32_t vmladavaq(uint32_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u8)))
uint32_t vmladavaq_u8(uint32_t, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaq_u8)))
uint32_t vmladavaq(uint32_t, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s16)))
int32_t vmladavaxq_p_s16(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s16)))
int32_t vmladavaxq_p(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s32)))
int32_t vmladavaxq_p_s32(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s32)))
int32_t vmladavaxq_p(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s8)))
int32_t vmladavaxq_p_s8(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_p_s8)))
int32_t vmladavaxq_p(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s16)))
int32_t vmladavaxq_s16(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s16)))
int32_t vmladavaxq(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s32)))
int32_t vmladavaxq_s32(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s32)))
int32_t vmladavaxq(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s8)))
int32_t vmladavaxq_s8(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavaxq_s8)))
int32_t vmladavaxq(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s16)))
int32_t vmladavq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s16)))
int32_t vmladavq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s32)))
int32_t vmladavq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s32)))
int32_t vmladavq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s8)))
int32_t vmladavq_p_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_s8)))
int32_t vmladavq_p(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u16)))
uint32_t vmladavq_p_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u16)))
uint32_t vmladavq_p(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u32)))
uint32_t vmladavq_p_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u32)))
uint32_t vmladavq_p(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u8)))
uint32_t vmladavq_p_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_p_u8)))
uint32_t vmladavq_p(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s16)))
int32_t vmladavq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s16)))
int32_t vmladavq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s32)))
int32_t vmladavq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s32)))
int32_t vmladavq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s8)))
int32_t vmladavq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_s8)))
int32_t vmladavq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u16)))
uint32_t vmladavq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u16)))
uint32_t vmladavq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u32)))
uint32_t vmladavq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u32)))
uint32_t vmladavq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u8)))
uint32_t vmladavq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavq_u8)))
uint32_t vmladavq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s16)))
int32_t vmladavxq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s16)))
int32_t vmladavxq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s32)))
int32_t vmladavxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s32)))
int32_t vmladavxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s8)))
int32_t vmladavxq_p_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_p_s8)))
int32_t vmladavxq_p(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s16)))
int32_t vmladavxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s16)))
int32_t vmladavxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s32)))
int32_t vmladavxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s32)))
int32_t vmladavxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s8)))
int32_t vmladavxq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmladavxq_s8)))
int32_t vmladavxq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_s16)))
int64_t vmlaldavaq_p_s16(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_s16)))
int64_t vmlaldavaq_p(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_s32)))
int64_t vmlaldavaq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_s32)))
int64_t vmlaldavaq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_u16)))
uint64_t vmlaldavaq_p_u16(uint64_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_u16)))
uint64_t vmlaldavaq_p(uint64_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_u32)))
uint64_t vmlaldavaq_p_u32(uint64_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_p_u32)))
uint64_t vmlaldavaq_p(uint64_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_s16)))
int64_t vmlaldavaq_s16(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_s16)))
int64_t vmlaldavaq(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_s32)))
int64_t vmlaldavaq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_s32)))
int64_t vmlaldavaq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_u16)))
uint64_t vmlaldavaq_u16(uint64_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_u16)))
uint64_t vmlaldavaq(uint64_t, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_u32)))
uint64_t vmlaldavaq_u32(uint64_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaq_u32)))
uint64_t vmlaldavaq(uint64_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_p_s16)))
int64_t vmlaldavaxq_p_s16(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_p_s16)))
int64_t vmlaldavaxq_p(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_p_s32)))
int64_t vmlaldavaxq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_p_s32)))
int64_t vmlaldavaxq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_s16)))
int64_t vmlaldavaxq_s16(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_s16)))
int64_t vmlaldavaxq(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_s32)))
int64_t vmlaldavaxq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavaxq_s32)))
int64_t vmlaldavaxq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_s16)))
int64_t vmlaldavq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_s16)))
int64_t vmlaldavq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_s32)))
int64_t vmlaldavq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_s32)))
int64_t vmlaldavq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_u16)))
uint64_t vmlaldavq_p_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_u16)))
uint64_t vmlaldavq_p(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_u32)))
uint64_t vmlaldavq_p_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_p_u32)))
uint64_t vmlaldavq_p(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_s16)))
int64_t vmlaldavq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_s16)))
int64_t vmlaldavq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_s32)))
int64_t vmlaldavq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_s32)))
int64_t vmlaldavq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_u16)))
uint64_t vmlaldavq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_u16)))
uint64_t vmlaldavq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_u32)))
uint64_t vmlaldavq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavq_u32)))
uint64_t vmlaldavq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_p_s16)))
int64_t vmlaldavxq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_p_s16)))
int64_t vmlaldavxq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_p_s32)))
int64_t vmlaldavxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_p_s32)))
int64_t vmlaldavxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_s16)))
int64_t vmlaldavxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_s16)))
int64_t vmlaldavxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_s32)))
int64_t vmlaldavxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlaldavxq_s32)))
int64_t vmlaldavxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s16)))
int32_t vmlsdavaq_p_s16(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s16)))
int32_t vmlsdavaq_p(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s32)))
int32_t vmlsdavaq_p_s32(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s32)))
int32_t vmlsdavaq_p(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s8)))
int32_t vmlsdavaq_p_s8(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_p_s8)))
int32_t vmlsdavaq_p(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s16)))
int32_t vmlsdavaq_s16(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s16)))
int32_t vmlsdavaq(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s32)))
int32_t vmlsdavaq_s32(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s32)))
int32_t vmlsdavaq(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s8)))
int32_t vmlsdavaq_s8(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaq_s8)))
int32_t vmlsdavaq(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s16)))
int32_t vmlsdavaxq_p_s16(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s16)))
int32_t vmlsdavaxq_p(int32_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s32)))
int32_t vmlsdavaxq_p_s32(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s32)))
int32_t vmlsdavaxq_p(int32_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s8)))
int32_t vmlsdavaxq_p_s8(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_p_s8)))
int32_t vmlsdavaxq_p(int32_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s16)))
int32_t vmlsdavaxq_s16(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s16)))
int32_t vmlsdavaxq(int32_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s32)))
int32_t vmlsdavaxq_s32(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s32)))
int32_t vmlsdavaxq(int32_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s8)))
int32_t vmlsdavaxq_s8(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavaxq_s8)))
int32_t vmlsdavaxq(int32_t, int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s16)))
int32_t vmlsdavq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s16)))
int32_t vmlsdavq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s32)))
int32_t vmlsdavq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s32)))
int32_t vmlsdavq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s8)))
int32_t vmlsdavq_p_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_p_s8)))
int32_t vmlsdavq_p(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s16)))
int32_t vmlsdavq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s16)))
int32_t vmlsdavq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s32)))
int32_t vmlsdavq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s32)))
int32_t vmlsdavq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s8)))
int32_t vmlsdavq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavq_s8)))
int32_t vmlsdavq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s16)))
int32_t vmlsdavxq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s16)))
int32_t vmlsdavxq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s32)))
int32_t vmlsdavxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s32)))
int32_t vmlsdavxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s8)))
int32_t vmlsdavxq_p_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_p_s8)))
int32_t vmlsdavxq_p(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s16)))
int32_t vmlsdavxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s16)))
int32_t vmlsdavxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s32)))
int32_t vmlsdavxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s32)))
int32_t vmlsdavxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s8)))
int32_t vmlsdavxq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsdavxq_s8)))
int32_t vmlsdavxq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_p_s16)))
int64_t vmlsldavaq_p_s16(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_p_s16)))
int64_t vmlsldavaq_p(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_p_s32)))
int64_t vmlsldavaq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_p_s32)))
int64_t vmlsldavaq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_s16)))
int64_t vmlsldavaq_s16(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_s16)))
int64_t vmlsldavaq(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_s32)))
int64_t vmlsldavaq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaq_s32)))
int64_t vmlsldavaq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_p_s16)))
int64_t vmlsldavaxq_p_s16(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_p_s16)))
int64_t vmlsldavaxq_p(int64_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_p_s32)))
int64_t vmlsldavaxq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_p_s32)))
int64_t vmlsldavaxq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_s16)))
int64_t vmlsldavaxq_s16(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_s16)))
int64_t vmlsldavaxq(int64_t, int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_s32)))
int64_t vmlsldavaxq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavaxq_s32)))
int64_t vmlsldavaxq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_p_s16)))
int64_t vmlsldavq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_p_s16)))
int64_t vmlsldavq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_p_s32)))
int64_t vmlsldavq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_p_s32)))
int64_t vmlsldavq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_s16)))
int64_t vmlsldavq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_s16)))
int64_t vmlsldavq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_s32)))
int64_t vmlsldavq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavq_s32)))
int64_t vmlsldavq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_p_s16)))
int64_t vmlsldavxq_p_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_p_s16)))
int64_t vmlsldavxq_p(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_p_s32)))
int64_t vmlsldavxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_p_s32)))
int64_t vmlsldavxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_s16)))
int64_t vmlsldavxq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_s16)))
int64_t vmlsldavxq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_s32)))
int64_t vmlsldavxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmlsldavxq_s32)))
int64_t vmlsldavxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s16)))
int16x8_t vmulhq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s16)))
int16x8_t vmulhq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s32)))
int32x4_t vmulhq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s32)))
int32x4_t vmulhq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s8)))
int8x16_t vmulhq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_s8)))
int8x16_t vmulhq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u16)))
uint16x8_t vmulhq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u16)))
uint16x8_t vmulhq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u32)))
uint32x4_t vmulhq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u32)))
uint32x4_t vmulhq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u8)))
uint8x16_t vmulhq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_m_u8)))
uint8x16_t vmulhq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s16)))
int16x8_t vmulhq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s16)))
int16x8_t vmulhq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s32)))
int32x4_t vmulhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s32)))
int32x4_t vmulhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s8)))
int8x16_t vmulhq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_s8)))
int8x16_t vmulhq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u16)))
uint16x8_t vmulhq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u16)))
uint16x8_t vmulhq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u32)))
uint32x4_t vmulhq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u32)))
uint32x4_t vmulhq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u8)))
uint8x16_t vmulhq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_u8)))
uint8x16_t vmulhq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s16)))
int16x8_t vmulhq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s16)))
int16x8_t vmulhq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s32)))
int32x4_t vmulhq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s32)))
int32x4_t vmulhq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s8)))
int8x16_t vmulhq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_s8)))
int8x16_t vmulhq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u16)))
uint16x8_t vmulhq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u16)))
uint16x8_t vmulhq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u32)))
uint32x4_t vmulhq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u32)))
uint32x4_t vmulhq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u8)))
uint8x16_t vmulhq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulhq_x_u8)))
uint8x16_t vmulhq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s16)))
int32x4_t vmullbq_int_m_s16(int32x4_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s16)))
int32x4_t vmullbq_int_m(int32x4_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s32)))
int64x2_t vmullbq_int_m_s32(int64x2_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s32)))
int64x2_t vmullbq_int_m(int64x2_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s8)))
int16x8_t vmullbq_int_m_s8(int16x8_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_s8)))
int16x8_t vmullbq_int_m(int16x8_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u16)))
uint32x4_t vmullbq_int_m_u16(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u16)))
uint32x4_t vmullbq_int_m(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u32)))
uint64x2_t vmullbq_int_m_u32(uint64x2_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u32)))
uint64x2_t vmullbq_int_m(uint64x2_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u8)))
uint16x8_t vmullbq_int_m_u8(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_m_u8)))
uint16x8_t vmullbq_int_m(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s16)))
int32x4_t vmullbq_int_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s16)))
int32x4_t vmullbq_int(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s32)))
int64x2_t vmullbq_int_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s32)))
int64x2_t vmullbq_int(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s8)))
int16x8_t vmullbq_int_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_s8)))
int16x8_t vmullbq_int(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u16)))
uint32x4_t vmullbq_int_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u16)))
uint32x4_t vmullbq_int(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u32)))
uint64x2_t vmullbq_int_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u32)))
uint64x2_t vmullbq_int(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u8)))
uint16x8_t vmullbq_int_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_u8)))
uint16x8_t vmullbq_int(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s16)))
int32x4_t vmullbq_int_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s16)))
int32x4_t vmullbq_int_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s32)))
int64x2_t vmullbq_int_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s32)))
int64x2_t vmullbq_int_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s8)))
int16x8_t vmullbq_int_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_s8)))
int16x8_t vmullbq_int_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u16)))
uint32x4_t vmullbq_int_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u16)))
uint32x4_t vmullbq_int_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u32)))
uint64x2_t vmullbq_int_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u32)))
uint64x2_t vmullbq_int_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u8)))
uint16x8_t vmullbq_int_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_int_x_u8)))
uint16x8_t vmullbq_int_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_m_p16)))
uint32x4_t vmullbq_poly_m_p16(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_m_p16)))
uint32x4_t vmullbq_poly_m(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_m_p8)))
uint16x8_t vmullbq_poly_m_p8(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_m_p8)))
uint16x8_t vmullbq_poly_m(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_p16)))
uint32x4_t vmullbq_poly_p16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_p16)))
uint32x4_t vmullbq_poly(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_p8)))
uint16x8_t vmullbq_poly_p8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_p8)))
uint16x8_t vmullbq_poly(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_x_p16)))
uint32x4_t vmullbq_poly_x_p16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_x_p16)))
uint32x4_t vmullbq_poly_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_x_p8)))
uint16x8_t vmullbq_poly_x_p8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmullbq_poly_x_p8)))
uint16x8_t vmullbq_poly_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s16)))
int32x4_t vmulltq_int_m_s16(int32x4_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s16)))
int32x4_t vmulltq_int_m(int32x4_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s32)))
int64x2_t vmulltq_int_m_s32(int64x2_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s32)))
int64x2_t vmulltq_int_m(int64x2_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s8)))
int16x8_t vmulltq_int_m_s8(int16x8_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_s8)))
int16x8_t vmulltq_int_m(int16x8_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u16)))
uint32x4_t vmulltq_int_m_u16(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u16)))
uint32x4_t vmulltq_int_m(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u32)))
uint64x2_t vmulltq_int_m_u32(uint64x2_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u32)))
uint64x2_t vmulltq_int_m(uint64x2_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u8)))
uint16x8_t vmulltq_int_m_u8(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_m_u8)))
uint16x8_t vmulltq_int_m(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s16)))
int32x4_t vmulltq_int_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s16)))
int32x4_t vmulltq_int(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s32)))
int64x2_t vmulltq_int_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s32)))
int64x2_t vmulltq_int(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s8)))
int16x8_t vmulltq_int_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_s8)))
int16x8_t vmulltq_int(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u16)))
uint32x4_t vmulltq_int_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u16)))
uint32x4_t vmulltq_int(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u32)))
uint64x2_t vmulltq_int_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u32)))
uint64x2_t vmulltq_int(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u8)))
uint16x8_t vmulltq_int_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_u8)))
uint16x8_t vmulltq_int(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s16)))
int32x4_t vmulltq_int_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s16)))
int32x4_t vmulltq_int_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s32)))
int64x2_t vmulltq_int_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s32)))
int64x2_t vmulltq_int_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s8)))
int16x8_t vmulltq_int_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_s8)))
int16x8_t vmulltq_int_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u16)))
uint32x4_t vmulltq_int_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u16)))
uint32x4_t vmulltq_int_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u32)))
uint64x2_t vmulltq_int_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u32)))
uint64x2_t vmulltq_int_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u8)))
uint16x8_t vmulltq_int_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_int_x_u8)))
uint16x8_t vmulltq_int_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_m_p16)))
uint32x4_t vmulltq_poly_m_p16(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_m_p16)))
uint32x4_t vmulltq_poly_m(uint32x4_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_m_p8)))
uint16x8_t vmulltq_poly_m_p8(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_m_p8)))
uint16x8_t vmulltq_poly_m(uint16x8_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_p16)))
uint32x4_t vmulltq_poly_p16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_p16)))
uint32x4_t vmulltq_poly(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_p8)))
uint16x8_t vmulltq_poly_p8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_p8)))
uint16x8_t vmulltq_poly(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_x_p16)))
uint32x4_t vmulltq_poly_x_p16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_x_p16)))
uint32x4_t vmulltq_poly_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_x_p8)))
uint16x8_t vmulltq_poly_x_p8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulltq_poly_x_p8)))
uint16x8_t vmulltq_poly_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s16)))
int16x8_t vmulq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s16)))
int16x8_t vmulq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s32)))
int32x4_t vmulq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s32)))
int32x4_t vmulq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s8)))
int8x16_t vmulq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_s8)))
int8x16_t vmulq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u16)))
uint16x8_t vmulq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u16)))
uint16x8_t vmulq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u32)))
uint32x4_t vmulq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u32)))
uint32x4_t vmulq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u8)))
uint8x16_t vmulq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_u8)))
uint8x16_t vmulq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_s16)))
int16x8_t vmulq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_s16)))
int16x8_t vmulq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_s32)))
int32x4_t vmulq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_s32)))
int32x4_t vmulq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_s8)))
int8x16_t vmulq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_s8)))
int8x16_t vmulq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_u16)))
uint16x8_t vmulq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_u16)))
uint16x8_t vmulq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_u32)))
uint32x4_t vmulq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_u32)))
uint32x4_t vmulq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_u8)))
uint8x16_t vmulq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_u8)))
uint8x16_t vmulq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s16)))
int16x8_t vmulq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s16)))
int16x8_t vmulq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s32)))
int32x4_t vmulq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s32)))
int32x4_t vmulq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s8)))
int8x16_t vmulq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_s8)))
int8x16_t vmulq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u16)))
uint16x8_t vmulq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u16)))
uint16x8_t vmulq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u32)))
uint32x4_t vmulq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u32)))
uint32x4_t vmulq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u8)))
uint8x16_t vmulq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_u8)))
uint8x16_t vmulq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s16)))
int16x8_t vornq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s16)))
int16x8_t vornq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s32)))
int32x4_t vornq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s32)))
int32x4_t vornq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s8)))
int8x16_t vornq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_s8)))
int8x16_t vornq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u16)))
uint16x8_t vornq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u16)))
uint16x8_t vornq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u32)))
uint32x4_t vornq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u32)))
uint32x4_t vornq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u8)))
uint8x16_t vornq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_u8)))
uint8x16_t vornq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_s16)))
int16x8_t vornq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_s16)))
int16x8_t vornq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_s32)))
int32x4_t vornq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_s32)))
int32x4_t vornq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_s8)))
int8x16_t vornq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_s8)))
int8x16_t vornq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_u16)))
uint16x8_t vornq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_u16)))
uint16x8_t vornq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_u32)))
uint32x4_t vornq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_u32)))
uint32x4_t vornq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_u8)))
uint8x16_t vornq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_u8)))
uint8x16_t vornq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s16)))
int16x8_t vornq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s16)))
int16x8_t vornq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s32)))
int32x4_t vornq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s32)))
int32x4_t vornq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s8)))
int8x16_t vornq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_s8)))
int8x16_t vornq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u16)))
uint16x8_t vornq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u16)))
uint16x8_t vornq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u32)))
uint32x4_t vornq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u32)))
uint32x4_t vornq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u8)))
uint8x16_t vornq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_u8)))
uint8x16_t vornq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s16)))
int16x8_t vorrq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s16)))
int16x8_t vorrq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s32)))
int32x4_t vorrq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s32)))
int32x4_t vorrq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s8)))
int8x16_t vorrq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_s8)))
int8x16_t vorrq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u16)))
uint16x8_t vorrq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u16)))
uint16x8_t vorrq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u32)))
uint32x4_t vorrq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u32)))
uint32x4_t vorrq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u8)))
uint8x16_t vorrq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_u8)))
uint8x16_t vorrq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_s16)))
int16x8_t vorrq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_s16)))
int16x8_t vorrq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_s32)))
int32x4_t vorrq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_s32)))
int32x4_t vorrq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_s8)))
int8x16_t vorrq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_s8)))
int8x16_t vorrq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_u16)))
uint16x8_t vorrq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_u16)))
uint16x8_t vorrq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_u32)))
uint32x4_t vorrq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_u32)))
uint32x4_t vorrq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_u8)))
uint8x16_t vorrq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_u8)))
uint8x16_t vorrq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s16)))
int16x8_t vorrq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s16)))
int16x8_t vorrq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s32)))
int32x4_t vorrq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s32)))
int32x4_t vorrq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s8)))
int8x16_t vorrq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_s8)))
int8x16_t vorrq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u16)))
uint16x8_t vorrq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u16)))
uint16x8_t vorrq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u32)))
uint32x4_t vorrq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u32)))
uint32x4_t vorrq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u8)))
uint8x16_t vorrq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_u8)))
uint8x16_t vorrq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpnot)))
mve_pred16_t vpnot(mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_s16)))
int16x8_t vpselq_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_s16)))
int16x8_t vpselq(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_s32)))
int32x4_t vpselq_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_s32)))
int32x4_t vpselq(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_s64)))
int64x2_t vpselq_s64(int64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_s64)))
int64x2_t vpselq(int64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_s8)))
int8x16_t vpselq_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_s8)))
int8x16_t vpselq(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_u16)))
uint16x8_t vpselq_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_u16)))
uint16x8_t vpselq(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_u32)))
uint32x4_t vpselq_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_u32)))
uint32x4_t vpselq(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_u64)))
uint64x2_t vpselq_u64(uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_u64)))
uint64x2_t vpselq(uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_u8)))
uint8x16_t vpselq_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_u8)))
uint8x16_t vpselq(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s16)))
int16x8_t vqaddq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s16)))
int16x8_t vqaddq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s32)))
int32x4_t vqaddq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s32)))
int32x4_t vqaddq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s8)))
int8x16_t vqaddq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_s8)))
int8x16_t vqaddq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u16)))
uint16x8_t vqaddq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u16)))
uint16x8_t vqaddq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u32)))
uint32x4_t vqaddq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u32)))
uint32x4_t vqaddq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u8)))
uint8x16_t vqaddq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_m_u8)))
uint8x16_t vqaddq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s16)))
int16x8_t vqaddq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s16)))
int16x8_t vqaddq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s32)))
int32x4_t vqaddq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s32)))
int32x4_t vqaddq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s8)))
int8x16_t vqaddq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_s8)))
int8x16_t vqaddq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u16)))
uint16x8_t vqaddq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u16)))
uint16x8_t vqaddq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u32)))
uint32x4_t vqaddq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u32)))
uint32x4_t vqaddq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u8)))
uint8x16_t vqaddq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqaddq_u8)))
uint8x16_t vqaddq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s16)))
int16x8_t vqdmulhq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s16)))
int16x8_t vqdmulhq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s32)))
int32x4_t vqdmulhq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s32)))
int32x4_t vqdmulhq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s8)))
int8x16_t vqdmulhq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_m_s8)))
int8x16_t vqdmulhq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s16)))
int16x8_t vqdmulhq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s16)))
int16x8_t vqdmulhq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s32)))
int32x4_t vqdmulhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s32)))
int32x4_t vqdmulhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s8)))
int8x16_t vqdmulhq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqdmulhq_s8)))
int8x16_t vqdmulhq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s16)))
int16x8_t vqrdmulhq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s16)))
int16x8_t vqrdmulhq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s32)))
int32x4_t vqrdmulhq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s32)))
int32x4_t vqrdmulhq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s8)))
int8x16_t vqrdmulhq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_m_s8)))
int8x16_t vqrdmulhq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s16)))
int16x8_t vqrdmulhq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s16)))
int16x8_t vqrdmulhq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s32)))
int32x4_t vqrdmulhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s32)))
int32x4_t vqrdmulhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s8)))
int8x16_t vqrdmulhq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrdmulhq_s8)))
int8x16_t vqrdmulhq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s16)))
int16x8_t vqrshlq_m_n_s16(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s16)))
int16x8_t vqrshlq_m_n(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s32)))
int32x4_t vqrshlq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s32)))
int32x4_t vqrshlq_m_n(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s8)))
int8x16_t vqrshlq_m_n_s8(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_s8)))
int8x16_t vqrshlq_m_n(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u16)))
uint16x8_t vqrshlq_m_n_u16(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u16)))
uint16x8_t vqrshlq_m_n(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u32)))
uint32x4_t vqrshlq_m_n_u32(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u32)))
uint32x4_t vqrshlq_m_n(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u8)))
uint8x16_t vqrshlq_m_n_u8(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_n_u8)))
uint8x16_t vqrshlq_m_n(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s16)))
int16x8_t vqrshlq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s16)))
int16x8_t vqrshlq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s32)))
int32x4_t vqrshlq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s32)))
int32x4_t vqrshlq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s8)))
int8x16_t vqrshlq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_s8)))
int8x16_t vqrshlq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u16)))
uint16x8_t vqrshlq_m_u16(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u16)))
uint16x8_t vqrshlq_m(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u32)))
uint32x4_t vqrshlq_m_u32(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u32)))
uint32x4_t vqrshlq_m(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u8)))
uint8x16_t vqrshlq_m_u8(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_m_u8)))
uint8x16_t vqrshlq_m(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s16)))
int16x8_t vqrshlq_n_s16(int16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s16)))
int16x8_t vqrshlq(int16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s32)))
int32x4_t vqrshlq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s32)))
int32x4_t vqrshlq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s8)))
int8x16_t vqrshlq_n_s8(int8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_s8)))
int8x16_t vqrshlq(int8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u16)))
uint16x8_t vqrshlq_n_u16(uint16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u16)))
uint16x8_t vqrshlq(uint16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u32)))
uint32x4_t vqrshlq_n_u32(uint32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u32)))
uint32x4_t vqrshlq(uint32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u8)))
uint8x16_t vqrshlq_n_u8(uint8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_n_u8)))
uint8x16_t vqrshlq(uint8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s16)))
int16x8_t vqrshlq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s16)))
int16x8_t vqrshlq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s32)))
int32x4_t vqrshlq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s32)))
int32x4_t vqrshlq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s8)))
int8x16_t vqrshlq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_s8)))
int8x16_t vqrshlq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u16)))
uint16x8_t vqrshlq_u16(uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u16)))
uint16x8_t vqrshlq(uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u32)))
uint32x4_t vqrshlq_u32(uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u32)))
uint32x4_t vqrshlq(uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u8)))
uint8x16_t vqrshlq_u8(uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshlq_u8)))
uint8x16_t vqrshlq(uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_s16)))
int8x16_t vqrshrnbq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_s16)))
int8x16_t vqrshrnbq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_s32)))
int16x8_t vqrshrnbq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_s32)))
int16x8_t vqrshrnbq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_u16)))
uint8x16_t vqrshrnbq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_u16)))
uint8x16_t vqrshrnbq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_u32)))
uint16x8_t vqrshrnbq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_m_n_u32)))
uint16x8_t vqrshrnbq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_s16)))
int8x16_t vqrshrnbq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_s16)))
int8x16_t vqrshrnbq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_s32)))
int16x8_t vqrshrnbq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_s32)))
int16x8_t vqrshrnbq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_u16)))
uint8x16_t vqrshrnbq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_u16)))
uint8x16_t vqrshrnbq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_u32)))
uint16x8_t vqrshrnbq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrnbq_n_u32)))
uint16x8_t vqrshrnbq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_s16)))
int8x16_t vqrshrntq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_s16)))
int8x16_t vqrshrntq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_s32)))
int16x8_t vqrshrntq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_s32)))
int16x8_t vqrshrntq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_u16)))
uint8x16_t vqrshrntq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_u16)))
uint8x16_t vqrshrntq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_u32)))
uint16x8_t vqrshrntq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_m_n_u32)))
uint16x8_t vqrshrntq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_s16)))
int8x16_t vqrshrntq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_s16)))
int8x16_t vqrshrntq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_s32)))
int16x8_t vqrshrntq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_s32)))
int16x8_t vqrshrntq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_u16)))
uint8x16_t vqrshrntq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_u16)))
uint8x16_t vqrshrntq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_u32)))
uint16x8_t vqrshrntq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrntq_n_u32)))
uint16x8_t vqrshrntq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_m_n_s16)))
uint8x16_t vqrshrunbq_m_n_s16(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_m_n_s16)))
uint8x16_t vqrshrunbq_m(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_m_n_s32)))
uint16x8_t vqrshrunbq_m_n_s32(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_m_n_s32)))
uint16x8_t vqrshrunbq_m(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_n_s16)))
uint8x16_t vqrshrunbq_n_s16(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_n_s16)))
uint8x16_t vqrshrunbq(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_n_s32)))
uint16x8_t vqrshrunbq_n_s32(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshrunbq_n_s32)))
uint16x8_t vqrshrunbq(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_m_n_s16)))
uint8x16_t vqrshruntq_m_n_s16(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_m_n_s16)))
uint8x16_t vqrshruntq_m(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_m_n_s32)))
uint16x8_t vqrshruntq_m_n_s32(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_m_n_s32)))
uint16x8_t vqrshruntq_m(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_n_s16)))
uint8x16_t vqrshruntq_n_s16(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_n_s16)))
uint8x16_t vqrshruntq(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_n_s32)))
uint16x8_t vqrshruntq_n_s32(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqrshruntq_n_s32)))
uint16x8_t vqrshruntq(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s16)))
int16x8_t vqshlq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s16)))
int16x8_t vqshlq_m_n(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s32)))
int32x4_t vqshlq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s32)))
int32x4_t vqshlq_m_n(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s8)))
int8x16_t vqshlq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_s8)))
int8x16_t vqshlq_m_n(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u16)))
uint16x8_t vqshlq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u16)))
uint16x8_t vqshlq_m_n(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u32)))
uint32x4_t vqshlq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u32)))
uint32x4_t vqshlq_m_n(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u8)))
uint8x16_t vqshlq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_n_u8)))
uint8x16_t vqshlq_m_n(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s16)))
int16x8_t vqshlq_m_r_s16(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s16)))
int16x8_t vqshlq_m_r(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s32)))
int32x4_t vqshlq_m_r_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s32)))
int32x4_t vqshlq_m_r(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s8)))
int8x16_t vqshlq_m_r_s8(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_s8)))
int8x16_t vqshlq_m_r(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u16)))
uint16x8_t vqshlq_m_r_u16(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u16)))
uint16x8_t vqshlq_m_r(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u32)))
uint32x4_t vqshlq_m_r_u32(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u32)))
uint32x4_t vqshlq_m_r(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u8)))
uint8x16_t vqshlq_m_r_u8(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_r_u8)))
uint8x16_t vqshlq_m_r(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s16)))
int16x8_t vqshlq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s16)))
int16x8_t vqshlq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s32)))
int32x4_t vqshlq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s32)))
int32x4_t vqshlq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s8)))
int8x16_t vqshlq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_s8)))
int8x16_t vqshlq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u16)))
uint16x8_t vqshlq_m_u16(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u16)))
uint16x8_t vqshlq_m(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u32)))
uint32x4_t vqshlq_m_u32(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u32)))
uint32x4_t vqshlq_m(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u8)))
uint8x16_t vqshlq_m_u8(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_m_u8)))
uint8x16_t vqshlq_m(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s16)))
int16x8_t vqshlq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s16)))
int16x8_t vqshlq_n(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s32)))
int32x4_t vqshlq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s32)))
int32x4_t vqshlq_n(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s8)))
int8x16_t vqshlq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_s8)))
int8x16_t vqshlq_n(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u16)))
uint16x8_t vqshlq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u16)))
uint16x8_t vqshlq_n(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u32)))
uint32x4_t vqshlq_n_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u32)))
uint32x4_t vqshlq_n(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u8)))
uint8x16_t vqshlq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_n_u8)))
uint8x16_t vqshlq_n(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s16)))
int16x8_t vqshlq_r_s16(int16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s16)))
int16x8_t vqshlq_r(int16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s32)))
int32x4_t vqshlq_r_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s32)))
int32x4_t vqshlq_r(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s8)))
int8x16_t vqshlq_r_s8(int8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_s8)))
int8x16_t vqshlq_r(int8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u16)))
uint16x8_t vqshlq_r_u16(uint16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u16)))
uint16x8_t vqshlq_r(uint16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u32)))
uint32x4_t vqshlq_r_u32(uint32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u32)))
uint32x4_t vqshlq_r(uint32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u8)))
uint8x16_t vqshlq_r_u8(uint8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_r_u8)))
uint8x16_t vqshlq_r(uint8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s16)))
int16x8_t vqshlq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s16)))
int16x8_t vqshlq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s32)))
int32x4_t vqshlq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s32)))
int32x4_t vqshlq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s8)))
int8x16_t vqshlq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_s8)))
int8x16_t vqshlq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u16)))
uint16x8_t vqshlq_u16(uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u16)))
uint16x8_t vqshlq(uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u32)))
uint32x4_t vqshlq_u32(uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u32)))
uint32x4_t vqshlq(uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u8)))
uint8x16_t vqshlq_u8(uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshlq_u8)))
uint8x16_t vqshlq(uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s16)))
uint16x8_t vqshluq_m_n_s16(uint16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s16)))
uint16x8_t vqshluq_m(uint16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s32)))
uint32x4_t vqshluq_m_n_s32(uint32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s32)))
uint32x4_t vqshluq_m(uint32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s8)))
uint8x16_t vqshluq_m_n_s8(uint8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_m_n_s8)))
uint8x16_t vqshluq_m(uint8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s16)))
uint16x8_t vqshluq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s16)))
uint16x8_t vqshluq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s32)))
uint32x4_t vqshluq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s32)))
uint32x4_t vqshluq(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s8)))
uint8x16_t vqshluq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshluq_n_s8)))
uint8x16_t vqshluq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_s16)))
int8x16_t vqshrnbq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_s16)))
int8x16_t vqshrnbq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_s32)))
int16x8_t vqshrnbq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_s32)))
int16x8_t vqshrnbq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_u16)))
uint8x16_t vqshrnbq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_u16)))
uint8x16_t vqshrnbq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_u32)))
uint16x8_t vqshrnbq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_m_n_u32)))
uint16x8_t vqshrnbq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_s16)))
int8x16_t vqshrnbq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_s16)))
int8x16_t vqshrnbq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_s32)))
int16x8_t vqshrnbq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_s32)))
int16x8_t vqshrnbq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_u16)))
uint8x16_t vqshrnbq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_u16)))
uint8x16_t vqshrnbq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_u32)))
uint16x8_t vqshrnbq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrnbq_n_u32)))
uint16x8_t vqshrnbq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_s16)))
int8x16_t vqshrntq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_s16)))
int8x16_t vqshrntq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_s32)))
int16x8_t vqshrntq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_s32)))
int16x8_t vqshrntq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_u16)))
uint8x16_t vqshrntq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_u16)))
uint8x16_t vqshrntq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_u32)))
uint16x8_t vqshrntq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_m_n_u32)))
uint16x8_t vqshrntq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_s16)))
int8x16_t vqshrntq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_s16)))
int8x16_t vqshrntq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_s32)))
int16x8_t vqshrntq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_s32)))
int16x8_t vqshrntq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_u16)))
uint8x16_t vqshrntq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_u16)))
uint8x16_t vqshrntq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_u32)))
uint16x8_t vqshrntq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrntq_n_u32)))
uint16x8_t vqshrntq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_m_n_s16)))
uint8x16_t vqshrunbq_m_n_s16(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_m_n_s16)))
uint8x16_t vqshrunbq_m(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_m_n_s32)))
uint16x8_t vqshrunbq_m_n_s32(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_m_n_s32)))
uint16x8_t vqshrunbq_m(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_n_s16)))
uint8x16_t vqshrunbq_n_s16(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_n_s16)))
uint8x16_t vqshrunbq(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_n_s32)))
uint16x8_t vqshrunbq_n_s32(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshrunbq_n_s32)))
uint16x8_t vqshrunbq(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_m_n_s16)))
uint8x16_t vqshruntq_m_n_s16(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_m_n_s16)))
uint8x16_t vqshruntq_m(uint8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_m_n_s32)))
uint16x8_t vqshruntq_m_n_s32(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_m_n_s32)))
uint16x8_t vqshruntq_m(uint16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_n_s16)))
uint8x16_t vqshruntq_n_s16(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_n_s16)))
uint8x16_t vqshruntq(uint8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_n_s32)))
uint16x8_t vqshruntq_n_s32(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqshruntq_n_s32)))
uint16x8_t vqshruntq(uint16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s16)))
int16x8_t vqsubq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s16)))
int16x8_t vqsubq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s32)))
int32x4_t vqsubq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s32)))
int32x4_t vqsubq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s8)))
int8x16_t vqsubq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_s8)))
int8x16_t vqsubq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u16)))
uint16x8_t vqsubq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u16)))
uint16x8_t vqsubq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u32)))
uint32x4_t vqsubq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u32)))
uint32x4_t vqsubq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u8)))
uint8x16_t vqsubq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_m_u8)))
uint8x16_t vqsubq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s16)))
int16x8_t vqsubq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s16)))
int16x8_t vqsubq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s32)))
int32x4_t vqsubq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s32)))
int32x4_t vqsubq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s8)))
int8x16_t vqsubq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_s8)))
int8x16_t vqsubq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u16)))
uint16x8_t vqsubq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u16)))
uint16x8_t vqsubq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u32)))
uint32x4_t vqsubq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u32)))
uint32x4_t vqsubq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u8)))
uint8x16_t vqsubq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vqsubq_u8)))
uint8x16_t vqsubq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s32)))
int16x8_t vreinterpretq_s16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s32)))
int16x8_t vreinterpretq_s16(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s64)))
int16x8_t vreinterpretq_s16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s64)))
int16x8_t vreinterpretq_s16(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s8)))
int16x8_t vreinterpretq_s16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_s8)))
int16x8_t vreinterpretq_s16(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u16)))
int16x8_t vreinterpretq_s16_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u16)))
int16x8_t vreinterpretq_s16(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u32)))
int16x8_t vreinterpretq_s16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u32)))
int16x8_t vreinterpretq_s16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u64)))
int16x8_t vreinterpretq_s16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u64)))
int16x8_t vreinterpretq_s16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u8)))
int16x8_t vreinterpretq_s16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_u8)))
int16x8_t vreinterpretq_s16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s16)))
int32x4_t vreinterpretq_s32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s16)))
int32x4_t vreinterpretq_s32(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s64)))
int32x4_t vreinterpretq_s32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s64)))
int32x4_t vreinterpretq_s32(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s8)))
int32x4_t vreinterpretq_s32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_s8)))
int32x4_t vreinterpretq_s32(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u16)))
int32x4_t vreinterpretq_s32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u16)))
int32x4_t vreinterpretq_s32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u32)))
int32x4_t vreinterpretq_s32_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u32)))
int32x4_t vreinterpretq_s32(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u64)))
int32x4_t vreinterpretq_s32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u64)))
int32x4_t vreinterpretq_s32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u8)))
int32x4_t vreinterpretq_s32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_u8)))
int32x4_t vreinterpretq_s32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s16)))
int64x2_t vreinterpretq_s64_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s16)))
int64x2_t vreinterpretq_s64(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s32)))
int64x2_t vreinterpretq_s64_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s32)))
int64x2_t vreinterpretq_s64(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s8)))
int64x2_t vreinterpretq_s64_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_s8)))
int64x2_t vreinterpretq_s64(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u16)))
int64x2_t vreinterpretq_s64_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u16)))
int64x2_t vreinterpretq_s64(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u32)))
int64x2_t vreinterpretq_s64_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u32)))
int64x2_t vreinterpretq_s64(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u64)))
int64x2_t vreinterpretq_s64_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u64)))
int64x2_t vreinterpretq_s64(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u8)))
int64x2_t vreinterpretq_s64_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_u8)))
int64x2_t vreinterpretq_s64(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s16)))
int8x16_t vreinterpretq_s8_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s16)))
int8x16_t vreinterpretq_s8(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s32)))
int8x16_t vreinterpretq_s8_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s32)))
int8x16_t vreinterpretq_s8(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s64)))
int8x16_t vreinterpretq_s8_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_s64)))
int8x16_t vreinterpretq_s8(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u16)))
int8x16_t vreinterpretq_s8_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u16)))
int8x16_t vreinterpretq_s8(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u32)))
int8x16_t vreinterpretq_s8_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u32)))
int8x16_t vreinterpretq_s8(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u64)))
int8x16_t vreinterpretq_s8_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u64)))
int8x16_t vreinterpretq_s8(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u8)))
int8x16_t vreinterpretq_s8_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_u8)))
int8x16_t vreinterpretq_s8(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s16)))
uint16x8_t vreinterpretq_u16_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s16)))
uint16x8_t vreinterpretq_u16(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s32)))
uint16x8_t vreinterpretq_u16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s32)))
uint16x8_t vreinterpretq_u16(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s64)))
uint16x8_t vreinterpretq_u16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s64)))
uint16x8_t vreinterpretq_u16(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s8)))
uint16x8_t vreinterpretq_u16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_s8)))
uint16x8_t vreinterpretq_u16(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u32)))
uint16x8_t vreinterpretq_u16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u32)))
uint16x8_t vreinterpretq_u16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u64)))
uint16x8_t vreinterpretq_u16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u64)))
uint16x8_t vreinterpretq_u16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u8)))
uint16x8_t vreinterpretq_u16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_u8)))
uint16x8_t vreinterpretq_u16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s16)))
uint32x4_t vreinterpretq_u32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s16)))
uint32x4_t vreinterpretq_u32(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s32)))
uint32x4_t vreinterpretq_u32_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s32)))
uint32x4_t vreinterpretq_u32(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s64)))
uint32x4_t vreinterpretq_u32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s64)))
uint32x4_t vreinterpretq_u32(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s8)))
uint32x4_t vreinterpretq_u32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_s8)))
uint32x4_t vreinterpretq_u32(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u16)))
uint32x4_t vreinterpretq_u32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u16)))
uint32x4_t vreinterpretq_u32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u64)))
uint32x4_t vreinterpretq_u32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u64)))
uint32x4_t vreinterpretq_u32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u8)))
uint32x4_t vreinterpretq_u32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_u8)))
uint32x4_t vreinterpretq_u32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s16)))
uint64x2_t vreinterpretq_u64_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s16)))
uint64x2_t vreinterpretq_u64(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s32)))
uint64x2_t vreinterpretq_u64_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s32)))
uint64x2_t vreinterpretq_u64(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s64)))
uint64x2_t vreinterpretq_u64_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s64)))
uint64x2_t vreinterpretq_u64(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s8)))
uint64x2_t vreinterpretq_u64_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_s8)))
uint64x2_t vreinterpretq_u64(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u16)))
uint64x2_t vreinterpretq_u64_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u16)))
uint64x2_t vreinterpretq_u64(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u32)))
uint64x2_t vreinterpretq_u64_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u32)))
uint64x2_t vreinterpretq_u64(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u8)))
uint64x2_t vreinterpretq_u64_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_u8)))
uint64x2_t vreinterpretq_u64(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s16)))
uint8x16_t vreinterpretq_u8_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s16)))
uint8x16_t vreinterpretq_u8(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s32)))
uint8x16_t vreinterpretq_u8_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s32)))
uint8x16_t vreinterpretq_u8(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s64)))
uint8x16_t vreinterpretq_u8_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s64)))
uint8x16_t vreinterpretq_u8(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s8)))
uint8x16_t vreinterpretq_u8_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_s8)))
uint8x16_t vreinterpretq_u8(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u16)))
uint8x16_t vreinterpretq_u8_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u16)))
uint8x16_t vreinterpretq_u8(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u32)))
uint8x16_t vreinterpretq_u8_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u32)))
uint8x16_t vreinterpretq_u8(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u64)))
uint8x16_t vreinterpretq_u8_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_u64)))
uint8x16_t vreinterpretq_u8(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s16)))
int16x8_t vrhaddq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s16)))
int16x8_t vrhaddq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s32)))
int32x4_t vrhaddq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s32)))
int32x4_t vrhaddq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s8)))
int8x16_t vrhaddq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_s8)))
int8x16_t vrhaddq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u16)))
uint16x8_t vrhaddq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u16)))
uint16x8_t vrhaddq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u32)))
uint32x4_t vrhaddq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u32)))
uint32x4_t vrhaddq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u8)))
uint8x16_t vrhaddq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_m_u8)))
uint8x16_t vrhaddq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s16)))
int16x8_t vrhaddq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s16)))
int16x8_t vrhaddq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s32)))
int32x4_t vrhaddq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s32)))
int32x4_t vrhaddq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s8)))
int8x16_t vrhaddq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_s8)))
int8x16_t vrhaddq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u16)))
uint16x8_t vrhaddq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u16)))
uint16x8_t vrhaddq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u32)))
uint32x4_t vrhaddq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u32)))
uint32x4_t vrhaddq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u8)))
uint8x16_t vrhaddq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_u8)))
uint8x16_t vrhaddq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s16)))
int16x8_t vrhaddq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s16)))
int16x8_t vrhaddq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s32)))
int32x4_t vrhaddq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s32)))
int32x4_t vrhaddq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s8)))
int8x16_t vrhaddq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_s8)))
int8x16_t vrhaddq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u16)))
uint16x8_t vrhaddq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u16)))
uint16x8_t vrhaddq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u32)))
uint32x4_t vrhaddq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u32)))
uint32x4_t vrhaddq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u8)))
uint8x16_t vrhaddq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrhaddq_x_u8)))
uint8x16_t vrhaddq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_p_s32)))
int64_t vrmlaldavhaq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_p_s32)))
int64_t vrmlaldavhaq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_p_u32)))
uint64_t vrmlaldavhaq_p_u32(uint64_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_p_u32)))
uint64_t vrmlaldavhaq_p(uint64_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_s32)))
int64_t vrmlaldavhaq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_s32)))
int64_t vrmlaldavhaq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_u32)))
uint64_t vrmlaldavhaq_u32(uint64_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaq_u32)))
uint64_t vrmlaldavhaq(uint64_t, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaxq_p_s32)))
int64_t vrmlaldavhaxq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaxq_p_s32)))
int64_t vrmlaldavhaxq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaxq_s32)))
int64_t vrmlaldavhaxq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhaxq_s32)))
int64_t vrmlaldavhaxq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_p_s32)))
int64_t vrmlaldavhq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_p_s32)))
int64_t vrmlaldavhq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_p_u32)))
uint64_t vrmlaldavhq_p_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_p_u32)))
uint64_t vrmlaldavhq_p(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_s32)))
int64_t vrmlaldavhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_s32)))
int64_t vrmlaldavhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_u32)))
uint64_t vrmlaldavhq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhq_u32)))
uint64_t vrmlaldavhq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhxq_p_s32)))
int64_t vrmlaldavhxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhxq_p_s32)))
int64_t vrmlaldavhxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhxq_s32)))
int64_t vrmlaldavhxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlaldavhxq_s32)))
int64_t vrmlaldavhxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaq_p_s32)))
int64_t vrmlsldavhaq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaq_p_s32)))
int64_t vrmlsldavhaq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaq_s32)))
int64_t vrmlsldavhaq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaq_s32)))
int64_t vrmlsldavhaq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaxq_p_s32)))
int64_t vrmlsldavhaxq_p_s32(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaxq_p_s32)))
int64_t vrmlsldavhaxq_p(int64_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaxq_s32)))
int64_t vrmlsldavhaxq_s32(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhaxq_s32)))
int64_t vrmlsldavhaxq(int64_t, int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhq_p_s32)))
int64_t vrmlsldavhq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhq_p_s32)))
int64_t vrmlsldavhq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhq_s32)))
int64_t vrmlsldavhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhq_s32)))
int64_t vrmlsldavhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhxq_p_s32)))
int64_t vrmlsldavhxq_p_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhxq_p_s32)))
int64_t vrmlsldavhxq_p(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhxq_s32)))
int64_t vrmlsldavhxq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmlsldavhxq_s32)))
int64_t vrmlsldavhxq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s16)))
int16x8_t vrmulhq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s16)))
int16x8_t vrmulhq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s32)))
int32x4_t vrmulhq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s32)))
int32x4_t vrmulhq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s8)))
int8x16_t vrmulhq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_s8)))
int8x16_t vrmulhq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u16)))
uint16x8_t vrmulhq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u16)))
uint16x8_t vrmulhq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u32)))
uint32x4_t vrmulhq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u32)))
uint32x4_t vrmulhq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u8)))
uint8x16_t vrmulhq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_m_u8)))
uint8x16_t vrmulhq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s16)))
int16x8_t vrmulhq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s16)))
int16x8_t vrmulhq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s32)))
int32x4_t vrmulhq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s32)))
int32x4_t vrmulhq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s8)))
int8x16_t vrmulhq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_s8)))
int8x16_t vrmulhq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u16)))
uint16x8_t vrmulhq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u16)))
uint16x8_t vrmulhq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u32)))
uint32x4_t vrmulhq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u32)))
uint32x4_t vrmulhq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u8)))
uint8x16_t vrmulhq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_u8)))
uint8x16_t vrmulhq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s16)))
int16x8_t vrmulhq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s16)))
int16x8_t vrmulhq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s32)))
int32x4_t vrmulhq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s32)))
int32x4_t vrmulhq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s8)))
int8x16_t vrmulhq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_s8)))
int8x16_t vrmulhq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u16)))
uint16x8_t vrmulhq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u16)))
uint16x8_t vrmulhq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u32)))
uint32x4_t vrmulhq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u32)))
uint32x4_t vrmulhq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u8)))
uint8x16_t vrmulhq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrmulhq_x_u8)))
uint8x16_t vrmulhq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s16)))
int16x8_t vrshlq_m_n_s16(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s16)))
int16x8_t vrshlq_m_n(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s32)))
int32x4_t vrshlq_m_n_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s32)))
int32x4_t vrshlq_m_n(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s8)))
int8x16_t vrshlq_m_n_s8(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_s8)))
int8x16_t vrshlq_m_n(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u16)))
uint16x8_t vrshlq_m_n_u16(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u16)))
uint16x8_t vrshlq_m_n(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u32)))
uint32x4_t vrshlq_m_n_u32(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u32)))
uint32x4_t vrshlq_m_n(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u8)))
uint8x16_t vrshlq_m_n_u8(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_n_u8)))
uint8x16_t vrshlq_m_n(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s16)))
int16x8_t vrshlq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s16)))
int16x8_t vrshlq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s32)))
int32x4_t vrshlq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s32)))
int32x4_t vrshlq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s8)))
int8x16_t vrshlq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_s8)))
int8x16_t vrshlq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u16)))
uint16x8_t vrshlq_m_u16(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u16)))
uint16x8_t vrshlq_m(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u32)))
uint32x4_t vrshlq_m_u32(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u32)))
uint32x4_t vrshlq_m(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u8)))
uint8x16_t vrshlq_m_u8(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_m_u8)))
uint8x16_t vrshlq_m(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s16)))
int16x8_t vrshlq_n_s16(int16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s16)))
int16x8_t vrshlq(int16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s32)))
int32x4_t vrshlq_n_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s32)))
int32x4_t vrshlq(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s8)))
int8x16_t vrshlq_n_s8(int8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_s8)))
int8x16_t vrshlq(int8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u16)))
uint16x8_t vrshlq_n_u16(uint16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u16)))
uint16x8_t vrshlq(uint16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u32)))
uint32x4_t vrshlq_n_u32(uint32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u32)))
uint32x4_t vrshlq(uint32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u8)))
uint8x16_t vrshlq_n_u8(uint8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_n_u8)))
uint8x16_t vrshlq(uint8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s16)))
int16x8_t vrshlq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s16)))
int16x8_t vrshlq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s32)))
int32x4_t vrshlq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s32)))
int32x4_t vrshlq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s8)))
int8x16_t vrshlq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_s8)))
int8x16_t vrshlq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u16)))
uint16x8_t vrshlq_u16(uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u16)))
uint16x8_t vrshlq(uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u32)))
uint32x4_t vrshlq_u32(uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u32)))
uint32x4_t vrshlq(uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u8)))
uint8x16_t vrshlq_u8(uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_u8)))
uint8x16_t vrshlq(uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s16)))
int16x8_t vrshlq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s16)))
int16x8_t vrshlq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s32)))
int32x4_t vrshlq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s32)))
int32x4_t vrshlq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s8)))
int8x16_t vrshlq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_s8)))
int8x16_t vrshlq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u16)))
uint16x8_t vrshlq_x_u16(uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u16)))
uint16x8_t vrshlq_x(uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u32)))
uint32x4_t vrshlq_x_u32(uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u32)))
uint32x4_t vrshlq_x(uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u8)))
uint8x16_t vrshlq_x_u8(uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshlq_x_u8)))
uint8x16_t vrshlq_x(uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_s16)))
int8x16_t vrshrnbq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_s16)))
int8x16_t vrshrnbq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_s32)))
int16x8_t vrshrnbq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_s32)))
int16x8_t vrshrnbq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_u16)))
uint8x16_t vrshrnbq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_u16)))
uint8x16_t vrshrnbq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_u32)))
uint16x8_t vrshrnbq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_m_n_u32)))
uint16x8_t vrshrnbq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_s16)))
int8x16_t vrshrnbq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_s16)))
int8x16_t vrshrnbq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_s32)))
int16x8_t vrshrnbq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_s32)))
int16x8_t vrshrnbq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_u16)))
uint8x16_t vrshrnbq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_u16)))
uint8x16_t vrshrnbq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_u32)))
uint16x8_t vrshrnbq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrnbq_n_u32)))
uint16x8_t vrshrnbq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_s16)))
int8x16_t vrshrntq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_s16)))
int8x16_t vrshrntq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_s32)))
int16x8_t vrshrntq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_s32)))
int16x8_t vrshrntq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_u16)))
uint8x16_t vrshrntq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_u16)))
uint8x16_t vrshrntq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_u32)))
uint16x8_t vrshrntq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_m_n_u32)))
uint16x8_t vrshrntq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_s16)))
int8x16_t vrshrntq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_s16)))
int8x16_t vrshrntq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_s32)))
int16x8_t vrshrntq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_s32)))
int16x8_t vrshrntq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_u16)))
uint8x16_t vrshrntq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_u16)))
uint8x16_t vrshrntq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_u32)))
uint16x8_t vrshrntq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrntq_n_u32)))
uint16x8_t vrshrntq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s16)))
int16x8_t vrshrq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s16)))
int16x8_t vrshrq_m(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s32)))
int32x4_t vrshrq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s32)))
int32x4_t vrshrq_m(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s8)))
int8x16_t vrshrq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_s8)))
int8x16_t vrshrq_m(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u16)))
uint16x8_t vrshrq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u16)))
uint16x8_t vrshrq_m(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u32)))
uint32x4_t vrshrq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u32)))
uint32x4_t vrshrq_m(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u8)))
uint8x16_t vrshrq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_m_n_u8)))
uint8x16_t vrshrq_m(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s16)))
int16x8_t vrshrq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s16)))
int16x8_t vrshrq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s32)))
int32x4_t vrshrq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s32)))
int32x4_t vrshrq(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s8)))
int8x16_t vrshrq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_s8)))
int8x16_t vrshrq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u16)))
uint16x8_t vrshrq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u16)))
uint16x8_t vrshrq(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u32)))
uint32x4_t vrshrq_n_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u32)))
uint32x4_t vrshrq(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u8)))
uint8x16_t vrshrq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_n_u8)))
uint8x16_t vrshrq(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s16)))
int16x8_t vrshrq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s16)))
int16x8_t vrshrq_x(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s32)))
int32x4_t vrshrq_x_n_s32(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s32)))
int32x4_t vrshrq_x(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s8)))
int8x16_t vrshrq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_s8)))
int8x16_t vrshrq_x(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u16)))
uint16x8_t vrshrq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u16)))
uint16x8_t vrshrq_x(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u32)))
uint32x4_t vrshrq_x_n_u32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u32)))
uint32x4_t vrshrq_x(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u8)))
uint8x16_t vrshrq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vrshrq_x_n_u8)))
uint8x16_t vrshrq_x(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s16)))
int16x8_t vsetq_lane_s16(int16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s16)))
int16x8_t vsetq_lane(int16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s32)))
int32x4_t vsetq_lane_s32(int32_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s32)))
int32x4_t vsetq_lane(int32_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s64)))
int64x2_t vsetq_lane_s64(int64_t, int64x2_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s64)))
int64x2_t vsetq_lane(int64_t, int64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s8)))
int8x16_t vsetq_lane_s8(int8_t, int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_s8)))
int8x16_t vsetq_lane(int8_t, int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u16)))
uint16x8_t vsetq_lane_u16(uint16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u16)))
uint16x8_t vsetq_lane(uint16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u32)))
uint32x4_t vsetq_lane_u32(uint32_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u32)))
uint32x4_t vsetq_lane(uint32_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u64)))
uint64x2_t vsetq_lane_u64(uint64_t, uint64x2_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u64)))
uint64x2_t vsetq_lane(uint64_t, uint64x2_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u8)))
uint8x16_t vsetq_lane_u8(uint8_t, uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_u8)))
uint8x16_t vsetq_lane(uint8_t, uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_s16)))
int32x4_t vshllbq_m_n_s16(int32x4_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_s16)))
int32x4_t vshllbq_m(int32x4_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_s8)))
int16x8_t vshllbq_m_n_s8(int16x8_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_s8)))
int16x8_t vshllbq_m(int16x8_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_u16)))
uint32x4_t vshllbq_m_n_u16(uint32x4_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_u16)))
uint32x4_t vshllbq_m(uint32x4_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_u8)))
uint16x8_t vshllbq_m_n_u8(uint16x8_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_m_n_u8)))
uint16x8_t vshllbq_m(uint16x8_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_s16)))
int32x4_t vshllbq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_s16)))
int32x4_t vshllbq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_s8)))
int16x8_t vshllbq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_s8)))
int16x8_t vshllbq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_u16)))
uint32x4_t vshllbq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_u16)))
uint32x4_t vshllbq(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_u8)))
uint16x8_t vshllbq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_n_u8)))
uint16x8_t vshllbq(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_s16)))
int32x4_t vshllbq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_s16)))
int32x4_t vshllbq_x(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_s8)))
int16x8_t vshllbq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_s8)))
int16x8_t vshllbq_x(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_u16)))
uint32x4_t vshllbq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_u16)))
uint32x4_t vshllbq_x(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_u8)))
uint16x8_t vshllbq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshllbq_x_n_u8)))
uint16x8_t vshllbq_x(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_s16)))
int32x4_t vshlltq_m_n_s16(int32x4_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_s16)))
int32x4_t vshlltq_m(int32x4_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_s8)))
int16x8_t vshlltq_m_n_s8(int16x8_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_s8)))
int16x8_t vshlltq_m(int16x8_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_u16)))
uint32x4_t vshlltq_m_n_u16(uint32x4_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_u16)))
uint32x4_t vshlltq_m(uint32x4_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_u8)))
uint16x8_t vshlltq_m_n_u8(uint16x8_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_m_n_u8)))
uint16x8_t vshlltq_m(uint16x8_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_s16)))
int32x4_t vshlltq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_s16)))
int32x4_t vshlltq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_s8)))
int16x8_t vshlltq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_s8)))
int16x8_t vshlltq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_u16)))
uint32x4_t vshlltq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_u16)))
uint32x4_t vshlltq(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_u8)))
uint16x8_t vshlltq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_n_u8)))
uint16x8_t vshlltq(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_s16)))
int32x4_t vshlltq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_s16)))
int32x4_t vshlltq_x(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_s8)))
int16x8_t vshlltq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_s8)))
int16x8_t vshlltq_x(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_u16)))
uint32x4_t vshlltq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_u16)))
uint32x4_t vshlltq_x(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_u8)))
uint16x8_t vshlltq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlltq_x_n_u8)))
uint16x8_t vshlltq_x(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s16)))
int16x8_t vshlq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s16)))
int16x8_t vshlq_m_n(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s32)))
int32x4_t vshlq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s32)))
int32x4_t vshlq_m_n(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s8)))
int8x16_t vshlq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_s8)))
int8x16_t vshlq_m_n(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u16)))
uint16x8_t vshlq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u16)))
uint16x8_t vshlq_m_n(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u32)))
uint32x4_t vshlq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u32)))
uint32x4_t vshlq_m_n(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u8)))
uint8x16_t vshlq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_n_u8)))
uint8x16_t vshlq_m_n(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s16)))
int16x8_t vshlq_m_r_s16(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s16)))
int16x8_t vshlq_m_r(int16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s32)))
int32x4_t vshlq_m_r_s32(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s32)))
int32x4_t vshlq_m_r(int32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s8)))
int8x16_t vshlq_m_r_s8(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_s8)))
int8x16_t vshlq_m_r(int8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u16)))
uint16x8_t vshlq_m_r_u16(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u16)))
uint16x8_t vshlq_m_r(uint16x8_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u32)))
uint32x4_t vshlq_m_r_u32(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u32)))
uint32x4_t vshlq_m_r(uint32x4_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u8)))
uint8x16_t vshlq_m_r_u8(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_r_u8)))
uint8x16_t vshlq_m_r(uint8x16_t, int32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s16)))
int16x8_t vshlq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s16)))
int16x8_t vshlq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s32)))
int32x4_t vshlq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s32)))
int32x4_t vshlq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s8)))
int8x16_t vshlq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_s8)))
int8x16_t vshlq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u16)))
uint16x8_t vshlq_m_u16(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u16)))
uint16x8_t vshlq_m(uint16x8_t, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u32)))
uint32x4_t vshlq_m_u32(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u32)))
uint32x4_t vshlq_m(uint32x4_t, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u8)))
uint8x16_t vshlq_m_u8(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_m_u8)))
uint8x16_t vshlq_m(uint8x16_t, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s16)))
int16x8_t vshlq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s16)))
int16x8_t vshlq_n(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s32)))
int32x4_t vshlq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s32)))
int32x4_t vshlq_n(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s8)))
int8x16_t vshlq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_s8)))
int8x16_t vshlq_n(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u16)))
uint16x8_t vshlq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u16)))
uint16x8_t vshlq_n(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u32)))
uint32x4_t vshlq_n_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u32)))
uint32x4_t vshlq_n(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u8)))
uint8x16_t vshlq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_n_u8)))
uint8x16_t vshlq_n(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s16)))
int16x8_t vshlq_r_s16(int16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s16)))
int16x8_t vshlq_r(int16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s32)))
int32x4_t vshlq_r_s32(int32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s32)))
int32x4_t vshlq_r(int32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s8)))
int8x16_t vshlq_r_s8(int8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_s8)))
int8x16_t vshlq_r(int8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u16)))
uint16x8_t vshlq_r_u16(uint16x8_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u16)))
uint16x8_t vshlq_r(uint16x8_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u32)))
uint32x4_t vshlq_r_u32(uint32x4_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u32)))
uint32x4_t vshlq_r(uint32x4_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u8)))
uint8x16_t vshlq_r_u8(uint8x16_t, int32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_r_u8)))
uint8x16_t vshlq_r(uint8x16_t, int32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_s16)))
int16x8_t vshlq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_s16)))
int16x8_t vshlq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_s32)))
int32x4_t vshlq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_s32)))
int32x4_t vshlq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_s8)))
int8x16_t vshlq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_s8)))
int8x16_t vshlq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_u16)))
uint16x8_t vshlq_u16(uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_u16)))
uint16x8_t vshlq(uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_u32)))
uint32x4_t vshlq_u32(uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_u32)))
uint32x4_t vshlq(uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_u8)))
uint8x16_t vshlq_u8(uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_u8)))
uint8x16_t vshlq(uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s16)))
int16x8_t vshlq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s16)))
int16x8_t vshlq_x_n(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s32)))
int32x4_t vshlq_x_n_s32(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s32)))
int32x4_t vshlq_x_n(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s8)))
int8x16_t vshlq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_s8)))
int8x16_t vshlq_x_n(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u16)))
uint16x8_t vshlq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u16)))
uint16x8_t vshlq_x_n(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u32)))
uint32x4_t vshlq_x_n_u32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u32)))
uint32x4_t vshlq_x_n(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u8)))
uint8x16_t vshlq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_n_u8)))
uint8x16_t vshlq_x_n(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s16)))
int16x8_t vshlq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s16)))
int16x8_t vshlq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s32)))
int32x4_t vshlq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s32)))
int32x4_t vshlq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s8)))
int8x16_t vshlq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_s8)))
int8x16_t vshlq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u16)))
uint16x8_t vshlq_x_u16(uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u16)))
uint16x8_t vshlq_x(uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u32)))
uint32x4_t vshlq_x_u32(uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u32)))
uint32x4_t vshlq_x(uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u8)))
uint8x16_t vshlq_x_u8(uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshlq_x_u8)))
uint8x16_t vshlq_x(uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_s16)))
int8x16_t vshrnbq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_s16)))
int8x16_t vshrnbq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_s32)))
int16x8_t vshrnbq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_s32)))
int16x8_t vshrnbq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_u16)))
uint8x16_t vshrnbq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_u16)))
uint8x16_t vshrnbq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_u32)))
uint16x8_t vshrnbq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_m_n_u32)))
uint16x8_t vshrnbq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_s16)))
int8x16_t vshrnbq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_s16)))
int8x16_t vshrnbq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_s32)))
int16x8_t vshrnbq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_s32)))
int16x8_t vshrnbq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_u16)))
uint8x16_t vshrnbq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_u16)))
uint8x16_t vshrnbq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_u32)))
uint16x8_t vshrnbq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrnbq_n_u32)))
uint16x8_t vshrnbq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_s16)))
int8x16_t vshrntq_m_n_s16(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_s16)))
int8x16_t vshrntq_m(int8x16_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_s32)))
int16x8_t vshrntq_m_n_s32(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_s32)))
int16x8_t vshrntq_m(int16x8_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_u16)))
uint8x16_t vshrntq_m_n_u16(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_u16)))
uint8x16_t vshrntq_m(uint8x16_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_u32)))
uint16x8_t vshrntq_m_n_u32(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_m_n_u32)))
uint16x8_t vshrntq_m(uint16x8_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_s16)))
int8x16_t vshrntq_n_s16(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_s16)))
int8x16_t vshrntq(int8x16_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_s32)))
int16x8_t vshrntq_n_s32(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_s32)))
int16x8_t vshrntq(int16x8_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_u16)))
uint8x16_t vshrntq_n_u16(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_u16)))
uint8x16_t vshrntq(uint8x16_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_u32)))
uint16x8_t vshrntq_n_u32(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrntq_n_u32)))
uint16x8_t vshrntq(uint16x8_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s16)))
int16x8_t vshrq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s16)))
int16x8_t vshrq_m(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s32)))
int32x4_t vshrq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s32)))
int32x4_t vshrq_m(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s8)))
int8x16_t vshrq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_s8)))
int8x16_t vshrq_m(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u16)))
uint16x8_t vshrq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u16)))
uint16x8_t vshrq_m(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u32)))
uint32x4_t vshrq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u32)))
uint32x4_t vshrq_m(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u8)))
uint8x16_t vshrq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_m_n_u8)))
uint8x16_t vshrq_m(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s16)))
int16x8_t vshrq_n_s16(int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s16)))
int16x8_t vshrq(int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s32)))
int32x4_t vshrq_n_s32(int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s32)))
int32x4_t vshrq(int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s8)))
int8x16_t vshrq_n_s8(int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_s8)))
int8x16_t vshrq(int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u16)))
uint16x8_t vshrq_n_u16(uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u16)))
uint16x8_t vshrq(uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u32)))
uint32x4_t vshrq_n_u32(uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u32)))
uint32x4_t vshrq(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u8)))
uint8x16_t vshrq_n_u8(uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_n_u8)))
uint8x16_t vshrq(uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s16)))
int16x8_t vshrq_x_n_s16(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s16)))
int16x8_t vshrq_x(int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s32)))
int32x4_t vshrq_x_n_s32(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s32)))
int32x4_t vshrq_x(int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s8)))
int8x16_t vshrq_x_n_s8(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_s8)))
int8x16_t vshrq_x(int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u16)))
uint16x8_t vshrq_x_n_u16(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u16)))
uint16x8_t vshrq_x(uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u32)))
uint32x4_t vshrq_x_n_u32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u32)))
uint32x4_t vshrq_x(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u8)))
uint8x16_t vshrq_x_n_u8(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vshrq_x_n_u8)))
uint8x16_t vshrq_x(uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s16)))
int16x8_t vsliq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s16)))
int16x8_t vsliq_m(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s32)))
int32x4_t vsliq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s32)))
int32x4_t vsliq_m(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s8)))
int8x16_t vsliq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_s8)))
int8x16_t vsliq_m(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u16)))
uint16x8_t vsliq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u16)))
uint16x8_t vsliq_m(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u32)))
uint32x4_t vsliq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u32)))
uint32x4_t vsliq_m(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u8)))
uint8x16_t vsliq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_m_n_u8)))
uint8x16_t vsliq_m(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s16)))
int16x8_t vsliq_n_s16(int16x8_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s16)))
int16x8_t vsliq(int16x8_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s32)))
int32x4_t vsliq_n_s32(int32x4_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s32)))
int32x4_t vsliq(int32x4_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s8)))
int8x16_t vsliq_n_s8(int8x16_t, int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_s8)))
int8x16_t vsliq(int8x16_t, int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u16)))
uint16x8_t vsliq_n_u16(uint16x8_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u16)))
uint16x8_t vsliq(uint16x8_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u32)))
uint32x4_t vsliq_n_u32(uint32x4_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u32)))
uint32x4_t vsliq(uint32x4_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u8)))
uint8x16_t vsliq_n_u8(uint8x16_t, uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsliq_n_u8)))
uint8x16_t vsliq(uint8x16_t, uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s16)))
int16x8_t vsriq_m_n_s16(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s16)))
int16x8_t vsriq_m(int16x8_t, int16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s32)))
int32x4_t vsriq_m_n_s32(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s32)))
int32x4_t vsriq_m(int32x4_t, int32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s8)))
int8x16_t vsriq_m_n_s8(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_s8)))
int8x16_t vsriq_m(int8x16_t, int8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u16)))
uint16x8_t vsriq_m_n_u16(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u16)))
uint16x8_t vsriq_m(uint16x8_t, uint16x8_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u32)))
uint32x4_t vsriq_m_n_u32(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u32)))
uint32x4_t vsriq_m(uint32x4_t, uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u8)))
uint8x16_t vsriq_m_n_u8(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_m_n_u8)))
uint8x16_t vsriq_m(uint8x16_t, uint8x16_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s16)))
int16x8_t vsriq_n_s16(int16x8_t, int16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s16)))
int16x8_t vsriq(int16x8_t, int16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s32)))
int32x4_t vsriq_n_s32(int32x4_t, int32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s32)))
int32x4_t vsriq(int32x4_t, int32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s8)))
int8x16_t vsriq_n_s8(int8x16_t, int8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_s8)))
int8x16_t vsriq(int8x16_t, int8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u16)))
uint16x8_t vsriq_n_u16(uint16x8_t, uint16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u16)))
uint16x8_t vsriq(uint16x8_t, uint16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u32)))
uint32x4_t vsriq_n_u32(uint32x4_t, uint32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u32)))
uint32x4_t vsriq(uint32x4_t, uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u8)))
uint8x16_t vsriq_n_u8(uint8x16_t, uint8x16_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsriq_n_u8)))
uint8x16_t vsriq(uint8x16_t, uint8x16_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s16)))
void vst1q_p_s16(int16_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s16)))
void vst1q_p(int16_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s32)))
void vst1q_p_s32(int32_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s32)))
void vst1q_p(int32_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s8)))
void vst1q_p_s8(int8_t *, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_s8)))
void vst1q_p(int8_t *, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u16)))
void vst1q_p_u16(uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u16)))
void vst1q_p(uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u32)))
void vst1q_p_u32(uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u32)))
void vst1q_p(uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u8)))
void vst1q_p_u8(uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_u8)))
void vst1q_p(uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_s16)))
void vst1q_s16(int16_t *, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_s16)))
void vst1q(int16_t *, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_s32)))
void vst1q_s32(int32_t *, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_s32)))
void vst1q(int32_t *, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_s8)))
void vst1q_s8(int8_t *, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_s8)))
void vst1q(int8_t *, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_u16)))
void vst1q_u16(uint16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_u16)))
void vst1q(uint16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_u32)))
void vst1q_u32(uint32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_u32)))
void vst1q(uint32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_u8)))
void vst1q_u8(uint8_t *, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_u8)))
void vst1q(uint8_t *, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_s16)))
void vst2q_s16(int16_t *, int16x8x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_s16)))
void vst2q(int16_t *, int16x8x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_s32)))
void vst2q_s32(int32_t *, int32x4x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_s32)))
void vst2q(int32_t *, int32x4x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_s8)))
void vst2q_s8(int8_t *, int8x16x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_s8)))
void vst2q(int8_t *, int8x16x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_u16)))
void vst2q_u16(uint16_t *, uint16x8x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_u16)))
void vst2q(uint16_t *, uint16x8x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_u32)))
void vst2q_u32(uint32_t *, uint32x4x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_u32)))
void vst2q(uint32_t *, uint32x4x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_u8)))
void vst2q_u8(uint8_t *, uint8x16x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_u8)))
void vst2q(uint8_t *, uint8x16x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_s16)))
void vst4q_s16(int16_t *, int16x8x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_s16)))
void vst4q(int16_t *, int16x8x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_s32)))
void vst4q_s32(int32_t *, int32x4x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_s32)))
void vst4q(int32_t *, int32x4x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_s8)))
void vst4q_s8(int8_t *, int8x16x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_s8)))
void vst4q(int8_t *, int8x16x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_u16)))
void vst4q_u16(uint16_t *, uint16x8x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_u16)))
void vst4q(uint16_t *, uint16x8x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_u32)))
void vst4q_u32(uint32_t *, uint32x4x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_u32)))
void vst4q(uint32_t *, uint32x4x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_u8)))
void vst4q_u8(uint8_t *, uint8x16x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_u8)))
void vst4q(uint8_t *, uint8x16x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s16)))
void vstrbq_p_s16(int8_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s16)))
void vstrbq_p(int8_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s32)))
void vstrbq_p_s32(int8_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s32)))
void vstrbq_p(int8_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s8)))
void vstrbq_p_s8(int8_t *, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_s8)))
void vstrbq_p(int8_t *, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u16)))
void vstrbq_p_u16(uint8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u16)))
void vstrbq_p(uint8_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u32)))
void vstrbq_p_u32(uint8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u32)))
void vstrbq_p(uint8_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u8)))
void vstrbq_p_u8(uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_p_u8)))
void vstrbq_p(uint8_t *, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s16)))
void vstrbq_s16(int8_t *, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s16)))
void vstrbq(int8_t *, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s32)))
void vstrbq_s32(int8_t *, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s32)))
void vstrbq(int8_t *, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s8)))
void vstrbq_s8(int8_t *, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_s8)))
void vstrbq(int8_t *, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s16)))
void vstrbq_scatter_offset_p_s16(int8_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s16)))
void vstrbq_scatter_offset_p(int8_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s32)))
void vstrbq_scatter_offset_p_s32(int8_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s32)))
void vstrbq_scatter_offset_p(int8_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s8)))
void vstrbq_scatter_offset_p_s8(int8_t *, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_s8)))
void vstrbq_scatter_offset_p(int8_t *, uint8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u16)))
void vstrbq_scatter_offset_p_u16(uint8_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u16)))
void vstrbq_scatter_offset_p(uint8_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u32)))
void vstrbq_scatter_offset_p_u32(uint8_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u32)))
void vstrbq_scatter_offset_p(uint8_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u8)))
void vstrbq_scatter_offset_p_u8(uint8_t *, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_p_u8)))
void vstrbq_scatter_offset_p(uint8_t *, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s16)))
void vstrbq_scatter_offset_s16(int8_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s16)))
void vstrbq_scatter_offset(int8_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s32)))
void vstrbq_scatter_offset_s32(int8_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s32)))
void vstrbq_scatter_offset(int8_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s8)))
void vstrbq_scatter_offset_s8(int8_t *, uint8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_s8)))
void vstrbq_scatter_offset(int8_t *, uint8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u16)))
void vstrbq_scatter_offset_u16(uint8_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u16)))
void vstrbq_scatter_offset(uint8_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u32)))
void vstrbq_scatter_offset_u32(uint8_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u32)))
void vstrbq_scatter_offset(uint8_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u8)))
void vstrbq_scatter_offset_u8(uint8_t *, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_scatter_offset_u8)))
void vstrbq_scatter_offset(uint8_t *, uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u16)))
void vstrbq_u16(uint8_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u16)))
void vstrbq(uint8_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u32)))
void vstrbq_u32(uint8_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u32)))
void vstrbq(uint8_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u8)))
void vstrbq_u8(uint8_t *, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrbq_u8)))
void vstrbq(uint8_t *, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_p_s64)))
void vstrdq_scatter_base_p_s64(uint64x2_t, int, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_p_s64)))
void vstrdq_scatter_base_p(uint64x2_t, int, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_p_u64)))
void vstrdq_scatter_base_p_u64(uint64x2_t, int, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_p_u64)))
void vstrdq_scatter_base_p(uint64x2_t, int, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_s64)))
void vstrdq_scatter_base_s64(uint64x2_t, int, int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_s64)))
void vstrdq_scatter_base(uint64x2_t, int, int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_u64)))
void vstrdq_scatter_base_u64(uint64x2_t, int, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_u64)))
void vstrdq_scatter_base(uint64x2_t, int, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_p_s64)))
void vstrdq_scatter_base_wb_p_s64(uint64x2_t *, int, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_p_s64)))
void vstrdq_scatter_base_wb_p(uint64x2_t *, int, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_p_u64)))
void vstrdq_scatter_base_wb_p_u64(uint64x2_t *, int, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_p_u64)))
void vstrdq_scatter_base_wb_p(uint64x2_t *, int, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_s64)))
void vstrdq_scatter_base_wb_s64(uint64x2_t *, int, int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_s64)))
void vstrdq_scatter_base_wb(uint64x2_t *, int, int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_u64)))
void vstrdq_scatter_base_wb_u64(uint64x2_t *, int, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_base_wb_u64)))
void vstrdq_scatter_base_wb(uint64x2_t *, int, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_p_s64)))
void vstrdq_scatter_offset_p_s64(int64_t *, uint64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_p_s64)))
void vstrdq_scatter_offset_p(int64_t *, uint64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_p_u64)))
void vstrdq_scatter_offset_p_u64(uint64_t *, uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_p_u64)))
void vstrdq_scatter_offset_p(uint64_t *, uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_s64)))
void vstrdq_scatter_offset_s64(int64_t *, uint64x2_t, int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_s64)))
void vstrdq_scatter_offset(int64_t *, uint64x2_t, int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_u64)))
void vstrdq_scatter_offset_u64(uint64_t *, uint64x2_t, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_offset_u64)))
void vstrdq_scatter_offset(uint64_t *, uint64x2_t, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_p_s64)))
void vstrdq_scatter_shifted_offset_p_s64(int64_t *, uint64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_p_s64)))
void vstrdq_scatter_shifted_offset_p(int64_t *, uint64x2_t, int64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_p_u64)))
void vstrdq_scatter_shifted_offset_p_u64(uint64_t *, uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_p_u64)))
void vstrdq_scatter_shifted_offset_p(uint64_t *, uint64x2_t, uint64x2_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_s64)))
void vstrdq_scatter_shifted_offset_s64(int64_t *, uint64x2_t, int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_s64)))
void vstrdq_scatter_shifted_offset(int64_t *, uint64x2_t, int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_u64)))
void vstrdq_scatter_shifted_offset_u64(uint64_t *, uint64x2_t, uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrdq_scatter_shifted_offset_u64)))
void vstrdq_scatter_shifted_offset(uint64_t *, uint64x2_t, uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_s16)))
void vstrhq_p_s16(int16_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_s16)))
void vstrhq_p(int16_t *, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_s32)))
void vstrhq_p_s32(int16_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_s32)))
void vstrhq_p(int16_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_u16)))
void vstrhq_p_u16(uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_u16)))
void vstrhq_p(uint16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_u32)))
void vstrhq_p_u32(uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_u32)))
void vstrhq_p(uint16_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_s16)))
void vstrhq_s16(int16_t *, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_s16)))
void vstrhq(int16_t *, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_s32)))
void vstrhq_s32(int16_t *, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_s32)))
void vstrhq(int16_t *, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_s16)))
void vstrhq_scatter_offset_p_s16(int16_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_s16)))
void vstrhq_scatter_offset_p(int16_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_s32)))
void vstrhq_scatter_offset_p_s32(int16_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_s32)))
void vstrhq_scatter_offset_p(int16_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_u16)))
void vstrhq_scatter_offset_p_u16(uint16_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_u16)))
void vstrhq_scatter_offset_p(uint16_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_u32)))
void vstrhq_scatter_offset_p_u32(uint16_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_u32)))
void vstrhq_scatter_offset_p(uint16_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_s16)))
void vstrhq_scatter_offset_s16(int16_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_s16)))
void vstrhq_scatter_offset(int16_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_s32)))
void vstrhq_scatter_offset_s32(int16_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_s32)))
void vstrhq_scatter_offset(int16_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_u16)))
void vstrhq_scatter_offset_u16(uint16_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_u16)))
void vstrhq_scatter_offset(uint16_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_u32)))
void vstrhq_scatter_offset_u32(uint16_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_u32)))
void vstrhq_scatter_offset(uint16_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_s16)))
void vstrhq_scatter_shifted_offset_p_s16(int16_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_s16)))
void vstrhq_scatter_shifted_offset_p(int16_t *, uint16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_s32)))
void vstrhq_scatter_shifted_offset_p_s32(int16_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_s32)))
void vstrhq_scatter_shifted_offset_p(int16_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_u16)))
void vstrhq_scatter_shifted_offset_p_u16(uint16_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_u16)))
void vstrhq_scatter_shifted_offset_p(uint16_t *, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_u32)))
void vstrhq_scatter_shifted_offset_p_u32(uint16_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_u32)))
void vstrhq_scatter_shifted_offset_p(uint16_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_s16)))
void vstrhq_scatter_shifted_offset_s16(int16_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_s16)))
void vstrhq_scatter_shifted_offset(int16_t *, uint16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_s32)))
void vstrhq_scatter_shifted_offset_s32(int16_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_s32)))
void vstrhq_scatter_shifted_offset(int16_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_u16)))
void vstrhq_scatter_shifted_offset_u16(uint16_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_u16)))
void vstrhq_scatter_shifted_offset(uint16_t *, uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_u32)))
void vstrhq_scatter_shifted_offset_u32(uint16_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_u32)))
void vstrhq_scatter_shifted_offset(uint16_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_u16)))
void vstrhq_u16(uint16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_u16)))
void vstrhq(uint16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_u32)))
void vstrhq_u32(uint16_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_u32)))
void vstrhq(uint16_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_s32)))
void vstrwq_p_s32(int32_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_s32)))
void vstrwq_p(int32_t *, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_u32)))
void vstrwq_p_u32(uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_u32)))
void vstrwq_p(uint32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_s32)))
void vstrwq_s32(int32_t *, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_s32)))
void vstrwq(int32_t *, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_s32)))
void vstrwq_scatter_base_p_s32(uint32x4_t, int, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_s32)))
void vstrwq_scatter_base_p(uint32x4_t, int, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_u32)))
void vstrwq_scatter_base_p_u32(uint32x4_t, int, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_u32)))
void vstrwq_scatter_base_p(uint32x4_t, int, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_s32)))
void vstrwq_scatter_base_s32(uint32x4_t, int, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_s32)))
void vstrwq_scatter_base(uint32x4_t, int, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_u32)))
void vstrwq_scatter_base_u32(uint32x4_t, int, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_u32)))
void vstrwq_scatter_base(uint32x4_t, int, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_s32)))
void vstrwq_scatter_base_wb_p_s32(uint32x4_t *, int, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_s32)))
void vstrwq_scatter_base_wb_p(uint32x4_t *, int, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_u32)))
void vstrwq_scatter_base_wb_p_u32(uint32x4_t *, int, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_u32)))
void vstrwq_scatter_base_wb_p(uint32x4_t *, int, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_s32)))
void vstrwq_scatter_base_wb_s32(uint32x4_t *, int, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_s32)))
void vstrwq_scatter_base_wb(uint32x4_t *, int, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_u32)))
void vstrwq_scatter_base_wb_u32(uint32x4_t *, int, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_u32)))
void vstrwq_scatter_base_wb(uint32x4_t *, int, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_s32)))
void vstrwq_scatter_offset_p_s32(int32_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_s32)))
void vstrwq_scatter_offset_p(int32_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_u32)))
void vstrwq_scatter_offset_p_u32(uint32_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_u32)))
void vstrwq_scatter_offset_p(uint32_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_s32)))
void vstrwq_scatter_offset_s32(int32_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_s32)))
void vstrwq_scatter_offset(int32_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_u32)))
void vstrwq_scatter_offset_u32(uint32_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_u32)))
void vstrwq_scatter_offset(uint32_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_s32)))
void vstrwq_scatter_shifted_offset_p_s32(int32_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_s32)))
void vstrwq_scatter_shifted_offset_p(int32_t *, uint32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_u32)))
void vstrwq_scatter_shifted_offset_p_u32(uint32_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_u32)))
void vstrwq_scatter_shifted_offset_p(uint32_t *, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_s32)))
void vstrwq_scatter_shifted_offset_s32(int32_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_s32)))
void vstrwq_scatter_shifted_offset(int32_t *, uint32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_u32)))
void vstrwq_scatter_shifted_offset_u32(uint32_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_u32)))
void vstrwq_scatter_shifted_offset(uint32_t *, uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_u32)))
void vstrwq_u32(uint32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_u32)))
void vstrwq(uint32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s16)))
int16x8_t vsubq_m_s16(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s16)))
int16x8_t vsubq_m(int16x8_t, int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s32)))
int32x4_t vsubq_m_s32(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s32)))
int32x4_t vsubq_m(int32x4_t, int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s8)))
int8x16_t vsubq_m_s8(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_s8)))
int8x16_t vsubq_m(int8x16_t, int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u16)))
uint16x8_t vsubq_m_u16(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u16)))
uint16x8_t vsubq_m(uint16x8_t, uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u32)))
uint32x4_t vsubq_m_u32(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u32)))
uint32x4_t vsubq_m(uint32x4_t, uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u8)))
uint8x16_t vsubq_m_u8(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_u8)))
uint8x16_t vsubq_m(uint8x16_t, uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_s16)))
int16x8_t vsubq_s16(int16x8_t, int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_s16)))
int16x8_t vsubq(int16x8_t, int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_s32)))
int32x4_t vsubq_s32(int32x4_t, int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_s32)))
int32x4_t vsubq(int32x4_t, int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_s8)))
int8x16_t vsubq_s8(int8x16_t, int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_s8)))
int8x16_t vsubq(int8x16_t, int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_u16)))
uint16x8_t vsubq_u16(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_u16)))
uint16x8_t vsubq(uint16x8_t, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_u32)))
uint32x4_t vsubq_u32(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_u32)))
uint32x4_t vsubq(uint32x4_t, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_u8)))
uint8x16_t vsubq_u8(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_u8)))
uint8x16_t vsubq(uint8x16_t, uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s16)))
int16x8_t vsubq_x_s16(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s16)))
int16x8_t vsubq_x(int16x8_t, int16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s32)))
int32x4_t vsubq_x_s32(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s32)))
int32x4_t vsubq_x(int32x4_t, int32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s8)))
int8x16_t vsubq_x_s8(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_s8)))
int8x16_t vsubq_x(int8x16_t, int8x16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u16)))
uint16x8_t vsubq_x_u16(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u16)))
uint16x8_t vsubq_x(uint16x8_t, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u32)))
uint32x4_t vsubq_x_u32(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u32)))
uint32x4_t vsubq_x(uint32x4_t, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u8)))
uint8x16_t vsubq_x_u8(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_u8)))
uint8x16_t vsubq_x(uint8x16_t, uint8x16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_s16)))
int16x8_t vuninitializedq(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_s32)))
int32x4_t vuninitializedq(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_s64)))
int64x2_t vuninitializedq(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_s8)))
int8x16_t vuninitializedq(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_u16)))
uint16x8_t vuninitializedq(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_u32)))
uint32x4_t vuninitializedq(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_u64)))
uint64x2_t vuninitializedq(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_u8)))
uint8x16_t vuninitializedq(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_s16)))
int16x8_t vuninitializedq_s16();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_s32)))
int32x4_t vuninitializedq_s32();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_s64)))
int64x2_t vuninitializedq_s64();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_s8)))
int8x16_t vuninitializedq_s8();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_u16)))
uint16x8_t vuninitializedq_u16();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_u32)))
uint32x4_t vuninitializedq_u32();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_u64)))
uint64x2_t vuninitializedq_u64();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_u8)))
uint8x16_t vuninitializedq_u8();

#endif /* (!defined __ARM_MVE_PRESERVE_USER_NAMESPACE) */

#if (__ARM_FEATURE_MVE & 2) && (!defined __ARM_MVE_PRESERVE_USER_NAMESPACE)

static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_f16)))
float16x8_t vabdq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_f16)))
float16x8_t vabdq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_f32)))
float32x4_t vabdq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_f32)))
float32x4_t vabdq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_f16)))
float16x8_t vabdq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_f16)))
float16x8_t vabdq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_f32)))
float32x4_t vabdq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_m_f32)))
float32x4_t vabdq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_f16)))
float16x8_t vabdq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_f16)))
float16x8_t vabdq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_f32)))
float32x4_t vabdq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vabdq_x_f32)))
float32x4_t vabdq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_f16)))
float16x8_t vaddq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_f16)))
float16x8_t vaddq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_f32)))
float32x4_t vaddq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_f32)))
float32x4_t vaddq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_f16)))
float16x8_t vaddq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_f16)))
float16x8_t vaddq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_f32)))
float32x4_t vaddq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_m_f32)))
float32x4_t vaddq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_f16)))
float16x8_t vaddq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_f16)))
float16x8_t vaddq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_f32)))
float32x4_t vaddq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vaddq_x_f32)))
float32x4_t vaddq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_f16)))
float16x8_t vandq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_f16)))
float16x8_t vandq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_f32)))
float32x4_t vandq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_f32)))
float32x4_t vandq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_f16)))
float16x8_t vandq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_f16)))
float16x8_t vandq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_m_f32)))
float32x4_t vandq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_m_f32)))
float32x4_t vandq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_f16)))
float16x8_t vandq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_f16)))
float16x8_t vandq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vandq_x_f32)))
float32x4_t vandq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vandq_x_f32)))
float32x4_t vandq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_f16)))
float16x8_t vbicq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_f16)))
float16x8_t vbicq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_f32)))
float32x4_t vbicq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_f32)))
float32x4_t vbicq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_f16)))
float16x8_t vbicq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_f16)))
float16x8_t vbicq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_f32)))
float32x4_t vbicq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_m_f32)))
float32x4_t vbicq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_f16)))
float16x8_t vbicq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_f16)))
float16x8_t vbicq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_f32)))
float32x4_t vbicq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vbicq_x_f32)))
float32x4_t vbicq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_f16)))
float16x8_t vcaddq_rot270_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_f16)))
float16x8_t vcaddq_rot270(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_f32)))
float32x4_t vcaddq_rot270_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_f32)))
float32x4_t vcaddq_rot270(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_f16)))
float16x8_t vcaddq_rot270_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_f16)))
float16x8_t vcaddq_rot270_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_f32)))
float32x4_t vcaddq_rot270_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_m_f32)))
float32x4_t vcaddq_rot270_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_f16)))
float16x8_t vcaddq_rot270_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_f16)))
float16x8_t vcaddq_rot270_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_f32)))
float32x4_t vcaddq_rot270_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot270_x_f32)))
float32x4_t vcaddq_rot270_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_f16)))
float16x8_t vcaddq_rot90_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_f16)))
float16x8_t vcaddq_rot90(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_f32)))
float32x4_t vcaddq_rot90_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_f32)))
float32x4_t vcaddq_rot90(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_f16)))
float16x8_t vcaddq_rot90_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_f16)))
float16x8_t vcaddq_rot90_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_f32)))
float32x4_t vcaddq_rot90_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_m_f32)))
float32x4_t vcaddq_rot90_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_f16)))
float16x8_t vcaddq_rot90_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_f16)))
float16x8_t vcaddq_rot90_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_f32)))
float32x4_t vcaddq_rot90_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcaddq_rot90_x_f32)))
float32x4_t vcaddq_rot90_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_f16)))
float16x8_t vcmlaq_f16(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_f16)))
float16x8_t vcmlaq(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_f32)))
float32x4_t vcmlaq_f32(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_f32)))
float32x4_t vcmlaq(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_m_f16)))
float16x8_t vcmlaq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_m_f16)))
float16x8_t vcmlaq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_m_f32)))
float32x4_t vcmlaq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_m_f32)))
float32x4_t vcmlaq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_f16)))
float16x8_t vcmlaq_rot180_f16(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_f16)))
float16x8_t vcmlaq_rot180(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_f32)))
float32x4_t vcmlaq_rot180_f32(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_f32)))
float32x4_t vcmlaq_rot180(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_m_f16)))
float16x8_t vcmlaq_rot180_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_m_f16)))
float16x8_t vcmlaq_rot180_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_m_f32)))
float32x4_t vcmlaq_rot180_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot180_m_f32)))
float32x4_t vcmlaq_rot180_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_f16)))
float16x8_t vcmlaq_rot270_f16(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_f16)))
float16x8_t vcmlaq_rot270(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_f32)))
float32x4_t vcmlaq_rot270_f32(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_f32)))
float32x4_t vcmlaq_rot270(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_m_f16)))
float16x8_t vcmlaq_rot270_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_m_f16)))
float16x8_t vcmlaq_rot270_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_m_f32)))
float32x4_t vcmlaq_rot270_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot270_m_f32)))
float32x4_t vcmlaq_rot270_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_f16)))
float16x8_t vcmlaq_rot90_f16(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_f16)))
float16x8_t vcmlaq_rot90(float16x8_t, float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_f32)))
float32x4_t vcmlaq_rot90_f32(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_f32)))
float32x4_t vcmlaq_rot90(float32x4_t, float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_m_f16)))
float16x8_t vcmlaq_rot90_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_m_f16)))
float16x8_t vcmlaq_rot90_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_m_f32)))
float32x4_t vcmlaq_rot90_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmlaq_rot90_m_f32)))
float32x4_t vcmlaq_rot90_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_f16)))
mve_pred16_t vcmpeqq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_f16)))
mve_pred16_t vcmpeqq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_f32)))
mve_pred16_t vcmpeqq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_f32)))
mve_pred16_t vcmpeqq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_f16)))
mve_pred16_t vcmpeqq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_f16)))
mve_pred16_t vcmpeqq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_f32)))
mve_pred16_t vcmpeqq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_f32)))
mve_pred16_t vcmpeqq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_f16)))
mve_pred16_t vcmpeqq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_f16)))
mve_pred16_t vcmpeqq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_f32)))
mve_pred16_t vcmpeqq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_m_n_f32)))
mve_pred16_t vcmpeqq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_f16)))
mve_pred16_t vcmpeqq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_f16)))
mve_pred16_t vcmpeqq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_f32)))
mve_pred16_t vcmpeqq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpeqq_n_f32)))
mve_pred16_t vcmpeqq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_f16)))
mve_pred16_t vcmpgeq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_f16)))
mve_pred16_t vcmpgeq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_f32)))
mve_pred16_t vcmpgeq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_f32)))
mve_pred16_t vcmpgeq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_f16)))
mve_pred16_t vcmpgeq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_f16)))
mve_pred16_t vcmpgeq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_f32)))
mve_pred16_t vcmpgeq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_f32)))
mve_pred16_t vcmpgeq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_f16)))
mve_pred16_t vcmpgeq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_f16)))
mve_pred16_t vcmpgeq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_f32)))
mve_pred16_t vcmpgeq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_m_n_f32)))
mve_pred16_t vcmpgeq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_f16)))
mve_pred16_t vcmpgeq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_f16)))
mve_pred16_t vcmpgeq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_f32)))
mve_pred16_t vcmpgeq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgeq_n_f32)))
mve_pred16_t vcmpgeq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_f16)))
mve_pred16_t vcmpgtq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_f16)))
mve_pred16_t vcmpgtq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_f32)))
mve_pred16_t vcmpgtq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_f32)))
mve_pred16_t vcmpgtq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_f16)))
mve_pred16_t vcmpgtq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_f16)))
mve_pred16_t vcmpgtq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_f32)))
mve_pred16_t vcmpgtq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_f32)))
mve_pred16_t vcmpgtq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_f16)))
mve_pred16_t vcmpgtq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_f16)))
mve_pred16_t vcmpgtq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_f32)))
mve_pred16_t vcmpgtq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_m_n_f32)))
mve_pred16_t vcmpgtq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_f16)))
mve_pred16_t vcmpgtq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_f16)))
mve_pred16_t vcmpgtq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_f32)))
mve_pred16_t vcmpgtq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpgtq_n_f32)))
mve_pred16_t vcmpgtq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_f16)))
mve_pred16_t vcmpleq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_f16)))
mve_pred16_t vcmpleq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_f32)))
mve_pred16_t vcmpleq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_f32)))
mve_pred16_t vcmpleq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_f16)))
mve_pred16_t vcmpleq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_f16)))
mve_pred16_t vcmpleq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_f32)))
mve_pred16_t vcmpleq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_f32)))
mve_pred16_t vcmpleq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_f16)))
mve_pred16_t vcmpleq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_f16)))
mve_pred16_t vcmpleq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_f32)))
mve_pred16_t vcmpleq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_m_n_f32)))
mve_pred16_t vcmpleq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_f16)))
mve_pred16_t vcmpleq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_f16)))
mve_pred16_t vcmpleq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_f32)))
mve_pred16_t vcmpleq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpleq_n_f32)))
mve_pred16_t vcmpleq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_f16)))
mve_pred16_t vcmpltq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_f16)))
mve_pred16_t vcmpltq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_f32)))
mve_pred16_t vcmpltq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_f32)))
mve_pred16_t vcmpltq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_f16)))
mve_pred16_t vcmpltq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_f16)))
mve_pred16_t vcmpltq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_f32)))
mve_pred16_t vcmpltq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_f32)))
mve_pred16_t vcmpltq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_f16)))
mve_pred16_t vcmpltq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_f16)))
mve_pred16_t vcmpltq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_f32)))
mve_pred16_t vcmpltq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_m_n_f32)))
mve_pred16_t vcmpltq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_f16)))
mve_pred16_t vcmpltq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_f16)))
mve_pred16_t vcmpltq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_f32)))
mve_pred16_t vcmpltq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpltq_n_f32)))
mve_pred16_t vcmpltq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_f16)))
mve_pred16_t vcmpneq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_f16)))
mve_pred16_t vcmpneq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_f32)))
mve_pred16_t vcmpneq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_f32)))
mve_pred16_t vcmpneq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_f16)))
mve_pred16_t vcmpneq_m_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_f16)))
mve_pred16_t vcmpneq_m(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_f32)))
mve_pred16_t vcmpneq_m_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_f32)))
mve_pred16_t vcmpneq_m(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_f16)))
mve_pred16_t vcmpneq_m_n_f16(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_f16)))
mve_pred16_t vcmpneq_m(float16x8_t, float16_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_f32)))
mve_pred16_t vcmpneq_m_n_f32(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_m_n_f32)))
mve_pred16_t vcmpneq_m(float32x4_t, float32_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_f16)))
mve_pred16_t vcmpneq_n_f16(float16x8_t, float16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_f16)))
mve_pred16_t vcmpneq(float16x8_t, float16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_f32)))
mve_pred16_t vcmpneq_n_f32(float32x4_t, float32_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmpneq_n_f32)))
mve_pred16_t vcmpneq(float32x4_t, float32_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_f16)))
float16x8_t vcmulq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_f16)))
float16x8_t vcmulq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_f32)))
float32x4_t vcmulq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_f32)))
float32x4_t vcmulq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_m_f16)))
float16x8_t vcmulq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_m_f16)))
float16x8_t vcmulq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_m_f32)))
float32x4_t vcmulq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_m_f32)))
float32x4_t vcmulq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_f16)))
float16x8_t vcmulq_rot180_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_f16)))
float16x8_t vcmulq_rot180(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_f32)))
float32x4_t vcmulq_rot180_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_f32)))
float32x4_t vcmulq_rot180(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_m_f16)))
float16x8_t vcmulq_rot180_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_m_f16)))
float16x8_t vcmulq_rot180_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_m_f32)))
float32x4_t vcmulq_rot180_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_m_f32)))
float32x4_t vcmulq_rot180_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_x_f16)))
float16x8_t vcmulq_rot180_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_x_f16)))
float16x8_t vcmulq_rot180_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_x_f32)))
float32x4_t vcmulq_rot180_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot180_x_f32)))
float32x4_t vcmulq_rot180_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_f16)))
float16x8_t vcmulq_rot270_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_f16)))
float16x8_t vcmulq_rot270(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_f32)))
float32x4_t vcmulq_rot270_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_f32)))
float32x4_t vcmulq_rot270(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_m_f16)))
float16x8_t vcmulq_rot270_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_m_f16)))
float16x8_t vcmulq_rot270_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_m_f32)))
float32x4_t vcmulq_rot270_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_m_f32)))
float32x4_t vcmulq_rot270_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_x_f16)))
float16x8_t vcmulq_rot270_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_x_f16)))
float16x8_t vcmulq_rot270_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_x_f32)))
float32x4_t vcmulq_rot270_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot270_x_f32)))
float32x4_t vcmulq_rot270_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_f16)))
float16x8_t vcmulq_rot90_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_f16)))
float16x8_t vcmulq_rot90(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_f32)))
float32x4_t vcmulq_rot90_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_f32)))
float32x4_t vcmulq_rot90(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_m_f16)))
float16x8_t vcmulq_rot90_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_m_f16)))
float16x8_t vcmulq_rot90_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_m_f32)))
float32x4_t vcmulq_rot90_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_m_f32)))
float32x4_t vcmulq_rot90_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_x_f16)))
float16x8_t vcmulq_rot90_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_x_f16)))
float16x8_t vcmulq_rot90_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_x_f32)))
float32x4_t vcmulq_rot90_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_rot90_x_f32)))
float32x4_t vcmulq_rot90_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_x_f16)))
float16x8_t vcmulq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_x_f16)))
float16x8_t vcmulq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcmulq_x_f32)))
float32x4_t vcmulq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vcmulq_x_f32)))
float32x4_t vcmulq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_f16)))
float16x8_t vcreateq_f16(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcreateq_f32)))
float32x4_t vcreateq_f32(uint64_t, uint64_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcvtbq_f16_f32)))
float16x8_t vcvtbq_f16_f32(float16x8_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcvtbq_m_f16_f32)))
float16x8_t vcvtbq_m_f16_f32(float16x8_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcvttq_f16_f32)))
float16x8_t vcvttq_f16_f32(float16x8_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vcvttq_m_f16_f32)))
float16x8_t vcvttq_m_f16_f32(float16x8_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_f16)))
float16x8_t veorq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_f16)))
float16x8_t veorq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_f32)))
float32x4_t veorq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_f32)))
float32x4_t veorq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_f16)))
float16x8_t veorq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_f16)))
float16x8_t veorq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_m_f32)))
float32x4_t veorq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_m_f32)))
float32x4_t veorq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_f16)))
float16x8_t veorq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_f16)))
float16x8_t veorq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_veorq_x_f32)))
float32x4_t veorq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_veorq_x_f32)))
float32x4_t veorq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_f16)))
float16_t vgetq_lane_f16(float16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_f16)))
float16_t vgetq_lane(float16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_f32)))
float32_t vgetq_lane_f32(float32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vgetq_lane_f32)))
float32_t vgetq_lane(float32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_f16)))
float16x8_t vld1q_f16(const float16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_f16)))
float16x8_t vld1q(const float16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_f32)))
float32x4_t vld1q_f32(const float32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_f32)))
float32x4_t vld1q(const float32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_f16)))
float16x8_t vld1q_z_f16(const float16_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_f16)))
float16x8_t vld1q_z(const float16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_f32)))
float32x4_t vld1q_z_f32(const float32_t *, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld1q_z_f32)))
float32x4_t vld1q_z(const float32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_f16)))
float16x8x2_t vld2q_f16(const float16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_f16)))
float16x8x2_t vld2q(const float16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld2q_f32)))
float32x4x2_t vld2q_f32(const float32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld2q_f32)))
float32x4x2_t vld2q(const float32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_f16)))
float16x8x4_t vld4q_f16(const float16_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_f16)))
float16x8x4_t vld4q(const float16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vld4q_f32)))
float32x4x4_t vld4q_f32(const float32_t *);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vld4q_f32)))
float32x4x4_t vld4q(const float32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_f16)))
float16x8_t vldrhq_f16(const float16_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_f16)))
float16x8_t vldrhq_gather_offset_f16(const float16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_f16)))
float16x8_t vldrhq_gather_offset(const float16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_f16)))
float16x8_t vldrhq_gather_offset_z_f16(const float16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_offset_z_f16)))
float16x8_t vldrhq_gather_offset_z(const float16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_f16)))
float16x8_t vldrhq_gather_shifted_offset_f16(const float16_t *, uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_f16)))
float16x8_t vldrhq_gather_shifted_offset(const float16_t *, uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_f16)))
float16x8_t vldrhq_gather_shifted_offset_z_f16(const float16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrhq_gather_shifted_offset_z_f16)))
float16x8_t vldrhq_gather_shifted_offset_z(const float16_t *, uint16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrhq_z_f16)))
float16x8_t vldrhq_z_f16(const float16_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_f32)))
float32x4_t vldrwq_f32(const float32_t *);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_f32)))
float32x4_t vldrwq_gather_base_f32(uint32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_f32)))
float32x4_t vldrwq_gather_base_wb_f32(uint32x4_t *, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_wb_z_f32)))
float32x4_t vldrwq_gather_base_wb_z_f32(uint32x4_t *, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_base_z_f32)))
float32x4_t vldrwq_gather_base_z_f32(uint32x4_t, int, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_f32)))
float32x4_t vldrwq_gather_offset_f32(const float32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_f32)))
float32x4_t vldrwq_gather_offset(const float32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_f32)))
float32x4_t vldrwq_gather_offset_z_f32(const float32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_offset_z_f32)))
float32x4_t vldrwq_gather_offset_z(const float32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_f32)))
float32x4_t vldrwq_gather_shifted_offset_f32(const float32_t *, uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_f32)))
float32x4_t vldrwq_gather_shifted_offset(const float32_t *, uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_f32)))
float32x4_t vldrwq_gather_shifted_offset_z_f32(const float32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vldrwq_gather_shifted_offset_z_f32)))
float32x4_t vldrwq_gather_shifted_offset_z(const float32_t *, uint32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vldrwq_z_f32)))
float32x4_t vldrwq_z_f32(const float32_t *, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_f16)))
float16x8_t vmaxnmq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_f16)))
float16x8_t vmaxnmq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_f32)))
float32x4_t vmaxnmq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_f32)))
float32x4_t vmaxnmq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_m_f16)))
float16x8_t vmaxnmq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_m_f16)))
float16x8_t vmaxnmq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_m_f32)))
float32x4_t vmaxnmq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_m_f32)))
float32x4_t vmaxnmq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_x_f16)))
float16x8_t vmaxnmq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_x_f16)))
float16x8_t vmaxnmq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_x_f32)))
float32x4_t vmaxnmq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmaxnmq_x_f32)))
float32x4_t vmaxnmq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_f16)))
float16x8_t vminnmq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_f16)))
float16x8_t vminnmq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_f32)))
float32x4_t vminnmq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_f32)))
float32x4_t vminnmq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_m_f16)))
float16x8_t vminnmq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_m_f16)))
float16x8_t vminnmq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_m_f32)))
float32x4_t vminnmq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_m_f32)))
float32x4_t vminnmq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_x_f16)))
float16x8_t vminnmq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_x_f16)))
float16x8_t vminnmq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vminnmq_x_f32)))
float32x4_t vminnmq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vminnmq_x_f32)))
float32x4_t vminnmq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_f16)))
float16x8_t vmulq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_f16)))
float16x8_t vmulq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_f32)))
float32x4_t vmulq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_f32)))
float32x4_t vmulq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_f16)))
float16x8_t vmulq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_f16)))
float16x8_t vmulq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_f32)))
float32x4_t vmulq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_m_f32)))
float32x4_t vmulq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_f16)))
float16x8_t vmulq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_f16)))
float16x8_t vmulq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_f32)))
float32x4_t vmulq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vmulq_x_f32)))
float32x4_t vmulq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_f16)))
float16x8_t vornq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_f16)))
float16x8_t vornq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_f32)))
float32x4_t vornq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_f32)))
float32x4_t vornq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_f16)))
float16x8_t vornq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_f16)))
float16x8_t vornq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_m_f32)))
float32x4_t vornq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_m_f32)))
float32x4_t vornq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_f16)))
float16x8_t vornq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_f16)))
float16x8_t vornq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vornq_x_f32)))
float32x4_t vornq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vornq_x_f32)))
float32x4_t vornq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_f16)))
float16x8_t vorrq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_f16)))
float16x8_t vorrq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_f32)))
float32x4_t vorrq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_f32)))
float32x4_t vorrq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_f16)))
float16x8_t vorrq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_f16)))
float16x8_t vorrq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_f32)))
float32x4_t vorrq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_m_f32)))
float32x4_t vorrq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_f16)))
float16x8_t vorrq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_f16)))
float16x8_t vorrq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_f32)))
float32x4_t vorrq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vorrq_x_f32)))
float32x4_t vorrq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_f16)))
float16x8_t vpselq_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_f16)))
float16x8_t vpselq(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vpselq_f32)))
float32x4_t vpselq_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vpselq_f32)))
float32x4_t vpselq(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_f32)))
float16x8_t vreinterpretq_f16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_f32)))
float16x8_t vreinterpretq_f16(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s16)))
float16x8_t vreinterpretq_f16_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s16)))
float16x8_t vreinterpretq_f16(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s32)))
float16x8_t vreinterpretq_f16_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s32)))
float16x8_t vreinterpretq_f16(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s64)))
float16x8_t vreinterpretq_f16_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s64)))
float16x8_t vreinterpretq_f16(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s8)))
float16x8_t vreinterpretq_f16_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_s8)))
float16x8_t vreinterpretq_f16(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u16)))
float16x8_t vreinterpretq_f16_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u16)))
float16x8_t vreinterpretq_f16(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u32)))
float16x8_t vreinterpretq_f16_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u32)))
float16x8_t vreinterpretq_f16(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u64)))
float16x8_t vreinterpretq_f16_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u64)))
float16x8_t vreinterpretq_f16(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u8)))
float16x8_t vreinterpretq_f16_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f16_u8)))
float16x8_t vreinterpretq_f16(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_f16)))
float32x4_t vreinterpretq_f32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_f16)))
float32x4_t vreinterpretq_f32(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s16)))
float32x4_t vreinterpretq_f32_s16(int16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s16)))
float32x4_t vreinterpretq_f32(int16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s32)))
float32x4_t vreinterpretq_f32_s32(int32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s32)))
float32x4_t vreinterpretq_f32(int32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s64)))
float32x4_t vreinterpretq_f32_s64(int64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s64)))
float32x4_t vreinterpretq_f32(int64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s8)))
float32x4_t vreinterpretq_f32_s8(int8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_s8)))
float32x4_t vreinterpretq_f32(int8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u16)))
float32x4_t vreinterpretq_f32_u16(uint16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u16)))
float32x4_t vreinterpretq_f32(uint16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u32)))
float32x4_t vreinterpretq_f32_u32(uint32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u32)))
float32x4_t vreinterpretq_f32(uint32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u64)))
float32x4_t vreinterpretq_f32_u64(uint64x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u64)))
float32x4_t vreinterpretq_f32(uint64x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u8)))
float32x4_t vreinterpretq_f32_u8(uint8x16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_f32_u8)))
float32x4_t vreinterpretq_f32(uint8x16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_f16)))
int16x8_t vreinterpretq_s16_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_f16)))
int16x8_t vreinterpretq_s16(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_f32)))
int16x8_t vreinterpretq_s16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s16_f32)))
int16x8_t vreinterpretq_s16(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_f16)))
int32x4_t vreinterpretq_s32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_f16)))
int32x4_t vreinterpretq_s32(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_f32)))
int32x4_t vreinterpretq_s32_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s32_f32)))
int32x4_t vreinterpretq_s32(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_f16)))
int64x2_t vreinterpretq_s64_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_f16)))
int64x2_t vreinterpretq_s64(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_f32)))
int64x2_t vreinterpretq_s64_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s64_f32)))
int64x2_t vreinterpretq_s64(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_f16)))
int8x16_t vreinterpretq_s8_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_f16)))
int8x16_t vreinterpretq_s8(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_f32)))
int8x16_t vreinterpretq_s8_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_s8_f32)))
int8x16_t vreinterpretq_s8(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_f16)))
uint16x8_t vreinterpretq_u16_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_f16)))
uint16x8_t vreinterpretq_u16(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_f32)))
uint16x8_t vreinterpretq_u16_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u16_f32)))
uint16x8_t vreinterpretq_u16(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_f16)))
uint32x4_t vreinterpretq_u32_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_f16)))
uint32x4_t vreinterpretq_u32(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_f32)))
uint32x4_t vreinterpretq_u32_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u32_f32)))
uint32x4_t vreinterpretq_u32(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_f16)))
uint64x2_t vreinterpretq_u64_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_f16)))
uint64x2_t vreinterpretq_u64(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_f32)))
uint64x2_t vreinterpretq_u64_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u64_f32)))
uint64x2_t vreinterpretq_u64(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_f16)))
uint8x16_t vreinterpretq_u8_f16(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_f16)))
uint8x16_t vreinterpretq_u8(float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_f32)))
uint8x16_t vreinterpretq_u8_f32(float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vreinterpretq_u8_f32)))
uint8x16_t vreinterpretq_u8(float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_f16)))
float16x8_t vsetq_lane_f16(float16_t, float16x8_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_f16)))
float16x8_t vsetq_lane(float16_t, float16x8_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_f32)))
float32x4_t vsetq_lane_f32(float32_t, float32x4_t, int);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsetq_lane_f32)))
float32x4_t vsetq_lane(float32_t, float32x4_t, int);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_f16)))
void vst1q_f16(float16_t *, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_f16)))
void vst1q(float16_t *, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_f32)))
void vst1q_f32(float32_t *, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_f32)))
void vst1q(float32_t *, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_f16)))
void vst1q_p_f16(float16_t *, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_f16)))
void vst1q_p(float16_t *, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_f32)))
void vst1q_p_f32(float32_t *, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst1q_p_f32)))
void vst1q_p(float32_t *, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_f16)))
void vst2q_f16(float16_t *, float16x8x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_f16)))
void vst2q(float16_t *, float16x8x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst2q_f32)))
void vst2q_f32(float32_t *, float32x4x2_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst2q_f32)))
void vst2q(float32_t *, float32x4x2_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_f16)))
void vst4q_f16(float16_t *, float16x8x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_f16)))
void vst4q(float16_t *, float16x8x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vst4q_f32)))
void vst4q_f32(float32_t *, float32x4x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vst4q_f32)))
void vst4q(float32_t *, float32x4x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_f16)))
void vstrhq_f16(float16_t *, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_f16)))
void vstrhq(float16_t *, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_f16)))
void vstrhq_p_f16(float16_t *, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_p_f16)))
void vstrhq_p(float16_t *, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_f16)))
void vstrhq_scatter_offset_f16(float16_t *, uint16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_f16)))
void vstrhq_scatter_offset(float16_t *, uint16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_f16)))
void vstrhq_scatter_offset_p_f16(float16_t *, uint16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_offset_p_f16)))
void vstrhq_scatter_offset_p(float16_t *, uint16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_f16)))
void vstrhq_scatter_shifted_offset_f16(float16_t *, uint16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_f16)))
void vstrhq_scatter_shifted_offset(float16_t *, uint16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_f16)))
void vstrhq_scatter_shifted_offset_p_f16(float16_t *, uint16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrhq_scatter_shifted_offset_p_f16)))
void vstrhq_scatter_shifted_offset_p(float16_t *, uint16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_f32)))
void vstrwq_f32(float32_t *, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_f32)))
void vstrwq(float32_t *, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_f32)))
void vstrwq_p_f32(float32_t *, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_p_f32)))
void vstrwq_p(float32_t *, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_f32)))
void vstrwq_scatter_base_f32(uint32x4_t, int, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_f32)))
void vstrwq_scatter_base(uint32x4_t, int, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_f32)))
void vstrwq_scatter_base_p_f32(uint32x4_t, int, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_p_f32)))
void vstrwq_scatter_base_p(uint32x4_t, int, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_f32)))
void vstrwq_scatter_base_wb_f32(uint32x4_t *, int, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_f32)))
void vstrwq_scatter_base_wb(uint32x4_t *, int, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_f32)))
void vstrwq_scatter_base_wb_p_f32(uint32x4_t *, int, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_base_wb_p_f32)))
void vstrwq_scatter_base_wb_p(uint32x4_t *, int, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_f32)))
void vstrwq_scatter_offset_f32(float32_t *, uint32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_f32)))
void vstrwq_scatter_offset(float32_t *, uint32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_f32)))
void vstrwq_scatter_offset_p_f32(float32_t *, uint32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_offset_p_f32)))
void vstrwq_scatter_offset_p(float32_t *, uint32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_f32)))
void vstrwq_scatter_shifted_offset_f32(float32_t *, uint32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_f32)))
void vstrwq_scatter_shifted_offset(float32_t *, uint32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_f32)))
void vstrwq_scatter_shifted_offset_p_f32(float32_t *, uint32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vstrwq_scatter_shifted_offset_p_f32)))
void vstrwq_scatter_shifted_offset_p(float32_t *, uint32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_f16)))
float16x8_t vsubq_f16(float16x8_t, float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_f16)))
float16x8_t vsubq(float16x8_t, float16x8_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_f32)))
float32x4_t vsubq_f32(float32x4_t, float32x4_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_f32)))
float32x4_t vsubq(float32x4_t, float32x4_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_f16)))
float16x8_t vsubq_m_f16(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_f16)))
float16x8_t vsubq_m(float16x8_t, float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_f32)))
float32x4_t vsubq_m_f32(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_m_f32)))
float32x4_t vsubq_m(float32x4_t, float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_f16)))
float16x8_t vsubq_x_f16(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_f16)))
float16x8_t vsubq_x(float16x8_t, float16x8_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_f32)))
float32x4_t vsubq_x_f32(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vsubq_x_f32)))
float32x4_t vsubq_x(float32x4_t, float32x4_t, mve_pred16_t);
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_f16)))
float16x8_t vuninitializedq_f16();
static __inline__ __attribute__((__clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_f32)))
float32x4_t vuninitializedq_f32();
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_f16)))
float16x8_t vuninitializedq(float16x8_t);
static __inline__ __attribute__((overloadable, __clang_arm_mve_alias(__builtin_arm_mve_vuninitializedq_polymorphic_f32)))
float32x4_t vuninitializedq(float32x4_t);

#endif /* (__ARM_FEATURE_MVE & 2) && (!defined __ARM_MVE_PRESERVE_USER_NAMESPACE) */

#endif /* __ARM_MVE_H */
