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


	ei_color_t black = {0,0,0,0xff};
	ei_point_t point_array[] = {{0,0}, {30, 0}, {50, 10}, {60,10},{60, 30}, {0, 30}};

	ei_draw_polygon(main_window, point_array, 6, black,NULL);
/*

	//Arcs of different sizes
	tab_and_length arc11 = (tab_and_length) arc((ei_point_t) {100,100}, 10, 0, 90);
	ei_draw_polyline(main_window, arc11.tab, arc11.length, (ei_color_t){0, 0, 0, 255}, NULL);
	tab_and_length arc12 = (tab_and_length) arc((ei_point_t) {100,100}, 50, 90, 180);
	ei_draw_polyline(main_window, arc12.tab, arc12.length, (ei_color_t){0, 0, 0, 255}, NULL);
	tab_and_length arc13 = (tab_and_length) arc((ei_point_t) {100,100}, 90, 180, 270);
	ei_draw_polyline(main_window, arc13.tab, arc13.length, (ei_color_t){0, 0, 0, 255}, NULL);
	tab_and_length arc14 = (tab_and_length) arc((ei_point_t) {100,100}, 100, 270, 360);
	ei_draw_polyline(main_window, arc14.tab, arc14.length, (ei_color_t){0, 0, 0, 255}, NULL);

	//Circle with one arc
	tab_and_length circle = (tab_and_length) arc((ei_point_t) {100,400}, 100, 0, 360);
	ei_draw_polyline(main_window, circle.tab, circle.length, (ei_color_t){255, 0, 255, 255}, NULL);

	//Circle with 4 arcs
	tab_and_length arc11b = (tab_and_length) arc((ei_point_t) {400,400}, 100, 0, 90);
	ei_draw_polyline(main_window, arc11b.tab, arc11b.length, (ei_color_t){0, 0, 255, 255}, NULL);
	tab_and_length arc12b = (tab_and_length) arc((ei_point_t) {400,400}, 100, 90, 180);
	ei_draw_polyline(main_window, arc12b.tab, arc12b.length, (ei_color_t){0, 0, 255, 255}, NULL);
	tab_and_length arc13b = (tab_and_length) arc((ei_point_t) {400,400}, 100, 180, 270);
	ei_draw_polyline(main_window, arc13b.tab, arc13b.length, (ei_color_t){0, 0, 255, 255}, NULL);
	tab_and_length arc14b = (tab_and_length) arc((ei_point_t) {400,400}, 100, 270, 360);
	ei_draw_polyline(main_window, arc14b.tab, arc14b.length, (ei_color_t){0, 0, 255, 255}, NULL);

	//Square inside a circle
	tab_and_length arc21 = (tab_and_length) arc((ei_point_t) {300,100}, 100, 0, 90);
	ei_draw_polygon(main_window, arc21.tab, arc21.length, (ei_color_t){0, 255, 255, 255}, NULL);
//	tab_and_length arc22 = (tab_and_length) arc((ei_point_t) {300,100}, 100, 90, 180);
//	ei_draw_polygon(main_window, arc22.tab, arc22.length, (ei_color_t){0, 255, 255, 255}, NULL);
//	tab_and_length arc23 = (tab_and_length) arc((ei_point_t) {300,100}, 100, 180, 270);
//	ei_draw_polygon(main_window, arc23.tab, arc23.length, (ei_color_t){0, 255, 255, 255}, NULL);
	tab_and_length arc24 = (tab_and_length) arc((ei_point_t) {300,100}, 100, 270, 360);
	ei_draw_polygon(main_window, arc24.tab, arc24.length, (ei_color_t){0, 255, 255, 255}, NULL);
*/

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
