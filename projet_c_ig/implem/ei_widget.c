//
// Created by Donald Duck on 1942.
//

#include "ei_widget.h"
#include "ei_widget_configure.h"
#include "ei_placer.h"
#include "ei_widgetclass.h"
#include "ei_implementation.h"
#include "ei_widget_attributes.h"
#include "ei_widgetclass.h"
#include "ei_utils.h"

void addWidget_to_parent(ei_impl_widget_t* widgetptr, ei_widget_t parent){
	/*Add widget to parent chained list*/
	//No children before
	if(parent->children_head == NULL){
		parent->children_head = widgetptr;
		//parent->children_tail = widgetptr;
		parent->next_sibling = NULL; //only one child now
	} else {
		/*Insert ahead*/
		widgetptr->next_sibling = parent->children_head;
		parent->children_head = widgetptr;
	}
}

ei_widget_t ei_widget_create(ei_const_string_t class_name, ei_widget_t parent, ei_user_param_t user_data, ei_widget_destructor_t destructor)
{
	/*Verify is class_name is known by the library*/
	ei_widgetclass_t* widgetclassptr = ei_widgetclass_from_name(class_name);
	if (widgetclassptr != NULL) {
		/*Call the function which allocate memory to store attribut of new widget of this class*/
		ei_impl_widget_t* widgetptr = widgetclassptr->allocfunc();
		/*Init widgets' commun attributs*/
		widgetptr->wclass = widgetclassptr;
		widgetptr->pick_id = 0; // a CHANGER
		widgetptr->pick_color = &ei_default_background_color; // a CHANGER
		widgetptr->user_data = user_data;
		widgetptr->destructor = destructor;

		/*Hierarchy*/
		if(parent != NULL) {
			widgetptr->next_sibling = parent->children_head; //If no other child, NULL;
			/*Update parent fields*/
			addWidget_to_parent(widgetptr, parent);
			widgetptr->parent = parent;
		} else {
			widgetptr->parent = NULL;
		}
		/*We've just created the widget so no children for now*/
		widgetptr->children_head = NULL;
		//widgetptr->children_tail = NULL;


		/*Geometry*/
		struct ei_impl_placer_params_t* params = calloc(1, sizeof(struct ei_impl_placer_params_t));
		widgetptr->placer_params = params; //A changer probablement
		ei_size_t size = ei_size(0,0);
		widgetptr->requested_size = size; // A CHANGER
		ei_point_t point = ei_point(0,0);
		ei_rect_t rect = ei_rect(point, size);
		widgetptr->screen_location = rect; // A CHANGER
		widgetptr->content_rect = rect; //A CHANGER

		/*Call the function which init specifics attributs of the class*/
		widgetclassptr->setdefaultsfunc(widgetptr);

		return widgetptr;
	} else {
		//Class doesn't exist or is not registered
	}
}

void ei_widget_destroy(ei_widget_t widget) //A CHECKER CELLE LA
{
	//Removes the widget from the screen if it is currently displayed.
	if(ei_widget_is_displayed(widget)){
		//TODO
	}

	/*Destroy widget and all its offspring (descendance)*/
	//destruction recursive
	if(widget->children_head != NULL) { //No children

		//get the list of children and DESTROY THEM !! AHAHAHAHAH (the evil strikes again)
		ei_widget_t current_widgetchild = widget->children_head; //head of the list
		while (current_widgetchild != NULL) {
			//Calls its destructor if it was provided.
			if (widget->destructor != NULL) {
				widget->destructor(widget);
			}

			//free memory
			ei_widget_t to_delete = current_widgetchild;

			current_widgetchild = current_widgetchild->next_sibling; //move in the list of children before detroying, otherwise may have pb
			ei_widget_destroy(to_delete);
		}
	}

	//Destroy the widget itself
	free(widget);
}

bool ei_widget_is_displayed	(ei_widget_t widget)
{
	return (widget->placer_params == NULL) ? false : true;
}

ei_widget_t	ei_widget_pick (ei_point_t*	where)
{

}
