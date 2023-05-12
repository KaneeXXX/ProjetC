
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t frame*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ei_implementation.h"

ei_impl_frame_t * alloc_frame()
{
	ei_impl_frame_t* frame = calloc(1, sizeof(ei_impl_frame_t));
	return frame;
}

void release_frame(ei_impl_frame_t* frame){
	free(frame);
}

void draw_frame(ei_impl_frame_t* frame){

}

void setdefaults_frame(ei_impl_frame_t* frame){

}

void geomnotify_frame(ei_impl_frame_t* frame){

}

void handle_frame(ei_impl_frame_t* frame){

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
