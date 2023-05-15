//
// Created by Rachmaninoff on 5/12/23.
//
#include "ei_widgetclass.h"
#include "ei_implementation.h"

/*Chained list of class*/
ei_widgetclass_t **listclass;

void draw(ei_widget_t		widget,
	  ei_surface_t		surface,
	  ei_surface_t		pick_surface,
	  ei_rect_t*		clipper) {
	hw_surface_lock	(surface);
	widget->wclass->drawfunc(widget, surface, pick_surface, clipper);
	hw_surface_unlock(surface);
	//hw_surface_update_rects(surface);
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

void initlistclassToNull(){
	listclass = malloc(sizeof(ei_widgetclass_t));
	*listclass = NULL;
}

//list_class dans ei_implementation.h
void ei_widgetclass_register (ei_widgetclass_t* widgetclass) {
	if(*listclass == NULL){
		*listclass = widgetclass;
	} else {
		ei_widgetclass_t * current = *listclass;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = widgetclass;
	}
}


bool alreadyRegistered(char* class_name){
	if (*listclass == NULL){
		return false;
	}
	ei_widgetclass_t* current = *listclass;
	while(current != NULL){
		if (strcmp(current->name, class_name) == 0){
			return true;
		}
		current = current->next;
	}
	return false;
}


ei_widgetclass_t* ei_widgetclass_from_name(ei_const_string_t name) {

	ei_widgetclass_t* current = *listclass;
	while (current != NULL) {
		if(strcmp(current->name, name) == 0){
			return current;
		}
		current = current->next;
	}
	return NULL;
}
