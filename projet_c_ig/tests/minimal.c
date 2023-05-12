#include <stdlib.h>

#include "ei_types.h"
#include "ei_event.h"
#include "ei_utils.h"
#include "hw_interface.h"
#include "ei_types.h"

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
	ei_point_t  point_array[] = {{20, 30}, {90, 10},{140, 10},{140, 50}, {120, 100}, {70, 70}, {20, 90}};
	size_t length=7;
	ei_color_t color = {0, 255, 255, 0};
	//ei_draw_polygon (main_window, point_array, length, color, NULL);

	/*//DRAW RECT
	ei_point_t  point_array[] = {{200, 200}, {100,200}, {100, 100}, {200, 100}};
	size_t length=4;
	ei_color_t color = {0, 255, 255, 0};
	ei_draw_polyline(main_window, point_array, length, color, NULL);*/

	ei_color_t noir = {0, 0, 0, 0xff};
	pixel_ptr = (uint32_t*)hw_surface_get_buffer(main_window);
	for(int i=0; i < length; i++) {
		u_int32_t *point = pixel_ptr + main_window_size.width * point_array[i].y + point_array[i].x;
		//Get order of colors in pixel because it's not always the same

		uint32_t pixel_value;
		uint8_t* channel_ptr = (uint8_t*) &pixel_value; //ptr to pixel_value
		channel_ptr[ir] = noir.red;
		channel_ptr[ig] = noir.green;
		channel_ptr[ib] = noir.blue;

		*point = pixel_value;
	}

	/*//TEST ARC TRIGO
	ei_point_t center = {10,10};
	int rayon=10;
	arc(center, rayon, 0, 90);
	printf("------------------------");
	arc(center, rayon, 90, 180);*/

//	//TEST DE DRAW_BUTTON*/
//	ei_size_t size={100, 50};
//	ei_point_t topleft = {300, 200};
//	ei_rect_t rectangle = {topleft, size};
//	//round_frame2(main_window, rectangle, 14, ei_default_background_color);
//	draw_button(main_window, rectangle, 13, ei_relief_raised);

	//TEST DE DRAW_TEXT
	ei_point_t where = {10, 10};
	ei_const_string_t text = "bonjour";
	ei_font_t super_font = hw_text_font_create(ei_default_font_filename, ei_style_normal, 50);
	ei_draw_text(main_window, &where, text, super_font, noir, NULL);

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
