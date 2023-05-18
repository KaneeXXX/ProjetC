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

	/* Draw the buttons */
	ei_fill(main_window, &white, NULL);

	//With polygon, height > width
	tab_and_length whole_figure_polygon = rounded_frame((ei_rect_t) {(ei_point_t) {100, 100}, (ei_size_t) {100, 150}}, 30, ei_relief_none);

	ei_point_t* l = calloc(whole_figure_polygon.length + 1, sizeof(ei_point_t));
	for(int i = 0; i < whole_figure_polygon.length; i++){
		l[i] = whole_figure_polygon.tab[i];
	}
	l[whole_figure_polygon.length] = ei_point(100, 200);
	printf("%i , %i", l[whole_figure_polygon.length].x, l[whole_figure_polygon.length].y);

	ei_draw_polygon(main_window, l, whole_figure_polygon.length + 1, (ei_color_t){255, 255, 0, 255}, NULL);
	tab_and_length top_figure_polygon = rounded_frame((ei_rect_t) {(ei_point_t) {300, 100}, (ei_size_t) {100, 150}}, 30, ei_relief_raised);
	ei_draw_polygon(main_window, top_figure_polygon.tab, top_figure_polygon.length, (ei_color_t){0, 255, 255, 255}, NULL);
	tab_and_length bottom_figure_polygon = rounded_frame((ei_rect_t) {(ei_point_t) {500, 100}, (ei_size_t) {100, 150}}, 30, ei_relief_sunken);
	ei_draw_polygon(main_window, bottom_figure_polygon.tab, bottom_figure_polygon.length, (ei_color_t){255, 0, 255, 255}, NULL);

	//With polygon, width > height
	tab_and_length whole_fig_polygon = rounded_frame((ei_rect_t) {(ei_point_t) {100, 300}, (ei_size_t) {150, 100}}, 30, ei_relief_none);
	ei_draw_polygon(main_window, whole_fig_polygon.tab, whole_fig_polygon.length, (ei_color_t){255, 255, 0, 255}, NULL);
	tab_and_length top_fig_polygon = rounded_frame((ei_rect_t) {(ei_point_t) {300, 300}, (ei_size_t) {150, 100}}, 30, ei_relief_raised);
	ei_draw_polygon(main_window, top_fig_polygon.tab, top_fig_polygon.length, (ei_color_t){0, 255, 255, 255}, NULL);
	tab_and_length bottom_fig_polygon = rounded_frame((ei_rect_t) {(ei_point_t) {500, 300}, (ei_size_t) {150, 100}}, 30, ei_relief_sunken);
	ei_draw_polygon(main_window, bottom_fig_polygon.tab, bottom_fig_polygon.length, (ei_color_t){255, 0, 255, 255}, NULL);

	ei_color_t black = (ei_color_t) {0, 0, 0, 255};

	//With polyline, height < width
	tab_and_length whole_figure = rounded_frame((ei_rect_t) {(ei_point_t) {100, 100}, (ei_size_t) {100, 150}}, 30, ei_relief_none);
	ei_draw_polyline(main_window, whole_figure.tab, whole_figure.length, black, NULL);
	tab_and_length top_figure = rounded_frame((ei_rect_t) {(ei_point_t) {300, 100}, (ei_size_t) {100, 150}}, 30, ei_relief_raised);
	ei_draw_polyline(main_window, top_figure.tab, top_figure.length, black, NULL);
	tab_and_length bottom_figure = rounded_frame((ei_rect_t) {(ei_point_t) {500, 100}, (ei_size_t) {100, 150}}, 30, ei_relief_sunken);
	ei_draw_polyline(main_window, bottom_figure.tab, bottom_figure.length, black, NULL);

	//With polyline, width < height
	tab_and_length whole_figurep = rounded_frame((ei_rect_t) {(ei_point_t) {100, 300}, (ei_size_t) {150, 100}}, 30, ei_relief_none);
	ei_draw_polyline(main_window, whole_figurep.tab, whole_figurep.length, black, NULL);
	tab_and_length top_figurep = rounded_frame((ei_rect_t) {(ei_point_t) {300, 300}, (ei_size_t) {150, 100}}, 30, ei_relief_raised);
	ei_draw_polyline(main_window, top_figurep.tab, top_figurep.length, black, NULL);
	tab_and_length bottom_figurep = rounded_frame((ei_rect_t) {(ei_point_t) {500, 300}, (ei_size_t) {150, 100}}, 30, ei_relief_sunken);
	ei_draw_polyline(main_window, bottom_figurep.tab, bottom_figurep.length, black, NULL);

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
