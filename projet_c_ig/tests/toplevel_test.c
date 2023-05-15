/*
 *	Tests the first version draw_toplevel by creating a single toplevel frame
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
	ei_size_t		win_size	= ei_size(600, 600);
	ei_surface_t		main_window	= NULL;
	ei_color_t		white		= { 0xff, 0xff, 0xff, 0xff };
	ei_event_t		event;

	hw_init();

	main_window = hw_create_window(win_size, false);

	/* Lock the drawing surface. */
	hw_surface_lock	(main_window);

	/* Draw the toplevel */
	ei_fill(main_window, &white, NULL);

	ei_rect_t rectangle = (ei_rect_t) {{100, 100}, {250, 300}};
	draw_toplevel(main_window, rectangle, "fenêtre", 5, true, (ei_axis_set_t) ei_axis_both);

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
