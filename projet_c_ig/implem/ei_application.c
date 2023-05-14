/**
*  @file      ei_application.c
*  @brief     Manages the main steps of a graphical application: initialization, main window,
*	      main loop, quitting, resource freeing.
*
*  \author
*  Created by Notre Groupe.
*
*/

#include "ei_application.h"
#include "hw_interface.h"

void ei_app_create(ei_size_t main_window_size, bool fullscreen)
{
	if (fullscreen == true) {
		//the size of the root window = main_window_size
		hw_create_window(main_window_size, true);
	} else {
		//the size of the root window = the current monitor resolution
		hw_create_window(main_window_size, false);
	}
}

void ei_app_free()
{

}

void ei_app_run()
{
	getchar();
}

void ei_app_invalidate_rect(const ei_rect_t* rect)
{

}

void ei_app_quit_request()
{

}

ei_widget_t ei_app_root_widget()
{
	ei_widget_t widget;
	return widget;
}

ei_surface_t ei_app_root_surface()
{
	ei_surface_t  surface;
	return surface;
}
