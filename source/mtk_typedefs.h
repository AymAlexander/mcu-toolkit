/*
 * This file is part of MCU Toolkit Library.
 *
 * Copyright (c) 2023, Aym, <aymhzy@163.com> 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Describe: MCU Toolkit typedefs
 * Author:   Aym
 * Date:     2023-04-26
 */

#ifndef __MTK_TYPEDEFS_H__
#define __MTK_TYPEDEFS_H__

/* INCLUDE */
#include "stdint.h"
#include "string.h"

#include "mtk_config.h"

#define MTK_TRUE    1
#define MTK_FALSE   0

#define mtk_break_if_fail(p) \
    if (!(p)) {              \
        break;               \
    }

#define mtk_return_if_fail(p) \
    if (!(p)) {               \
        return;               \
    }

#define mtk_return_value_if_fail(p, value) \
    if (!(p)) {                            \
        return (value);                    \
    }

#define mtk_goto_error_if_fail(p) \
    if (!(p)) {                   \
        goto error;               \
    }

#define mtk_min(a, b)   ((a)<(b)?(a):(b))
#define mtk_max(a, b)   ((a)<(b)?(b):(a))
#define mtk_abs(a)      ((a)<(0)?-(a):(a))
#define mtk_align(a, n) (((a)/(n))*(n))

typedef enum __mtk_ret_t {
    mtk_oom     = -2,
    mtk_fail    = -1,
    mtk_ok      = 0,
    mtk_empty   = 1,
    mtk_full    = 2,
} mtk_ret_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_TYPEDEFS_H__ */
