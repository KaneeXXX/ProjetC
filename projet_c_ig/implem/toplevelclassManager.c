
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t TopLevel*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ei_implementation.h"
#include "ei_utils.h"
#include "ei_widget_configure.h"
#include "ei_event.h"
#include "ei_application.h"
#include "ei_types.h"

//(ei_widget_t	widget,
//ei_size_t*	requested_size,
//ei_color_t*	color,
//int*		border_width,
//ei_string_t*	title,
//bool*		losable,
//ei_axis_set_t*resizable,
//ei_size_ptr_t*min_size);

ei_point_t current_pointer_pos;

ei_widget_t alloc_toplevel(){
	ei_impl_toplevel_t* toplevel = calloc(1, sizeof(ei_impl_toplevel_t));
	return toplevel;
}

void release_toplevel(ei_widget_t widget){
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	free(toplevel);
}

void draw_in_offscreen(ei_rect_t rectangle, ei_surface_t surface, ei_color_t color){
	//Draw the big frame
	int RADIUS = 0;
	tab_and_length conc;
	ei_point_t top_left_point = rectangle.top_left;
	int height = rectangle.size.height;
	int width = rectangle.size.width;

	ei_point_t center_top_left = {top_left_point.x + RADIUS, top_left_point.y + RADIUS};
	tab_and_length t1 = arc(center_top_left, RADIUS, 180, 270);

	ei_point_t center_top_right = {top_left_point.x + (width - RADIUS), top_left_point.y + RADIUS};
	tab_and_length t2 = arc(center_top_right, RADIUS, 270, 360);

	ei_point_t center_bottom_right = (ei_point_t) {top_left_point.x + width, top_left_point.y + height};

	ei_point_t center_bottom_left = (ei_point_t) {top_left_point.x, top_left_point.y + height};

	ei_point_t * list_1point = calloc(1, sizeof(ei_point_t));
	list_1point[0] = center_bottom_right;
	ei_point_t * list_1point2 = calloc(1, sizeof(ei_point_t));
	list_1point2[0] = center_bottom_left;

	conc = concatenate_four_point_lists(t1.tab, t2.tab, list_1point, list_1point2, t1.length, t2.length, 1, 1);

	ei_draw_polygon(surface, conc.tab, conc.length, color, NULL);
}

void drawtoplevel(ei_widget_t		widget,
		   ei_surface_t		surface,
		   ei_surface_t		pick_surface,
		   ei_rect_t*		clipper){
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	draw_toplevel(surface,
	       (ei_rect_t) {widget->screen_location.top_left, widget->screen_location.size},
		toplevel->color,
		toplevel->border_width,
		toplevel->title,
		toplevel->closable,
		toplevel->resizable,
		toplevel->min_size
		);

	//dessiner dans offscreen
	draw_in_offscreen((ei_rect_t) {widget->screen_location.top_left, widget->screen_location.size}, pick_surface, *widget->pick_color);

	ei_impl_widget_draw_children(widget, ei_app_root_surface(), get_picksurface(), NULL);
}

void setdefaults_toplevel(ei_widget_t widget){
	//configure avec truc pas défault
	ei_size_t sizedef = ei_size(100,100);
	bool closable = true;
	bool resisable = true;
	ei_size_t min_size = ei_size(100, 100);
	ei_size_ptr_t ptrsize = &min_size;
	int border_width = 4;
	ei_string_t titledef = "default title";
	ei_color_t colordef = {162, 219, 225, 0xff};
	ei_toplevel_configure(widget, &sizedef, &colordef, &border_width, &titledef, &closable, &resisable, &ptrsize);

}

void geomnotify_toplevel(ei_widget_t widget){

}

//traitant interne de la classe toplevel
bool handle_toplevel(ei_widget_t toplevel, struct ei_event_t* event){
	switch (event->type) {
		case ei_ev_mouse_buttondown:
			ei_event_set_active_widget(toplevel);
			current_pointer_pos = event->param.mouse.where;
			return true;
			break;
		case ei_ev_mouse_move:
			if(toplevel == ei_event_get_active_widget()){
				int rel_x = current_pointer_pos.x - event->param.mouse.where.x;
				int rel_y = current_pointer_pos.y - event->param.mouse.where.y;
				int x = toplevel->screen_location.top_left.x - rel_x;
				int y = toplevel->screen_location.top_left.y - rel_y;
				ei_place_xy(toplevel, x, y);

				//update current pos
				current_pointer_pos.x = event->param.mouse.where.x;
				current_pointer_pos.y = event->param.mouse.where.y;
			}
			return true;
			break;

		case ei_ev_mouse_buttonup:
			ei_event_set_active_widget(NULL);
			return true;
		default:
			break;
	}
	return false;
}

void create_widgetclass_toplevel(){
	ei_widgetclass_t* toplevel = calloc(1, sizeof(ei_widgetclass_t));
	ei_widgetclass_name_t name = "toplevel";
	strcpy(toplevel->name, name);
	toplevel->allocfunc = &alloc_toplevel;
	toplevel->releasefunc = &release_toplevel;
	toplevel->drawfunc = &drawtoplevel;
	toplevel->setdefaultsfunc = &setdefaults_toplevel;
	toplevel->geomnotifyfunc = &geomnotify_toplevel;
	toplevel->handlefunc = &handle_toplevel;
	toplevel->next = NULL;

	ei_widgetclass_register(toplevel);
}
