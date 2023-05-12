//
// Created by Donald Duck on 1942.
//

#include "ei_widget.h"
#include "ei_widget_configure.h"
#include "ei_placer.h"
#include "ei_widgetclass.h"
#include "ei_implementation.h"
#include "ei_widget_attributes.h"

ei_widget_t	ei_widget_create(ei_const_string_t class_name, ei_widget_t	parent, ei_user_param_t	user_data, ei_widget_destructor_t destructor)
{
	if (alreadyRegistered(class_name)) {


	} else {

	}
}

void ei_widget_destroy(ei_widget_t widget)
{

}

bool ei_widget_is_displayed	(ei_widget_t widget)
{

}

ei_widget_t	ei_widget_pick (ei_point_t*	where)
{

}
