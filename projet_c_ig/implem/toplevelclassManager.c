
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t TopLevel*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ei_implementation.h"
#include "ei_utils.h"
#include "ei_widget_configure.h"
#include "ei_event.h"
#include "ei_application.h"

//(ei_widget_t	widget,
//ei_size_t*	requested_size,
//ei_color_t*	color,
//int*		border_width,
//ei_string_t*	title,
//bool*		losable,
//ei_axis_set_t*resizable,
//ei_size_ptr_t*min_size);

ei_widget_t alloc_toplevel(){
	ei_impl_toplevel_t* toplevel = calloc(1, sizeof(ei_impl_toplevel_t));
	return toplevel;
}

void release_toplevel(ei_widget_t widget){
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	free(toplevel);
}

void drawtoplevel(ei_widget_t		widget,
		   ei_surface_t		surface,
		   ei_surface_t		pick_surface,
		   ei_rect_t*		clipper){
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	draw_toplevel(surface,
	       (ei_rect_t) {widget->screen_location.top_left, widget->requested_size},
		toplevel->color,
		toplevel->border_width,
		toplevel->title,
		toplevel->closable,
		toplevel->resizable,
		toplevel->min_size
		);
}

void setdefaults_toplevel(ei_widget_t widget){
	//configure avec truc pas défault
	ei_size_t sizedef = ei_size(100,100);
	bool closable = true;
	bool resisable = true;
	int min_size = 100;
	int border_width = 4;
	ei_string_t titledef = "default title";
	ei_color_t colordef = {162, 219, 225, 0xff};
	ei_toplevel_configure(widget, &sizedef, &colordef, &border_width, &titledef, &closable, &resisable, &min_size);
}

void geomnotify_toplevel(ei_widget_t widget){

}

//traitant interne de la classe toplevel
bool handle_toplevel(ei_widget_t widget, struct ei_event_t* event){
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	bool mouse_location = is_point_in_rect(ei_rect(widget->screen_location.top_left, ei_size(15, 15)), event->param.mouse.where);
	if (event->type == ei_ev_keydown){
		return true;
	}
	if ((event->type == ei_ev_mouse_buttonup)&&(event->param.mouse.button == ei_mouse_button_left)&&(mouse_location)){
		return true;
	}
	return false;
}

void create_widgetclass_toplevel(){
	ei_widgetclass_t* toplevel = calloc(1, sizeof(ei_widgetclass_t));
	ei_widgetclass_name_t name = "toplevel";
	strcpy(toplevel->name, name);
	toplevel->allocfunc = &alloc_toplevel;
	toplevel->releasefunc = &release_toplevel;
	toplevel->drawfunc = &drawtoplevel;
	toplevel->setdefaultsfunc = &setdefaults_toplevel;
	toplevel->geomnotifyfunc = &geomnotify_toplevel;
	toplevel->handlefunc = &handle_toplevel;
	toplevel->next = NULL;
	ei_widgetclass_register(toplevel);
}




