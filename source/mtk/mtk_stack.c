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
 * Describe: MCU Toolkit Component: Stack
 * Author:   Aym
 * Date:     2023-04-27
 */

#include "mtk_stack.h"

#if MTK_ENABLE_COMPONENT_STACK

mtk_stack_t* mtk_stack_init (void* buf, uint16_t bufSize, uint16_t sizePerData)
{
    mtk_stack_t* stack;
    stack = mtk_buffer_init(buf, bufSize, sizePerData);
    mtk_return_value_if_fail(stack != NULL, NULL);

    stack->is_stack = MTK_TRUE;

    return stack;
}

mtk_ret_t mtk_stack_push (mtk_stack_t* stack, void* data)
{
    uint16_t write = stack->w;

    mtk_return_value_if_fail(stack != NULL, mtk_fail);
    mtk_return_value_if_fail(stack->is_stack == MTK_TRUE, mtk_fail);
    mtk_return_value_if_fail(write + stack->sizePerData != stack->r, mtk_full);
    
    memcpy(&stack->buf[stack->w], data, stack->sizePerData);
    stack->r = stack->w;
    stack->w += stack->sizePerData;
    
    return mtk_ok;
}

mtk_ret_t mtk_stack_pop (mtk_stack_t* stack, void* read)
{
    mtk_ret_t ret;

    mtk_return_value_if_fail(stack != NULL, mtk_fail);
    mtk_return_value_if_fail(stack->is_stack == MTK_TRUE, mtk_fail);
    mtk_return_value_if_fail(stack->r != stack->w, mtk_empty);

    ret = mtk_buffer_peak (stack, read);
    mtk_return_value_if_fail(ret == mtk_ok, ret);

    stack->w = stack->r;
    stack->r -= stack->sizePerData;

    return ret;
}

mtk_ret_t mtk_stack_flush (mtk_stack_t* stack)
{
    return mtk_buffer_flush(stack);
}

uint16_t mtk_stack_data_cnt (mtk_stack_t* stack)
{
    return mtk_buffer_data_cnt(stack);
}

uint16_t mtk_stack_capcity (mtk_stack_t* stack)
{
    return mtk_buffer_capcity(stack);
}

uint16_t mtk_stack_size (mtk_stack_t* stack)
{
    return mtk_buffer_size(stack);
}

#endif /* MTK_ENABLE_COMPONENT_STACK */
