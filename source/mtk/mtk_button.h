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

#ifndef __MTK_BUTTON_H__
#define __MTK_BUTTON_H__

/* INCLUDE */
#include "mtk_typedefs.h"

#if MTK_ENABLE_COMPONENT_BUTTON

#define MTK_BTN_EVT_NONE        0
#define MTK_BTN_EVT_DOWN        1
#define MTK_BTN_EVT_UP          2
#define MTK_BTN_EVT_N_CLICKS    3
#define MTK_BTN_EVT_HOLD        4
#define MTK_BTN_EVT_HOLD_UP     5

typedef void (*mtk_btn_cb)(void*);
typedef uint8_t (*mtk_btn_read)(void*);

typedef struct mtk_button
{
    struct mtk_button* next;

    mtk_btn_read  read;
    mtk_btn_cb    cb;

    uint16_t active_cnt;
    uint16_t click_cnt;
    uint16_t max_combo_gap;

    uint16_t hold_start_tick;

    uint8_t fix_sta      :4;           /* after debounce  */
    uint8_t rt_sta       :2;           /* real time value */
    uint8_t prev_rt_sta  :2;

    uint8_t low_valid    :1;
    uint8_t event        :4;
    uint8_t status       :3;
} mtk_button_t;

#endif /* MTK_ENABLE_COMPONENT_BUTTON */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_BUTTON

void mtk_button_manager_init (uint32_t call_freq_hz, uint32_t scan_hz);
void mtk_button_init (mtk_button_t* btn,
                      uint16_t      max_combo_gap_ms,
                      uint16_t      hold_start_ms,
                      uint8_t       low_valid,
                      mtk_btn_read  read,
                      mtk_btn_cb    cb);
void mtk_button_scan (void);

static inline uint8_t mtk_button_evt_down (mtk_button_t* btn)
{
    return (btn->event == MTK_BTN_EVT_DOWN);
}

static inline uint8_t mtk_button_evt_up (mtk_button_t* btn)
{
    return (btn->event == MTK_BTN_EVT_UP);
}

static inline uint8_t mtk_button_evt_holdup (mtk_button_t* btn)
{
    return (btn->event == MTK_BTN_EVT_HOLD_UP);
}

static inline uint8_t mtk_button_evt_holddown (mtk_button_t* btn)
{
    return (btn->event == MTK_BTN_EVT_HOLD);
}

static inline uint8_t mtk_button_evt_clicks (mtk_button_t* btn, uint32_t nClicks)
{
    if (btn->event == MTK_BTN_EVT_N_CLICKS) {
        return ((uint32_t)(btn->click_cnt) == nClicks);
    }

    return MTK_FALSE;
}

static inline uint8_t mtk_button_evt_hold_ms (mtk_button_t* btn, uint32_t duration)
{
    if (btn->event == MTK_BTN_EVT_HOLD) {
        return ((uint32_t)(btn->active_cnt) == duration / btn_mgr.period);
    }

    return MTK_FALSE;
}

#endif /* MTK_ENABLE_COMPONENT_BUTTON */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_BUTTON_H__ */
