/*
 *	Tests ei_fill by filling the screen in blue then adding a red rectangle inside using clipping
 *
 */
#include <stdlib.h>
#include <stdio.h>

#include "hw_interface.h"
#include "ei_utils.h"
#include "ei_draw.h"
#include "ei_event.h"

int main(int argc, char** argv)
{
	ei_size_t		win_size	= ei_size(800, 600);
	ei_surface_t		main_window	= NULL;
	ei_color_t		blue		= { 0x00, 0x00, 0xff, 0xff };
	ei_color_t		red		= { 0xff, 0x00, 0x00, 0xff };
	ei_rect_t*		clipper_ptr	= NULL;
	ei_rect_t		clipper		= ei_rect(ei_point(200, 100), ei_size(100, 50));
	clipper_ptr		= &clipper;
	ei_event_t		event;

	hw_init();

	main_window = hw_create_window(win_size, false);

	/* Lock the drawing surface. */
	hw_surface_lock	(main_window);

	/* Paint in blue.*/
	ei_fill(main_window, &blue, NULL);

	/* Paint the red clipped rectangle.*/
	ei_fill(main_window, &red, clipper_ptr);

	/* Unlock and update the surface. */
	hw_surface_unlock(main_window);
	hw_surface_update_rects(main_window, NULL);

	/* Wait for a character on command line. */
	event.type = ei_ev_none;
	while ((event.type != ei_ev_close) && (event.type != ei_ev_keydown))
		hw_event_wait_next(&event);

	hw_quit();
	return (EXIT_SUCCESS);
}
