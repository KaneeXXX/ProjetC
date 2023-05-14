
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

ei_widget_t alloc_toplevel(){
	ei_impl_toplevel_t* toplevel = calloc(1, sizeof(ei_impl_toplevel_t));
	return toplevel;
}

void release_toplevel(ei_widget_t widget){
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	free(toplevel);
}

void draw_toplevel(ei_widget_t		widget,
		   ei_surface_t		surface,
		   ei_surface_t		pick_surface,
		   ei_rect_t*		clipper){
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	//draw avec les param de top level
}

void setdefaults_toplevel(ei_widget_t widget){
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	toplevel->title = "Default Title";
	toplevel->canClose = true;
	toplevel->axis_set = ei_axis_both;
	toplevel->minimalSize = ei_size(100, 100);
}

void geomnotify_toplevel(ei_widget_t widget){

}

bool handle_toplevel(ei_widget_t widget, struct ei_event_t* event){

}

void create_widgetclass_toplevel(){
	ei_widgetclass_t* toplevel = calloc(1, sizeof(ei_widgetclass_t));
	ei_widgetclass_name_t name = "toplevel";
	strcpy(toplevel->name, name);
	toplevel->allocfunc = &alloc_toplevel;
	toplevel-> releasefunc = &release_toplevel;
	toplevel->drawfunc = &draw_toplevel;
	toplevel->setdefaultsfunc = &setdefaults_toplevel;
	toplevel->geomnotifyfunc = &geomnotify_toplevel;
	toplevel->handlefunc = &handle_toplevel;
	toplevel->next = NULL;

	ei_widgetclass_register(toplevel);
}




