/*
 *	Tests the first version draw_button by creating buttons with different sizes
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
	ei_color_t		white		= { 0xff, 0xff, 0xff, 0xff };
	ei_event_t		event;

	hw_init();

	main_window = hw_create_window(win_size, false);

	/* Lock the drawing surface. */
	hw_surface_lock	(main_window);

	/* Draw the buttons */
	ei_fill(main_window, &white, NULL);

	ei_rect_t rectangle11 = (ei_rect_t) {{0, 0}, {150, 100}};
	draw_button(main_window, rectangle11, 16, ei_relief_none);
	ei_rect_t rectangle12 = (ei_rect_t) {{150, 0}, {150, 100}};
	draw_button(main_window, rectangle12, 16, ei_relief_raised);
	ei_rect_t rectangle13 = (ei_rect_t) {{300, 0}, {150, 100}};
	draw_button(main_window, rectangle13, 16, ei_relief_sunken);

	ei_rect_t rectangle21 = (ei_rect_t) {{0, 200}, {100, 150}};
	draw_button(main_window, rectangle21, 16, ei_relief_none);
	ei_rect_t rectangle22 = (ei_rect_t) {{150, 200}, {100, 150}};
	draw_button(main_window, rectangle22, 16, ei_relief_raised);
	ei_rect_t rectangle23 = (ei_rect_t) {{300, 200}, {100, 150}};
	draw_button(main_window, rectangle23, 16, ei_relief_sunken);

	ei_rect_t rectangle31 = (ei_rect_t) {{0, 400}, {10, 10}};
	draw_button(main_window, rectangle31, 5, ei_relief_none);
	ei_rect_t rectangle32 = (ei_rect_t) {{150, 400}, {100, 100}};
	draw_button(main_window, rectangle32, 16, ei_relief_raised);
	ei_rect_t rectangle33 = (ei_rect_t) {{300, 400}, {100, 150}};
	draw_button(main_window, rectangle33, 30, ei_relief_sunken);

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
