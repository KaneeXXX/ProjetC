//
// Created by Jack the Ripper in 1888.
//

#include "ei_application.h"
#include "hw_interface.h"

void ei_app_create(ei_size_t main_window_size, bool fullscreen) {
	if (fullscreen == true) {
		//the size of the root window = main_window_size
		hw_create_window(main_window_size, true);
	} else {
		//the size of the root window = the current monitor resolution
		hw_create_window(main_window_size, false);
	}
}