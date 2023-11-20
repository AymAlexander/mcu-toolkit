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
 * Describe: MCU Toolkit Component: Button
 * Author:   Aym
 * Date:     2023-08-17
 */

#include "mtk_button.h"

#if MTK_ENABLE_COMPONENT_BUTTON

#define MTK_BTN_STA_RELEASE     0
#define MTK_BTN_STA_ACTIVE      1
#define MTK_BTN_STA_CLICK       2

#define MTK_BTN_CB(btn, evt)        \
        do {                        \
            btn->event = evt;       \
            if (btn->cb != NULL) {  \
                btn->cb(btn);       \
            }                       \
        } while(0)                  \

static struct {
    uint32_t      period;
    mtk_button_t* btn_head;
} btn_mgr = {
    .period = 0,
    .btn_head = NULL,
};

void mtk_button_manager_init (uint32_t call_freq_hz, uint32_t scan_hz)
{
    mtk_return_if_fail(call_freq_hz != 0 && scan_hz != 0);
    mtk_return_if_fail(scan_hz <= call_freq_hz);
    
    btn_mgr.period = call_freq_hz / scan_hz;
}

void mtk_button_init (mtk_button_t* btn,
                      uint16_t      max_combo_gap_ms,
                      uint16_t      hold_start_ms,
                      uint8_t       low_valid,
                      mtk_btn_read  read,
                      mtk_btn_cb    cb)
{
    mtk_button_t *button = btn_mgr.btn_head;

    mtk_return_if_fail(btn != NULL);
    mtk_return_if_fail(read != NULL);
    mtk_return_if_fail(btn_mgr.period != 0);

    /* Check list */
    while (button != NULL) {
        if (button == btn) {
            return;
        }
        button = button->next;
    }

    memset(btn, 0, sizeof(mtk_button_t));

    btn->next = btn_mgr.btn_head;
    btn_mgr.btn_head = btn;

    btn->max_combo_gap = max_combo_gap_ms / btn_mgr.period;
    btn->hold_start_tick = hold_start_ms / btn_mgr.period;
    btn->low_valid = low_valid;
    btn->read = read;
    btn->cb = cb;
}

static void __mtk_btn_readall (void)
{
    mtk_button_t* btn = NULL;

    for (btn = btn_mgr.btn_head; btn != NULL; btn = btn->next) {
        btn->prev_rt_sta = btn->rt_sta;
        btn->rt_sta = btn->read(btn)^btn->low_valid;
        if (btn->rt_sta == btn->prev_rt_sta) {
            btn->fix_sta = btn->rt_sta;
        }
    }
}

static void __mtk_btn_process (void)
{
    mtk_button_t* btn;

    for (btn = btn_mgr.btn_head; btn != NULL; btn = btn->next) {
        if (btn->status != MTK_BTN_STA_RELEASE) {
            if (btn->active_cnt < 0xFFFF) {
                btn->active_cnt++;
            }
        }

        switch (btn->status) {
        case MTK_BTN_STA_RELEASE:
            if (btn->fix_sta == MTK_TRUE) {
                btn->active_cnt = 0;
                btn->click_cnt = 0;

                MTK_BTN_CB(btn, MTK_BTN_EVT_DOWN);

                btn->status = MTK_BTN_STA_ACTIVE;
            } else {
                btn->event = MTK_BTN_EVT_NONE;
            }
            break;

        case MTK_BTN_STA_ACTIVE:
            if (btn->fix_sta == MTK_TRUE) {
                if (btn->click_cnt > 0) {
                    if (btn->active_cnt >= btn->max_combo_gap) {
                        MTK_BTN_CB(btn, MTK_BTN_EVT_N_CLICKS);
                        btn->click_cnt = 0;
                    }
                }
                
                if (btn->active_cnt >= btn->hold_start_tick) {
                    MTK_BTN_CB(btn, MTK_BTN_EVT_HOLD);
                }
            } else {
                if (btn->active_cnt >= btn->hold_start_tick) {
                    MTK_BTN_CB(btn, MTK_BTN_EVT_HOLD_UP);
                    btn->status = MTK_BTN_STA_RELEASE;
                } else {
                    btn->click_cnt++;
                    MTK_BTN_CB(btn, MTK_BTN_EVT_UP);
                    btn->status = MTK_BTN_STA_CLICK;
                }
            }
            break;

        case MTK_BTN_STA_CLICK:
            if (btn->fix_sta == MTK_TRUE) {
                MTK_BTN_CB(btn, MTK_BTN_EVT_DOWN);
                btn->status = MTK_BTN_STA_ACTIVE;
                btn->active_cnt = 0;
            } else {
                if (btn->active_cnt >= btn->max_combo_gap) {
                    MTK_BTN_CB(btn, MTK_BTN_EVT_N_CLICKS);
                    btn->status = MTK_BTN_STA_RELEASE;
                    btn->event = MTK_BTN_EVT_NONE;
                    btn->click_cnt = 0;
                }
            }
            break;
        }
    }
}

void mtk_button_scan (void)
{
    static uint32_t cnt = 0;

    if (cnt++ == btn_mgr.period) {
        __mtk_btn_readall();
        __mtk_btn_process();
        cnt = 0;
    }
}

#endif /* MTK_ENABLE_COMPONENT_BUTTON */
