//
// Created by Rachmaninoff on 5/12/23.
//
#include "ei_widgetclass.h"
#include "ei_implementation.h"


void draw(ei_widget_t		widget,
	  ei_surface_t		surface,
	  ei_surface_t		pick_surface,
	  ei_rect_t*		clipper) {
	widget->wclass->drawfunc(widget, surface, pick_surface, clipper);
}

void setDefault(ei_widget_t widget) {
	widget->wclass->setdefaultsfunc(widget); // comprend pas comment son gerer les arguments, pasles meme ds draw frame par exemple
}

void release(ei_widget_t widget) {

}

void geomnotify(ei_widget_t widget) {
	widget->wclass->geomnotifyfunc(widget);
}

void handle(ei_widget_t widget, struct ei_event_t* event) {
	widget -> wclass -> handlefunc(widget, event);
}

//list_class dans ei_implementation.h
void ei_widgetclass_register (ei_widgetclass_t* widgetclass) {
	if(list_class == NULL){
		*list_class = *widgetclass;
	} else {
		ei_widgetclass_t * current = list_class;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = widgetclass;
	}
}

bool alreadyRegistered(char* class_name){
	if (list_class == NULL){
		return false;
	}
	ei_widgetclass_t* current = list_class;
	while(current != NULL){
		if (current->name == class_name){
			return true;
		}
	}
	return false;
}

ei_widgetclass_t* ei_widgetclass_from_name(ei_const_string_t name) {
	ei_widgetclass_t* current = list_class;
	while (current != NULL) {
		if(current -> name == name){
			return current;
		}
	}
	return NULL;
}



