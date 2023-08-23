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
 * Describe: MCU ToolKit Component: Timer
 * Author:   Aym
 * Date:     2023-08-17
 */

#ifndef __MTK_TIMER_H__
#define __MTK_TIMER_H__

/* INCLUDE */
#include "mtk_typedefs.h"

#if MTK_ENABLE_COMPONENT_TIMER

typedef void (*mtk_timer_cb)(void*);

typedef struct mtk_timer {
    struct mtk_timer* next;

    uint32_t ticks;
    uint32_t reload;

    mtk_timer_cb  cb;
    void* data;

    uint8_t autoReload : 1;
    uint8_t isTimeout  : 1;
    uint8_t isStart    : 1;
    uint8_t type       : 5;
} mtk_timer_t;

#endif /* TK_ENABLE_COMPONENT_TIMER */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_TIMER

void mtk_timer_manager_init (uint32_t call_freq_hz);
void mtk_timer_init (mtk_timer_t*  tmr,
                     uint32_t      ms,
                     uint8_t       autoReload,
                     mtk_timer_cb  cb,
                     void*         data);
void mtk_timer_onoff (mtk_timer_t* tmr, uint8_t on);
void mtk_timer_restart (mtk_timer_t* tmr);
void mtk_timer_set_period (mtk_timer_t* tmr, uint32_t period_ms);
uint8_t mtk_timer_isTimeout (mtk_timer_t* tmr);
uint32_t mtk_timer_get_time_ms (mtk_timer_t* tmr);

void mtk_timer_process (void);  /* Periodic Call */

#endif /* MTK_ENABLE_COMPONENT_TIMER */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_TIMER_H__ */
