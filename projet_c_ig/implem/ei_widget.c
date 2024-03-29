//
// ei_widget.c
//

#include <stdio.h>
#include "ei_widget.h"
#include "ei_widget_configure.h"
#include "ei_implementation.h"
#include "ei_widget_attributes.h"
#include "ei_utils.h"
#include "ei_application.h"
#include "ei_types.h"
#include "ei_event.h"

uint32_t pick_id;

void create_buttons_toplevel(ei_point_t topleft, ei_widget_t parent);

void addWidget_to_parent(ei_impl_widget_t* widgetptr, ei_widget_t parent)
{
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
	/* Verify the widget class_name is known by the library */
	ei_widgetclass_t* widgetclassptr = ei_widgetclass_from_name(class_name);
	if (widgetclassptr != NULL) {
		/*Call the function which allocate memory to store attribut of new widget of this class*/
		ei_impl_widget_t* widgetptr = widgetclassptr->allocfunc();
		/*Init widget common attributes*/
		widgetptr->wclass = widgetclassptr;
		widgetptr->user_data = user_data;
		widgetptr->destructor = destructor;

		/*Hierarchy*/
		if (parent != NULL) {
			widgetptr->next_sibling = parent->children_head; //If no other child, NULL;
			/*Update parent fields*/
			addWidget_to_parent(widgetptr, parent);
			widgetptr->parent = parent;
		} else {
			widgetptr->parent = NULL;
		}
		widgetptr->children_head = NULL; //no children because widget just has been created
		widgetptr->children_tail = NULL;

		widgetptr->pick_id = pick_id;
		uint32_t* tp = &pick_id;
		uint8_t* tp8 = (uint8_t*) tp;
		uint8_t R = tp8[0];
		uint8_t G = tp8[1];
		uint8_t B = tp8[2];
		ei_color_t* pick_color = calloc(1, sizeof(ei_color_t));
		//Penser a free
		*pick_color = (ei_color_t) {R, G, B, 0xff};
		//ei_color_t pick_color = (ei_color_t) {R, G, B, 0xff};
		widgetptr->pick_color = pick_color;
		pick_id = pick_id + 1;

		/*Geometry*/
		struct ei_impl_placer_params_t* params = NULL;
		widgetptr->placer_params = params;
		ei_size_t size = ei_size(0,0);
		widgetptr->requested_size = size;
		ei_point_t point = ei_point(0,0);
		ei_rect_t rect = ei_rect(point, size);
		widgetptr->screen_location = rect;
		widgetptr->content_rect = widgetptr->screen_location;

		/*Call the function which init specifics attributs of the class*/
		widgetclassptr->setdefaultsfunc(widgetptr);

		return widgetptr;
	} else {
		printf("This widget class does not exist !");
		return NULL;
	}
}

void ei_widget_destroy(ei_widget_t widget) //A CHECKER CELLE LA
{
	ei_widget_t child = ei_widget_get_first_child(widget);
	if(child == NULL) {
		return; //plus rien a dessiner en dessous dans hiérarchie
	}
	while(child != NULL){

		ei_widget_t temp =  child;
		child = child->next_sibling;
		temp->wclass->releasefunc(temp);

	}
}

bool ei_widget_is_displayed(ei_widget_t widget)
{
	return (widget->placer_params == NULL) ? false : true;
}

//unused with picking
bool is_point_in_rect(ei_rect_t rect, ei_point_t point)
{
	int x_rect = rect.top_left.x;
	int y_rect = rect.top_left.y;
	int width = rect.size.width;
	int height = rect.size.height;
	if ((point.x >= x_rect) && (point.x <= (x_rect + width)) && (point.y >= y_rect) && (point.y <= y_rect + height)) {
		return true;
	}
	return false;
}

//unused with picking
bool is_point_in_widget(ei_widget_t widget, ei_point_t point)
{
	return (is_point_in_rect(widget->screen_location, point)) ? true : false;
}

ei_color_t get_widget_offscreen_color(ei_surface_t surface, int width ,ei_point_t point)
{
	//Get order of colors in pixel because it's not always the same
	int ir, ig, ib, ia;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

	hw_surface_lock(surface);
	//get the adresse of the pixel (x,y)
	uint32_t* surface_buffer = (uint32_t*) hw_surface_get_buffer(surface);
	uint32_t* px_y = surface_buffer + point.y * width + point.x; //+  =  move forward with 4 bytes (4 octets en 4 octets)     32 bits = 4 octets (1 octet = 8 bits)
	//px_y = adress of pixel
	uint8_t * px_y8 = (uint8_t*) px_y;
	ei_color_t color;

	color.red = px_y8[ir];
	color.green = px_y8[ig];
	color.blue = px_y8[ib];
	color.alpha = px_y8[ia];
	hw_surface_unlock(surface);

	return color;
}

bool is_same_color(ei_color_t color1, ei_color_t color2)
{
	if (color1.red == color2.red && color1.green == color2.green && color1.blue == color2.blue && color1.alpha == color2.alpha) {
		return true;
	}
	return false;
}

ei_widget_t find_widget(ei_widget_t current_widget, ei_color_t picked_color) //recursif
{
	if (is_same_color(*current_widget->pick_color, picked_color)) {
		if(current_widget == ei_app_root_widget()){
			return NULL;
		}
		//printf("%s\n", current_widget->wclass->name);
		return current_widget;
	}

	ei_widget_t child = ei_widget_get_first_child(current_widget);
	while (child != NULL) {
		ei_widget_t widget = find_widget(child, picked_color);
		if (widget != NULL) {
			return widget;
		}
		child = child->next_sibling;
	}
	return NULL;
}

ei_widget_t	ei_widget_pick (ei_point_t*	where) // A TESTER
{
	//get the pick color at the coordinate of the point
	ei_size_t size = hw_surface_get_size(get_picksurface());
	ei_color_t picked_color = get_widget_offscreen_color(get_picksurface(), size.width ,*where);
	//printf("%i %i %i\n", picked_color.red, picked_color.green, picked_color.blue);

	ei_widget_t current_widget = ei_app_root_widget(); //start exploring the widget tree

	return find_widget(current_widget, picked_color);
}

/*//unused with picking
ei_widget_t	ei_widget_pick (ei_point_t*	where) // A TESTER
{
	ei_widget_t widget_picked = NULL; //default

	ei_widget_t current_widget = ei_app_root_widget();

	while(ei_widget_get_first_child(current_widget) != NULL) {

		bool cursor_in_no_children = false;
		ei_widget_t child = ei_widget_get_first_child(current_widget);
		while (child != NULL) {
			if (is_point_in_widget(child, *where)) {
				widget_picked = child;
				cursor_in_no_children = true;
			}
			child = child->next_sibling;
		}
		if(cursor_in_no_children == false){
			return widget_picked;
		} else {
			current_widget = widget_picked;
		}
	}
	return NULL;
}*/
