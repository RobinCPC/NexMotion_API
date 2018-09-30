/*!
 * @file        nex_type.h
 * @brief       A head file define variable types for NexMotion Library
 * @author      NexCOBOT, Inc.
 */

#ifndef __NEX_TYPE_H
#define __NEX_TYPE_H

/*****************************************************************
Copyright (c) NEXCOM International Co., Ltd. All Rights Reserved.
Variable type define. For cross compile
*******************************************************************/

#include <inttypes.h>

typedef int                 BOOL_T;  //!< 0:False, else:True
typedef unsigned char       U8_T;    //!< 0 ~ 255
typedef unsigned short      U16_T;   //!< 0 ~ 65535
typedef unsigned int        U32_T;   //!< 0 ~ 4294967295
#if (_MSC_VER)
typedef unsigned __int64    U64_T;   //!< 0 ~ 18446744073709551615
#else
typedef unsigned long long  U64_T;   //!< 0 ~ 18446744073709551615
#endif

typedef char                I8_T;    //!< -128 ~ 127
typedef short               I16_T;   //!< -32768 ~ 32767
typedef int                 I32_T;   //!< -2147483648 ~ 2147483647
#if (_MSC_VER)
typedef __int64             I64_T;   //!< -9223372036854775808 ~ 9223372036854775807
#else
typedef long long           I64_T;   //!< -9223372036854775808 ~ 9223372036854775807
#endif

typedef float               F32_T;   //!< Single precision floating point
typedef double              F64_T;   //!< Double precision floating point

typedef I32_T               RTN_ERR; //!< Return code. Return error code. See error_code define file (NexMotionError.h).


#define I32_T_MAX  ( 2147483647)     //!< Define I32_T_MAX to present maximum value of integer type.
#define I32_T_MIN  (-2147483648)     //!< Define I32_T_MIN to present minimum value of integer type.

#define BOOL_TRUE  (1)               //!< Define BOOL_TRUE to present true value (1).
#define BOOL_FALSE (0)               //!< Define BOOL_FALSE to present false value (0).


#define _opt_null_                   //!< It enable input pointer can be null.

#endif

