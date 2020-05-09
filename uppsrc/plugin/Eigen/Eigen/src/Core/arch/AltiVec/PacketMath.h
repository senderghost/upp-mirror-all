// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008-2016 Konstantinos Margaritis <markos@freevec.org>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EIGEN_PACKET_MATH_ALTIVEC_H
#define EIGEN_PACKET_MATH_ALTIVEC_H

namespace Eigen {

namespace internal {

#ifndef EIGEN_CACHEFRIENDLY_PRODUCT_THRESHOLD
#define EIGEN_CACHEFRIENDLY_PRODUCT_THRESHOLD 4
#endif

#ifndef EIGEN_HAS_SINGLE_INSTRUCTION_MADD
#define EIGEN_HAS_SINGLE_INSTRUCTION_MADD
#endif

#ifndef EIGEN_HAS_SINGLE_INSTRUCTION_CJMADD
#define EIGEN_HAS_SINGLE_INSTRUCTION_CJMADD
#endif

// NOTE Altivec has 32 registers, but Eigen only accepts a value of 8 or 16
#ifndef EIGEN_ARCH_DEFAULT_NUMBER_OF_REGISTERS
#define EIGEN_ARCH_DEFAULT_NUMBER_OF_REGISTERS  32
#endif

typedef __vector float                   Packet4f;
typedef __vector int                     Packet4i;
typedef __vector unsigned int            Packet4ui;
typedef __vector __bool int              Packet4bi;
typedef __vector short int               Packet8s;
typedef __vector unsigned short int      Packet8us;
typedef __vector int8_t                  Packet16c;
typedef __vector uint8_t                 Packet16uc;

// We don't want to write the same code all the time, but we need to reuse the constants
// and it doesn't really work to declare them global, so we define macros instead

#define _EIGEN_DECLARE_CONST_FAST_Packet4f(NAME,X) \
  Packet4f p4f_##NAME = {X, X, X, X}

#define _EIGEN_DECLARE_CONST_FAST_Packet4i(NAME,X) \
  Packet4i p4i_##NAME = vec_splat_s32(X)

#define _EIGEN_DECLARE_CONST_FAST_Packet4ui(NAME,X) \
  Packet4ui p4ui_##NAME = {X, X, X, X}

#define _EIGEN_DECLARE_CONST_FAST_Packet8us(NAME,X) \
  Packet8us p8us_##NAME = {X, X, X, X, X, X, X, X}

#define _EIGEN_DECLARE_CONST_FAST_Packet16uc(NAME,X) \
  Packet16uc p16uc_##NAME = {X, X, X, X, X, X, X, X, X, X, X, X, X, X, X, X}

#define _EIGEN_DECLARE_CONST_Packet4f(NAME,X) \
  Packet4f p4f_##NAME = pset1<Packet4f>(X)

#define _EIGEN_DECLARE_CONST_Packet4i(NAME,X) \
  Packet4i p4i_##NAME = pset1<Packet4i>(X)

#define _EIGEN_DECLARE_CONST_Packet2d(NAME,X) \
  Packet2d p2d_##NAME = pset1<Packet2d>(X)

#define _EIGEN_DECLARE_CONST_Packet2l(NAME,X) \
  Packet2l p2l_##NAME = pset1<Packet2l>(X)

#define _EIGEN_DECLARE_CONST_Packet4f_FROM_INT(NAME,X) \
  const Packet4f p4f_##NAME = reinterpret_cast<Packet4f>(pset1<Packet4i>(X))

#define DST_CHAN 1
#define DST_CTRL(size, count, stride) (((size) << 24) | ((count) << 16) | (stride))

// These constants are endian-agnostic
static _EIGEN_DECLARE_CONST_FAST_Packet4f(ZERO, 0); //{ 0.0, 0.0, 0.0, 0.0}
static _EIGEN_DECLARE_CONST_FAST_Packet4i(ZERO, 0); //{ 0, 0, 0, 0,}
static _EIGEN_DECLARE_CONST_FAST_Packet4i(ONE,1); //{ 1, 1, 1, 1}
static _EIGEN_DECLARE_CONST_FAST_Packet4i(MINUS16,-16); //{ -16, -16, -16, -16}
static _EIGEN_DECLARE_CONST_FAST_Packet4i(MINUS1,-1); //{ -1, -1, -1, -1}
static _EIGEN_DECLARE_CONST_FAST_Packet4ui(SIGN, 0x80000000u);
static _EIGEN_DECLARE_CONST_FAST_Packet4ui(PREV0DOT5, 0x3EFFFFFFu);
static _EIGEN_DECLARE_CONST_FAST_Packet8us(ONE,1); //{ 1, 1, 1, 1, 1, 1, 1, 1}
static _EIGEN_DECLARE_CONST_FAST_Packet16uc(ONE,1);
static Packet4f p4f_MZERO = (Packet4f) vec_sl((Packet4ui)p4i_MINUS1, (Packet4ui)p4i_MINUS1); //{ 0x80000000, 0x80000000, 0x80000000, 0x80000000}
#ifndef __VSX__
static Packet4f p4f_ONE = vec_ctf(p4i_ONE, 0); //{ 1.0, 1.0, 1.0, 1.0}
#endif

static Packet4f  p4f_COUNTDOWN  = { 0.0, 1.0, 2.0, 3.0 };
static Packet4i  p4i_COUNTDOWN  = { 0, 1, 2, 3 };
static Packet8s  p8s_COUNTDOWN  = { 0, 1, 2, 3, 4, 5, 6, 7 };
static Packet8us p8us_COUNTDOWN = { 0, 1, 2, 3, 4, 5, 6, 7 };
static Packet16c  p16c_COUNTDOWN = { 0, 1, 2, 3, 4, 5, 6, 7,
                                    8, 9, 10, 11, 12, 13, 14, 15};
static Packet16uc p16uc_COUNTDOWN = { 0, 1, 2, 3, 4, 5, 6, 7, 
                                    8, 9, 10, 11, 12, 13, 14, 15};

static Packet16uc p16uc_REVERSE32 = { 12,13,14,15, 8,9,10,11, 4,5,6,7, 0,1,2,3 };
static Packet16uc p16uc_REVERSE16 = { 14,15, 12,13, 10,11, 8,9, 6,7, 4,5, 2,3, 0,1 };
static Packet16uc p16uc_REVERSE8 = { 15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0 };

static Packet16uc p16uc_DUPLICATE32_HI = { 0,1,2,3, 0,1,2,3, 4,5,6,7, 4,5,6,7 };
static Packet16uc p16uc_DUPLICATE16_HI = { 0,1,0,1, 2,3,2,3, 4,5,4,5, 6,7,6,7 };
static Packet16uc p16uc_DUPLICATE8_HI = { 0,0, 1,1, 2,2, 3,3, 4,4, 5,5, 6,6, 7,7 };

static Packet16uc p16uc_QUADRUPLICATE16_HI = { 0,1,0,1,0,1,0,1, 2,3,2,3,2,3,2,3 };

// Handle endianness properly while loading constants
// Define global static constants:
#ifdef _BIG_ENDIAN
static Packet16uc p16uc_FORWARD = vec_lvsl(0, (float*)0);
#ifdef __VSX__
static Packet16uc p16uc_REVERSE64 = { 8,9,10,11, 12,13,14,15, 0,1,2,3, 4,5,6,7 };
#endif
static Packet16uc p16uc_PSET32_WODD   = vec_sld((Packet16uc) vec_splat((Packet4ui)p16uc_FORWARD, 0), (Packet16uc) vec_splat((Packet4ui)p16uc_FORWARD, 2), 8);//{ 0,1,2,3, 0,1,2,3, 8,9,10,11, 8,9,10,11 };
static Packet16uc p16uc_PSET32_WEVEN  = vec_sld(p16uc_DUPLICATE32_HI, (Packet16uc) vec_splat((Packet4ui)p16uc_FORWARD, 3), 8);//{ 4,5,6,7, 4,5,6,7, 12,13,14,15, 12,13,14,15 };
static Packet16uc p16uc_HALF64_0_16 = vec_sld((Packet16uc)p4i_ZERO, vec_splat((Packet16uc) vec_abs(p4i_MINUS16), 3), 8);      //{ 0,0,0,0, 0,0,0,0, 16,16,16,16, 16,16,16,16};
#else
static Packet16uc p16uc_FORWARD = p16uc_REVERSE32;
static Packet16uc p16uc_REVERSE64 = { 8,9,10,11, 12,13,14,15, 0,1,2,3, 4,5,6,7 };
static Packet16uc p16uc_PSET32_WODD = vec_sld((Packet16uc) vec_splat((Packet4ui)p16uc_FORWARD, 1), (Packet16uc) vec_splat((Packet4ui)p16uc_FORWARD, 3), 8);//{ 0,1,2,3, 0,1,2,3, 8,9,10,11, 8,9,10,11 };
static Packet16uc p16uc_PSET32_WEVEN = vec_sld((Packet16uc) vec_splat((Packet4ui)p16uc_FORWARD, 0), (Packet16uc) vec_splat((Packet4ui)p16uc_FORWARD, 2), 8);//{ 4,5,6,7, 4,5,6,7, 12,13,14,15, 12,13,14,15 };
static Packet16uc p16uc_HALF64_0_16 = vec_sld(vec_splat((Packet16uc) vec_abs(p4i_MINUS16), 0), (Packet16uc)p4i_ZERO, 8);      //{ 0,0,0,0, 0,0,0,0, 16,16,16,16, 16,16,16,16};
#endif // _BIG_ENDIAN

static Packet16uc p16uc_PSET64_HI = (Packet16uc) vec_mergeh((Packet4ui)p16uc_PSET32_WODD, (Packet4ui)p16uc_PSET32_WEVEN);     //{ 0,1,2,3, 4,5,6,7, 0,1,2,3, 4,5,6,7 };
static Packet16uc p16uc_PSET64_LO = (Packet16uc) vec_mergel((Packet4ui)p16uc_PSET32_WODD, (Packet4ui)p16uc_PSET32_WEVEN);     //{ 8,9,10,11, 12,13,14,15, 8,9,10,11, 12,13,14,15 };
static Packet16uc p16uc_TRANSPOSE64_HI = p16uc_PSET64_HI + p16uc_HALF64_0_16;                                         //{ 0,1,2,3, 4,5,6,7, 16,17,18,19, 20,21,22,23};
static Packet16uc p16uc_TRANSPOSE64_LO = p16uc_PSET64_LO + p16uc_HALF64_0_16;                                         //{ 8,9,10,11, 12,13,14,15, 24,25,26,27, 28,29,30,31};

static Packet16uc p16uc_COMPLEX32_REV = vec_sld(p16uc_REVERSE32, p16uc_REVERSE32, 8);                                         //{ 4,5,6,7, 0,1,2,3, 12,13,14,15, 8,9,10,11 };

#ifdef _BIG_ENDIAN
static Packet16uc p16uc_COMPLEX32_REV2 = vec_sld(p16uc_FORWARD, p16uc_FORWARD, 8);                                            //{ 8,9,10,11, 12,13,14,15, 0,1,2,3, 4,5,6,7 };
#else
static Packet16uc p16uc_COMPLEX32_REV2 = vec_sld(p16uc_PSET64_HI, p16uc_PSET64_LO, 8);                                            //{ 8,9,10,11, 12,13,14,15, 0,1,2,3, 4,5,6,7 };
#endif // _BIG_ENDIAN

#if EIGEN_HAS_BUILTIN(__builtin_prefetch) || EIGEN_COMP_GNUC
  #define EIGEN_PPC_PREFETCH(ADDR) __builtin_prefetch(ADDR);
#else
  #define EIGEN_PPC_PREFETCH(ADDR) asm( "   dcbt [%[addr]]\n" :: [addr] "r" (ADDR) : "cc" );
#endif

template <>
struct packet_traits<float> : default_packet_traits {
  typedef Packet4f type;
  typedef Packet4f half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 4,
    HasHalfPacket = 1,

    HasAdd = 1,
    HasSub = 1,
    HasMul = 1,
    HasDiv = 1,
    HasMin = 1,
    HasMax = 1,
    HasAbs = 1,
    HasSin = EIGEN_FAST_MATH,
    HasCos = EIGEN_FAST_MATH,
    HasLog = 1,
    HasExp = 1,
#ifdef __VSX__
    HasSqrt = 1,
#if !EIGEN_COMP_CLANG
    HasRsqrt = 1,
#else
    HasRsqrt = 0,
#endif
#else
    HasSqrt = 0,
    HasRsqrt = 0,
    HasTanh = EIGEN_FAST_MATH,
    HasErf = EIGEN_FAST_MATH,
#endif
    HasRound = 1,
    HasFloor = 1,
    HasCeil = 1,
    HasNegate = 1,
    HasBlend = 1
  };
};
template <>
struct packet_traits<int> : default_packet_traits {
  typedef Packet4i type;
  typedef Packet4i half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 4,
    HasHalfPacket = 0,

    HasAdd   = 1,
    HasSub   = 1,
    HasShift = 1,
    HasMul   = 1,
    HasDiv   = 0,
    HasBlend = 1
  };
};

template <>
struct packet_traits<short int> : default_packet_traits {
  typedef Packet8s type;
  typedef Packet8s half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 8,
    HasHalfPacket = 0,

    HasAdd  = 1,
    HasSub  = 1,
    HasMul  = 1,
    HasDiv  = 0,
    HasBlend = 1
  };
};

template <>
struct packet_traits<unsigned short int> : default_packet_traits {
  typedef Packet8us type;
  typedef Packet8us half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 8,
    HasHalfPacket = 0,

    HasAdd  = 1,
    HasSub  = 1,
    HasMul  = 1,
    HasDiv  = 0,
    HasBlend = 1
  };
};

template <>
struct packet_traits<int8_t> : default_packet_traits {
  typedef Packet16c type;
  typedef Packet16c half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 16,
    HasHalfPacket = 0,

    HasAdd  = 1,
    HasSub  = 1,
    HasMul  = 1,
    HasDiv  = 0,
    HasBlend = 1
  };
};

template <>
struct packet_traits<uint8_t> : default_packet_traits {
  typedef Packet16uc type;
  typedef Packet16uc half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size = 16,
    HasHalfPacket = 0,

    HasAdd  = 1,
    HasSub  = 1,
    HasMul  = 1,
    HasDiv  = 0,
    HasBlend = 1
  };
};

template<> struct unpacket_traits<Packet4f>
{
  typedef float     type;
  typedef Packet4f  half;
  typedef Packet4i  integer_packet;
  enum {size=4, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
template<> struct unpacket_traits<Packet4i>
{
  typedef int       type;
  typedef Packet4i  half;
  enum {size=4, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
template<> struct unpacket_traits<Packet8s>
{
  typedef short int type;
  typedef Packet8s  half;
  enum {size=8, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
template<> struct unpacket_traits<Packet8us>
{
  typedef unsigned short int type;
  typedef Packet8us          half;
  enum {size=8, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};

template<> struct unpacket_traits<Packet16c>
{
  typedef int8_t type;
  typedef Packet16c  half;
  enum {size=16, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};
template<> struct unpacket_traits<Packet16uc>
{
  typedef uint8_t type;
  typedef Packet16uc  half;
  enum {size=16, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false};
};

inline std::ostream & operator <<(std::ostream & s, const Packet16c & v)
{
  union {
    Packet16c   v;
    int8_t n[16];
  } vt;
  vt.v = v;
  for (int i=0; i< 16; i++)
    s << vt.n[i] << ", ";
  return s;
}

inline std::ostream & operator <<(std::ostream & s, const Packet16uc & v)
{
  union {
    Packet16uc   v;
    uint8_t n[16];
  } vt;
  vt.v = v;
  for (int i=0; i< 16; i++)
    s << vt.n[i] << ", ";
  return s;
}

inline std::ostream & operator <<(std::ostream & s, const Packet4f & v)
{
  union {
    Packet4f   v;
    float n[4];
  } vt;
  vt.v = v;
  s << vt.n[0] << ", " << vt.n[1] << ", " << vt.n[2] << ", " << vt.n[3];
  return s;
}

inline std::ostream & operator <<(std::ostream & s, const Packet4i & v)
{
  union {
    Packet4i   v;
    int n[4];
  } vt;
  vt.v = v;
  s << vt.n[0] << ", " << vt.n[1] << ", " << vt.n[2] << ", " << vt.n[3];
  return s;
}

inline std::ostream & operator <<(std::ostream & s, const Packet4ui & v)
{
  union {
    Packet4ui   v;
    unsigned int n[4];
  } vt;
  vt.v = v;
  s << vt.n[0] << ", " << vt.n[1] << ", " << vt.n[2] << ", " << vt.n[3];
  return s;
}

// Need to define them first or we get specialization after instantiation errors
template<> EIGEN_STRONG_INLINE Packet4f pload<Packet4f>(const float* from)
{
  // some versions of GCC throw "unused-but-set-parameter".
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(from);
  EIGEN_DEBUG_ALIGNED_LOAD
#ifdef __VSX__
  return vec_xl(0, from);
#else
  return vec_ld(0, from);
#endif
}

template<> EIGEN_STRONG_INLINE Packet4i pload<Packet4i>(const int*     from)
{
  // some versions of GCC throw "unused-but-set-parameter".
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(from);
  EIGEN_DEBUG_ALIGNED_LOAD
#ifdef __VSX__
  return vec_xl(0, from);
#else
  return vec_ld(0, from);
#endif
}

template<> EIGEN_STRONG_INLINE Packet8s pload<Packet8s>(const short int* from)
{
  // some versions of GCC throw "unused-but-set-parameter".
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(from);
  EIGEN_DEBUG_ALIGNED_LOAD
  return vec_ld(0, from);
}

template<> EIGEN_STRONG_INLINE Packet8us pload<Packet8us>(const unsigned short int* from)
{
  // some versions of GCC throw "unused-but-set-parameter".
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(from);
  EIGEN_DEBUG_ALIGNED_LOAD
  return vec_ld(0, from);
}

template<> EIGEN_STRONG_INLINE Packet16c pload<Packet16c>(const int8_t*     from)
{
  // some versions of GCC throw "unused-but-set-parameter".
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(from);
  EIGEN_DEBUG_ALIGNED_LOAD
  return vec_ld(0, from);
}

template<> EIGEN_STRONG_INLINE Packet16uc pload<Packet16uc>(const uint8_t*     from)
{
  // some versions of GCC throw "unused-but-set-parameter".
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(from);
  EIGEN_DEBUG_ALIGNED_LOAD
  return vec_ld(0, from);
}

template<> EIGEN_STRONG_INLINE void pstore<float>(float*   to, const Packet4f& from)
{
  // some versions of GCC throw "unused-but-set-parameter" (float *to).
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(to);
  EIGEN_DEBUG_ALIGNED_STORE
#ifdef __VSX__
  vec_xst(from, 0, to);
#else
  vec_st(from, 0, to);
#endif
}

template<> EIGEN_STRONG_INLINE void pstore<int>(int*       to, const Packet4i& from)
{
  // some versions of GCC throw "unused-but-set-parameter" (float *to).
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(to);
  EIGEN_DEBUG_ALIGNED_STORE
#ifdef __VSX__
  vec_xst(from, 0, to);
#else
  vec_st(from, 0, to);
#endif
}

template<> EIGEN_STRONG_INLINE void pstore<short int>(short int*       to, const Packet8s& from)
{
  // some versions of GCC throw "unused-but-set-parameter" (float *to).
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(to);
  EIGEN_DEBUG_ALIGNED_STORE
  vec_st(from, 0, to);
}

template<> EIGEN_STRONG_INLINE void pstore<unsigned short int>(unsigned short int*       to, const Packet8us& from)
{
  // some versions of GCC throw "unused-but-set-parameter" (float *to).
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(to);
  EIGEN_DEBUG_ALIGNED_STORE
  vec_st(from, 0, to);
}
template<> EIGEN_STRONG_INLINE void pstore<int8_t>(int8_t*       to, const Packet16c& from)
{
  // some versions of GCC throw "unused-but-set-parameter" (float *to).
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(to);
  EIGEN_DEBUG_ALIGNED_STORE
  vec_st(from, 0, to);
}

template<> EIGEN_STRONG_INLINE void pstore<uint8_t>(uint8_t*       to, const Packet16uc& from)
{
  // some versions of GCC throw "unused-but-set-parameter" (float *to).
  // ignoring these warnings for now.
  EIGEN_UNUSED_VARIABLE(to);
  EIGEN_DEBUG_ALIGNED_STORE
  vec_st(from, 0, to);
}

template<> EIGEN_STRONG_INLINE Packet4f pset1<Packet4f>(const float&  from) {
  Packet4f v = {from, from, from, from};
  return v;
}

template<> EIGEN_STRONG_INLINE Packet4i pset1<Packet4i>(const int&    from)   {
  Packet4i v = {from, from, from, from};
  return v;
}

template<> EIGEN_STRONG_INLINE Packet8s pset1<Packet8s>(const short int&    from)   {
  Packet8s v = {from, from, from, from, from, from, from, from};
  return v;
}

template<> EIGEN_STRONG_INLINE Packet8us pset1<Packet8us>(const unsigned short int&    from)   {
  Packet8us v = {from, from, from, from, from, from, from, from};
  return v;
}

template<> EIGEN_STRONG_INLINE Packet16c pset1<Packet16c>(const int8_t&    from)   {
  Packet16c v = {from, from, from, from, from, from, from, from, from, from, from, from, from, from, from, from};
  return v;
}

template<> EIGEN_STRONG_INLINE Packet16uc pset1<Packet16uc>(const uint8_t&    from)   {
  Packet16uc v = {from, from, from, from, from, from, from, from, from, from, from, from, from, from, from, from};
  return v;
}

template<> EIGEN_STRONG_INLINE Packet4f pset1frombits<Packet4f>(unsigned int from) {
  return reinterpret_cast<Packet4f>(pset1<Packet4i>(from));
}

template<> EIGEN_STRONG_INLINE void
pbroadcast4<Packet4f>(const float *a,
                      Packet4f& a0, Packet4f& a1, Packet4f& a2, Packet4f& a3)
{
  a3 = pload<Packet4f>(a);
  a0 = vec_splat(a3, 0);
  a1 = vec_splat(a3, 1);
  a2 = vec_splat(a3, 2);
  a3 = vec_splat(a3, 3);
}
template<> EIGEN_STRONG_INLINE void
pbroadcast4<Packet4i>(const int *a,
                      Packet4i& a0, Packet4i& a1, Packet4i& a2, Packet4i& a3)
{
  a3 = pload<Packet4i>(a);
  a0 = vec_splat(a3, 0);
  a1 = vec_splat(a3, 1);
  a2 = vec_splat(a3, 2);
  a3 = vec_splat(a3, 3);
}

template<> EIGEN_DEVICE_FUNC inline Packet4f pgather<float, Packet4f>(const float* from, Index stride)
{
  EIGEN_ALIGN16 float af[4];
  af[0] = from[0*stride];
  af[1] = from[1*stride];
  af[2] = from[2*stride];
  af[3] = from[3*stride];
 return pload<Packet4f>(af);
}
template<> EIGEN_DEVICE_FUNC inline Packet4i pgather<int, Packet4i>(const int* from, Index stride)
{
  EIGEN_ALIGN16 int ai[4];
  ai[0] = from[0*stride];
  ai[1] = from[1*stride];
  ai[2] = from[2*stride];
  ai[3] = from[3*stride];
 return pload<Packet4i>(ai);
}
template<> EIGEN_DEVICE_FUNC inline Packet8s pgather<short int, Packet8s>(const short int* from, Index stride)
{
  EIGEN_ALIGN16 short int ai[8];
  ai[0] = from[0*stride];
  ai[1] = from[1*stride];
  ai[2] = from[2*stride];
  ai[3] = from[3*stride];
  ai[4] = from[4*stride];
  ai[5] = from[5*stride];
  ai[6] = from[6*stride];
  ai[7] = from[7*stride];
  return pload<Packet8s>(ai);
}

template<> EIGEN_DEVICE_FUNC inline Packet8us pgather<unsigned short int, Packet8us>(const unsigned short int* from, Index stride)
{
  EIGEN_ALIGN16 unsigned short int ai[8];
  ai[0] = from[0*stride];
  ai[1] = from[1*stride];
  ai[2] = from[2*stride];
  ai[3] = from[3*stride];
  ai[4] = from[4*stride];
  ai[5] = from[5*stride];
  ai[6] = from[6*stride];
  ai[7] = from[7*stride];
  return pload<Packet8us>(ai);
}

template<> EIGEN_DEVICE_FUNC inline Packet16c pgather<int8_t, Packet16c>(const int8_t* from, Index stride)
{
  EIGEN_ALIGN16 int8_t ai[16];
  ai[0] = from[0*stride];
  ai[1] = from[1*stride];
  ai[2] = from[2*stride];
  ai[3] = from[3*stride];
  ai[4] = from[4*stride];
  ai[5] = from[5*stride];
  ai[6] = from[6*stride];
  ai[7] = from[7*stride];
  ai[8] = from[8*stride];
  ai[9] = from[9*stride];
  ai[10] = from[10*stride];
  ai[11] = from[11*stride];
  ai[12] = from[12*stride];
  ai[13] = from[13*stride];
  ai[14] = from[14*stride];
  ai[15] = from[15*stride];
  return pload<Packet16c>(ai);
}

template<> EIGEN_DEVICE_FUNC inline Packet16uc pgather<uint8_t, Packet16uc>(const uint8_t* from, Index stride)
{
  EIGEN_ALIGN16 uint8_t ai[16];
  ai[0] = from[0*stride];
  ai[1] = from[1*stride];
  ai[2] = from[2*stride];
  ai[3] = from[3*stride];
  ai[4] = from[4*stride];
  ai[5] = from[5*stride];
  ai[6] = from[6*stride];
  ai[7] = from[7*stride];
  ai[8] = from[8*stride];
  ai[9] = from[9*stride];
  ai[10] = from[10*stride];
  ai[11] = from[11*stride];
  ai[12] = from[12*stride];
  ai[13] = from[13*stride];
  ai[14] = from[14*stride];
  ai[15] = from[15*stride];
  return pload<Packet16uc>(ai);
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<float, Packet4f>(float* to, const Packet4f& from, Index stride)
{
  EIGEN_ALIGN16 float af[4];
  pstore<float>(af, from);
  to[0*stride] = af[0];
  to[1*stride] = af[1];
  to[2*stride] = af[2];
  to[3*stride] = af[3];
}
template<> EIGEN_DEVICE_FUNC inline void pscatter<int, Packet4i>(int* to, const Packet4i& from, Index stride)
{
  EIGEN_ALIGN16 int ai[4];
  pstore<int>((int *)ai, from);
  to[0*stride] = ai[0];
  to[1*stride] = ai[1];
  to[2*stride] = ai[2];
  to[3*stride] = ai[3];
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<short int, Packet8s>(short int* to, const Packet8s& from, Index stride)
{
  EIGEN_ALIGN16 short int ai[8];
  pstore<short int>((short int *)ai, from);
  to[0*stride] = ai[0];
  to[1*stride] = ai[1];
  to[2*stride] = ai[2];
  to[3*stride] = ai[3];
  to[4*stride] = ai[4];
  to[5*stride] = ai[5];
  to[6*stride] = ai[6];
  to[7*stride] = ai[7];
}

template<> EIGEN_DEVICE_FUNC inline void pscatter<unsigned short int, Packet8us>(unsigned short int* to, const Packet8us& from, Index stride)
{
  EIGEN_ALIGN16 unsigned short int ai[8];
  pstore<unsigned short int>((unsigned short int *)ai, from);
  to[0*stride] = ai[0];
  to[1*stride] = ai[1];
  to[2*stride] = ai[2];
  to[3*stride] = ai[3];
  to[4*stride] = ai[4];
  to[5*stride] = ai[5];
  to[6*stride] = ai[6];
  to[7*stride] = ai[7];
}

template<> EIGEN_STRONG_INLINE Packet4f   plset<Packet4f>(const float&     a) { return pset1<Packet4f>(a) + p4f_COUNTDOWN;  }
template<> EIGEN_STRONG_INLINE Packet4i   plset<Packet4i>(const int&       a) { return pset1<Packet4i>(a) + p4i_COUNTDOWN;  }
template<> EIGEN_STRONG_INLINE Packet8s   plset<Packet8s>(const short int& a) { return pset1<Packet8s>(a) + p8s_COUNTDOWN; }
template<> EIGEN_STRONG_INLINE Packet8us  plset<Packet8us>(const unsigned short int& a) { return pset1<Packet8us>(a) + p8us_COUNTDOWN; }
template<> EIGEN_STRONG_INLINE Packet16c  plset<Packet16c>(const int8_t& a)   { return pset1<Packet16c>(a) + p16c_COUNTDOWN; }
template<> EIGEN_STRONG_INLINE Packet16uc plset<Packet16uc>(const uint8_t& a)   { return pset1<Packet16uc>(a) + p16uc_COUNTDOWN; }

template<> EIGEN_STRONG_INLINE Packet4f   padd<Packet4f>  (const Packet4f&   a, const Packet4f&   b) { return a + b; }
template<> EIGEN_STRONG_INLINE Packet4i   padd<Packet4i>  (const Packet4i&   a, const Packet4i&   b) { return a + b; }
template<> EIGEN_STRONG_INLINE Packet8s   padd<Packet8s>  (const Packet8s&   a, const Packet8s&   b) { return a + b; }
template<> EIGEN_STRONG_INLINE Packet8us  padd<Packet8us> (const Packet8us&  a, const Packet8us&  b) { return a + b; }
template<> EIGEN_STRONG_INLINE Packet16c  padd<Packet16c> (const Packet16c&  a, const Packet16c&  b) { return a + b; }
template<> EIGEN_STRONG_INLINE Packet16uc padd<Packet16uc>(const Packet16uc& a, const Packet16uc& b) { return a + b; }

template<> EIGEN_STRONG_INLINE Packet4f   psub<Packet4f>  (const Packet4f&   a, const Packet4f&   b) { return a - b; }
template<> EIGEN_STRONG_INLINE Packet4i   psub<Packet4i>  (const Packet4i&   a, const Packet4i&   b) { return a - b; }
template<> EIGEN_STRONG_INLINE Packet16c  psub<Packet16c> (const Packet16c&  a, const Packet16c&  b) { return a - b; }
template<> EIGEN_STRONG_INLINE Packet16uc psub<Packet16uc>(const Packet16uc& a, const Packet16uc& b) { return a - b; }

template<> EIGEN_STRONG_INLINE Packet4f pnegate(const Packet4f& a) { return p4f_ZERO - a; }
template<> EIGEN_STRONG_INLINE Packet4i pnegate(const Packet4i& a) { return p4i_ZERO - a; }

template<> EIGEN_STRONG_INLINE Packet4f pconj(const Packet4f& a) { return a; }
template<> EIGEN_STRONG_INLINE Packet4i pconj(const Packet4i& a) { return a; }

template<> EIGEN_STRONG_INLINE Packet4f   pmul<Packet4f>  (const Packet4f&   a, const Packet4f&   b) { return vec_madd(a,b, p4f_MZERO); }
template<> EIGEN_STRONG_INLINE Packet4i   pmul<Packet4i>  (const Packet4i&   a, const Packet4i&   b) { return a * b; }
template<> EIGEN_STRONG_INLINE Packet16c  pmul<Packet16c> (const Packet16c&  a, const Packet16c&  b) { return vec_mul(a,b); }
template<> EIGEN_STRONG_INLINE Packet16uc pmul<Packet16uc>(const Packet16uc& a, const Packet16uc& b) { return vec_mul(a,b); }

template<> EIGEN_STRONG_INLINE Packet4f pdiv<Packet4f>(const Packet4f& a, const Packet4f& b)
{
#ifndef __VSX__  // VSX actually provides a div instruction
  Packet4f t, y_0, y_1;

  // Altivec does not offer a divide instruction, we have to do a reciprocal approximation
  y_0 = vec_re(b);

  // Do one Newton-Raphson iteration to get the needed accuracy
  t   = vec_nmsub(y_0, b, p4f_ONE);
  y_1 = vec_madd(y_0, t, y_0);

  return vec_madd(a, y_1, p4f_MZERO);
#else
  return vec_div(a, b);
#endif
}

template<> EIGEN_STRONG_INLINE Packet4i pdiv<Packet4i>(const Packet4i& /*a*/, const Packet4i& /*b*/)
{ eigen_assert(false && "packet integer division are not supported by AltiVec");
  return pset1<Packet4i>(0);
}

// for some weird raisons, it has to be overloaded for packet of integers
template<> EIGEN_STRONG_INLINE Packet4f pmadd(const Packet4f& a, const Packet4f& b, const Packet4f& c) { return vec_madd(a,b,c); }
template<> EIGEN_STRONG_INLINE Packet4i pmadd(const Packet4i& a, const Packet4i& b, const Packet4i& c) { return a*b + c; }

template<> EIGEN_STRONG_INLINE Packet4f pmin<Packet4f>(const Packet4f& a, const Packet4f& b)
{
  #ifdef __VSX__
  // NOTE: about 10% slower than vec_min, but consistent with std::min and SSE regarding NaN
  Packet4f ret;
  __asm__ ("xvcmpgesp %x0,%x1,%x2\n\txxsel %x0,%x1,%x2,%x0" : "=&wa" (ret) : "wa" (a), "wa" (b));
  return ret;
  #else
  return vec_min(a, b);
  #endif
}
template<> EIGEN_STRONG_INLINE Packet4i pmin<Packet4i>(const Packet4i& a, const Packet4i& b) { return vec_min(a, b); }
template<> EIGEN_STRONG_INLINE Packet8s pmin<Packet8s>(const Packet8s& a, const Packet8s& b) { return vec_min(a, b); }
template<> EIGEN_STRONG_INLINE Packet8us pmin<Packet8us>(const Packet8us& a, const Packet8us& b) { return vec_min(a, b); }
template<> EIGEN_STRONG_INLINE Packet16c pmin<Packet16c>(const Packet16c& a, const Packet16c& b) { return vec_min(a, b); }
template<> EIGEN_STRONG_INLINE Packet16uc pmin<Packet16uc>(const Packet16uc& a, const Packet16uc& b) { return vec_min(a, b); }

template<> EIGEN_STRONG_INLINE Packet4f pmax<Packet4f>(const Packet4f& a, const Packet4f& b)
{
  #ifdef __VSX__
  // NOTE: about 10% slower than vec_max, but consistent with std::max and SSE regarding NaN
  Packet4f ret;
  __asm__ ("xvcmpgtsp %x0,%x2,%x1\n\txxsel %x0,%x1,%x2,%x0" : "=&wa" (ret) : "wa" (a), "wa" (b));
  return ret;
  #else
  return vec_max(a, b);
  #endif
}
template<> EIGEN_STRONG_INLINE Packet4i pmax<Packet4i>(const Packet4i& a, const Packet4i& b) { return vec_max(a, b); }
template<> EIGEN_STRONG_INLINE Packet8s pmax<Packet8s>(const Packet8s& a, const Packet8s& b) { return vec_max(a, b); }
template<> EIGEN_STRONG_INLINE Packet8us pmax<Packet8us>(const Packet8us& a, const Packet8us& b) { return vec_max(a, b); }
template<> EIGEN_STRONG_INLINE Packet16c pmax<Packet16c>(const Packet16c& a, const Packet16c& b) { return vec_max(a, b); }
template<> EIGEN_STRONG_INLINE Packet16uc pmax<Packet16uc>(const Packet16uc& a, const Packet16uc& b) { return vec_max(a, b); }

template<> EIGEN_STRONG_INLINE Packet4f pcmp_le(const Packet4f& a, const Packet4f& b) { return reinterpret_cast<Packet4f>(vec_cmple(a,b)); }
template<> EIGEN_STRONG_INLINE Packet4f pcmp_lt(const Packet4f& a, const Packet4f& b) { return reinterpret_cast<Packet4f>(vec_cmplt(a,b)); }
template<> EIGEN_STRONG_INLINE Packet4f pcmp_eq(const Packet4f& a, const Packet4f& b) { return reinterpret_cast<Packet4f>(vec_cmpeq(a,b)); }
template<> EIGEN_STRONG_INLINE Packet4f pcmp_lt_or_nan(const Packet4f& a, const Packet4f& b) {
  Packet4f c = reinterpret_cast<Packet4f>(vec_cmpge(a,b));
  return vec_nor(c,c);
}
template<> EIGEN_STRONG_INLINE Packet4i pcmp_eq(const Packet4i& a, const Packet4i& b) { return reinterpret_cast<Packet4i>(vec_cmpeq(a,b)); }

template<> EIGEN_STRONG_INLINE Packet4f pand<Packet4f>(const Packet4f& a, const Packet4f& b) { return vec_and(a, b); }
template<> EIGEN_STRONG_INLINE Packet4i pand<Packet4i>(const Packet4i& a, const Packet4i& b) { return vec_and(a, b); }

template<> EIGEN_STRONG_INLINE Packet4f por<Packet4f>(const Packet4f& a, const Packet4f& b) { return vec_or(a, b); }
template<> EIGEN_STRONG_INLINE Packet4i por<Packet4i>(const Packet4i& a, const Packet4i& b) { return vec_or(a, b); }

template<> EIGEN_STRONG_INLINE Packet4f pxor<Packet4f>(const Packet4f& a, const Packet4f& b) { return vec_xor(a, b); }
template<> EIGEN_STRONG_INLINE Packet4i pxor<Packet4i>(const Packet4i& a, const Packet4i& b) { return vec_xor(a, b); }

template<> EIGEN_STRONG_INLINE Packet4f pandnot<Packet4f>(const Packet4f& a, const Packet4f& b) { return vec_and(a, vec_nor(b, b)); }
template<> EIGEN_STRONG_INLINE Packet4i pandnot<Packet4i>(const Packet4i& a, const Packet4i& b) { return vec_and(a, vec_nor(b, b)); }

template<> EIGEN_STRONG_INLINE Packet4f pselect(const Packet4f& mask, const Packet4f& a, const Packet4f& b) {
  return vec_sel(b, a, reinterpret_cast<Packet4ui>(mask));
}
template<> EIGEN_STRONG_INLINE Packet4f pround<Packet4f>(const Packet4f& a) {
    Packet4f t = vec_add(reinterpret_cast<Packet4f>(vec_or(vec_and(reinterpret_cast<Packet4ui>(a), p4ui_SIGN), p4ui_PREV0DOT5)), a);
    Packet4f res;

    __asm__("vrfiz %0, %1\n\t"
        : "=v" (res)
        : "v" (t));

    return res;
}
template<> EIGEN_STRONG_INLINE Packet4f pceil<Packet4f>(const  Packet4f& a) { return vec_ceil(a); }
template<> EIGEN_STRONG_INLINE Packet4f pfloor<Packet4f>(const Packet4f& a) { return vec_floor(a); }

#ifdef _BIG_ENDIAN
template<> EIGEN_STRONG_INLINE Packet4f ploadu<Packet4f>(const float* from)
{
  EIGEN_DEBUG_ALIGNED_LOAD
  Packet16uc MSQ, LSQ;
  Packet16uc mask;
  MSQ = vec_ld(0, (unsigned char *)from);          // most significant quadword
  LSQ = vec_ld(15, (unsigned char *)from);         // least significant quadword
  mask = vec_lvsl(0, from);                        // create the permute mask
  return (Packet4f) vec_perm(MSQ, LSQ, mask);           // align the data

}
template<> EIGEN_STRONG_INLINE Packet4i ploadu<Packet4i>(const int* from)
{
  EIGEN_DEBUG_ALIGNED_LOAD
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  Packet16uc MSQ, LSQ;
  Packet16uc mask;
  MSQ = vec_ld(0, (unsigned char *)from);          // most significant quadword
  LSQ = vec_ld(15, (unsigned char *)from);         // least significant quadword
  mask = vec_lvsl(0, from);                        // create the permute mask
  return (Packet4i) vec_perm(MSQ, LSQ, mask);    // align the data
}
template<> EIGEN_STRONG_INLINE Packet8s ploadu<Packet8s>(const short int* from)
{
  EIGEN_DEBUG_ALIGNED_LOAD
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  Packet16uc MSQ, LSQ;
  Packet16uc mask;
  MSQ = vec_ld(0, (unsigned char *)from);          // most significant quadword
  LSQ = vec_ld(15, (unsigned char *)from);         // least significant quadword
  mask = vec_lvsl(0, from);                        // create the permute mask
  return static_cast<Packet8s>(vec_perm(MSQ, LSQ, mask));    // align the data
}
template<> EIGEN_STRONG_INLINE Packet8us ploadu<Packet8us>(const unsigned short int* from)
{
  EIGEN_DEBUG_ALIGNED_LOAD
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  Packet16uc MSQ, LSQ;
  Packet16uc mask;
  MSQ = vec_ld(0, (unsigned char *)from);          // most significant quadword
  LSQ = vec_ld(15, (unsigned char *)from);         // least significant quadword
  mask = vec_lvsl(0, from);                        // create the permute mask
  return static_cast<Packet8us>(vec_perm(MSQ, LSQ, mask));    // align the data
}
template<> EIGEN_STRONG_INLINE Packet16c ploadu<Packet16c>(const char* from)
{
  EIGEN_DEBUG_ALIGNED_LOAD
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  Packet16uc MSQ, LSQ;
  Packet16uc mask;
  MSQ = vec_ld(0, from);          // most significant quadword
  LSQ = vec_ld(15, from);         // least significant quadword
  mask = vec_lvsl(0, from);                        // create the permute mask
  return static_cast<Packet16c>(vec_perm(MSQ, LSQ, mask));    // align the data
}

template<> EIGEN_STRONG_INLINE Packet16uc ploadu<Packet16uc>(const unsigned char* from)
{
  EIGEN_DEBUG_ALIGNED_LOAD
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  Packet16uc MSQ, LSQ;
  Packet16uc mask;
  MSQ = vec_ld(0, from);          // most significant quadword
  LSQ = vec_ld(15, from);         // least significant quadword
  mask = vec_lvsl(0, from);                        // create the permute mask
  return static_cast<Packet16uc>(vec_perm(MSQ, LSQ, mask));    // align the data
}
#else
// We also need to redefine little endian loading of Packet4i/Packet4f using VSX
template<> EIGEN_STRONG_INLINE Packet4i ploadu<Packet4i>(const int* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return vec_xl(0, from);
}
template<> EIGEN_STRONG_INLINE Packet4f ploadu<Packet4f>(const float* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return vec_xl(0, from);
}
template<> EIGEN_STRONG_INLINE Packet8s ploadu<Packet8s>(const short int* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return vec_vsx_ld(0, from);
}
template<> EIGEN_STRONG_INLINE Packet8us ploadu<Packet8us>(const unsigned short int* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return vec_vsx_ld(0, from);
}
template<> EIGEN_STRONG_INLINE Packet16c ploadu<Packet16c>(const int8_t* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return vec_vsx_ld(0, from);
}
template<> EIGEN_STRONG_INLINE Packet16uc ploadu<Packet16uc>(const uint8_t* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return vec_vsx_ld(0, from);
}
#endif

template<> EIGEN_STRONG_INLINE Packet4f ploaddup<Packet4f>(const float*   from)
{
  Packet4f p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet4f>(from);
  else                                  p = ploadu<Packet4f>(from);
  return vec_perm(p, p, p16uc_DUPLICATE32_HI);
}

template<> EIGEN_STRONG_INLINE Packet4i ploaddup<Packet4i>(const int*     from)
{
  Packet4i p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet4i>(from);
  else                                  p = ploadu<Packet4i>(from);
  return vec_perm(p, p, p16uc_DUPLICATE32_HI);
}

template<> EIGEN_STRONG_INLINE Packet8s ploaddup<Packet8s>(const short int*     from)
{
  Packet8s p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet8s>(from);
  else                                  p = ploadu<Packet8s>(from);
  return vec_perm(p, p, p16uc_DUPLICATE16_HI);
}

template<> EIGEN_STRONG_INLINE Packet8us ploaddup<Packet8us>(const unsigned short int*     from)
{
  Packet8us p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet8us>(from);
  else                                  p = ploadu<Packet8us>(from);
  return vec_perm(p, p, p16uc_DUPLICATE16_HI);
}

template<> EIGEN_STRONG_INLINE Packet8s ploadquad<Packet8s>(const short int*     from)
{
  Packet8s p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet8s>(from);
  else                                  p = ploadu<Packet8s>(from);
  return vec_perm(p, p, p16uc_QUADRUPLICATE16_HI);
}

template<> EIGEN_STRONG_INLINE Packet8us ploadquad<Packet8us>(const unsigned short int*     from)
{
  Packet8us p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet8us>(from);
  else                                  p = ploadu<Packet8us>(from);
  return vec_perm(p, p, p16uc_QUADRUPLICATE16_HI);
}

template<> EIGEN_STRONG_INLINE Packet16c ploaddup<Packet16c>(const int8_t*     from)
{
  Packet16c p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet16c>(from);
  else                                  p = ploadu<Packet16c>(from);
  return vec_perm(p, p, p16uc_DUPLICATE8_HI);
}

template<> EIGEN_STRONG_INLINE Packet16uc ploaddup<Packet16uc>(const uint8_t*     from)
{
  Packet16uc p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet16uc>(from);
  else                                  p = ploadu<Packet16uc>(from);
  return vec_perm(p, p, p16uc_DUPLICATE8_HI);
}

#ifdef _BIG_ENDIAN
template<> EIGEN_STRONG_INLINE void pstoreu<float>(float*  to, const Packet4f& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  // Warning: not thread safe!
  Packet16uc MSQ, LSQ, edges;
  Packet16uc edgeAlign, align;

  MSQ = vec_ld(0, (unsigned char *)to);                     // most significant quadword
  LSQ = vec_ld(15, (unsigned char *)to);                    // least significant quadword
  edgeAlign = vec_lvsl(0, to);                              // permute map to extract edges
  edges=vec_perm(LSQ,MSQ,edgeAlign);                        // extract the edges
  align = vec_lvsr( 0, to );                                // permute map to misalign data
  MSQ = vec_perm(edges,(Packet16uc)from,align);             // misalign the data (MSQ)
  LSQ = vec_perm((Packet16uc)from,edges,align);             // misalign the data (LSQ)
  vec_st( LSQ, 15, (unsigned char *)to );                   // Store the LSQ part first
  vec_st( MSQ, 0, (unsigned char *)to );                    // Store the MSQ part
}
template<> EIGEN_STRONG_INLINE void pstoreu<int>(int*      to, const Packet4i& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  // Warning: not thread safe!
  Packet16uc MSQ, LSQ, edges;
  Packet16uc edgeAlign, align;

  MSQ = vec_ld(0, (unsigned char *)to);                     // most significant quadword
  LSQ = vec_ld(15, (unsigned char *)to);                    // least significant quadword
  edgeAlign = vec_lvsl(0, to);                              // permute map to extract edges
  edges=vec_perm(LSQ, MSQ, edgeAlign);                      // extract the edges
  align = vec_lvsr( 0, to );                                // permute map to misalign data
  MSQ = vec_perm(edges, (Packet16uc) from, align);          // misalign the data (MSQ)
  LSQ = vec_perm((Packet16uc) from, edges, align);          // misalign the data (LSQ)
  vec_st( LSQ, 15, (unsigned char *)to );                   // Store the LSQ part first
  vec_st( MSQ, 0, (unsigned char *)to );                    // Store the MSQ part
}
template<> EIGEN_STRONG_INLINE void pstoreu<short int>(short int*      to, const Packet8s& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  // Warning: not thread safe!
  Packet16uc MSQ, LSQ, edges;
  Packet16uc edgeAlign, align;

  MSQ = vec_ld(0, (unsigned char *)to);                     // most significant quadword
  LSQ = vec_ld(15, (unsigned char *)to);                    // least significant quadword
  edgeAlign = vec_lvsl(0, to);                              // permute map to extract edges
  edges = vec_perm(LSQ, MSQ, edgeAlign);                      // extract the edges
  align = vec_lvsr( 0, to );                                // permute map to misalign data
  MSQ = vec_perm(edges, (Packet16uc) from, align);          // misalign the data (MSQ)
  LSQ = vec_perm((Packet16uc) from, edges, align);          // misalign the data (LSQ)
  vec_st( LSQ, 15, (unsigned char *)to );                   // Store the LSQ part first
  vec_st( MSQ, 0, (unsigned char *)to );                    // Store the MSQ part
}
template<> EIGEN_STRONG_INLINE void pstoreu<unsigned short int>(unsigned short int*      to, const Packet8us& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  // Warning: not thread safe!
  Packet16uc MSQ, LSQ, edges;
  Packet16uc edgeAlign, align;

  MSQ = vec_ld(0, (unsigned char *)to);                     // most significant quadword
  LSQ = vec_ld(15, (unsigned char *)to);                    // least significant quadword
  edgeAlign = vec_lvsl(0, to);                              // permute map to extract edges
  edges = vec_perm(LSQ, MSQ, edgeAlign);                      // extract the edges
  align = vec_lvsr( 0, to );                                // permute map to misalign data
  MSQ = vec_perm(edges, (Packet16uc) from, align);          // misalign the data (MSQ)
  LSQ = vec_perm((Packet16uc) from, edges, align);          // misalign the data (LSQ)
  vec_st( LSQ, 15, (unsigned char *)to );                   // Store the LSQ part first
  vec_st( MSQ, 0, (unsigned char *)to );                    // Store the MSQ part
}

template<> EIGEN_STRONG_INLINE void pstoreu<char>(char*      to, const Packet16c& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  // Warning: not thread safe!
  Packet16uc MSQ, LSQ, edges;
  Packet16uc edgeAlign, align;

  MSQ = vec_ld(0, to);                     // most significant quadword
  LSQ = vec_ld(15,to);                    // least significant quadword
  edgeAlign = vec_lvsl(0, to);                              // permute map to extract edges
  edges=vec_perm(LSQ, MSQ, edgeAlign);                      // extract the edges
  align = vec_lvsr( 0, to );                                // permute map to misalign data
  MSQ = vec_perm(edges, (Packet16uc) from, align);          // misalign the data (MSQ)
  LSQ = vec_perm((Packet16uc) from, edges, align);          // misalign the data (LSQ)
  vec_st( LSQ, 15, to );                   // Store the LSQ part first
  vec_st( MSQ, 0, to );                    // Store the MSQ part
}
template<> EIGEN_STRONG_INLINE void pstoreu<unsigned char>(unsigned char*      to, const Packet16uc& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  // Taken from http://developer.apple.com/hardwaredrivers/ve/alignment.html
  // Warning: not thread safe!
  Packet16uc MSQ, LSQ, edges;
  Packet16uc edgeAlign, align;

  MSQ = vec_ld(0, to);                     // most significant quadword
  LSQ = vec_ld(15,to);                    // least significant quadword
  edgeAlign = vec_lvsl(0, to);                              // permute map to extract edges
  edges=vec_perm(LSQ, MSQ, edgeAlign);                      // extract the edges
  align = vec_lvsr( 0, to );                                // permute map to misalign data
  MSQ = vec_perm(edges, (Packet16uc) from, align);          // misalign the data (MSQ)
  LSQ = vec_perm((Packet16uc) from, edges, align);          // misalign the data (LSQ)
  vec_st( LSQ, 15, to );                   // Store the LSQ part first
  vec_st( MSQ, 0, to );                    // Store the MSQ part
}
#else
// We also need to redefine little endian loading of Packet4i/Packet4f using VSX
template<> EIGEN_STRONG_INLINE void pstoreu<int>(int*       to, const Packet4i& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  vec_xst(from, 0, to);
}
template<> EIGEN_STRONG_INLINE void pstoreu<float>(float*   to, const Packet4f& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  vec_xst(from, 0, to);
}
template<> EIGEN_STRONG_INLINE void pstoreu<short int>(short int*       to, const Packet8s& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  /*GCC provides a commonly used synonym for vec_xst called vec_vsx_st.
   * Although these have the same behavior,
   *  only vec_xst is guaranteed to be portable across compliant compilers
   *  vec_xst should be preferred. */
  vec_xst(from, 0, to);
}
template<> EIGEN_STRONG_INLINE void pstoreu<unsigned short int>(unsigned short int*       to, const Packet8us& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  /*GCC provides a commonly used synonym for vec_xst called vec_vsx_st.
   * Although these have the same behavior,
   *  only vec_xst is guaranteed to be portable across compliant compilers
   *  vec_xst should be preferred. */
  vec_xst(from, 0, to);
}
template<> EIGEN_STRONG_INLINE void pstoreu<int8_t>(int8_t*   to, const Packet16c& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  vec_vsx_st(from, 0, to);
}
template<> EIGEN_STRONG_INLINE void pstoreu<uint8_t>(uint8_t*   to, const Packet16uc& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  vec_vsx_st(from, 0, to);
}
#endif

template<> EIGEN_STRONG_INLINE void prefetch<float>(const float* addr)    { EIGEN_PPC_PREFETCH(addr); }
template<> EIGEN_STRONG_INLINE void prefetch<int>(const int*     addr)    { EIGEN_PPC_PREFETCH(addr); }

template<> EIGEN_STRONG_INLINE float  pfirst<Packet4f>(const Packet4f& a) { EIGEN_ALIGN16 float x; vec_ste(a, 0, &x); return x; }
template<> EIGEN_STRONG_INLINE int    pfirst<Packet4i>(const Packet4i& a) { EIGEN_ALIGN16 int   x; vec_ste(a, 0, &x); return x; }

template<> EIGEN_STRONG_INLINE short int pfirst<Packet8s>(const Packet8s& a) { 
  EIGEN_ALIGN16 short int x;
  vec_ste(a, 0, &x);
  return x;
}

template<> EIGEN_STRONG_INLINE unsigned short int pfirst<Packet8us>(const Packet8us& a) { 
  EIGEN_ALIGN16 unsigned short int x;
  vec_ste(a, 0, &x);
  return x;
}

template<> EIGEN_STRONG_INLINE int8_t pfirst<Packet16c>(const Packet16c& a)
{
  EIGEN_ALIGN16 int8_t x;
  vec_ste(a, 0, &x);
  return x;
}
template<> EIGEN_STRONG_INLINE uint8_t pfirst<Packet16uc>(const Packet16uc& a)
{
  EIGEN_ALIGN16 uint8_t x;
  vec_ste(a, 0, &x);
  return x;
}

template<> EIGEN_STRONG_INLINE Packet4f preverse(const Packet4f& a)
{
  return reinterpret_cast<Packet4f>(vec_perm(reinterpret_cast<Packet16uc>(a), reinterpret_cast<Packet16uc>(a), p16uc_REVERSE32));
}
template<> EIGEN_STRONG_INLINE Packet4i preverse(const Packet4i& a)
{
  return reinterpret_cast<Packet4i>(vec_perm(reinterpret_cast<Packet16uc>(a), reinterpret_cast<Packet16uc>(a), p16uc_REVERSE32));
}
template<> EIGEN_STRONG_INLINE Packet8s preverse(const Packet8s& a)
{
  return reinterpret_cast<Packet8s>(vec_perm(reinterpret_cast<Packet16uc>(a), reinterpret_cast<Packet16uc>(a), p16uc_REVERSE16));
}
template<> EIGEN_STRONG_INLINE Packet8us preverse(const Packet8us& a)
{
  return reinterpret_cast<Packet8us>(vec_perm(reinterpret_cast<Packet16uc>(a), reinterpret_cast<Packet16uc>(a), p16uc_REVERSE16));
}
template<> EIGEN_STRONG_INLINE Packet16c preverse(const Packet16c& a)
{
  return vec_perm(a, a, p16uc_REVERSE8);
}
template<> EIGEN_STRONG_INLINE Packet16uc preverse(const Packet16uc& a)
{
  return vec_perm(a, a, p16uc_REVERSE8);
}

template<> EIGEN_STRONG_INLINE Packet4f pabs(const Packet4f& a) { return vec_abs(a); }
template<> EIGEN_STRONG_INLINE Packet4i pabs(const Packet4i& a) { return vec_abs(a); }
template<> EIGEN_STRONG_INLINE Packet8s pabs(const Packet8s& a) { return vec_abs(a); }
template<> EIGEN_STRONG_INLINE Packet8us pabs(const Packet8us& a) { return a; }
template<> EIGEN_STRONG_INLINE Packet16c pabs(const Packet16c& a) { return vec_abs(a); }
template<> EIGEN_STRONG_INLINE Packet16uc pabs(const Packet16uc& a) { return a; }

template<int N> EIGEN_STRONG_INLINE Packet4i parithmetic_shift_right(Packet4i a)
{ return vec_sra(a,reinterpret_cast<Packet4ui>(pset1<Packet4i>(N))); }
template<int N> EIGEN_STRONG_INLINE Packet4i plogical_shift_right(Packet4i a)
{ return vec_sr(a,reinterpret_cast<Packet4ui>(pset1<Packet4i>(N))); }
template<int N> EIGEN_STRONG_INLINE Packet4i plogical_shift_left(Packet4i a)
{ return vec_sl(a,reinterpret_cast<Packet4ui>(pset1<Packet4i>(N))); }

template<> EIGEN_STRONG_INLINE Packet4f pfrexp<Packet4f>(const Packet4f& a, Packet4f& exponent) {
  return pfrexp_float(a,exponent);
}

template<> EIGEN_STRONG_INLINE Packet4f pldexp<Packet4f>(const Packet4f& a, const Packet4f& exponent) {
  return pldexp_float(a,exponent);
}

template<> EIGEN_STRONG_INLINE float predux<Packet4f>(const Packet4f& a)
{
  Packet4f b, sum;
  b   = vec_sld(a, a, 8);
  sum = a + b;
  b   = vec_sld(sum, sum, 4);
  sum += b;
  return pfirst(sum);
}

template<> EIGEN_STRONG_INLINE int predux<Packet4i>(const Packet4i& a)
{
  Packet4i sum;
  sum = vec_sums(a, p4i_ZERO);
#ifdef _BIG_ENDIAN
  sum = vec_sld(sum, p4i_ZERO, 12);
#else
  sum = vec_sld(p4i_ZERO, sum, 4);
#endif
  return pfirst(sum);
}

template<> EIGEN_STRONG_INLINE short int predux<Packet8s>(const Packet8s& a)
{
  union{
    Packet8s v;
    short int n[8];
  } vt;
  vt.v = a;

  EIGEN_ALIGN16 int  first_loader[4] = { vt.n[0], vt.n[1], vt.n[2], vt.n[3] };
  EIGEN_ALIGN16 int second_loader[4] = { vt.n[4], vt.n[5], vt.n[6], vt.n[7] };
  Packet4i first_half  = pload<Packet4i>(first_loader);
  Packet4i second_half = pload<Packet4i>(second_loader);

  return static_cast<short int>(predux(first_half) + predux(second_half));
}

template<> EIGEN_STRONG_INLINE unsigned short int predux<Packet8us>(const Packet8us& a)
{
  union{
    Packet8us v;
    unsigned short int n[8];
  } vt;
  vt.v = a;

  //There is no predux for Packet4ui. So we are intentionally using int
  EIGEN_ALIGN16 int first_loader[4]  = { vt.n[0], vt.n[1], vt.n[2], vt.n[3] };
  EIGEN_ALIGN16 int second_loader[4] = { vt.n[4], vt.n[5], vt.n[6], vt.n[7] };
  Packet4i first_half  = pload<Packet4i>(first_loader);
  Packet4i second_half = pload<Packet4i>(second_loader);

  return static_cast<unsigned short int>(predux(first_half) + predux(second_half));
}

template<> EIGEN_STRONG_INLINE int8_t predux<Packet16c>(const Packet16c& a)
{
  union{
    Packet16c v;
    int8_t n[16];
  } vt;
  vt.v = a;

  EIGEN_ALIGN16 int first_loader[4] = { vt.n[0], vt.n[1], vt.n[2], vt.n[3] };
  EIGEN_ALIGN16 int second_loader[4] = { vt.n[4], vt.n[5], vt.n[6], vt.n[7] };
  EIGEN_ALIGN16 int third_loader[4] = { vt.n[8], vt.n[9], vt.n[10], vt.n[11] };
  EIGEN_ALIGN16 int fourth_loader[4] = { vt.n[12], vt.n[13], vt.n[14], vt.n[15] };

  Packet4i first_quarter = pload<Packet4i>(first_loader);
  Packet4i second_quarter = pload<Packet4i>(second_loader);
  Packet4i third_quarter = pload<Packet4i>(third_loader);
  Packet4i fourth_quarter = pload<Packet4i>(fourth_loader);

  return static_cast<int8_t>(predux(first_quarter) + predux(second_quarter)
		                  + predux(third_quarter) + predux(fourth_quarter));
}

template<> EIGEN_STRONG_INLINE uint8_t predux<Packet16uc>(const Packet16uc& a)
{
  union{
    Packet16uc v;
    uint8_t n[16];
  } vt;
  vt.v = a;

  EIGEN_ALIGN16 int first_loader[4] = { vt.n[0], vt.n[1], vt.n[2], vt.n[3] };
  EIGEN_ALIGN16 int second_loader[4] = { vt.n[4], vt.n[5], vt.n[6], vt.n[7] };
  EIGEN_ALIGN16 int third_loader[4] = { vt.n[8], vt.n[9], vt.n[10], vt.n[11] };
  EIGEN_ALIGN16 int fourth_loader[4] = { vt.n[12], vt.n[13], vt.n[14], vt.n[15] };

  Packet4i first_quarter = pload<Packet4i>(first_loader);
  Packet4i second_quarter = pload<Packet4i>(second_loader);
  Packet4i third_quarter = pload<Packet4i>(third_loader);
  Packet4i fourth_quarter = pload<Packet4i>(fourth_loader);


  return static_cast<uint8_t>(predux(first_quarter) + predux(second_quarter)
		                  + predux(third_quarter) + predux(fourth_quarter));
}


// Other reduction functions:
// mul
template<> EIGEN_STRONG_INLINE float predux_mul<Packet4f>(const Packet4f& a)
{
  Packet4f prod;
  prod = pmul(a, vec_sld(a, a, 8));
  return pfirst(pmul(prod, vec_sld(prod, prod, 4)));
}

template<> EIGEN_STRONG_INLINE int predux_mul<Packet4i>(const Packet4i& a)
{
  EIGEN_ALIGN16 int aux[4];
  pstore(aux, a);
  return aux[0] * aux[1] * aux[2] * aux[3];
}

template<> EIGEN_STRONG_INLINE short int predux_mul<Packet8s>(const Packet8s& a)
{
  Packet8s pair, quad, octo;

  pair = vec_mul(a, vec_sld(a, a, 8));
  quad = vec_mul(pair, vec_sld(pair, pair, 4));
  octo = vec_mul(quad, vec_sld(quad, quad, 2));

  return pfirst(octo);
}

template<> EIGEN_STRONG_INLINE unsigned short int predux_mul<Packet8us>(const Packet8us& a)
{
  Packet8us pair, quad, octo;

  pair = vec_mul(a, vec_sld(a, a, 8));
  quad = vec_mul(pair, vec_sld(pair, pair, 4));
  octo = vec_mul(quad, vec_sld(quad, quad, 2));

  return pfirst(octo);
}

template<> EIGEN_STRONG_INLINE int8_t predux_mul<Packet16c>(const Packet16c& a)
{
  Packet16c pair, quad, octo, result;

  pair = vec_mul(a, vec_sld(a, a, 8));
  quad = vec_mul(pair, vec_sld(pair, pair, 4));
  octo = vec_mul(quad, vec_sld(quad, quad, 2));
  result = vec_mul(octo, vec_sld(octo, octo, 1));

  return pfirst(result);
}

template<> EIGEN_STRONG_INLINE uint8_t predux_mul<Packet16uc>(const Packet16uc& a)
{
  Packet16uc pair, quad, octo, result;

  pair = vec_mul(a, vec_sld(a, a, 8));
  quad = vec_mul(pair, vec_sld(pair, pair, 4));
  octo = vec_mul(quad, vec_sld(quad, quad, 2));
  result = vec_mul(octo, vec_sld(octo, octo, 1));

  return pfirst(result);
}

// min
template<> EIGEN_STRONG_INLINE float predux_min<Packet4f>(const Packet4f& a)
{
  Packet4f b, res;
  b = vec_min(a, vec_sld(a, a, 8));
  res = vec_min(b, vec_sld(b, b, 4));
  return pfirst(res);
}

template<> EIGEN_STRONG_INLINE int predux_min<Packet4i>(const Packet4i& a)
{
  Packet4i b, res;
  b = vec_min(a, vec_sld(a, a, 8));
  res = vec_min(b, vec_sld(b, b, 4));
  return pfirst(res);
}

template<> EIGEN_STRONG_INLINE short int predux_min<Packet8s>(const Packet8s& a)
{
  Packet8s pair, quad, octo;
  
  //pair = { Min(a0,a4), Min(a1,a5), Min(a2,a6), Min(a3,a7) }
  pair = vec_min(a, vec_sld(a, a, 8)); 

  //quad = { Min(a0, a4, a2, a6), Min(a1, a5, a3, a7) }
  quad = vec_min(pair, vec_sld(pair, pair, 4));

  //octo = { Min(a0, a4, a2, a6, a1, a5, a3, a7) }
  octo = vec_min(quad, vec_sld(quad, quad, 2));
  return pfirst(octo);
}

template<> EIGEN_STRONG_INLINE unsigned short int predux_min<Packet8us>(const Packet8us& a)
{
  Packet8us pair, quad, octo;
  
  //pair = { Min(a0,a4), Min(a1,a5), Min(a2,a6), Min(a3,a7) }
  pair = vec_min(a, vec_sld(a, a, 8)); 

  //quad = { Min(a0, a4, a2, a6), Min(a1, a5, a3, a7) }
  quad = vec_min(pair, vec_sld(pair, pair, 4));

  //octo = { Min(a0, a4, a2, a6, a1, a5, a3, a7) }
  octo = vec_min(quad, vec_sld(quad, quad, 2));
  return pfirst(octo);
}

template<> EIGEN_STRONG_INLINE int8_t predux_min<Packet16c>(const Packet16c& a)
{
  Packet16c pair, quad, octo, result;

  pair = vec_min(a, vec_sld(a, a, 8));
  quad = vec_min(pair, vec_sld(pair, pair, 4));
  octo = vec_min(quad, vec_sld(quad, quad, 2));
  result = vec_min(octo, vec_sld(octo, octo, 1));

  return pfirst(result);
}

template<> EIGEN_STRONG_INLINE uint8_t predux_min<Packet16uc>(const Packet16uc& a)
{
  Packet16uc pair, quad, octo, result;

  pair = vec_min(a, vec_sld(a, a, 8));
  quad = vec_min(pair, vec_sld(pair, pair, 4));
  octo = vec_min(quad, vec_sld(quad, quad, 2));
  result = vec_min(octo, vec_sld(octo, octo, 1));

  return pfirst(result);
}
// max
template<> EIGEN_STRONG_INLINE float predux_max<Packet4f>(const Packet4f& a)
{
  Packet4f b, res;
  b = vec_max(a, vec_sld(a, a, 8));
  res = vec_max(b, vec_sld(b, b, 4));
  return pfirst(res);
}

template<> EIGEN_STRONG_INLINE int predux_max<Packet4i>(const Packet4i& a)
{
  Packet4i b, res;
  b = vec_max(a, vec_sld(a, a, 8));
  res = vec_max(b, vec_sld(b, b, 4));
  return pfirst(res);
}

template<> EIGEN_STRONG_INLINE short int predux_max<Packet8s>(const Packet8s& a)
{
  Packet8s pair, quad, octo;
  
  //pair = { Max(a0,a4), Max(a1,a5), Max(a2,a6), Max(a3,a7) }
  pair = vec_max(a, vec_sld(a, a, 8)); 

  //quad = { Max(a0, a4, a2, a6), Max(a1, a5, a3, a7) }
  quad = vec_max(pair, vec_sld(pair, pair, 4));

  //octo = { Max(a0, a4, a2, a6, a1, a5, a3, a7) }
  octo = vec_max(quad, vec_sld(quad, quad, 2));
  return pfirst(octo);
}

template<> EIGEN_STRONG_INLINE unsigned short int predux_max<Packet8us>(const Packet8us& a)
{
  Packet8us pair, quad, octo;
  
  //pair = { Max(a0,a4), Max(a1,a5), Max(a2,a6), Max(a3,a7) }
  pair = vec_max(a, vec_sld(a, a, 8)); 

  //quad = { Max(a0, a4, a2, a6), Max(a1, a5, a3, a7) }
  quad = vec_max(pair, vec_sld(pair, pair, 4));

  //octo = { Max(a0, a4, a2, a6, a1, a5, a3, a7) }
  octo = vec_max(quad, vec_sld(quad, quad, 2));
  return pfirst(octo);
}

template<> EIGEN_STRONG_INLINE int8_t predux_max<Packet16c>(const Packet16c& a)
{
  Packet16c pair, quad, octo, result;

  pair = vec_max(a, vec_sld(a, a, 8));
  quad = vec_max(pair, vec_sld(pair, pair, 4));
  octo = vec_max(quad, vec_sld(quad, quad, 2));
  result = vec_max(octo, vec_sld(octo, octo, 1));

  return pfirst(result);
}

template<> EIGEN_STRONG_INLINE uint8_t predux_max<Packet16uc>(const Packet16uc& a)
{
  Packet16uc pair, quad, octo, result;

  pair = vec_max(a, vec_sld(a, a, 8));
  quad = vec_max(pair, vec_sld(pair, pair, 4));
  octo = vec_max(quad, vec_sld(quad, quad, 2));
  result = vec_max(octo, vec_sld(octo, octo, 1));

  return pfirst(result);
}

template<> EIGEN_STRONG_INLINE bool predux_any(const Packet4f& x)
{
  return vec_any_ne(x, pzero(x));
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet4f,4>& kernel) {
  Packet4f t0, t1, t2, t3;
  t0 = vec_mergeh(kernel.packet[0], kernel.packet[2]);
  t1 = vec_mergel(kernel.packet[0], kernel.packet[2]);
  t2 = vec_mergeh(kernel.packet[1], kernel.packet[3]);
  t3 = vec_mergel(kernel.packet[1], kernel.packet[3]);
  kernel.packet[0] = vec_mergeh(t0, t2);
  kernel.packet[1] = vec_mergel(t0, t2);
  kernel.packet[2] = vec_mergeh(t1, t3);
  kernel.packet[3] = vec_mergel(t1, t3);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet4i,4>& kernel) {
  Packet4i t0, t1, t2, t3;
  t0 = vec_mergeh(kernel.packet[0], kernel.packet[2]);
  t1 = vec_mergel(kernel.packet[0], kernel.packet[2]);
  t2 = vec_mergeh(kernel.packet[1], kernel.packet[3]);
  t3 = vec_mergel(kernel.packet[1], kernel.packet[3]);
  kernel.packet[0] = vec_mergeh(t0, t2);
  kernel.packet[1] = vec_mergel(t0, t2);
  kernel.packet[2] = vec_mergeh(t1, t3);
  kernel.packet[3] = vec_mergel(t1, t3);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8s,4>& kernel) {
  Packet8s t0, t1, t2, t3;
  t0 = vec_mergeh(kernel.packet[0], kernel.packet[2]);
  t1 = vec_mergel(kernel.packet[0], kernel.packet[2]);
  t2 = vec_mergeh(kernel.packet[1], kernel.packet[3]);
  t3 = vec_mergel(kernel.packet[1], kernel.packet[3]);
  kernel.packet[0] = vec_mergeh(t0, t2);
  kernel.packet[1] = vec_mergel(t0, t2);
  kernel.packet[2] = vec_mergeh(t1, t3);
  kernel.packet[3] = vec_mergel(t1, t3);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8us,4>& kernel) {
  Packet8us t0, t1, t2, t3;
  t0 = vec_mergeh(kernel.packet[0], kernel.packet[2]);
  t1 = vec_mergel(kernel.packet[0], kernel.packet[2]);
  t2 = vec_mergeh(kernel.packet[1], kernel.packet[3]);
  t3 = vec_mergel(kernel.packet[1], kernel.packet[3]);
  kernel.packet[0] = vec_mergeh(t0, t2);
  kernel.packet[1] = vec_mergel(t0, t2);
  kernel.packet[2] = vec_mergeh(t1, t3);
  kernel.packet[3] = vec_mergel(t1, t3);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet16c,4>& kernel) {
  Packet16c t0, t1, t2, t3;
  t0 = vec_mergeh(kernel.packet[0], kernel.packet[2]);
  t1 = vec_mergel(kernel.packet[0], kernel.packet[2]);
  t2 = vec_mergeh(kernel.packet[1], kernel.packet[3]);
  t3 = vec_mergel(kernel.packet[1], kernel.packet[3]);
  kernel.packet[0] = vec_mergeh(t0, t2);
  kernel.packet[1] = vec_mergel(t0, t2);
  kernel.packet[2] = vec_mergeh(t1, t3);
  kernel.packet[3] = vec_mergel(t1, t3);
}


EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet16uc,4>& kernel) {
  Packet16uc t0, t1, t2, t3;
  t0 = vec_mergeh(kernel.packet[0], kernel.packet[2]);
  t1 = vec_mergel(kernel.packet[0], kernel.packet[2]);
  t2 = vec_mergeh(kernel.packet[1], kernel.packet[3]);
  t3 = vec_mergel(kernel.packet[1], kernel.packet[3]);
  kernel.packet[0] = vec_mergeh(t0, t2);
  kernel.packet[1] = vec_mergel(t0, t2);
  kernel.packet[2] = vec_mergeh(t1, t3);
  kernel.packet[3] = vec_mergel(t1, t3);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8s,8>& kernel) {
  Packet8s v[8], sum[8];

  v[0] = vec_mergeh(kernel.packet[0], kernel.packet[4]);
  v[1] = vec_mergel(kernel.packet[0], kernel.packet[4]);
  v[2] = vec_mergeh(kernel.packet[1], kernel.packet[5]);
  v[3] = vec_mergel(kernel.packet[1], kernel.packet[5]);
  v[4] = vec_mergeh(kernel.packet[2], kernel.packet[6]);
  v[5] = vec_mergel(kernel.packet[2], kernel.packet[6]);
  v[6] = vec_mergeh(kernel.packet[3], kernel.packet[7]);
  v[7] = vec_mergel(kernel.packet[3], kernel.packet[7]);
  sum[0] = vec_mergeh(v[0], v[4]);
  sum[1] = vec_mergel(v[0], v[4]);
  sum[2] = vec_mergeh(v[1], v[5]);
  sum[3] = vec_mergel(v[1], v[5]);
  sum[4] = vec_mergeh(v[2], v[6]);
  sum[5] = vec_mergel(v[2], v[6]);
  sum[6] = vec_mergeh(v[3], v[7]);
  sum[7] = vec_mergel(v[3], v[7]);

  kernel.packet[0] = vec_mergeh(sum[0], sum[4]);
  kernel.packet[1] = vec_mergel(sum[0], sum[4]);
  kernel.packet[2] = vec_mergeh(sum[1], sum[5]);
  kernel.packet[3] = vec_mergel(sum[1], sum[5]);
  kernel.packet[4] = vec_mergeh(sum[2], sum[6]);
  kernel.packet[5] = vec_mergel(sum[2], sum[6]);
  kernel.packet[6] = vec_mergeh(sum[3], sum[7]);
  kernel.packet[7] = vec_mergel(sum[3], sum[7]);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet8us,8>& kernel) {
  Packet8us v[8], sum[8];

  v[0] = vec_mergeh(kernel.packet[0], kernel.packet[4]);
  v[1] = vec_mergel(kernel.packet[0], kernel.packet[4]);
  v[2] = vec_mergeh(kernel.packet[1], kernel.packet[5]);
  v[3] = vec_mergel(kernel.packet[1], kernel.packet[5]);
  v[4] = vec_mergeh(kernel.packet[2], kernel.packet[6]);
  v[5] = vec_mergel(kernel.packet[2], kernel.packet[6]);
  v[6] = vec_mergeh(kernel.packet[3], kernel.packet[7]);
  v[7] = vec_mergel(kernel.packet[3], kernel.packet[7]);
  sum[0] = vec_mergeh(v[0], v[4]);
  sum[1] = vec_mergel(v[0], v[4]);
  sum[2] = vec_mergeh(v[1], v[5]);
  sum[3] = vec_mergel(v[1], v[5]);
  sum[4] = vec_mergeh(v[2], v[6]);
  sum[5] = vec_mergel(v[2], v[6]);
  sum[6] = vec_mergeh(v[3], v[7]);
  sum[7] = vec_mergel(v[3], v[7]);

  kernel.packet[0] = vec_mergeh(sum[0], sum[4]);
  kernel.packet[1] = vec_mergel(sum[0], sum[4]);
  kernel.packet[2] = vec_mergeh(sum[1], sum[5]);
  kernel.packet[3] = vec_mergel(sum[1], sum[5]);
  kernel.packet[4] = vec_mergeh(sum[2], sum[6]);
  kernel.packet[5] = vec_mergel(sum[2], sum[6]);
  kernel.packet[6] = vec_mergeh(sum[3], sum[7]);
  kernel.packet[7] = vec_mergel(sum[3], sum[7]);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet16c,16>& kernel) {
  Packet16c step1[16], step2[16], step3[16];

  step1[0] = vec_mergeh(kernel.packet[0], kernel.packet[8]);
  step1[1] = vec_mergel(kernel.packet[0], kernel.packet[8]);
  step1[2] = vec_mergeh(kernel.packet[1], kernel.packet[9]);
  step1[3] = vec_mergel(kernel.packet[1], kernel.packet[9]);
  step1[4] = vec_mergeh(kernel.packet[2], kernel.packet[10]);
  step1[5] = vec_mergel(kernel.packet[2], kernel.packet[10]);
  step1[6] = vec_mergeh(kernel.packet[3], kernel.packet[11]);
  step1[7] = vec_mergel(kernel.packet[3], kernel.packet[11]);
  step1[8] = vec_mergeh(kernel.packet[4], kernel.packet[12]);
  step1[9] = vec_mergel(kernel.packet[4], kernel.packet[12]);
  step1[10] = vec_mergeh(kernel.packet[5], kernel.packet[13]);
  step1[11] = vec_mergel(kernel.packet[5], kernel.packet[13]);
  step1[12] = vec_mergeh(kernel.packet[6], kernel.packet[14]);
  step1[13] = vec_mergel(kernel.packet[6], kernel.packet[14]);
  step1[14] = vec_mergeh(kernel.packet[7], kernel.packet[15]);
  step1[15] = vec_mergel(kernel.packet[7], kernel.packet[15]);

  step2[0]  = vec_mergeh(step1[0], step1[8]);
  step2[1]  = vec_mergel(step1[0], step1[8]);
  step2[2]  = vec_mergeh(step1[1], step1[9]);
  step2[3]  = vec_mergel(step1[1], step1[9]);
  step2[4]  = vec_mergeh(step1[2], step1[10]);
  step2[5]  = vec_mergel(step1[2], step1[10]);
  step2[6]  = vec_mergeh(step1[3], step1[11]);
  step2[7]  = vec_mergel(step1[3], step1[11]);
  step2[8]  = vec_mergeh(step1[4], step1[12]);
  step2[9]  = vec_mergel(step1[4], step1[12]);
  step2[10] = vec_mergeh(step1[5], step1[13]);
  step2[11] = vec_mergel(step1[5], step1[13]);
  step2[12] = vec_mergeh(step1[6], step1[14]);
  step2[13] = vec_mergel(step1[6], step1[14]);
  step2[14] = vec_mergeh(step1[7], step1[15]);
  step2[15] = vec_mergel(step1[7], step1[15]);

  step3[0]  = vec_mergeh(step2[0], step2[8]);
  step3[1]  = vec_mergel(step2[0], step2[8]);
  step3[2]  = vec_mergeh(step2[1], step2[9]);
  step3[3]  = vec_mergel(step2[1], step2[9]);
  step3[4]  = vec_mergeh(step2[2], step2[10]);
  step3[5]  = vec_mergel(step2[2], step2[10]);
  step3[6]  = vec_mergeh(step2[3], step2[11]);
  step3[7]  = vec_mergel(step2[3], step2[11]);
  step3[8]  = vec_mergeh(step2[4], step2[12]);
  step3[9]  = vec_mergel(step2[4], step2[12]);
  step3[10] = vec_mergeh(step2[5], step2[13]);
  step3[11] = vec_mergel(step2[5], step2[13]);
  step3[12] = vec_mergeh(step2[6], step2[14]);
  step3[13] = vec_mergel(step2[6], step2[14]);
  step3[14] = vec_mergeh(step2[7], step2[15]);
  step3[15] = vec_mergel(step2[7], step2[15]);

  kernel.packet[0]  = vec_mergeh(step3[0], step3[8]);
  kernel.packet[1]  = vec_mergel(step3[0], step3[8]);
  kernel.packet[2]  = vec_mergeh(step3[1], step3[9]);
  kernel.packet[3]  = vec_mergel(step3[1], step3[9]);
  kernel.packet[4]  = vec_mergeh(step3[2], step3[10]);
  kernel.packet[5]  = vec_mergel(step3[2], step3[10]);
  kernel.packet[6]  = vec_mergeh(step3[3], step3[11]);
  kernel.packet[7]  = vec_mergel(step3[3], step3[11]);
  kernel.packet[8]  = vec_mergeh(step3[4], step3[12]);
  kernel.packet[9]  = vec_mergel(step3[4], step3[12]);
  kernel.packet[10] = vec_mergeh(step3[5], step3[13]);
  kernel.packet[11] = vec_mergel(step3[5], step3[13]);
  kernel.packet[12] = vec_mergeh(step3[6], step3[14]);
  kernel.packet[13] = vec_mergel(step3[6], step3[14]);
  kernel.packet[14] = vec_mergeh(step3[7], step3[15]);
  kernel.packet[15] = vec_mergel(step3[7], step3[15]);
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet16uc,16>& kernel) {
  Packet16uc step1[16], step2[16], step3[16];

  step1[0] = vec_mergeh(kernel.packet[0], kernel.packet[8]);
  step1[1] = vec_mergel(kernel.packet[0], kernel.packet[8]);
  step1[2] = vec_mergeh(kernel.packet[1], kernel.packet[9]);
  step1[3] = vec_mergel(kernel.packet[1], kernel.packet[9]);
  step1[4] = vec_mergeh(kernel.packet[2], kernel.packet[10]);
  step1[5] = vec_mergel(kernel.packet[2], kernel.packet[10]);
  step1[6] = vec_mergeh(kernel.packet[3], kernel.packet[11]);
  step1[7] = vec_mergel(kernel.packet[3], kernel.packet[11]);
  step1[8] = vec_mergeh(kernel.packet[4], kernel.packet[12]);
  step1[9] = vec_mergel(kernel.packet[4], kernel.packet[12]);
  step1[10] = vec_mergeh(kernel.packet[5], kernel.packet[13]);
  step1[11] = vec_mergel(kernel.packet[5], kernel.packet[13]);
  step1[12] = vec_mergeh(kernel.packet[6], kernel.packet[14]);
  step1[13] = vec_mergel(kernel.packet[6], kernel.packet[14]);
  step1[14] = vec_mergeh(kernel.packet[7], kernel.packet[15]);
  step1[15] = vec_mergel(kernel.packet[7], kernel.packet[15]);

  step2[0]  = vec_mergeh(step1[0], step1[8]);
  step2[1]  = vec_mergel(step1[0], step1[8]);
  step2[2]  = vec_mergeh(step1[1], step1[9]);
  step2[3]  = vec_mergel(step1[1], step1[9]);
  step2[4]  = vec_mergeh(step1[2], step1[10]);
  step2[5]  = vec_mergel(step1[2], step1[10]);
  step2[6]  = vec_mergeh(step1[3], step1[11]);
  step2[7]  = vec_mergel(step1[3], step1[11]);
  step2[8]  = vec_mergeh(step1[4], step1[12]);
  step2[9]  = vec_mergel(step1[4], step1[12]);
  step2[10] = vec_mergeh(step1[5], step1[13]);
  step2[11] = vec_mergel(step1[5], step1[13]);
  step2[12] = vec_mergeh(step1[6], step1[14]);
  step2[13] = vec_mergel(step1[6], step1[14]);
  step2[14] = vec_mergeh(step1[7], step1[15]);
  step2[15] = vec_mergel(step1[7], step1[15]);

  step3[0]  = vec_mergeh(step2[0], step2[8]);
  step3[1]  = vec_mergel(step2[0], step2[8]);
  step3[2]  = vec_mergeh(step2[1], step2[9]);
  step3[3]  = vec_mergel(step2[1], step2[9]);
  step3[4]  = vec_mergeh(step2[2], step2[10]);
  step3[5]  = vec_mergel(step2[2], step2[10]);
  step3[6]  = vec_mergeh(step2[3], step2[11]);
  step3[7]  = vec_mergel(step2[3], step2[11]);
  step3[8]  = vec_mergeh(step2[4], step2[12]);
  step3[9]  = vec_mergel(step2[4], step2[12]);
  step3[10] = vec_mergeh(step2[5], step2[13]);
  step3[11] = vec_mergel(step2[5], step2[13]);
  step3[12] = vec_mergeh(step2[6], step2[14]);
  step3[13] = vec_mergel(step2[6], step2[14]);
  step3[14] = vec_mergeh(step2[7], step2[15]);
  step3[15] = vec_mergel(step2[7], step2[15]);

  kernel.packet[0]  = vec_mergeh(step3[0], step3[8]);
  kernel.packet[1]  = vec_mergel(step3[0], step3[8]);
  kernel.packet[2]  = vec_mergeh(step3[1], step3[9]);
  kernel.packet[3]  = vec_mergel(step3[1], step3[9]);
  kernel.packet[4]  = vec_mergeh(step3[2], step3[10]);
  kernel.packet[5]  = vec_mergel(step3[2], step3[10]);
  kernel.packet[6]  = vec_mergeh(step3[3], step3[11]);
  kernel.packet[7]  = vec_mergel(step3[3], step3[11]);
  kernel.packet[8]  = vec_mergeh(step3[4], step3[12]);
  kernel.packet[9]  = vec_mergel(step3[4], step3[12]);
  kernel.packet[10] = vec_mergeh(step3[5], step3[13]);
  kernel.packet[11] = vec_mergel(step3[5], step3[13]);
  kernel.packet[12] = vec_mergeh(step3[6], step3[14]);
  kernel.packet[13] = vec_mergel(step3[6], step3[14]);
  kernel.packet[14] = vec_mergeh(step3[7], step3[15]);
  kernel.packet[15] = vec_mergel(step3[7], step3[15]);
}

template<> EIGEN_STRONG_INLINE Packet4i pblend(const Selector<4>& ifPacket, const Packet4i& thenPacket, const Packet4i& elsePacket) {
  Packet4ui select = { ifPacket.select[0], ifPacket.select[1], ifPacket.select[2], ifPacket.select[3] };
  Packet4ui mask = reinterpret_cast<Packet4ui>(vec_cmpeq(reinterpret_cast<Packet4ui>(select), reinterpret_cast<Packet4ui>(p4i_ONE)));
  return vec_sel(elsePacket, thenPacket, mask);
}

template<> EIGEN_STRONG_INLINE Packet4f pblend(const Selector<4>& ifPacket, const Packet4f& thenPacket, const Packet4f& elsePacket) {
  Packet4ui select = { ifPacket.select[0], ifPacket.select[1], ifPacket.select[2], ifPacket.select[3] };
  Packet4ui mask = reinterpret_cast<Packet4ui>(vec_cmpeq(reinterpret_cast<Packet4ui>(select), reinterpret_cast<Packet4ui>(p4i_ONE)));
  return vec_sel(elsePacket, thenPacket, mask);
}

template<> EIGEN_STRONG_INLINE Packet8s pblend(const Selector<8>& ifPacket, const Packet8s& thenPacket, const Packet8s& elsePacket) {
  Packet8us select = { ifPacket.select[0], ifPacket.select[1], ifPacket.select[2], ifPacket.select[3],
                       ifPacket.select[4], ifPacket.select[5], ifPacket.select[6], ifPacket.select[7] };
  Packet8us mask = reinterpret_cast<Packet8us>(vec_cmpeq(select, p8us_ONE));
  Packet8s result = vec_sel(elsePacket, thenPacket, mask);
  return result;
}

template<> EIGEN_STRONG_INLINE Packet8us pblend(const Selector<8>& ifPacket, const Packet8us& thenPacket, const Packet8us& elsePacket) {
  Packet8us select = { ifPacket.select[0], ifPacket.select[1], ifPacket.select[2], ifPacket.select[3],
                       ifPacket.select[4], ifPacket.select[5], ifPacket.select[6], ifPacket.select[7] };
  Packet8us mask = reinterpret_cast<Packet8us>(vec_cmpeq(reinterpret_cast<Packet8us>(select), p8us_ONE));
  return vec_sel(elsePacket, thenPacket, mask);
}

template<> EIGEN_STRONG_INLINE Packet16c pblend(const Selector<16>& ifPacket, const Packet16c& thenPacket, const Packet16c& elsePacket) {
  Packet16uc select = { ifPacket.select[0], ifPacket.select[1], ifPacket.select[2], ifPacket.select[3],
                       ifPacket.select[4], ifPacket.select[5], ifPacket.select[6], ifPacket.select[7],
                       ifPacket.select[8], ifPacket.select[9], ifPacket.select[10], ifPacket.select[11],
                       ifPacket.select[12], ifPacket.select[13], ifPacket.select[14], ifPacket.select[15] };

  Packet16uc mask = reinterpret_cast<Packet16uc>(vec_cmpeq(reinterpret_cast<Packet16uc>(select), p16uc_ONE));
  return vec_sel(elsePacket, thenPacket, mask);
}

template<> EIGEN_STRONG_INLINE Packet16uc pblend(const Selector<16>& ifPacket, const Packet16uc& thenPacket, const Packet16uc& elsePacket) {
  Packet16uc select = { ifPacket.select[0], ifPacket.select[1], ifPacket.select[2], ifPacket.select[3],
                       ifPacket.select[4], ifPacket.select[5], ifPacket.select[6], ifPacket.select[7],
                       ifPacket.select[8], ifPacket.select[9], ifPacket.select[10], ifPacket.select[11],
                       ifPacket.select[12], ifPacket.select[13], ifPacket.select[14], ifPacket.select[15] };

  Packet16uc mask = reinterpret_cast<Packet16uc>(vec_cmpeq(reinterpret_cast<Packet16uc>(select), p16uc_ONE));
  return vec_sel(elsePacket, thenPacket, mask);
}

template <>
struct type_casting_traits<float, int> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};

template <>
struct type_casting_traits<int, float> {
  enum {
    VectorizedCast = 1,
    SrcCoeffRatio = 1,
    TgtCoeffRatio = 1
  };
};


template<> EIGEN_STRONG_INLINE Packet4i pcast<Packet4f, Packet4i>(const Packet4f& a) {
  return vec_cts(a,0);
}

template<> EIGEN_STRONG_INLINE Packet4f pcast<Packet4i, Packet4f>(const Packet4i& a) {
  return vec_ctf(a,0);
}

template<> EIGEN_STRONG_INLINE Packet4i preinterpret<Packet4i,Packet4f>(const Packet4f& a) {
  return reinterpret_cast<Packet4i>(a);
}

template<> EIGEN_STRONG_INLINE Packet4f preinterpret<Packet4f,Packet4i>(const Packet4i& a) {
  return reinterpret_cast<Packet4f>(a);
}



//---------- double ----------
#ifdef __VSX__
typedef __vector double              Packet2d;
typedef __vector unsigned long long  Packet2ul;
typedef __vector long long           Packet2l;
#if EIGEN_COMP_CLANG
typedef Packet2ul                    Packet2bl;
#else
typedef __vector __bool long         Packet2bl;
#endif

static Packet2l  p2l_ONE  = { 1, 1 };
static Packet2l  p2l_ZERO = reinterpret_cast<Packet2l>(p4i_ZERO);
static Packet2d  p2d_ONE  = { 1.0, 1.0 };
static Packet2d  p2d_ZERO = reinterpret_cast<Packet2d>(p4f_ZERO);
static Packet2d  p2d_MZERO = { -0.0, -0.0 };

#ifdef _BIG_ENDIAN
static Packet2d p2d_COUNTDOWN = reinterpret_cast<Packet2d>(vec_sld(reinterpret_cast<Packet4f>(p2d_ZERO), reinterpret_cast<Packet4f>(p2d_ONE), 8));
#else
static Packet2d p2d_COUNTDOWN = reinterpret_cast<Packet2d>(vec_sld(reinterpret_cast<Packet4f>(p2d_ONE), reinterpret_cast<Packet4f>(p2d_ZERO), 8));
#endif

template<int index> Packet2d vec_splat_dbl(Packet2d& a);

template<> EIGEN_STRONG_INLINE Packet2d vec_splat_dbl<0>(Packet2d& a)
{
  return reinterpret_cast<Packet2d>(vec_perm(a, a, p16uc_PSET64_HI));
}

template<> EIGEN_STRONG_INLINE Packet2d vec_splat_dbl<1>(Packet2d& a)
{
  return reinterpret_cast<Packet2d>(vec_perm(a, a, p16uc_PSET64_LO));
}

template<> struct packet_traits<double> : default_packet_traits
{
  typedef Packet2d type;
  typedef Packet2d half;
  enum {
    Vectorizable = 1,
    AlignedOnScalar = 1,
    size=2,
    HasHalfPacket = 1,

    HasAdd  = 1,
    HasSub  = 1,
    HasMul  = 1,
    HasDiv  = 1,
    HasMin  = 1,
    HasMax  = 1,
    HasAbs  = 1,
    HasSin  = 0,
    HasCos  = 0,
    HasLog  = 0,
    HasExp  = 1,
    HasSqrt = 1,
    HasRsqrt = 1,
    HasRound = 1,
    HasFloor = 1,
    HasCeil = 1,
    HasNegate = 1,
    HasBlend = 1
  };
};

template<> struct unpacket_traits<Packet2d> { typedef double type; enum {size=2, alignment=Aligned16, vectorizable=true, masked_load_available=false, masked_store_available=false}; typedef Packet2d half; };

inline std::ostream & operator <<(std::ostream & s, const Packet2l & v)
{
  union {
    Packet2l   v;
    int64_t n[2];
  } vt;
  vt.v = v;
  s << vt.n[0] << ", " << vt.n[1];
  return s;
}

inline std::ostream & operator <<(std::ostream & s, const Packet2d & v)
{
  union {
    Packet2d   v;
    double n[2];
  } vt;
  vt.v = v;
  s << vt.n[0] << ", " << vt.n[1];
  return s;
}

// Need to define them first or we get specialization after instantiation errors
template<> EIGEN_STRONG_INLINE Packet2d pload<Packet2d>(const double* from)
{
  EIGEN_DEBUG_ALIGNED_LOAD
  return vec_xl(0, const_cast<double *>(from)); // cast needed by Clang
}

template<> EIGEN_STRONG_INLINE void pstore<double>(double*   to, const Packet2d& from)
{
  EIGEN_DEBUG_ALIGNED_STORE
  vec_xst(from, 0, to);
}

template<> EIGEN_STRONG_INLINE Packet2d pset1<Packet2d>(const double&  from) {
  Packet2d v = {from, from};
  return v;
}

template<> EIGEN_STRONG_INLINE void
pbroadcast4<Packet2d>(const double *a,
                      Packet2d& a0, Packet2d& a1, Packet2d& a2, Packet2d& a3)
{
  a1 = pload<Packet2d>(a);
  a0 = vec_splat_dbl<0>(a1);
  a1 = vec_splat_dbl<1>(a1);
  a3 = pload<Packet2d>(a+2);
  a2 = vec_splat_dbl<0>(a3);
  a3 = vec_splat_dbl<1>(a3);
}

template<> EIGEN_DEVICE_FUNC inline Packet2d pgather<double, Packet2d>(const double* from, Index stride)
{
  EIGEN_ALIGN16 double af[2];
  af[0] = from[0*stride];
  af[1] = from[1*stride];
 return pload<Packet2d>(af);
}
template<> EIGEN_DEVICE_FUNC inline void pscatter<double, Packet2d>(double* to, const Packet2d& from, Index stride)
{
  EIGEN_ALIGN16 double af[2];
  pstore<double>(af, from);
  to[0*stride] = af[0];
  to[1*stride] = af[1];
}

template<> EIGEN_STRONG_INLINE Packet2d plset<Packet2d>(const double& a) { return pset1<Packet2d>(a) + p2d_COUNTDOWN; }

template<> EIGEN_STRONG_INLINE Packet2d padd<Packet2d>(const Packet2d& a, const Packet2d& b) { return a + b; }

template<> EIGEN_STRONG_INLINE Packet2d psub<Packet2d>(const Packet2d& a, const Packet2d& b) { return a - b; }

template<> EIGEN_STRONG_INLINE Packet2d pnegate(const Packet2d& a) { return p2d_ZERO - a; }

template<> EIGEN_STRONG_INLINE Packet2d pconj(const Packet2d& a) { return a; }

template<> EIGEN_STRONG_INLINE Packet2d pmul<Packet2d>(const Packet2d& a, const Packet2d& b) { return vec_madd(a,b,p2d_MZERO); }
template<> EIGEN_STRONG_INLINE Packet2d pdiv<Packet2d>(const Packet2d& a, const Packet2d& b) { return vec_div(a,b); }

// for some weird raisons, it has to be overloaded for packet of integers
template<> EIGEN_STRONG_INLINE Packet2d pmadd(const Packet2d& a, const Packet2d& b, const Packet2d& c) { return vec_madd(a, b, c); }

template<> EIGEN_STRONG_INLINE Packet2d pmin<Packet2d>(const Packet2d& a, const Packet2d& b)
{
  // NOTE: about 10% slower than vec_min, but consistent with std::min and SSE regarding NaN
  Packet2d ret;
  __asm__ ("xvcmpgedp %x0,%x1,%x2\n\txxsel %x0,%x1,%x2,%x0" : "=&wa" (ret) : "wa" (a), "wa" (b));
  return ret;
 }

template<> EIGEN_STRONG_INLINE Packet2d pmax<Packet2d>(const Packet2d& a, const Packet2d& b)
{
  // NOTE: about 10% slower than vec_max, but consistent with std::max and SSE regarding NaN
  Packet2d ret;
  __asm__ ("xvcmpgtdp %x0,%x2,%x1\n\txxsel %x0,%x1,%x2,%x0" : "=&wa" (ret) : "wa" (a), "wa" (b));
  return ret;
}

template<> EIGEN_STRONG_INLINE Packet2d pcmp_le(const Packet2d& a, const Packet2d& b) { return reinterpret_cast<Packet2d>(vec_cmple(a,b)); }
template<> EIGEN_STRONG_INLINE Packet2d pcmp_lt(const Packet2d& a, const Packet2d& b) { return reinterpret_cast<Packet2d>(vec_cmplt(a,b)); }
template<> EIGEN_STRONG_INLINE Packet2d pcmp_eq(const Packet2d& a, const Packet2d& b) { return reinterpret_cast<Packet2d>(vec_cmpeq(a,b)); }
template<> EIGEN_STRONG_INLINE Packet2d pcmp_lt_or_nan(const Packet2d& a, const Packet2d& b) {
  Packet2d c = reinterpret_cast<Packet2d>(vec_cmpge(a,b));
  return vec_nor(c,c);
}

template<> EIGEN_STRONG_INLINE Packet2d pand<Packet2d>(const Packet2d& a, const Packet2d& b) { return vec_and(a, b); }

template<> EIGEN_STRONG_INLINE Packet2d por<Packet2d>(const Packet2d& a, const Packet2d& b) { return vec_or(a, b); }

template<> EIGEN_STRONG_INLINE Packet2d pxor<Packet2d>(const Packet2d& a, const Packet2d& b) { return vec_xor(a, b); }

template<> EIGEN_STRONG_INLINE Packet2d pandnot<Packet2d>(const Packet2d& a, const Packet2d& b) { return vec_and(a, vec_nor(b, b)); }

template<> EIGEN_STRONG_INLINE Packet2d pround<Packet2d>(const Packet2d& a) { return vec_round(a); }
template<> EIGEN_STRONG_INLINE Packet2d pceil<Packet2d>(const  Packet2d& a) { return vec_ceil(a); }
template<> EIGEN_STRONG_INLINE Packet2d pfloor<Packet2d>(const Packet2d& a) { return vec_floor(a); }

template<> EIGEN_STRONG_INLINE Packet2d ploadu<Packet2d>(const double* from)
{
  EIGEN_DEBUG_UNALIGNED_LOAD
  return vec_xl(0, from);
}

template<> EIGEN_STRONG_INLINE Packet2d ploaddup<Packet2d>(const double*   from)
{
  Packet2d p;
  if((std::ptrdiff_t(from) % 16) == 0)  p = pload<Packet2d>(from);
  else                                  p = ploadu<Packet2d>(from);
  return vec_splat_dbl<0>(p);
}

template<> EIGEN_STRONG_INLINE void pstoreu<double>(double*  to, const Packet2d& from)
{
  EIGEN_DEBUG_UNALIGNED_STORE
  vec_xst(from, 0, to);
}

template<> EIGEN_STRONG_INLINE void prefetch<double>(const double* addr) { EIGEN_PPC_PREFETCH(addr); }

template<> EIGEN_STRONG_INLINE double  pfirst<Packet2d>(const Packet2d& a) { EIGEN_ALIGN16 double x[2]; pstore<double>(x, a); return x[0]; }

template<> EIGEN_STRONG_INLINE Packet2d preverse(const Packet2d& a)
{
  return reinterpret_cast<Packet2d>(vec_perm(reinterpret_cast<Packet16uc>(a), reinterpret_cast<Packet16uc>(a), p16uc_REVERSE64));
}
template<> EIGEN_STRONG_INLINE Packet2d pabs(const Packet2d& a) { return vec_abs(a); }

// VSX support varies between different compilers and even different
// versions of the same compiler.  For gcc version >= 4.9.3, we can use
// vec_cts to efficiently convert Packet2d to Packet2l.  Otherwise, use
// a slow version that works with older compilers. 
// Update: apparently vec_cts/vec_ctf intrinsics for 64-bit doubles
// are buggy, https://gcc.gnu.org/bugzilla/show_bug.cgi?id=70963
static inline Packet2l ConvertToPacket2l(const Packet2d& x) {
#if EIGEN_GNUC_AT_LEAST(5, 4) || \
    (EIGEN_GNUC_AT(6, 1) && __GNUC_PATCHLEVEL__ >= 1)
  return vec_cts(x, 0);    // TODO: check clang version.
#else
  double tmp[2];
  memcpy(tmp, &x, sizeof(tmp));
  Packet2l l = { static_cast<long long>(tmp[0]),
                 static_cast<long long>(tmp[1]) };
  return l;
#endif
}

template<> EIGEN_STRONG_INLINE Packet2d pldexp<Packet2d>(const Packet2d& a, const Packet2d& exponent) {
  
  // build 2^n
  Packet2l emm0 = ConvertToPacket2l(exponent);

#ifdef __POWER8_VECTOR__ 
  const Packet2l  p2l_1023 = { 1023, 1023 };
  const Packet2ul p2ul_52 = { 52, 52 };
  emm0 = vec_add(emm0, p2l_1023);
  emm0 = vec_sl(emm0, p2ul_52);
#else
  // Code is a bit complex for POWER7.  There is actually a
  // vec_xxsldi intrinsic but it is not supported by some gcc versions.
  // So we shift (52-32) bits and do a word swap with zeros.
  const Packet4i p4i_1023 = pset1<Packet4i>(1023);
  const Packet4i p4i_20 = pset1<Packet4i>(20);    // 52 - 32

  Packet4i emm04i = reinterpret_cast<Packet4i>(emm0);
  emm04i = vec_add(emm04i, p4i_1023);
  emm04i = vec_sl(emm04i, reinterpret_cast<Packet4ui>(p4i_20));
  static const Packet16uc perm = {
    0x14, 0x15, 0x16, 0x17, 0x00, 0x01, 0x02, 0x03, 
    0x1c, 0x1d, 0x1e, 0x1f, 0x08, 0x09, 0x0a, 0x0b };
#ifdef  _BIG_ENDIAN
  emm0 = reinterpret_cast<Packet2l>(vec_perm(p4i_ZERO, emm04i, perm));
#else
  emm0 = reinterpret_cast<Packet2l>(vec_perm(emm04i, p4i_ZERO, perm));
#endif

#endif

  return pmul(a, reinterpret_cast<Packet2d>(emm0));
}

template<> EIGEN_STRONG_INLINE double predux<Packet2d>(const Packet2d& a)
{
  Packet2d b, sum;
  b   = reinterpret_cast<Packet2d>(vec_sld(reinterpret_cast<Packet4f>(a), reinterpret_cast<Packet4f>(a), 8));
  sum = a + b;
  return pfirst<Packet2d>(sum);
}

// Other reduction functions:
// mul
template<> EIGEN_STRONG_INLINE double predux_mul<Packet2d>(const Packet2d& a)
{
  return pfirst(pmul(a, reinterpret_cast<Packet2d>(vec_sld(reinterpret_cast<Packet4ui>(a), reinterpret_cast<Packet4ui>(a), 8))));
}

// min
template<> EIGEN_STRONG_INLINE double predux_min<Packet2d>(const Packet2d& a)
{
  return pfirst(pmin(a, reinterpret_cast<Packet2d>(vec_sld(reinterpret_cast<Packet4ui>(a), reinterpret_cast<Packet4ui>(a), 8))));
}

// max
template<> EIGEN_STRONG_INLINE double predux_max<Packet2d>(const Packet2d& a)
{
  return pfirst(pmax(a, reinterpret_cast<Packet2d>(vec_sld(reinterpret_cast<Packet4ui>(a), reinterpret_cast<Packet4ui>(a), 8))));
}

EIGEN_DEVICE_FUNC inline void
ptranspose(PacketBlock<Packet2d,2>& kernel) {
  Packet2d t0, t1;
  t0 = vec_perm(kernel.packet[0], kernel.packet[1], p16uc_TRANSPOSE64_HI);
  t1 = vec_perm(kernel.packet[0], kernel.packet[1], p16uc_TRANSPOSE64_LO);
  kernel.packet[0] = t0;
  kernel.packet[1] = t1;
}

template<> EIGEN_STRONG_INLINE Packet2d pblend(const Selector<2>& ifPacket, const Packet2d& thenPacket, const Packet2d& elsePacket) {
  Packet2l select = { ifPacket.select[0], ifPacket.select[1] };
  Packet2bl mask = reinterpret_cast<Packet2bl>( vec_cmpeq(reinterpret_cast<Packet2d>(select), reinterpret_cast<Packet2d>(p2l_ONE)) );
  return vec_sel(elsePacket, thenPacket, mask);
}
#endif // __VSX__
} // end namespace internal

} // end namespace Eigen

#endif // EIGEN_PACKET_MATH_ALTIVEC_H
