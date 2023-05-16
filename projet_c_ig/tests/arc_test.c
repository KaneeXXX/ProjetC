/*
 *	Tests arc by drawing arcs with different sizes and angles
 *
 */
#include <stdlib.h>
#include <stdio.h>

#include "hw_interface.h"
#include "ei_utils.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "ei_implementation.h"

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

	/* Draw the arcs */
	ei_fill(main_window, &white, NULL);

	//Circle
	tab_and_length arc11 = (tab_and_length) arc((ei_point_t) {100,100}, 50, 0, 90);
	ei_draw_polyline(main_window, arc11.tab, arc11.length, (ei_color_t){0, 255, 0, 255}, NULL);
	tab_and_length arc12 = (tab_and_length) arc((ei_point_t) {100,100}, 50, 90, 180);
	ei_draw_polyline(main_window, arc12.tab, arc12.length, (ei_color_t){0, 255, 0, 255}, NULL);
	tab_and_length arc13 = (tab_and_length) arc((ei_point_t) {100,100}, 50, 180, 270);
	ei_draw_polyline(main_window, arc13.tab, arc13.length, (ei_color_t){0, 255, 0, 255}, NULL);
	tab_and_length arc14 = (tab_and_length) arc((ei_point_t) {100,100}, 50, 270, 360);
	ei_draw_polyline(main_window, arc14.tab, arc14.length, (ei_color_t){0, 255, 0, 255}, NULL);

//	//Square inside a circle
//	tab_and_length arc21 = (tab_and_length) arc((ei_point_t) {300,100}, 30, 0, 90);
//	ei_draw_polygon(main_window, arc21.tab, arc21.length, (ei_color_t){0, 255, 255, 255}, NULL);
//	tab_and_length arc22 = (tab_and_length) arc((ei_point_t) {300,100}, 30, 90, 180);
//	ei_draw_polygon(main_window, arc22.tab, arc22.length, (ei_color_t){0, 255, 255, 255}, NULL);
//	tab_and_length arc23 = (tab_and_length) arc((ei_point_t) {300,100}, 30, 180, 270);
//	ei_draw_polygon(main_window, arc23.tab, arc23.length, (ei_color_t){0, 255, 255, 255}, NULL);
//	tab_and_length arc24 = (tab_and_length) arc((ei_point_t) {300,100}, 30, 270, 360);
//	ei_draw_polygon(main_window, arc24.tab, arc24.length, (ei_color_t){0, 255, 255, 255}, NULL);

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
