
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t TopLevel*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ei_implementation.h"

ei_impl_toplevel_t * alloc_toplevel(){
	ei_impl_toplevel_t* toplevel = calloc(1, sizeof(ei_impl_toplevel_t));
	return toplevel;
}

void release_toplevel(ei_impl_toplevel_t* toplevel){
	free(toplevel);
}

void draw_toplevel(ei_impl_toplevel_t* toplevel){

}

void setdefaults_toplevel(ei_impl_toplevel_t* toplevel){

}

void geomnotify_toplevel(ei_impl_toplevel_t* toplevel){

}

void handle_toplevel(ei_impl_toplevel_t* toplevel){

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




