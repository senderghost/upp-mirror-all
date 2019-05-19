/** @file matio.h
 * LIBMATIO Header
 * @ingroup MAT
 */
/*
 * Copyright (c) 2005-2019, Christopher C. Hulbert
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MATIO_H
#define MATIO_H

#include <stdlib.h>
#include <stdio.h>
#include "matio_pubconf.h"

#include <stdarg.h>

#ifdef __cplusplus
#   define EXTERN extern "C"
#else
#   define EXTERN extern
#endif

/** @defgroup MAT Matlab MAT File I/O Library */
/** @defgroup mat_util MAT File I/O Utility Functions */
/** @if mat_devman @defgroup mat_internal Internal Functions @endif */

/** @brief MAT file access types
 *
 * @ingroup MAT
 * MAT file access types
 */
enum mat_acc {
    MAT_ACC_RDONLY = 0,  /**< @brief Read only file access                */
    MAT_ACC_RDWR   = 1   /**< @brief Read/Write file access               */
};

/** @brief MAT file versions
 *
 * @ingroup MAT
 * MAT file versions
 */
enum mat_ft {
    MAT_FT_MAT73  = 0x0200,   /**< @brief Matlab version 7.3 file             */
    MAT_FT_MAT5   = 0x0100,   /**< @brief Matlab version 5 file               */
    MAT_FT_MAT4   = 0x0010,   /**< @brief Matlab version 4 file               */
    MAT_FT_UNDEFINED =   0    /**< @brief Undefined version                   */
};

/** @brief Matlab data types
 *
 * @ingroup MAT
 * Matlab data types
 */
enum matio_types {
    MAT_T_UNKNOWN    =  0,    /**< @brief UNKNOWN data type                   */
    MAT_T_INT8       =  1,    /**< @brief 8-bit signed integer data type      */
    MAT_T_UINT8      =  2,    /**< @brief 8-bit unsigned integer data type    */
    MAT_T_INT16      =  3,    /**< @brief 16-bit signed integer data type     */
    MAT_T_UINT16     =  4,    /**< @brief 16-bit unsigned integer data type   */
    MAT_T_INT32      =  5,    /**< @brief 32-bit signed integer data type     */
    MAT_T_UINT32     =  6,    /**< @brief 32-bit unsigned integer data type   */
    MAT_T_SINGLE     =  7,    /**< @brief IEEE 754 single precision data type */
    MAT_T_DOUBLE     =  9,    /**< @brief IEEE 754 double precision data type */
    MAT_T_INT64      = 12,    /**< @brief 64-bit signed integer data type     */
    MAT_T_UINT64     = 13,    /**< @brief 64-bit unsigned integer data type   */
    MAT_T_MATRIX     = 14,    /**< @brief matrix data type                    */
    MAT_T_COMPRESSED = 15,    /**< @brief compressed data type                */
    MAT_T_UTF8       = 16,    /**< @brief 8-bit Unicode text data type        */
    MAT_T_UTF16      = 17,    /**< @brief 16-bit Unicode text data type       */
    MAT_T_UTF32      = 18,    /**< @brief 32-bit Unicode text data type       */

    MAT_T_STRING     = 20,    /**< @brief String data type                    */
    MAT_T_CELL       = 21,    /**< @brief Cell array data type                */
    MAT_T_STRUCT     = 22,    /**< @brief Structure data type                 */
    MAT_T_ARRAY      = 23,    /**< @brief Array data type                     */
    MAT_T_FUNCTION   = 24     /**< @brief Function data type                  */
};

/** @brief Matlab variable classes
 *
 * @ingroup MAT
 * Matlab variable classes
 */
enum matio_classes {
    MAT_C_EMPTY    =  0, /**< @brief Empty array                           */
    MAT_C_CELL     =  1, /**< @brief Matlab cell array class               */
    MAT_C_STRUCT   =  2, /**< @brief Matlab structure class                */
    MAT_C_OBJECT   =  3, /**< @brief Matlab object class                   */
    MAT_C_CHAR     =  4, /**< @brief Matlab character array class          */
    MAT_C_SPARSE   =  5, /**< @brief Matlab sparse array class             */
    MAT_C_DOUBLE   =  6, /**< @brief Matlab double-precision class         */
    MAT_C_SINGLE   =  7, /**< @brief Matlab single-precision class         */
    MAT_C_INT8     =  8, /**< @brief Matlab signed 8-bit integer class     */
    MAT_C_UINT8    =  9, /**< @brief Matlab unsigned 8-bit integer class   */
    MAT_C_INT16    = 10, /**< @brief Matlab signed 16-bit integer class    */
    MAT_C_UINT16   = 11, /**< @brief Matlab unsigned 16-bit integer class  */
    MAT_C_INT32    = 12, /**< @brief Matlab signed 32-bit integer class    */
    MAT_C_UINT32   = 13, /**< @brief Matlab unsigned 32-bit integer class  */
    MAT_C_INT64    = 14, /**< @brief Matlab signed 64-bit integer class    */
    MAT_C_UINT64   = 15, /**< @brief Matlab unsigned 64-bit integer class  */
    MAT_C_FUNCTION = 16, /**< @brief Matlab function class                 */
    MAT_C_OPAQUE   = 17  /**< @brief Matlab opaque class                   */
};

/** @brief Matlab array flags
 *
 * @ingroup MAT
 * Matlab array flags
 */
enum matio_flags {
    MAT_F_COMPLEX        = 0x0800, /**< @brief Complex bit flag */
    MAT_F_GLOBAL         = 0x0400, /**< @brief Global bit flag */
    MAT_F_LOGICAL        = 0x0200, /**< @brief Logical bit flag */
    MAT_F_DONT_COPY_DATA = 0x0001  /**< Don't copy data, use keep the pointer */
};

/** @brief MAT file compression options
 *
 * This option is only used on version 5 MAT files
 * @ingroup MAT
 */
enum matio_compression {
    MAT_COMPRESSION_NONE = 0,   /**< @brief No compression */
    MAT_COMPRESSION_ZLIB = 1    /**< @brief zlib compression */
};

/** @brief matio lookup type
 *
 * @ingroup MAT
 * matio lookup type
 */
enum {
    MAT_BY_NAME  = 1, /**< Lookup by name */
    MAT_BY_INDEX = 2  /**< Lookup by index */
};

/** @brief Complex data type using split storage
 *
 * Complex data type using split real/imaginary pointers
 * @ingroup MAT
 */
typedef struct mat_complex_split_t {
    void *Re; /**< Pointer to the real part */
    void *Im; /**< Pointer to the imaginary part */
} mat_complex_split_t;

struct _mat_t;
/** @brief Matlab MAT File information
 * Contains information about a Matlab MAT file
 * @ingroup MAT
 */
typedef struct _mat_t mat_t;

/* Incomplete definition for private library data */
struct matvar_internal;

/** @brief Matlab variable information
 *
 * Contains information about a Matlab variable
 * @ingroup MAT
 */
typedef struct matvar_t {
    size_t nbytes;                    /**< Number of bytes for the MAT variable */
    int    rank;                      /**< Rank (Number of dimensions) of the data */
    enum matio_types   data_type;     /**< Data type (MAT_T_*) */
    int   data_size;                  /**< Bytes / element for the data */
    enum matio_classes class_type;    /**< Class type in Matlab (MAT_C_DOUBLE, etc) */
    int   isComplex;                  /**< non-zero if the data is complex, 0 if real */
    int   isGlobal;                   /**< non-zero if the variable is global */
    int   isLogical;                  /**< non-zero if the variable is logical */
    size_t *dims;                     /**< Array of lengths for each dimension */
    char *name;                       /**< Name of the variable */
    void *data;                       /**< Pointer to the data */
    int   mem_conserve;               /**< 1 if Memory was conserved with data */
    enum matio_compression  compression; /**< Variable compression type */
    struct matvar_internal *internal;    /**< matio internal data */
} matvar_t;

/** @brief sparse data information
 *
 * Contains information and data for a sparse matrix
 * @ingroup MAT
 */
typedef struct mat_sparse_t {
    int nzmax;               /**< Maximum number of non-zero elements */
    mat_int32_t *ir;         /**< Array of size nzmax where ir[k] is the row of
                               *  data[k].  0 <= k <= nzmax
                               */
    int nir;                 /**< number of elements in ir */
    mat_int32_t *jc;         /**< Array size N+1 (N is number of columns) with
                               *  jc[k] being the index into ir/data of the
                               *  first non-zero element for row k.
                               */
    int   njc;               /**< Number of elements in jc */
    int   ndata;             /**< Number of complex/real data values */
    void *data;              /**< Array of data elements */
} mat_sparse_t;

/** @cond 0 */
#define MATIO_LOG_LEVEL_ERROR    1
#define MATIO_LOG_LEVEL_CRITICAL 1 << 1
#define MATIO_LOG_LEVEL_WARNING  1 << 2
#define MATIO_LOG_LEVEL_MESSAGE  1 << 3
#define MATIO_LOG_LEVEL_DEBUG    1 << 4
/** @endcond */

/* Library function */
EXTERN void Mat_GetLibraryVersion(int *major,int *minor,int *release);

/* io.c */
EXTERN char  *strdup_vprintf(const char *format, va_list ap) MATIO_FORMATATTR_VPRINTF;
EXTERN char  *strdup_printf(const char *format, ...) MATIO_FORMATATTR_PRINTF1;
EXTERN int    Mat_SetVerbose(int verb, int s);
EXTERN int    Mat_SetDebug(int d);
EXTERN void   Mat_Critical(const char *format, ...) MATIO_FORMATATTR_PRINTF1;
EXTERN MATIO_NORETURN void Mat_Error(const char *format, ...) MATIO_NORETURNATTR MATIO_FORMATATTR_PRINTF1;
EXTERN void   Mat_Help(const char *helpstr[]);
EXTERN int    Mat_LogInit(const char *prog_name);
EXTERN int    Mat_LogClose(void);
EXTERN int    Mat_LogInitFunc(const char *prog_name,
                  void (*log_func)(int log_level, char *message));
EXTERN int    Mat_Message(const char *format, ...) MATIO_FORMATATTR_PRINTF1;
EXTERN int    Mat_DebugMessage(int level, const char *format, ...) MATIO_FORMATATTR_PRINTF2;
EXTERN int    Mat_VerbMessage(int level, const char *format, ...) MATIO_FORMATATTR_PRINTF2;
EXTERN void   Mat_Warning(const char *format, ...) MATIO_FORMATATTR_PRINTF1;
EXTERN size_t Mat_SizeOf(enum matio_types data_type);
EXTERN size_t Mat_SizeOfClass(int class_type);

/* MAT File functions */
/** Create new Matlab MAT file */
#define            Mat_Create(a,b) Mat_CreateVer(a,b,MAT_FT_DEFAULT)
EXTERN mat_t      *Mat_CreateVer(const char *matname,const char *hdr_str,
                       enum mat_ft mat_file_ver);
EXTERN int         Mat_Close(mat_t *mat);
EXTERN mat_t      *Mat_Open(const char *matname,int mode);
EXTERN const char *Mat_GetFilename(mat_t *mat);
EXTERN const char *Mat_GetHeader(mat_t *mat);
EXTERN enum mat_ft Mat_GetVersion(mat_t *mat);
EXTERN char      **Mat_GetDir(mat_t *mat, size_t *n);
EXTERN int         Mat_Rewind(mat_t *mat);

/* MAT variable functions */
EXTERN matvar_t  *Mat_VarCalloc(void);
EXTERN matvar_t  *Mat_VarCreate(const char *name,enum matio_classes class_type,
                      enum matio_types data_type,int rank,size_t *dims,
                      void *data,int opt);
EXTERN matvar_t  *Mat_VarCreateStruct(const char *name,int rank,size_t *dims,
                      const char **fields,unsigned nfields);
EXTERN int        Mat_VarDelete(mat_t *mat, const char *name);
EXTERN matvar_t  *Mat_VarDuplicate(const matvar_t *in, int opt);
EXTERN void       Mat_VarFree(matvar_t *matvar);
EXTERN matvar_t  *Mat_VarGetCell(matvar_t *matvar,int index);
EXTERN matvar_t **Mat_VarGetCells(matvar_t *matvar,int *start,int *stride,
                      int *edge);
EXTERN matvar_t **Mat_VarGetCellsLinear(matvar_t *matvar,int start,int stride,
                      int edge);
EXTERN size_t     Mat_VarGetSize(matvar_t *matvar);
EXTERN unsigned   Mat_VarGetNumberOfFields(matvar_t *matvar);
EXTERN int        Mat_VarAddStructField(matvar_t *matvar,const char *fieldname);
EXTERN char * const *Mat_VarGetStructFieldnames(const matvar_t *matvar);
EXTERN matvar_t  *Mat_VarGetStructFieldByIndex(matvar_t *matvar,
                      size_t field_index,size_t index);
EXTERN matvar_t  *Mat_VarGetStructFieldByName(matvar_t *matvar,
                      const char *field_name,size_t index);
EXTERN matvar_t  *Mat_VarGetStructField(matvar_t *matvar,void *name_or_index,
                      int opt,int index);
EXTERN matvar_t  *Mat_VarGetStructs(matvar_t *matvar,int *start,int *stride,
                      int *edge,int copy_fields);
EXTERN matvar_t  *Mat_VarGetStructsLinear(matvar_t *matvar,int start,int stride,
                      int edge,int copy_fields);
EXTERN void       Mat_VarPrint(matvar_t *matvar, int printdata);
EXTERN matvar_t  *Mat_VarRead(mat_t *mat, const char *name);
EXTERN int        Mat_VarReadData(mat_t *mat,matvar_t *matvar,void *data,
                      int *start,int *stride,int *edge);
EXTERN int        Mat_VarReadDataAll(mat_t *mat,matvar_t *matvar);
EXTERN int        Mat_VarReadDataLinear(mat_t *mat,matvar_t *matvar,void *data,
                      int start,int stride,int edge);
EXTERN matvar_t  *Mat_VarReadInfo(mat_t *mat, const char *name);
EXTERN matvar_t  *Mat_VarReadNext(mat_t *mat);
EXTERN matvar_t  *Mat_VarReadNextInfo(mat_t *mat);
EXTERN matvar_t  *Mat_VarSetCell(matvar_t *matvar,int index,matvar_t *cell);
EXTERN matvar_t  *Mat_VarSetStructFieldByIndex(matvar_t *matvar,
                      size_t field_index,size_t index,matvar_t *field);
EXTERN matvar_t  *Mat_VarSetStructFieldByName(matvar_t *matvar,
                      const char *field_name,size_t index,matvar_t *field);
EXTERN int        Mat_VarWrite(mat_t *mat,matvar_t *matvar,
                      enum matio_compression compress);
EXTERN int        Mat_VarWriteAppend(mat_t *mat,matvar_t *matvar,
                      enum matio_compression compress,int dim);
EXTERN int        Mat_VarWriteInfo(mat_t *mat,matvar_t *matvar);
EXTERN int        Mat_VarWriteData(mat_t *mat,matvar_t *matvar,void *data,
                      int *start,int *stride,int *edge);

/* Other functions */
EXTERN int     Mat_CalcSingleSubscript(int rank,int *dims,int *subs);
EXTERN int     Mat_CalcSingleSubscript2(int rank,size_t *dims,size_t *subs,size_t *index);
EXTERN int    *Mat_CalcSubscripts(int rank,int *dims,int index);
EXTERN size_t *Mat_CalcSubscripts2(int rank,size_t *dims,size_t index);

#endif
