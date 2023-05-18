//
// ei_widgetclass.c
//

#include "ei_widgetclass.h"
#include "ei_implementation.h"

ei_widgetclass_t **listclass; //linked list to store the widget classes

size_t ei_widget_struct_size()
{
	return sizeof(ei_widget_t);
}

void			draw			(ei_widget_t		widget,
						  ei_surface_t		surface,
						  ei_surface_t		pick_surface,
						  ei_rect_t*		clipper)
						  {
	widget->wclass->drawfunc(widget, surface, pick_surface, clipper);
	ei_impl_widget_draw_children(widget, surface, pick_surface, clipper);
}

ei_widget_t alloc(ei_widget_t widget)
{
	ei_widget_t block_of_memory = widget->wclass->allocfunc();
	return block_of_memory;
}

void setDefault(ei_widget_t widget)
{
	widget->wclass->setdefaultsfunc(widget);
}

void release(ei_widget_t widget)
{
	widget->wclass->releasefunc(widget);
}

void geomnotify(ei_widget_t widget)
{
	widget->wclass->geomnotifyfunc(widget);
}

void			handle			(ei_widget_t 		widget,
	    					struct ei_event_t* 	event)
						{
	widget->wclass->handlefunc(widget, event);
}

void initlistclassToNull()
{
	listclass = malloc(sizeof(ei_widgetclass_t));
	*listclass = NULL;
}

void ei_widgetclass_register (ei_widgetclass_t* widgetclass)
{
	if (*listclass == NULL) //list_class in ei_implementation.h
		*listclass = widgetclass;
	else {
		ei_widgetclass_t * current = *listclass;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = widgetclass;
	}
}

bool alreadyRegistered(char* class_name)
{
	if (*listclass == NULL)
		return false;
	ei_widgetclass_t* current = *listclass;
	while (current != NULL) {
		if (strcmp(current->name, class_name) == 0)
			return true;
		current = current->next;
	}
	return false;
}

ei_widgetclass_t* ei_widgetclass_from_name(ei_const_string_t name)
{
	ei_widgetclass_t* current = *listclass;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0)
			return current;
		current = current->next;
	}
	return NULL;
}
