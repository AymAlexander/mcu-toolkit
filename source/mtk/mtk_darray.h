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
 * Describe: MCU Toolkit Component: Dynamic Array
 * Author:   Aym
 * Date:     2023-04-27
 */

#ifndef __MTK_DARRAY_H__
#define __MTK_DARRAY_H__

/* INCLUDE */
#include "mtk_typedefs.h"
#include "mtk_mempool.h"

#if MTK_ENABLE_COMPONENT_DARRAY

typedef struct _mtk_darray {
    uint32_t  capacity;
    int32_t   lastDataIndex;
    uint32_t  sizePerData;
    uint8_t*  buf;
} mtk_darray_t;

#endif /* MTK_ENABLE_COMPONENT_DARRAY */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_DARRAY

mtk_ret_t mtk_darray_init (mtk_darray_t* da, uint32_t size, uint32_t sizePerData);
mtk_ret_t mtk_darray_append (mtk_darray_t* da, void* data);
mtk_ret_t mtk_darray_remove (mtk_darray_t* da, int32_t index);
mtk_ret_t mtk_darray_set (mtk_darray_t* da, int32_t index, void* data);
mtk_ret_t mtk_darray_get (mtk_darray_t* da, int32_t index, void* read);

#endif /* MTK_ENABLE_COMPONENT_DARRAY */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_DARRAY_H__ */
