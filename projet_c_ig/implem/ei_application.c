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
#include "ei_widget_attributes.h"

ei_widget_t root_widget;
ei_surface_t root_surface;
ei_surface_t pick_surface;

ei_event_t *event_listener;

void ei_app_create(ei_size_t main_window_size, bool fullscreen)
{
	hw_init();
	//Create window system

	//the size of the root window = main_window_size
	root_surface = hw_create_window(main_window_size, fullscreen);
	ei_size_t size_windows = hw_surface_get_size(root_surface);
	//init offscreen surface
	//penser a free plus tard
	pick_surface = hw_surface_create(root_surface, size_windows, true);
	//pick_surface = hw_create_window(main_window_size, fullscreen);

	pick_id = 0;

	initlistclassToNull();

	//Register class
	create_widgetclass_button();
	create_widgetclass_frame();
	create_widgetclass_toplevel();

	//create root widget
	root_widget = ei_widget_create("frame", NULL, NULL, NULL);

	ei_frame_set_requested_size(root_widget, size_windows);

	//register event_listener
	event_listener = malloc(sizeof(ei_event_t));
	event_listener->type = ei_ev_none;
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

	if(widget != ei_app_root_widget()) { //normalement on rentre jamais dedans mais bon au cas ou
		ei_impl_placer_run(widget);
	}
	ei_widget_t child = ei_widget_get_first_child(widget);
	if(child == NULL) {
		return; //plus rien a dessiner en dessous dans hiérarchie
	}

	while(child != NULL){
		child->wclass->drawfunc(child, ei_app_root_surface(), get_picksurface(), NULL);
		child = child->next_sibling;
	}
}

_Noreturn void ei_app_run()
{
	//WHILE( l'utilisateur n'appuie pas sur croix pour ferme l'appli)
	//Draw tout l'arbre de widget

	while(event_listener->type != ei_ev_close) {
		hw_surface_lock	(ei_app_root_surface());
		hw_surface_lock(get_picksurface());


		ei_app_root_widget()->wclass->drawfunc(ei_app_root_widget(), ei_app_root_surface(), get_picksurface(), NULL);

		hw_surface_unlock(ei_app_root_surface());
		hw_surface_unlock(get_picksurface());

		hw_surface_update_rects(ei_app_root_surface(), NULL);
		//hw_surface_update_rects(get_picksurface(), NULL);

		//I) Attendre un event
		hw_event_wait_next(event_listener);

		//II) Analyser l'event pour trouver traitant associe
		//appeler traitant associé

		/*Si un event de souris*/
		if (event_listener->type == ei_ev_mouse_buttondown || event_listener->type == ei_ev_mouse_buttonup) {

			ei_widget_t widget_manipulated = ei_widget_pick(&event_listener->param.mouse.where);
			if(widget_manipulated != NULL){//Otherwise we're manipulating the root widget -> background
				switch (event_listener->type) {
					case ei_ev_mouse_buttondown:
						ei_event_set_active_widget(widget_manipulated); //Full attention focused on this amazing widget !
						bool res = widget_manipulated->wclass->handlefunc;
						printf("%s", widget_manipulated->wclass->name);
					case ei_ev_mouse_buttonup:
						ei_event_set_active_widget(NULL); //We are no longer manipulating the amazing widget, so the attention is no longer focus on it !
					case ei_ev_mouse_move:
						widget_manipulated->wclass->handlefunc(widget_manipulated, event_listener);
					}
			}
		}
//		else if (c est un keyboard event) {
//			current_widget->wclass->handlefunc(current_widget, event_listener);
//		}
//		else if (c est un application event) {
//			current_widget->wclass->handlefunc(current_widget, event_listener);
//		}//Event de keyboard et autre
		else {
			//call default handle function
		}

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

ei_surface_t get_picksurface()
{
	return pick_surface;
}
