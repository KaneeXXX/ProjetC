
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t button*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ei_implementation.h"
#include "ei_widget_configure.h"

ei_widget_t alloc_button()
{
	ei_impl_button_t* bouton = calloc(1, sizeof(ei_impl_button_t));
	return bouton;
}

void release_button(ei_widget_t widget)
{
	ei_impl_button_t* button = (ei_impl_button_t*) widget;
	free(button);
}

void drawbutton(ei_widget_t		widget,
		 ei_surface_t		surface,
		 ei_surface_t		pick_surface,
		 ei_rect_t*		clipper)
		 {
	ei_impl_button_t* button = (ei_impl_button_t*) widget;
	draw_button(surface, *widget->content_rect, button->corner_radius, *button->relief);
}

void setdefaults_button(ei_widget_t widget){
	//configure avec valeur par default
	//ei_button_configure();
}

void geomnotify_button(ei_widget_t widget){

}

bool handle_button(ei_widget_t widget, struct ei_event_t* event){

}

void create_widgetclass_button(){
	ei_widgetclass_t* button = calloc(1, sizeof(ei_widgetclass_t));
	ei_widgetclass_name_t name = "button";
	strcpy(button->name, name);
	button->allocfunc = &alloc_button;
	button-> releasefunc = &release_button;
	button->drawfunc = &drawbutton;
	button->setdefaultsfunc = &setdefaults_button;
	button->geomnotifyfunc = &geomnotify_button;
	button->handlefunc = &handle_button;
	button->next = NULL;

	ei_widgetclass_register(button);
}




