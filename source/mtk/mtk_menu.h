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

#ifndef __MTK_MENU_H__
#define __MTK_MENU_H__

/* INCLUDE */
#include "mtk_typedefs.h"

#if MTK_ENABLE_COMPONENT_MENU

typedef void (*mtk_menuitem_cb)(void*);
typedef void (*mtk_menu_handle)(void*);

typedef struct mtk_menuitem mtk_menuitem_t;
typedef struct mtk_menupage mtk_menupage_t;
typedef struct mtk_menustate mtk_menustate_t;

typedef struct mtk_menuitem {
    char* name;
    mtk_menuitem_cb cb;
    mtk_menupage_t* child;
} mtk_menuitem_t;

typedef struct mtk_menupage {
    char* title;
    mtk_menuitem_t** menuitem_array;
    uint32_t menuitem_num;
    mtk_menupage_t* parent;
    uint32_t last_top;
    uint32_t last_index;
} mtk_menupage_t;

typedef struct mtk_menustate {
    uint32_t top;
    uint32_t max_rows;
    uint32_t curr_index;
    mtk_menupage_t* curr_menupage;
    mtk_menu_handle cb;
    void* data;
} mtk_menustate_t;

#endif /* MTK_ENABLE_COMPONENT_MENU */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if MTK_ENABLE_COMPONENT_MENU

#define mtk_menu_curr_item(ms) (ms->curr_menupage->menuitem_array[ms->curr_index])

void mtk_menu_quit (mtk_menustate_t* ms);
void mtk_menu_enter (mtk_menustate_t* ms);
void mtk_menu_prev (mtk_menustate_t* ms);
void mtk_menu_next (mtk_menustate_t* ms);
void mtk_menu_process (mtk_menustate_t* ms);

#endif /* MTK_ENABLE_COMPONENT_MENU */

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MTK_MENU_H__ */
