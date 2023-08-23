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

#include "mtk_darray.h"

#if MTK_ENABLE_COMPONENT_DARRAY

mtk_ret_t mtk_darray_init (mtk_darray_t* da, uint32_t size, uint32_t sizePerData)
{
    uint32_t total_size = size * sizePerData;

    mtk_return_value_if_fail(total_size != 0, mtk_fail);
    mtk_return_value_if_fail(total_size >= size && total_size >= sizePerData, mtk_fail);

    da->buf = mtk_calloc(1, total_size);
    
    mtk_return_value_if_fail(da->buf != NULL, mtk_fail);

    da->capacity = size;
    da->lastDataIndex = -1;
    da->sizePerData = sizePerData;

    return mtk_ok;
}

mtk_ret_t mtk_darray_append (mtk_darray_t* da, void* data)
{
    void* extend;

    mtk_return_value_if_fail(da != NULL, mtk_fail);
    mtk_return_value_if_fail(data != NULL, mtk_fail);

    if (da->lastDataIndex + 1 >= da->capacity) {
        extend = mtk_realloc(da->buf, (da->capacity * 3 / 2) * da->sizePerData);
        mtk_return_value_if_fail(extend != NULL, mtk_oom);
        da->buf = extend;
        da->capacity = da->capacity * 3 / 2;
        memset(da->buf + (da->lastDataIndex + 1) * da->sizePerData, 0, (da->capacity - da->lastDataIndex - 1) * da->sizePerData);
    }

    memcpy(da->buf + (da->lastDataIndex + 1) * da->sizePerData, data, da->sizePerData);

    da->lastDataIndex++;

    return mtk_ok;
}

mtk_ret_t mtk_darray_remove (mtk_darray_t* da, int32_t index)
{
    mtk_return_value_if_fail(da != NULL, mtk_fail);
    mtk_return_value_if_fail(da->lastDataIndex >= 0, mtk_oom);

    if (index < 0) {
        index = da->capacity + index;
    }

    mtk_return_value_if_fail(index <= da->lastDataIndex, mtk_oom);

    memcpy(da->buf + index * da->sizePerData, da->buf + index * da->sizePerData + da->sizePerData, (da->lastDataIndex - index) * da->sizePerData);
    memset(da->buf + da->lastDataIndex * da->sizePerData, 0, da->sizePerData);
    da->lastDataIndex--;
    

    return mtk_ok;
}

mtk_ret_t mtk_darray_set (mtk_darray_t* da, int32_t index, void* data)
{
    mtk_return_value_if_fail(da != NULL, mtk_fail);
    mtk_return_value_if_fail(data != NULL, mtk_fail);

    if (index < 0) {
        index = da->capacity + index;
    }

    mtk_return_value_if_fail(index + 1 <= da->lastDataIndex, mtk_oom);
    
    memcpy(da->buf + index * da->sizePerData, data, da->sizePerData);
    
    return mtk_ok;
}

mtk_ret_t mtk_darray_get (mtk_darray_t* da, int32_t index, void* read)
{
    mtk_return_value_if_fail(da != NULL, mtk_fail);
    mtk_return_value_if_fail(read != NULL, mtk_fail);

    if (index < 0) {
        index = da->capacity + index;
    }    

    mtk_return_value_if_fail(index + 1 <= da->lastDataIndex, mtk_oom);

    memcpy(read, da->buf + index * da->sizePerData, da->sizePerData);

    return mtk_ok;
}

#endif /* MTK_ENABLE_COMPONENT_DARRAY */
