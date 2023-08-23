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
 * Describe: MCU ToolKit Component: Timer
 * Author:   Aym
 * Date:     2023-08-17
 */

#include "mtk_timer.h"

#if MTK_ENABLE_COMPONENT_TIMER

static struct {
    float period;
    mtk_timer_t* tmr_head;
} tmr_mgr = {
    .period = 0,
    .tmr_head = NULL,
};

void mtk_timer_manager_init (uint32_t call_freq_hz)
{
    mtk_return_if_fail(call_freq_hz != 0);

    tmr_mgr.period = 1000 / call_freq_hz;
}

void mtk_timer_init (mtk_timer_t*  tmr,
                     uint32_t      ms,
                     uint8_t       autoReload,
                     mtk_timer_cb  cb,
                     void*         data)
{
    mtk_timer_t* timer = tmr_mgr.tmr_head;

    mtk_return_if_fail(tmr_mgr.period != 0);
    mtk_return_if_fail(tmr != NULL);

    /* Check list */
    while (timer != NULL) {
        if (timer == tmr) {
            return;
        }
        timer = tmr->next;
    }

    tmr->next = tmr_mgr.tmr_head;
    tmr_mgr.tmr_head = tmr;
    tmr->isStart = MTK_FALSE;
    tmr->isTimeout = MTK_FALSE;
    tmr->type = 0;

    tmr->ticks = ms / tmr_mgr.period;
    tmr->reload = tmr->ticks;
    tmr->autoReload = autoReload & 0x01;
    tmr->cb = cb;
    tmr->data = data;
}

void mtk_timer_onoff (mtk_timer_t* tmr, uint8_t on)
{
    mtk_return_if_fail(tmr != NULL);

    tmr->isStart = on;
}

void mtk_timer_restart (mtk_timer_t* tmr)
{
	mtk_return_if_fail(tmr != NULL);
    
    tmr->isTimeout = 0;
    tmr->ticks = tmr->reload;
    tmr->isStart = MTK_TRUE;
}

void mtk_timer_set_period (mtk_timer_t* tmr, uint32_t period_ms)
{
    mtk_return_if_fail(tmr != NULL);
    mtk_return_if_fail(period_ms != 0);
    
    tmr->ticks = period_ms / tmr_mgr.period;
    tmr->reload = tmr->ticks;
}

uint8_t mtk_timer_isTimeout (mtk_timer_t* tmr)
{
	mtk_return_value_if_fail(tmr != NULL, MTK_FALSE);
    
    if (tmr->isTimeout == MTK_TRUE) {
        tmr->isTimeout = MTK_FALSE;
        return MTK_TRUE;
    }
    return MTK_FALSE;
}

uint32_t mtk_timer_get_time_ms (mtk_timer_t* tmr)
{
    mtk_return_value_if_fail(tmr != NULL, MTK_FALSE);

    return (uint32_t)((tmr->reload - tmr->ticks) * tmr_mgr.period);
}

void mtk_timer_process (void)
{
	mtk_timer_t* tmr = tmr_mgr.tmr_head;

	while (tmr != NULL) {
		if (tmr->isStart == MTK_FALSE) {
			tmr = tmr->next;
			continue;
		}

		tmr->ticks--;
		
		if (tmr->ticks == 0) {
			tmr->isTimeout = MTK_TRUE;
			if (tmr->cb != NULL) {
                tmr->cb(tmr->data);
                tmr->isTimeout = MTK_FALSE;
            }
			if (tmr->autoReload == MTK_TRUE) {
				tmr->ticks = tmr->reload;
			} else {
				tmr->isStart = MTK_FALSE;
			}
		}
		tmr = tmr->next;
	}
}

#endif /* MTK_ENABLE_COMPONENT_TIMER */
