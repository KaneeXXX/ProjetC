#include <stdlib.h>

#include "ei_types.h"
#include "ei_event.h"
#include "ei_utils.h"
#include "hw_interface.h"

int main(int argc, char* argv[])
{
	ei_surface_t			main_window		= NULL;
	ei_size_t			main_window_size	= ei_size(640, 480);
	ei_event_t			event;
	uint32_t			white			= 0xffffffff;
	uint8_t 			red[4]			= { 255, 255, 255, 255 };
	uint32_t*			pixel_ptr;
	int				i, ir, ig, ib, ia;

	// Init acces to hardware.
	hw_init();

	// Create the main window.
	main_window = hw_create_window(main_window_size, false);

	// Compute the value of a red pixel for this surface.
	hw_surface_get_channel_indices(main_window, &ir, &ig, &ib, &ia);
	red[ir]	= 255;
	red[ig]	= red[ib] = 0;

	// Lock the surface for drawing,
	hw_surface_lock(main_window);

	// fill the top half in white, the bottom half in red (hurray Poland!)
	pixel_ptr = (uint32_t*)hw_surface_get_buffer(main_window);

	for (i = 0; i < (main_window_size.width * (main_window_size.height/2)); i++)
		*pixel_ptr++ = white;

	for (i = 0; i < (main_window_size.width * (main_window_size.height/2)); i++)
		*pixel_ptr++ = *((uint32_t*)red);

	//FIGURE DU SUJET POUR DRAW_POLYGON
	ei_point_t  point_array[] = {{20, 30}, {90, 10},{140, 10},{130, 50}, {120, 100}, {70, 70}, {20, 90}};
	size_t length=7;
	ei_color_t color = {0, 255, 255, 0};
	ei_draw_polygon (main_window, point_array, length, color, NULL);

	ei_color_t noir = {0, 0, 0, 0xff};
	pixel_ptr = (uint32_t*)hw_surface_get_buffer(main_window);
	for(int i=0; i < length; i++) {
		u_int32_t *point = pixel_ptr + main_window_size.width * point_array[i].y + point_array[i].x;
		//Get order of colors in pixel because it's not always the same

	//TESTS DRAW_POLYGON
//	ei_point_t  point_array_test[7] = {{20, 30}, {90, 10}, {150, 10}, {130, 50}, {120, 100}, {70, 70}, {20, 90}};
//	size_t length=7;
//	ei_color_t color = {0, 255, 255, 0};
//	ei_draw_polygon (main_window, point_array_test, length, color, NULL);

		uint32_t pixel_value;
		uint8_t* channel_ptr = (uint8_t*) &pixel_value; //ptr to pixel_value
		channel_ptr[ir] = noir.red;
		channel_ptr[ig] = noir.green;
		channel_ptr[ib] = noir.blue;

		*point = pixel_value;
	}

	//TEST DE ARC
	ei_size_t size={100, 100};
	ei_rect_t rectangle = {point_array[3], size};
	ei_point_t centre={100, 100};
	int rayon=100;
	float ad=0.;
	float aa=90.;
	//tab_and_length test = arc(main_window, centre, rayon, ad, aa);

	//TEST DE ROUNDED_FRAME
	int rayon_=10;
	ei_rect_t rectangle_frame = {{300, 300}, {100, 50}};
	ei_point_t* test=rounded_frame(main_window, rectangle_frame, rayon_, ei_relief_none);

	//TEST DE DRAW_BUTTON

	// unlock, update screen.
	hw_surface_unlock(main_window);
	hw_surface_update_rects(main_window, NULL);

	// Wait for a key press.
	event.type = ei_ev_none;
	while ((event.type != ei_ev_close) && (event.type != ei_ev_keydown))
		hw_event_wait_next(&event);

	// Free hardware resources.
	hw_quit();

	// Terminate program with no error code.
	return 0;
}
