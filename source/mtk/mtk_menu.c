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
 * Describe: MCU Toolkit Component: Menu tool
 * Author:   Aym
 * Date:     2023-08-18
 */

#include "mtk_menu.h"

#if MTK_ENABLE_COMPONENT_MENU

void mtk_menu_quit (mtk_menustate_t* ms)
{
    mtk_return_if_fail(ms->curr_menupage->parent != NULL);

    ms->top = ms->curr_menupage->last_top;
    ms->curr_index = ms->curr_menupage->last_index;
    ms->curr_menupage = ms->curr_menupage->parent;
}

void mtk_menu_enter (mtk_menustate_t* ms)
{
    if (mtk_menu_curr_item(ms)->cb != NULL) {
        mtk_menu_curr_item(ms)->cb(ms->data);
    } else if (mtk_menu_curr_item(ms)->child != NULL) {
        mtk_menu_curr_item(ms)->child->last_top = ms->top;
        mtk_menu_curr_item(ms)->child->last_index = ms->curr_index;
        ms->curr_menupage = mtk_menu_curr_item(ms)->child;
        ms->top = 0;
        ms->curr_index = 0;
    }
}

void mtk_menu_prev (mtk_menustate_t* ms)
{
    if (ms->curr_index != 0) {
        ms->curr_index -= 1;
        if (ms->top > ms->curr_index) {
            ms->top -= 1;
        }
    } else {
        if (ms->curr_menupage->menuitem_num > ms->max_rows) {
            ms->top = (ms->curr_menupage->menuitem_num - ms->max_rows);
        }
        ms->curr_index = ms->curr_menupage->menuitem_num - 1;
    }
}

void mtk_menu_next (mtk_menustate_t* ms)
{
    if (ms->curr_index != ms->curr_menupage->menuitem_num - 1) {
        ms->curr_index++;
        if (ms->curr_index - ms->top == ms->max_rows) {
            ms->top++;
        }
    } else {
        ms->top = 0;
        ms->curr_index = 0;
    }
}

void mtk_menu_process (mtk_menustate_t* ms)
{
    ms->cb(ms);
}

#endif /* MTK_ENABLE_COMPONENT_MENU */
