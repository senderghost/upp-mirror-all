/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#ifndef _INTSAFE_H_INCLUDED_
#define _INTSAFE_H_INCLUDED_

#include <winapifamily.h>

#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

#include <wtypesbase.h>
#include <specstrings.h>

#define INTSAFE_E_ARITHMETIC_OVERFLOW ((HRESULT)0x80070216)

#ifndef S_OK
#define S_OK ((HRESULT)0)
#endif

#ifdef __clang__
#if __has_builtin(__builtin_add_overflow)
#define __MINGW_INTSAFE_WORKS
#endif
#elif __GNUC__ >= 5
#define __MINGW_INTSAFE_WORKS
#endif

#ifdef __MINGW_INTSAFE_WORKS

#ifndef __MINGW_INTSAFE_API
#define __MINGW_INTSAFE_API FORCEINLINE
#endif

/** If CHAR is unsigned, use static inline for functions that operate
on chars.  This avoids the risk of linking to the wrong function when
different translation units with different types of chars are linked
together, and code using signed chars will not be affected. */
#ifndef __MINGW_INTSAFE_CHAR_API
#ifdef __CHAR_UNSIGNED__
#define __MINGW_INTSAFE_CHAR_API static inline
#else
#define __MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_API
#endif
#endif

#define __MINGW_INTSAFE_BODY(operation, x, y) \
{ \
  if (__builtin_##operation##_overflow(x, y, result)) \
  { \
      *result = 0; \
      return INTSAFE_E_ARITHMETIC_OVERFLOW; \
  } \
  return S_OK; \
}

#define __MINGW_INTSAFE_CONV(name, type_src, type_dest) \
    HRESULT name(type_src operand, type_dest * result) \
    __MINGW_INTSAFE_BODY(add, operand, 0)

#define __MINGW_INTSAFE_MATH(name, type, operation) \
    HRESULT name(type x, type y, type * result) \
    __MINGW_INTSAFE_BODY(operation, x, y)

__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UInt8ToInt8, UINT8, INT8)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(UInt8ToChar, UINT8, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ByteToInt8, BYTE, INT8)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(ByteToChar, BYTE, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int8ToUChar, INT8, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int8ToUInt8, INT8, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int8ToUShort, INT8, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int8ToUInt, INT8, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int8ToULong, INT8, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int8ToUIntPtr, INT8, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int8ToULongPtr, INT8, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int8ToULongLong, INT8, ULONGLONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UShortToUChar, USHORT, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UShortToUInt8, USHORT, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UShortToByte, USHORT, BYTE)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UShortToInt8, USHORT, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UShortToShort, USHORT, SHORT)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(UShortToChar, USHORT, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(WordToUChar, WORD, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(WordToByte, WORD, BYTE)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(WordToShort, WORD, SHORT)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(WordToChar, WORD, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToUChar, SHORT, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToUInt8, SHORT, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToByte, SHORT, BYTE)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToInt8, SHORT, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToUShort, SHORT, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToWord, SHORT, WORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToUInt, SHORT, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToULong, SHORT, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToUIntPtr, SHORT, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToULongPtr, SHORT, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToDWordPtr, SHORT, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ShortToULongLong, SHORT, ULONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(ShortToChar, SHORT, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToUChar, UINT, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToUInt8, UINT, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToByte, UINT, BYTE)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToInt8, UINT, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToUShort, UINT, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToWord, UINT, WORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToShort, UINT, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToLong, UINT, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToInt, UINT, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToIntPtr, UINT, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToPtrdiffT, UINT, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToLongPtr, UINT, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntToSSIZET, UINT, SSIZE_T)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(UIntToChar, UINT, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToUChar, ULONG, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToUInt8, ULONG, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToByte, ULONG, BYTE)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToInt8, ULONG, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToUShort, ULONG, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToWord, ULONG, WORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToShort, ULONG, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToUInt, ULONG, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToLong, ULONG, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToInt, ULONG, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToUIntPtr, ULONG, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToIntPtr, ULONG, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToPtrdiffT, ULONG, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToLongPtr, ULONG, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongToSSIZET, ULONG, SSIZE_T)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(ULongToChar, ULONG, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToUChar, DWORD, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToByte, DWORD, BYTE)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToUShort, DWORD, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToWord, DWORD, WORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToShort, DWORD, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToUInt, DWORD, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToLong, DWORD, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToInt, DWORD, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToUIntPtr, DWORD, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToIntPtr, DWORD, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToPtrdiffT, DWORD, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToLongPtr, DWORD, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordToSSIZET, DWORD, SSIZE_T)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(DWordToChar, DWORD, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToUChar, LONG, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToUInt8, LONG, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToByte, LONG, BYTE)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToInt8, LONG, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToUShort, LONG, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToWord, LONG, WORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToShort, LONG, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToUInt, LONG, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToULong, LONG, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToDWord, LONG, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToInt, LONG, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToUIntPtr, LONG, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToSizeT, LONG, size_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToULongPtr, LONG, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToDWordPtr, LONG, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToIntPtr, LONG, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToPtrdiffT, LONG, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongToULongLong, LONG, ULONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(LongToChar, LONG, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToUChar, INT, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToUInt8, INT, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToByte, INT, BYTE)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToInt8, INT, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToUShort, INT, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToWord, INT, WORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToShort, INT, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToUInt, INT, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToULong, INT, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToDWord, INT, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToUIntPtr, INT, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToSizeT, INT, size_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToULongPtr, INT, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToDWordPtr, INT, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntToULongLong, INT, ULONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(IntToChar, INT, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToUChar, UINT_PTR, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToUInt8, UINT_PTR, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToInt8, UINT_PTR, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToUInt16, UINT_PTR, UINT16)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToUShort, UINT_PTR, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToInt16, UINT_PTR, INT16)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToShort, UINT_PTR, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToUInt, UINT_PTR, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToULong, UINT_PTR, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToDWord, UINT_PTR, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToLong, UINT_PTR, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToInt, UINT_PTR, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToIntPtr, UINT_PTR, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToLongPtr, UINT_PTR, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToSSIZET, UINT_PTR, SSIZE_T)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToInt64, UINT_PTR, INT64)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(UIntPtrToLongLong, UINT_PTR, LONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(UIntPtrToChar, UINT_PTR, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToUInt, size_t, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToULong, size_t, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToDWord, size_t, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToLong, size_t, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToInt, size_t, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToIntPtr, size_t, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToPtrdiffT, size_t, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToLongPtr, size_t, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToSSIZET, size_t, SSIZE_T)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SizeTToInt64, size_t, INT64)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToUChar, ULONG_PTR, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToUInt8, ULONG_PTR, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToInt8, ULONG_PTR, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToUShort, ULONG_PTR, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToShort, ULONG_PTR, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToUInt, ULONG_PTR, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToULong, ULONG_PTR, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToDWord, ULONG_PTR, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToLong, ULONG_PTR, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToInt, ULONG_PTR, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToUIntPtr, ULONG_PTR, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToIntPtr, ULONG_PTR, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToPtrdiffT, ULONG_PTR, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToLongPtr, ULONG_PTR, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToSSIZET, ULONG_PTR, SSIZE_T)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToInt64, ULONG_PTR, INT64)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongPtrToLongLong, ULONG_PTR, LONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(ULongPtrToChar, ULONG_PTR, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToUInt, DWORD_PTR, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToULong, DWORD_PTR, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToDWord, DWORD_PTR, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToLong, DWORD_PTR, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToInt, DWORD_PTR, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToUIntPtr, DWORD_PTR, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToIntPtr, DWORD_PTR, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToPtrdiffT, DWORD_PTR, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToLongPtr, DWORD_PTR, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToSSIZET, DWORD_PTR, SSIZE_T)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(DWordPtrToInt64, DWORD_PTR, INT64)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToUChar, INT_PTR, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToUInt8, INT_PTR, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToInt8, INT_PTR, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToUShort, INT_PTR, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToShort, INT_PTR, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToUInt, INT_PTR, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToULong, INT_PTR, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToDWord, INT_PTR, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToLong, INT_PTR, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToInt, INT_PTR, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToUIntPtr, INT_PTR, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToSizeT, INT_PTR, size_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToULongPtr, INT_PTR, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToDWordPtr, INT_PTR, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToLongPtr, INT_PTR, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(IntPtrToULongLong, INT_PTR, ULONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(IntPtrToChar, INT_PTR, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToUInt, ptrdiff_t, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToULong, ptrdiff_t, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToDWord, ptrdiff_t, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToLong, ptrdiff_t, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToInt, ptrdiff_t, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToUIntPtr, ptrdiff_t, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToSizeT, ptrdiff_t, size_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToULongPtr, ptrdiff_t, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(PtrdiffTToDWordPtr, ptrdiff_t, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToUChar, LONG_PTR, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToUInt8, LONG_PTR, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToInt8, LONG_PTR, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToUShort, LONG_PTR, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToShort, LONG_PTR, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToUInt, LONG_PTR, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToULong, LONG_PTR, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToDWord, LONG_PTR, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToLong, LONG_PTR, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToInt, LONG_PTR, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToUIntPtr, LONG_PTR, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToSizeT, LONG_PTR, size_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToULongPtr, LONG_PTR, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToDWordPtr, LONG_PTR, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToIntPtr, LONG_PTR, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongPtrToULongLong, LONG_PTR, ULONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(LongPtrToChar, LONG_PTR, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToUInt, SSIZE_T, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToULong, SSIZE_T, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToDWord, SSIZE_T, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToLong, SSIZE_T, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToInt, SSIZE_T, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToUIntPtr, SSIZE_T, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToSizeT, SSIZE_T, size_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToULongPtr, SSIZE_T, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToDWordPtr, SSIZE_T, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(SSIZETToIntPtr, SSIZE_T, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToUChar, ULONGLONG, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToUInt8, ULONGLONG, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToInt8, ULONGLONG, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToUShort, ULONGLONG, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToShort, ULONGLONG, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToUInt, ULONGLONG, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToULong, ULONGLONG, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToDWord, ULONGLONG, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToLong, ULONGLONG, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToInt, ULONGLONG, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToUIntPtr, ULONGLONG, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToSizeT, ULONGLONG, size_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToULongPtr, ULONGLONG, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToDWordPtr, ULONGLONG, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToIntPtr, ULONGLONG, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToPtrdiffT, ULONGLONG, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToLongPtr, ULONGLONG, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToSSIZET, ULONGLONG, SSIZE_T)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToInt64, ULONGLONG, INT64)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(ULongLongToLongLong, ULONGLONG, LONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(ULongLongToChar, ULONGLONG, CHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToUInt, INT64, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToULong, INT64, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToDWord, INT64, DWORD)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToLong, INT64, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToInt, INT64, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToUIntPtr, INT64, UINT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToSizeT, INT64, size_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToULongPtr, INT64, ULONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToDWordPtr, INT64, DWORD_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToIntPtr, INT64, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToPtrdiffT, INT64, ptrdiff_t)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToLongPtr, INT64, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToSSIZET, INT64, SSIZE_T)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(Int64ToULongLong, INT64, ULONGLONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToUChar, LONGLONG, UCHAR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToUInt8, LONGLONG, UINT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToInt8, LONGLONG, INT8)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToUShort, LONGLONG, USHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToShort, LONGLONG, SHORT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToUInt, LONGLONG, UINT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToULong, LONGLONG, ULONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToLong, LONGLONG, LONG)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToInt, LONGLONG, INT)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToIntPtr, LONGLONG, INT_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToLongPtr, LONGLONG, LONG_PTR)
__MINGW_INTSAFE_API __MINGW_INTSAFE_CONV(LongLongToULongLong, LONGLONG, ULONGLONG)
__MINGW_INTSAFE_CHAR_API __MINGW_INTSAFE_CONV(LongLongToChar, LONGLONG, CHAR)

__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UInt8Add, UINT8, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(Int8Add, INT8, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UShortAdd, USHORT, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(WordAdd, WORD, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ShortAdd, SHORT, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UIntAdd, UINT, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongAdd, ULONG, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(DWordAdd, DWORD, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongAdd, LONG, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(IntAdd, INT, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UIntPtrAdd, UINT_PTR, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(SizeTAdd, size_t, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongPtrAdd, ULONG_PTR, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(DWordPtrAdd, DWORD_PTR, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(IntPtrAdd, INT_PTR, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(PtrdiffTAdd, ptrdiff_t, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongPtrAdd, LONG_PTR, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(SSIZETAdd, SSIZE_T, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongLongAdd, ULONGLONG, add)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongLongAdd, LONGLONG, add)

__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UInt8Sub, UINT8, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(Int8Sub, INT8, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UShortSub, USHORT, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(WordSub, WORD, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ShortSub, SHORT, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UIntSub, UINT, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongSub, ULONG, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(DWordSub, DWORD, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongSub, LONG, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(IntSub, INT, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UIntPtrSub, UINT_PTR, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(SizeTSub, size_t, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongPtrSub, ULONG_PTR, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(DWordPtrSub, DWORD_PTR, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(IntPtrSub, INT_PTR, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(PtrdiffTSub, ptrdiff_t, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongPtrSub, LONG_PTR, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(SSIZETSub, SSIZE_T, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongLongSub, ULONGLONG, sub)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongLongSub, LONGLONG, sub)

__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UInt8Mult, UINT8, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(Int8Mult, INT8, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UShortMult, USHORT, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(WordMult, WORD, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ShortMult, SHORT, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UIntMult, UINT, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongMult, ULONG, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(DWordMult, DWORD, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongMult, LONG, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(IntMult, INT, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(UIntPtrMult, UINT_PTR, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(SizeTMult, size_t, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongPtrMult, ULONG_PTR, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(DWordPtrMult, DWORD_PTR, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(IntPtrMult, INT_PTR, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(PtrdiffTMult, ptrdiff_t, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongPtrMult, LONG_PTR, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(SSIZETMult, SSIZE_T, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(ULongLongMult, ULONGLONG, mul)
__MINGW_INTSAFE_API __MINGW_INTSAFE_MATH(LongLongMult, LONGLONG, mul)

#endif /* __GNUC__ >= 5 */
#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) */
#endif /* _INTSAFE_H_INCLUDED_ */
