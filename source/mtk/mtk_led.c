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

#include "mtk_led.h"

#if MTK_ENABLE_COMPONENT_LED

mtk_led_t* led_head = NULL;

static void __mtk_led_tmr_cb (void* arg)
{
    mtk_led_t* led = (mtk_led_t*)arg;
    led->ctrl = !led->status;
}

void mtk_led_init (mtk_led_t* led, void* hardware_info, led_ctrl led_handle)
{
    mtk_led_t* led_itor = led_head;

    mtk_return_if_fail(led != NULL);
    mtk_return_if_fail(led_handle != NULL);

    /* Check list */
    while (led_itor != NULL) {
        if (led_itor == led) {
            return;
        }
        led_itor = led_itor->next;
    }

    memset(led, 0, sizeof(mtk_led_t));

    led->next = led_head;
    led_head = led;

    mtk_timer_init(&led->tmr, 0, 1, __mtk_led_tmr_cb, led);
    led->hardware_info = hardware_info;
    led->led_handle = led_handle;
    led->led_handle(led->ctrl, led->hardware_info);
}

void mtk_led_onoff_now (mtk_led_t* led, uint8_t on)
{
    mtk_return_if_fail(led != NULL);
    
    led->ctrl = on;
    led->status = led->ctrl;

    if (led->flash == MTK_TRUE) {
        led->flash = MTK_FALSE;
        mtk_timer_onoff(&led->tmr, led->flash);
    }
    
    led->led_handle(led->status, led->hardware_info);
}

void mtk_led_onoff (mtk_led_t* led, uint8_t on)
{
    mtk_return_if_fail(led != NULL);
    
    led->ctrl = on;

    if (led->flash == MTK_TRUE) {
        led->flash = MTK_FALSE;
        mtk_timer_onoff(&led->tmr, led->flash);
    }
}

void mtk_led_toggle_now (mtk_led_t* led)
{
    mtk_return_if_fail(led != NULL);
    
    led->ctrl = !led->status;
    led->status = !led->status;

    if (led->flash == MTK_TRUE) {
        led->flash = MTK_FALSE;
        mtk_timer_onoff(&led->tmr, led->flash);
    }

    led->led_handle(led->status, led->hardware_info);
}

void mtk_led_toggle (mtk_led_t* led)
{
    mtk_return_if_fail(led != NULL);
    
    led->ctrl = !led->status;
    if (led->flash == MTK_TRUE) {
        led->flash = MTK_FALSE;
        mtk_timer_onoff(&led->tmr, led->flash);
    }
}

void mtk_led_flash (mtk_led_t* led, uint32_t period_ms)
{
    mtk_return_if_fail(led != NULL);
    mtk_return_if_fail(period_ms != 0);
    mtk_return_if_fail(led->flash != MTK_TRUE || led->flash_period_ms != period_ms);

    led->flash_period_ms = period_ms;
    mtk_timer_set_period(&led->tmr, led->flash_period_ms);
    led->flash = MTK_TRUE;
    mtk_timer_onoff(&led->tmr, led->flash);
}

void mtk_led_process (void)
{
    mtk_led_t* led = NULL;

    for (led = led_head; led != NULL; led = led->next) {
        if (led->status != led->ctrl) {
            led->led_handle(led->status, led->hardware_info);
            led->status = led->ctrl;
        }
    }
}

#endif /* MTK_ENABLE_COMPONENT_LED */
