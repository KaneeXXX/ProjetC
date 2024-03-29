//
// Created by serafith on 12/05/2023.
//

#include "ei_widgetclass.h"
#include "ei_event.h"

ei_widget_t active_widget;
ei_default_handle_func_t handle_func = NULL;

void ei_event_set_active_widget(ei_widget_t widget) {
	active_widget = widget;
}

ei_widget_t ei_event_get_active_widget() {
	return active_widget;
}


void ei_event_set_default_handle_func(ei_default_handle_func_t func) {
	//handle_func = malloc(sizeof(ei_default_handle_func_t));
	handle_func = func;
}

ei_default_handle_func_t ei_event_get_default_handle_func() {
	return handle_func;
}


