//
// Created by Rachmaninoff on 5/12/23.
//
#include "ei_widgetclass.h"

/*Chained list of class*/
ei_widgetclass_t * list_class = NULL;

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