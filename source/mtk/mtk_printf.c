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

#include "mtk_printf.h"
#include "stdio.h"
#include "stdarg.h"

typedef struct mtk_printf {
    char* buffer;
    size_t buffer_size;
    mtk_output output_fn;
    uint8_t init;
} mtk_printf_t;

static mtk_printf_t mtk_printf_hdl = {
    .buffer = NULL,
    .buffer_size = 0,
    .output_fn = NULL,
    .init = 0
};

static const char* mtk_log_level[] = {
    "DBUG",
    "INFO",
    "WARN",
    "ERRO",
};

mtk_ret_t mtk_printf_init (char* buffer, size_t size, mtk_output output_fn)
{
    mtk_return_value_if_fail(mtk_printf_hdl.init == 0, mtk_ok);
    mtk_return_value_if_fail(buffer != NULL, mtk_fail);
    mtk_return_value_if_fail(size > 20, mtk_fail);
    mtk_return_value_if_fail(output_fn != NULL, mtk_fail);

    mtk_printf_hdl.buffer = buffer;
    mtk_printf_hdl.buffer_size = size;
    mtk_printf_hdl.output_fn = output_fn;

    mtk_printf_hdl.init = 1; 
    
    return mtk_ok;
}

mtk_ret_t mtk_printf (const char *restrict format, ...)
{
    va_list arglist;
    int32_t len;

    mtk_return_value_if_fail(mtk_printf_hdl.init == 1, mtk_fail);

    va_start(arglist, format);
    len = vsnprintf(mtk_printf_hdl.buffer, mtk_printf_hdl.buffer_size, format, arglist);
    va_end(arglist);

    if ((len > 0) && (len < mtk_printf_hdl.buffer_size)) {
        return mtk_printf_hdl.output_fn(mtk_printf_hdl.buffer, len);
    } else {
        return mtk_fail;
    }
}

mtk_ret_t mtk_log_printf (mtk_loglv_t lv, const char* func, const char* str, ...)
{
    va_list arglist;
    int32_t len;
    int32_t len2;

    mtk_return_value_if_fail(mtk_printf_hdl.init == 1, mtk_fail);

    len = snprintf(mtk_printf_hdl.buffer, mtk_printf_hdl.buffer_size, "[%s](%s) ", mtk_log_level[lv], func);

    if (!((len > 0) && (len < mtk_printf_hdl.buffer_size))) {
        return mtk_fail;
    }

    va_start(arglist, str);
    len2 = vsnprintf(&(mtk_printf_hdl.buffer[len]), mtk_printf_hdl.buffer_size - len, str, arglist);
    va_end(arglist);

    if ((len2 > 0) && (len2 + len < mtk_printf_hdl.buffer_size)) {
        return mtk_printf_hdl.output_fn(mtk_printf_hdl.buffer, len+len2);
    } else {
        return mtk_fail;
    }

}
