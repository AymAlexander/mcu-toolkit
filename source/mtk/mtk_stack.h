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
 * Describe: MCU Toolkit Component: Stack
 * Author:   Aym
 * Date:     2023-04-27
 */

#ifndef __MTK_STACK_H__
#define __MTK_STACK_H__

/* INCLUDE */
#include "mtk_typedefs.h"
#include "mtk_buffer.h"

#if MTK_ENABLE_COMPONENT_STACK

typedef mtk_buffer_t mtk_stack_t;

#endif /* MTK_ENABLE_COMPONENT_STACK */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_STACK

mtk_stack_t* mtk_stack_init (void* buf, uint16_t bufSize, uint16_t sizePerData);
mtk_ret_t mtk_stack_push (mtk_stack_t* stack, void* data);
mtk_ret_t mtk_stack_pop (mtk_stack_t* stack, void* read);
mtk_ret_t mtk_stack_flush (mtk_stack_t* stack);
uint16_t mtk_stack_data_cnt (mtk_stack_t* stack);
uint16_t mtk_stack_capacity (mtk_stack_t* stack);

#endif /* MTK_ENABLE_COMPONENT_STACK */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_STACK_H__ */
