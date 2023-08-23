/*
 *  This file is part of MCU Toolkit Library.
 *
 *  Copyright (c) 2023, Aym, <aymhzy@163.com> 
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 * Describe: MCU Toolkit Component: Memory Pool
 * Author:   Aym
 * Date:     2023-04-27
 */

#ifndef __MTK_MEMPOOL_H__
#define __MTK_MEMPOOL_H__

/* INCLUDE */
#include "mtk_typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_MEMPOOL

void mtk_mempool_init (void);
void* mtk_malloc (uint32_t size);
void* mtk_calloc(uint32_t num, uint32_t size);
void* mtk_realloc (void* addr, uint32_t size);
void mtk_free (void* addr);

uint32_t mtk_mempool_size_get (void);
uint32_t mtk_mempool_max_usage_get (void);
uint32_t mtk_mempool_free_bytes_get (void);

#endif /* MTK_ENABLE_COMPONENT_MEMPOOL */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_MEMPOOL_H__ */
