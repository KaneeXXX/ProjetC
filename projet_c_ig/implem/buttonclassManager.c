
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t button*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ei_implementation.h"

ei_impl_button_t * alloc_button()
{
	ei_impl_button_t* bouton = calloc(1, sizeof(ei_impl_button_t));
	return bouton;
}

void release_button(ei_impl_button_t* bouton)
{
	free(bouton);
}

void draw_button(ei_impl_button_t* bouton, surface){

	draw_bouton(surface, bouton->widget.screen_location, bouton->radius, bouton->widget.user_data.)

}

void setdefaults_button(){

}

void geomnotify_button(){

}

void handle_button(){

}

void create_widgetclass_button(){
	ei_widgetclass_t* button = calloc(1, sizeof(ei_widgetclass_t));
	ei_widgetclass_name_t name = "button";
	strcpy(button->name, name);
	button->allocfunc = &alloc_button;
	button-> releasefunc = &release_button;
	button->drawfunc = &draw_button;
	button->setdefaultsfunc = &setdefaults_button;
	button->geomnotifyfunc = &geomnotify_button;
	button->handlefunc = &handle_button;
	button->next = NULL;

	ei_widgetclass_register(button);
}




