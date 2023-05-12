//
// Created by Donald Duck on 1942.
//

#include "ei_widget.h"
#include "ei_widget_configure.h"
#include "ei_placer.h"
#include "ei_widgetclass.h"
#include "ei_implementation.h"
#include "ei_widget_attributes.h"

https://code-with-me.global.jetbrains.com/YqWSz8bq1brCo2WbwZ9ywg#p=CL&fp=BBC0A6AAFC8F4659218745E2686207DFFDD9DE02A12CDC18AC7E6BA88601D57C
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
