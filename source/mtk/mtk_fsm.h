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
 * Describe: MCU ToolKit Component: Finite state machine
 * Author:   Aym
 * Date:     2023-08-21
 */

#ifndef __MTK_FSM_H__
#define __MTK_FSM_H__

/* INCLUDE */
#include "mtk_typedefs.h"

#if MTK_ENABLE_COMPONENT_FSM

typedef struct mtk_fsm_evt mtk_fsm_evt_t;
typedef struct mtk_fsm_trans mtk_fsm_trans_t;
typedef struct mtk_fsm_state mtk_fsm_state_t;

typedef uint8_t (*mtk_fsm_guard)(mtk_fsm_evt_t* evt);
typedef void (*mtk_fsm_trans_action)(void* currstate_data, void* nextstate_data, mtk_fsm_evt_t* evt);
typedef void (*mtk_fsm_action)(void* state_data, mtk_fsm_evt_t* evt);

typedef struct mtk_fsm_evt {
    uint32_t event_type;
    void* data;
} mtk_fsm_evt_t;

typedef struct mtk_fsm_trans {
    uint32_t event_type;
    mtk_fsm_guard guard;
    mtk_fsm_trans_action action;
    mtk_fsm_state_t* nextstate;
} mtk_fsm_trans_t;

typedef struct mtk_fsm_state {
    mtk_fsm_trans_t* transitions;
    uint32_t trans_num;
    void* data;
    mtk_fsm_action entry;
    mtk_fsm_action exit;
} mtk_fsm_state_t;

typedef struct mtk_fsm_mgr {
    mtk_fsm_state_t* currstate;
} mtk_fsm_mgr_t;

#endif /* MTK_ENABLE_COMPONENT_FSM */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_FSM

void mtk_fsm_init (mtk_fsm_mgr_t* fsm, mtk_fsm_state_t* first_state);
mtk_fsm_state_t* mtk_fsm_current_state (mtk_fsm_mgr_t* fsm);
mtk_ret_t mtk_fsm_process (mtk_fsm_mgr_t* fsm, mtk_fsm_evt_t* event);

#endif /* MTK_ENABLE_COMPONENT_FSM */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_FSM_H__ */
