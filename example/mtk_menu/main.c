#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#include "mtk_menu.h"

void test_cb (void* arg);

void menu_ctrl_cb (void* arg);

mtk_menupage_t m1;
mtk_menupage_t m11;
mtk_menupage_t m21;
mtk_menupage_t m111;

mtk_menuitem_t i1 = {"item1", NULL, &m11};
mtk_menuitem_t i2 = {"item2", NULL, &m21};
mtk_menuitem_t i3 = {"item3", test_cb, NULL};
mtk_menuitem_t i4 = {"item4", test_cb, NULL};
mtk_menuitem_t i5 = {"item5", test_cb, NULL};

mtk_menuitem_t i11 = {"item11", NULL, &m111};
mtk_menuitem_t i12 = {"item12", test_cb, NULL};
mtk_menuitem_t i13 = {"item13", test_cb, NULL};

mtk_menuitem_t i21 = {"item21", test_cb, NULL};
mtk_menuitem_t i22 = {"item22", test_cb, NULL};
mtk_menuitem_t i23 = {"item23", test_cb, NULL};

mtk_menuitem_t i111 = {"item111", test_cb, NULL};

mtk_menuitem_t* m1_array[] = {&i1, &i2, &i3, &i4, &i5};
mtk_menuitem_t* m11_array[] = {&i11, &i12, &i13};
mtk_menuitem_t* m21_array[] = {&i21, &i22, &i23};
mtk_menuitem_t* m111_array[] = {&i111};

mtk_menupage_t m1 = {
    .title = "menu1",
    .menuitem_array = m1_array,
    .menuitem_num = 5,
    .parent = NULL,
    .last_index = 0,
    .last_top = 0,
};
mtk_menupage_t m11 = {
    .title = "menu11",
    .menuitem_array = m11_array,
    .menuitem_num = 3,
    .parent = &m1,
    .last_index = 0,
    .last_top = 0,
};
mtk_menupage_t m21 = {
    .title = "menu21",
    .menuitem_array = m21_array,
    .menuitem_num = 3,
    .parent = &m1,
    .last_index = 0,
    .last_top = 0,
};
mtk_menupage_t m111 = {
    .title = "menu111",
    .menuitem_array = m111_array,
    .menuitem_num = 1,
    .parent = &m11,
    .last_index = 0,
    .last_top = 0,
};
mtk_menustate_t menu_ctrl = {
    .top = 0,
    .max_rows = 4,
    .curr_index = 0,
    .curr_menupage = &m1,
    .cb = menu_ctrl_cb,
    .data = &menu_ctrl,
};

void test_cb (void* arg)
{
    mtk_menustate_t* ms = arg;
    printf("\n%s, hello world", mtk_menu_curr_item(ms)->name);
    getch();
}

void menu_ctrl_cb (void* arg)
{
    uint8_t i = 0;
    mtk_menustate_t* ms = arg;
    system("cls");
    printf("Title: %s    %d/%d\n", ms->curr_menupage->title, ms->curr_index+1, ms->curr_menupage->menuitem_num);
    for (i = ms->top; i < ms->top + ms->max_rows; i++) {
        if (i == ms->curr_menupage->menuitem_num) {
            return;
        }
        if (ms->curr_index == i) {
            printf(">%s\n", ms->curr_menupage->menuitem_array[i]->name);
        } else {
            printf("%s\n", ms->curr_menupage->menuitem_array[i]->name);
        }
    }
}

int main (void)
{
    char input;
    mtk_menu_process(&menu_ctrl);
    while (1) {
        input = getch();
        if (input == 'w') {
            mtk_menu_prev(&menu_ctrl);
        } else if (input == 's') {
            mtk_menu_next(&menu_ctrl);
        } else if (input == 'd') {
            mtk_menu_enter(&menu_ctrl);
        } else if (input == 'a') {
            mtk_menu_quit(&menu_ctrl);
        } else if (input == 'q') {
            return 0;
        }
        mtk_menu_process(&menu_ctrl);
    }
    return 0;
}