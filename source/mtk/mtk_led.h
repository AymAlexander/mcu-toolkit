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
 * Describe: MCU Toolkit Component: LED Control
 * Author:   Aym
 * Date:     2023-08-21
 */

#ifndef __MTK_LED_H__
#define __MTK_LED_H__

/* INCLUDE */
#include "mtk_typedefs.h"
#include "mtk_timer.h"

#if MTK_ENABLE_COMPONENT_LED

typedef void (*led_ctrl)(uint8_t, void*);

typedef struct mtk_led {
    struct mtk_led* next;

    mtk_timer_t tmr;
    void* hardware_info;
    led_ctrl led_handle;

    uint16_t flash_period_ms;
    uint8_t ctrl:1;
    uint8_t status:1;
    uint8_t flash:1;
    uint8_t pad:5;
} mtk_led_t;

#endif /* MTK_ENABLE_COMPONENT_LED */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_LED

void mtk_led_init (mtk_led_t* led, void* hardware_info, led_ctrl led_handle);
void mtk_led_onoff_now (mtk_led_t* led, uint8_t on);
void mtk_led_onoff (mtk_led_t* led, uint8_t on);
void mtk_led_toggle_now (mtk_led_t* led);
void mtk_led_toggle (mtk_led_t* led);
void mtk_led_flash (mtk_led_t* led, uint32_t period_ms);
void mtk_led_process (void);

#endif /* MTK_ENABLE_COMPONENT_LED */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_LED_H__ */
