
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t TopLevel*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void alloc_toplevel(){


}

void release_toplevel(){

}

void draw_toplevel(){

}

void setdefaults_toplevel(){

}

void geomnotify_toplevel(){

}

void handle_toplevel(){

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




