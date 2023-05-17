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
#include "ei_widget.h"
#include "ei_implementation.h"
#include "ei_widget_configure.h"
#include "ei_utils.h"
#include "ei_event.h"

ei_widget_t root_widget;
ei_surface_t root_surface;
ei_surface_t offscreen_surface;

ei_event_t *event_listener;

void ei_app_create(ei_size_t main_window_size, bool fullscreen)
{
	hw_init();
	//Create window system
	root_surface = malloc(sizeof(ei_surface_t));
	if (fullscreen == true) {
		//the size of the root window = main_window_size
		root_surface = hw_create_window(main_window_size, true);
	} else {
		//the size of the root window = the current monitor resolution
		root_surface = hw_create_window(main_window_size, false);
	}
	initlistclassToNull();

	//Register class
	create_widgetclass_button();
	create_widgetclass_frame();
	create_widgetclass_toplevel();

	//create root widget
	root_widget = calloc(1, sizeof(ei_widget_t));
	root_widget = ei_widget_create("frame", NULL, NULL, NULL);
	ei_size_t size_windows = hw_surface_get_size(root_surface);
	ei_frame_set_requested_size(root_widget, size_windows);

/*	//register event_listener
	event_listener = malloc(sizeof(ei_event_t));
	event_listener->type = ei_ev_none;

	//init offscreen surface
	offscreen_surface = malloc(sizeof(ei_surface_t));
	//penser a free plus tard
	offscreen_surface = hw_surface_create(root_surface, size_windows, true);*/
}

void ei_app_free()
{
	ei_widget_destroy(root_widget);
	hw_quit();
}

void ei_impl_widget_draw_children      (ei_widget_t		widget,
					ei_surface_t		surface,
					ei_surface_t		pick_surface,
					ei_rect_t*		clipper) {

	ei_widget_t childrenhead = widget->children_head;

	if(childrenhead == NULL) { //No children
		if (ei_widget_is_displayed(widget)){
			hw_surface_lock	(surface);
			ei_impl_placer_run(widget);
			widget->wclass->drawfunc(widget, surface, pick_surface, clipper);
			hw_surface_unlock(surface);
			hw_surface_update_rects(surface, NULL);
		}

	} else {
		ei_widget_t currentchildren = childrenhead;
		while(currentchildren != NULL){
			ei_impl_widget_draw_children(currentchildren, surface, pick_surface, clipper);
			currentchildren = currentchildren->next_sibling;
		}
	}
}

_Noreturn void ei_app_run() {
	//getchar();

	//WHILE( l'utilisateur n'appuie pas sur croix pour ferme l'appli)
	//Draw tout l'arbre de widget

	while (true) {
		hw_surface_lock(ei_app_root_surface());
		ei_app_root_widget()->wclass->drawfunc(ei_app_root_widget(), ei_app_root_surface(), NULL, NULL);
		hw_surface_unlock(ei_app_root_surface());
		ei_impl_widget_draw_children(ei_app_root_widget(), ei_app_root_surface(), NULL, NULL);

		//Attendre un event
		event_listener = calloc(1, sizeof(ei_event_t));
		hw_event_wait_next(event_listener);
		ei_widget_t current = ei_app_root_widget()->children_head;
		if (current->wclass->handlefunc(current, event_listener)) {
			ei_app_free();
		}

		//Analyser l'event pour trouver traitant associe
		//appeler traitant associé

/*		if(event_listener->type == ei_ev_mouse_buttondown) {
			ei_widget_t manipulated_widget = ei_widget_pick(&event_listener->param.mouse.where);
			if(manipulated_widget != NULL) {
				manipulated_widget->wclass->handlefunc(manipulated_widget, event_listener);
			}
		}

		ei_widget_t current_widget = ei_widget_pick(&event_listener->param.mouse.where);
		if (event_listener->type == ei_ev_mouse_buttondown) {
			current_widget->wclass->handlefunc(current_widget, event_listener);
		}
//		else if (c est un keyboard event) {
//			current_widget->wclass->handlefunc(current_widget, event_listener);
//		}
//		else if (c est un application event) {
//			current_widget->wclass->handlefunc(current_widget, event_listener);
//		}
		else {
			ei_event_set_default_handle_func(ei_event_get_default_handle_func());
		}

	}*/
	}
}
void ei_app_invalidate_rect(const ei_rect_t* rect)
{

}

void ei_app_quit_request()
{
	ei_app_free();
}

ei_widget_t ei_app_root_widget()
{
	return root_widget;
}

ei_surface_t ei_app_root_surface()
{
	return root_surface;
}