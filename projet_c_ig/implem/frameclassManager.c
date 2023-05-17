
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t frame*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ei_implementation.h"
#include "ei_widget_configure.h"
#include "ei_utils.h"

ei_widget_t alloc_frame()
{
	ei_impl_frame_t* frame = calloc(1, sizeof(ei_impl_frame_t));
	return (ei_widget_t) frame;
}

void release_frame(ei_widget_t widget){
	ei_impl_frame_t* frame = (ei_impl_frame_t*) widget;
	free(frame);
}

void draw_frame(ei_widget_t		widget,
		ei_surface_t		surface,
		ei_surface_t		pick_surface,
		ei_rect_t*		clipper)
		{
	ei_impl_frame_t* frame = (ei_impl_frame_t*) widget;
	int x=widget->screen_location.top_left.x;
	int y=widget->screen_location.top_left.y;
	int width=widget->requested_size.width;
	int height=widget->requested_size.height;
	ei_point_t points_rectangle[] = {{x, y}, {x+width, y}, {x+width, y+height}, {x, y+height}};
	size_t size=4;
	ei_draw_polygon(surface, points_rectangle, size, frame->color, clipper);

	//dessiner dans offscreen
	ei_draw_polygon(pick_surface, points_rectangle, size, *(widget->pick_color), NULL);
}

void setdefaults_frame(ei_widget_t widget){
	ei_size_t sizedef = ei_size(50,50);

	ei_frame_configure(widget, &sizedef, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

void geomnotify_frame(ei_widget_t widget){

}

//traitant interne de la classe frame
bool handle_frame(ei_widget_t widget, struct ei_event_t* event){

	exit(1);
}

void create_widgetclass_frame(){
	ei_widgetclass_t* frame = calloc(1, sizeof(ei_widgetclass_t));
	ei_widgetclass_name_t name = "frame";
	strcpy(frame->name, name);
	frame->allocfunc = &alloc_frame;
	frame-> releasefunc = &release_frame;
	frame->drawfunc = &draw_frame;
	frame->setdefaultsfunc = &setdefaults_frame;
	frame->geomnotifyfunc = &geomnotify_frame;
	frame->handlefunc = &handle_frame;
	frame->next = NULL;

	ei_widgetclass_register(frame);
}
