/*
 *	Tests ei_draw_polygon by using the example of the subject + 1 extra point
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
	ei_size_t		win_size	= ei_size(1500, 1000);
	ei_surface_t		main_window	= NULL;
	ei_color_t		color		= { 0x00, 0xff, 0xff, 0xff };
	ei_color_t		white		= { 0xff, 0xff, 0xff, 0xff };
	ei_rect_t*		clipper_ptr	= NULL;
	ei_rect_t		clipper		= ei_rect(ei_point(0, 0), ei_size(1500, 1000));
	clipper_ptr		= &clipper;
	ei_event_t		event;

	hw_init();

	main_window = hw_create_window(win_size, false);

	/* Lock the drawing surface. */
	hw_surface_lock	(main_window);

	/* Draw the polygon */
	ei_fill(main_window, &white, NULL);
	//Remarque: quand on prend les 4 premiers points, ça ne marche plus
	ei_point_t  point_array[] = {{200, 300}, {900, 100},{1400, 100},{1400, 500}, {1200, 1000}, {700, 700}, {200, 900}};
	size_t length=7;
	ei_draw_polygon (main_window, point_array, length, color, clipper_ptr);

	/* Place the points of the polygon in theory on the figure */
	ei_color_t noir = {0, 0, 0, 0xff};
	uint32_t*			pixel_ptr;
	int				ir = 0;
	int				ig = 0;
	int				ib = 0;
	pixel_ptr = (uint32_t*)hw_surface_get_buffer(main_window);
	for(int i=0; i < (int) length; i++) {
		u_int32_t *point = pixel_ptr + win_size.width * point_array[i].y + point_array[i].x;
		uint32_t pixel_value;
		uint8_t* channel_ptr = (uint8_t*) &pixel_value;
		channel_ptr[ir] = noir.red;
		channel_ptr[ig] = noir.green;
		channel_ptr[ib] = noir.blue;
		*point = pixel_value;
	}

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
