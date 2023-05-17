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
	ei_color_t 		red		= {0xff, 0, 0, 0xff};
	ei_event_t		event;

	hw_init();

	main_window = hw_create_window(win_size, false);

	/* Lock the drawing surface. */
	hw_surface_lock	(main_window);

	/* Draw the buttons */
	ei_fill(main_window, &white, NULL);
	ei_color_t black = { 0, 0, 0, 0xff};

	ei_rect_t rectangle11 = (ei_rect_t) {{0, 0}, {150, 100}};
	draw_button(main_window,
		    rectangle11,
		    red,
		    5,
		    16,
		    ei_relief_none,
		    NULL,
		    NULL,
		    black,
		    NULL,
		    NULL);
	ei_rect_t rectangle12 = (ei_rect_t) {{150, 0}, {150, 100}};
	draw_button(main_window,
		    rectangle12,
		    red,
		    5,
		    16,
		    ei_relief_raised,
		    "Bouton",
		    (ei_font_t) hw_text_font_create(ei_default_font_filename, ei_style_normal, 20),
		    black,
		    NULL,
		    NULL);
	ei_rect_t rectangle13 = (ei_rect_t) {{300, 0}, {150, 100}};
	draw_button(main_window,
		    rectangle13,
		    red,
		    5,
		    16,
		    ei_relief_sunken,
		    "Boutonricotapanamariejevoussalue",
		    hw_text_font_create(ei_default_font_filename, ei_style_italic, 20),
		    black,
		    NULL,
		    NULL);
	ei_rect_t rectangle21 = (ei_rect_t) {{0, 200}, {100, 150}};
	draw_button(main_window,
		    rectangle21,
		    red,
		    5,
		    16,
		    ei_relief_none,
		    "Bouton",
		    hw_text_font_create(ei_default_font_filename, ei_style_strikethrough, 20),
		    black,
		    NULL,
		    NULL);
	ei_rect_t rectangle22 = (ei_rect_t) {{150, 200}, {100, 150}};
	draw_button(main_window,
		    rectangle22,
		    red,
		    5,
		    16,
		    ei_relief_raised,
		    "Bouton",
		    hw_text_font_create(ei_default_font_filename, ei_style_underline, 20),
		    black,
		    NULL,
		    NULL);
	ei_rect_t rectangle23 = (ei_rect_t) {{300, 200}, {100, 150}};
	draw_button(main_window,
		    rectangle23,
		    red,
		    5,
		    16,
		    ei_relief_sunken,
		    "Bouton",
		    hw_text_font_create(ei_default_font_filename, ei_style_bold, 20),
		    black,
		    NULL,
		    NULL);
	ei_rect_t rectangle31 = (ei_rect_t) {{0, 400}, {10, 10}};
	draw_button(main_window,
		    rectangle31,
		    red,
		    2,
		    1,
		    ei_relief_none,
		    "W",
		    hw_text_font_create(ei_default_font_filename, ei_style_normal, 3),
		    black,
		    NULL,
		    NULL);
	ei_rect_t rectangle32 = (ei_rect_t) {{150, 400}, {100, 100}};
	draw_button(main_window,
		    rectangle32,
		    red,
		    5,
		    1,
		    ei_relief_raised,
		    "123",
		    hw_text_font_create(ei_default_font_filename, ei_style_normal, 20),
		    black,
		    NULL,
		    NULL);
	ei_rect_t rectangle33 = (ei_rect_t) {{300, 400}, {100, 150}};
	draw_button(main_window,
		    rectangle33,
		    red,
		    5,
		    16,
		    ei_relief_sunken,
		    "&é'(-è_çà))=",
		    hw_text_font_create(ei_default_font_filename, ei_style_normal, 12),
		    black,
		    NULL,
		    NULL);
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
