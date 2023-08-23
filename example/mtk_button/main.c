#include "hardware.h"
#include "mtk_button.h"

static mtk_button_t user_button;

static uint8_t __button_read (void* arg)
{
 	return hardware_read_gpio();
}

static void __button_event_callback (void* arg)
{
	if (mtk_button_evt_clicks(&user_button, 1)) {				/* single click */
		/* do something... */
	} else if (mtk_button_evt_clicks(&user_button, 2)) {		/* double clicks, or more, change the 2nd parameter */
		/* do something... */
	} else if (mtk_button_evt_hold_ms(&user_button, 1500)) {	/* long press for 1500 ms */
		/* do somethint... */
	} else if (mtk_button_evt_hold_down(&user_button)) {		/* long press */
		/* do something... */
	} else if (mtk_button_evt_down(&user_button)) {				/* button down */
		/* do something... */
	} else if (mtk_button_evt_up(&user_button)) {				/* button up */
		/* do something... */
	} /* ...... */
}

void button_init (void)
{
	hardware_button_init();

	/* call frequency 1000hz, button scan 100hz */
	mtk_button_manager_init(1000, 100);

	/* max combo interval 300ms, long press to start at 1000ms, is low vaild */
	mtk_button_init(&user_button, 0, 300, 1000, 1, __button_read, __button_event_callback);
}

void hardware_timer_1ms_isr_cb (void)
{
	mtk_button_scan();
}