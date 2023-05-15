//
// Created by kanee on 15/05/2023.
//

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widget_attributes.h"

void		ei_place	(ei_widget_t		widget,
				     ei_anchor_t*		anchor,
				     int*			x,
				     int*			y,
				     int*			width,
				     int*			height,
				     float*			rel_x,
				     float*			rel_y,
				     float*			rel_width,
				     float*			rel_height){

	ei_widget_t parent = ei_widget_get_parent(widget);
	const ei_rect_t* content_rect = ei_widget_get_content_rect(parent);



}

