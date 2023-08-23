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

#include "mtk_buffer.h"

#if MTK_ENABLE_COMPONENT_BUFFER

mtk_buffer_t* mtk_buffer_init (void* buf, uint16_t bufSize, uint16_t sizePerData)
{
    mtk_buffer_t* buffer;

    mtk_return_value_if_fail(buf != NULL, NULL);
    mtk_return_value_if_fail(bufSize >= sizeof(mtk_buffer_t), NULL);
    mtk_return_value_if_fail(sizePerData != 0, NULL);

    buffer = (mtk_buffer_t*)buf;
    buffer->size = mtk_align((bufSize - (uint16_t)(((mtk_buffer_t*)0)->buf)), sizePerData);
    buffer->r = 0;
    buffer->w = 0;
    buffer->is_stack = MTK_FALSE;
    buffer->sizePerData = sizePerData;

    return buffer;
}

mtk_ret_t mtk_buffer_read (mtk_buffer_t* buffer, void* read)
{
    mtk_return_value_if_fail(buffer != NULL, mtk_fail);
    mtk_return_value_if_fail(buffer->is_stack == MTK_FALSE, mtk_fail);
    mtk_return_value_if_fail(buffer->r != buffer->w, mtk_empty);

    memcpy(read, &buffer->buf[buffer->r], buffer->sizePerData);
    buffer->r += buffer->sizePerData;

    if (buffer->r >= buffer->size) {
        buffer->r = 0;
    }

    return mtk_ok;
}

mtk_ret_t mtk_buffer_peak (mtk_buffer_t* buffer, void* read)
{
    mtk_return_value_if_fail(buffer != NULL, mtk_fail);
    mtk_return_value_if_fail(buffer->r != buffer->w, mtk_empty);

    memcpy(read, &buffer->buf[buffer->r], buffer->sizePerData);

    return mtk_ok;
}

mtk_ret_t mtk_buffer_read_buf (mtk_buffer_t* buffer, void* buf, uint16_t num)
{
    mtk_ret_t ret;
    uint8_t* readBuf;

    readBuf = (uint8_t*)buf;

    while (num--) {
        ret = mtk_buffer_read(buffer, readBuf);
        mtk_break_if_fail(ret != mtk_ok);
        readBuf += buffer->sizePerData;
    }

    return ret;
}

mtk_ret_t mtk_buffer_write (mtk_buffer_t* buffer, void* data)
{
    mtk_return_value_if_fail(buffer != NULL, mtk_fail);
    mtk_return_value_if_fail(buffer->is_stack == MTK_FALSE, mtk_fail);
    if (buffer->w + buffer->sizePerData >= buffer->size) {
        mtk_return_value_if_fail(0 != buffer->r, mtk_full);
    } else {
        mtk_return_value_if_fail(buffer->w + buffer->sizePerData != buffer->r, mtk_full);
    }
    
    memcpy(&buffer->buf[buffer->w], data, buffer->sizePerData);
    buffer->w += buffer->sizePerData;
    
    if (buffer->w >= buffer->size) {
        buffer->w = 0;
    }
    
    return mtk_ok;
}

mtk_ret_t mtk_buffer_write_buf (mtk_buffer_t* buffer, void* buf, uint16_t num)
{
    mtk_ret_t ret;
    uint8_t* writeBuf;

    writeBuf = (uint8_t*)buf;

    while (num--) {
        ret = mtk_buffer_write(buf, writeBuf);
        mtk_break_if_fail(ret != mtk_ok);
        writeBuf += buffer->sizePerData;
    }

    return ret;
}

mtk_ret_t mtk_buffer_flush (mtk_buffer_t* buffer)
{   
    mtk_return_value_if_fail(buffer != NULL, mtk_fail);
    
    buffer->r = 0;
    buffer->w = 0;

    return mtk_ok;
}

uint16_t mtk_buffer_data_cnt (mtk_buffer_t* buffer)
{
    mtk_return_value_if_fail(buffer != NULL, 0);
    
    if (buffer->w >= buffer->r) {
        return (buffer->w - buffer->r) / buffer->sizePerData;
    } else {
        return (buffer->size - (buffer->r - buffer->w)) / buffer->sizePerData;
    }
}

uint16_t mtk_buffer_capcity (mtk_buffer_t* buffer)
{
    mtk_return_value_if_fail(buffer != NULL, 0);
    
    return buffer->size / buffer->sizePerData - 1;
}

uint16_t mtk_buffer_size (mtk_buffer_t* buffer)
{
    mtk_return_value_if_fail(buffer != NULL, 0);
    
    return buffer->size;
}

#endif /* MTK_ENABLE_COMPONENT_BUFFER */
