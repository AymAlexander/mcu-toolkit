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
 * Describe: MCU Toolkit Component: Buffer
 * Author:   Aym
 * Date:     2023-05-01
 */

#ifndef __MTK_BASIC_BUFFER_H__
#define __MTK_BASIC_BUFFER_H__

/* INCLUDE */
#include "mtk_typedefs.h"

#if MTK_ENABLE_COMPONENT_BUFFER

typedef struct {
    uint16_t    r;
    uint16_t    w;
    uint16_t    size;
    uint16_t    sizePerData : 15;
    uint16_t    is_stack    : 1;
    uint8_t     buf[1];
} mtk_buffer_t;

#endif /* MTK_ENABLE_COMPONENT_BUFFER */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_BUFFER

mtk_buffer_t* mtk_buffer_init (void* buf, uint16_t bufSize, uint16_t sizePerData);
mtk_ret_t mtk_buffer_read (mtk_buffer_t* buffer, void* read);
mtk_ret_t mtk_buffer_peak (mtk_buffer_t* buffer, void* read);
mtk_ret_t mtk_buffer_read_buf (mtk_buffer_t* buffer, void* buf, uint16_t num);
mtk_ret_t mtk_buffer_write (mtk_buffer_t* buffer, void* data);
mtk_ret_t mtk_buffer_write_buf (mtk_buffer_t* buffer, void* buf, uint16_t num);
mtk_ret_t mtk_buffer_flush (mtk_buffer_t* buffer);
uint16_t mtk_buffer_data_cnt (mtk_buffer_t* buffer);
uint16_t mtk_buffer_capcity (mtk_buffer_t* buffer);
uint16_t mtk_buffer_size (mtk_buffer_t* buffer);

#endif /* MTK_ENABLE_COMPONENT_BUFFER */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_BASIC_BUFFER_H__ */
