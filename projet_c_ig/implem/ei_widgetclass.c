//
// Created by Rachmaninoff on 5/12/23.
//
#include "ei_widgetclass.h"
#include "ei_implementation.h"

/*list_class dans ei_implementation.h*/
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