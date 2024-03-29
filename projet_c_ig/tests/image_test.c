#include <stdio.h>
#include <stdlib.h>

#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget_configure.h"

static ei_string_t		k_default_image_filename	= "misc/klimt.jpg";




bool process_key(ei_event_t* event)
{
	if ( (event->type == ei_ev_close) ||
	     ((event->type == ei_ev_keydown) && (event->param.key.key_code == SDLK_ESCAPE))) {
		ei_app_quit_request();
		return true;
	} else
		return false;
}

int main(int argc, char** argv)
{
	ei_widget_t	button;

	/* Create the application and change the color of the background. */
	ei_app_create			((ei_size_t){800, 800}, false);
	ei_frame_set_bg_color		(ei_app_root_widget(), (ei_color_t){0x52, 0x7f, 0xb4, 0xff});
	ei_event_set_default_handle_func(process_key);

	/* Create, configure and place the image on a button on screen. */

	ei_surface_t image		= hw_image_load(k_default_image_filename, ei_app_root_surface());
	ei_size_t image_size	= hw_surface_get_size(image);

	button = ei_widget_create	("button", ei_app_root_widget(), NULL, NULL);
	ei_button_configure		(button, &(image_size),
					    &(ei_color_t){0x88, 0x88, 0x88, 0xff},
					    &(int){6},
					    &(int){40},
					    &(ei_relief_t){ei_relief_raised},NULL, NULL,
					    &(ei_color_t){0x00, 0x00, 0x00, 0xff}, NULL, &image, NULL, NULL,
					    NULL, NULL);
	ei_place_xy			(button, 150, 200);

	/* Run the application's main loop. */
	ei_app_run();

	/* We just exited from the main loop. Terminate the application (cleanup). */
	ei_app_free();

	return (EXIT_SUCCESS);
}
