//
// Created by Donald Duck on 1942.
//

#include "ei_widget.h"
#include "ei_widget_configure.h"
#include "ei_placer.h"

ei_widget_t		ei_widget_create		(ei_const_string_t	class_name,
							    ei_widget_t		parent,
							    ei_user_param_t	user_data,
							    ei_widget_destructor_t destructor) {

}

void			ei_frame_configure		(ei_widget_t		widget,
							       ei_size_t*		requested_size,
							       const ei_color_t*	color,
							       int*			border_width,
							       ei_relief_t*		relief,
							       ei_string_t*		text,
							       ei_font_t*		text_font,
							       ei_color_t*		text_color,
							       ei_anchor_t*		text_anchor,
							       ei_surface_t*		img,
							       ei_rect_ptr_t*		img_rect,
							       ei_anchor_t*		img_anchor) {

}

void		ei_place	(ei_widget_t		widget,
				     ei_anchor_t*		anchor,
				     int*			x,
				     int*			y,
				     int*			width,
				     int*			height,
				     float*			rel_x,
				     float*			rel_y,
				     float*			rel_width,
				     float*			rel_height) {

}
