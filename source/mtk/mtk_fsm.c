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

#include "mtk_fsm.h"

#if MTK_ENABLE_COMPONENT_FSM

static mtk_fsm_trans_t* mtk_get_trans (mtk_fsm_state_t* state, mtk_fsm_evt_t* event)
{
    mtk_fsm_trans_t* trans;
    uint32_t i;

    for (i = 0; i < state->trans_num; i++) {
        trans = &state->transitions[i];

        if (trans->event_type != event->event_type) {
            continue;
        }

        if (trans->guard == NULL || trans->guard(event)) {
            return trans;
        }
    }

    return NULL;
}

void mtk_fsm_init (mtk_fsm_mgr_t* fsm, mtk_fsm_state_t* first_state)
{
    mtk_return_if_fail(fsm != NULL || first_state != NULL);

    fsm->currstate = first_state;
}

mtk_fsm_state_t* mtk_fsm_current_state (mtk_fsm_mgr_t* fsm)
{
    mtk_return_value_if_fail(fsm != NULL, NULL);
    return fsm->currstate;
}

mtk_ret_t mtk_fsm_process (mtk_fsm_mgr_t* fsm, mtk_fsm_evt_t* event)
{
    mtk_fsm_state_t* nextstate;
    mtk_fsm_trans_t* trans;

    uint32_t i;

    mtk_return_value_if_fail(fsm != NULL || event != NULL, mtk_fail);
    mtk_return_value_if_fail(fsm->currstate != NULL, mtk_fail);
    mtk_return_value_if_fail(fsm->currstate->trans_num != 0, mtk_ok);

    nextstate = fsm->currstate;

    trans = mtk_get_trans(fsm->currstate, event);

    mtk_return_value_if_fail(trans != NULL, mtk_ok);
    mtk_return_value_if_fail(trans->nextstate != NULL, mtk_fail);

    nextstate = trans->nextstate;

    if (nextstate != fsm->currstate && fsm->currstate->exit != NULL) {
        fsm->currstate->exit(fsm->currstate->data, event);
    }

    if (trans->action != NULL) {
        trans->action(fsm->currstate->data, nextstate->data, event);
    }

    if (nextstate != fsm->currstate && nextstate->entry != NULL) {
        nextstate->entry(nextstate->data, event);
    }

    fsm->currstate = nextstate;

    return mtk_ok;
}

#endif /* MTK_ENABLE_COMPONENT_FSM */
