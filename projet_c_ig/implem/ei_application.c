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

ei_widget_t root_widget;
ei_surface_t root_surface;

void ei_app_create(ei_size_t main_window_size, bool fullscreen)
{
	//Create window system
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

	//creat root widget (frame with blue background)
	root_widget = ei_widget_create("frame", NULL, NULL, NULL);
	ei_frame_configure		(root_widget, &(ei_size_t){600,600},
					   &ei_default_background_color,
					   &(int){6},
					   &(ei_relief_t){ei_relief_raised}, NULL, NULL, NULL, NULL, NULL, NULL, NULL);


	//ei_place_xy(root_widget, 0, 0);

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
/*	hw_surface_lock	(surface);
	widget->wclass->drawfunc(widget, surface, pick_surface, clipper);
	hw_surface_unlock(surface);
	hw_surface_update_rects(surface, NULL);
	ei_widget_t child = widget->children_head;
	hw_surface_lock	(surface);
	widget->wclass->drawfunc(child, surface, pick_surface, clipper);
	hw_surface_unlock(surface);
	hw_surface_update_rects(surface, NULL);*/

	root_widget->wclass->drawfunc(root_widget, surface, pick_surface, clipper);

	ei_widget_t childrenhead = widget->children_head;

	if(childrenhead == NULL) { //No children
		hw_surface_lock	(surface);
		widget->wclass->drawfunc(widget, surface, pick_surface, clipper);
		hw_surface_unlock(surface);
		hw_surface_update_rects(surface, NULL);
	} else {
		ei_widget_t currentchildren = childrenhead;
		while(currentchildren != NULL){
			ei_impl_widget_draw_children(currentchildren, surface, pick_surface, clipper);
			currentchildren = currentchildren->next_sibling;
		}
	}
}

void ei_app_run()
{
	//getchar();

	//WHILE( l'utilisateur n'appuie pas sur croix pour ferme l'appli)
	//Draw tout l'arbre de widget
	while(true) {
		ei_impl_widget_draw_children(ei_app_root_widget(), ei_app_root_surface(), NULL, NULL);
	}
	//Listen event
	//traite l'event


}

void ei_app_invalidate_rect(const ei_rect_t* rect)
{

}

void ei_app_quit_request()
{

}

ei_widget_t ei_app_root_widget()
{
	return root_widget;
}

ei_surface_t ei_app_root_surface()
{
	return root_surface;
}
