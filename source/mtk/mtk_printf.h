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
 * Describe: MCU Toolkit Component: Printf
 * Author:   Aym
 * Date:     2023-10-30
 */

#ifndef __MTK_PRINTF_H__
#define __MTK_PRINTF_H__

/* INCLUDE */
#include "mtk_typedefs.h"

typedef mtk_ret_t (*mtk_output)(char* buf, size_t size);

typedef enum mtk_loglv {
    mtk_log_dbug = 0,
    mtk_log_info,
    mtk_log_warn,
    mtk_log_erro,
} mtk_loglv_t;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

mtk_ret_t mtk_printf_init (char* buffer, size_t size, mtk_output output_fn);
mtk_ret_t mtk_printf (const char *restrict format, ...);
mtk_ret_t mtk_log_printf (mtk_loglv_t lv, const char* func, const char* str, ...);

#define mtk_logDBUG(...)   mtk_log_printf(mtk_log_dbug, __func__, __VA_ARGS__)
#define mtk_logINFO(...)  mtk_log_printf(mtk_log_info, __func__, __VA_ARGS__)
#define mtk_logWARN(...)  mtk_log_printf(mtk_log_warn, __func__, __VA_ARGS__)
#define mtk_logERRO(...)   mtk_log_printf(mtk_log_erro, __func__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_PRINTF_H__ */
