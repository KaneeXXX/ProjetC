//
// Created by Donald Duck on 1942.
//

#include "ei_widget.h"
#include "ei_widget_configure.h"
#include "ei_placer.h"
#include "ei_widgetclass.h"
#include "ei_implementation.h"
#include "ei_widget_attributes.h"

https://code-with-me.global.jetbrains.com/Y_EUtOQbuZjGjmjU6R-gjA#p=CL&fp=BBC0A6AAFC8F4659218745E2686207DFFDD9DE02A12CDC18AC7E6BA88601D57C
ei_widget_t		ei_widget_create		(ei_const_string_t	class_name,
							    ei_widget_t		parent,
							    ei_user_param_t	user_data,
							    ei_widget_destructor_t destructor) {
	if(alreadyRegistered(class_name)){

	} else {

	}
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


