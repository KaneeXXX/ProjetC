//
// ei_widget_configure.c
//

#include "ei_types.h"
#include "ei_widget_configure.h"
#include "ei_implementation.h"

void			ei_frame_configure			(ei_widget_t		widget,
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
							       ei_anchor_t*		img_anchor)
							       {
	ei_impl_frame_t* frame = (ei_impl_frame_t*) widget;
	if (requested_size != NULL)
		frame -> widget.requested_size = *requested_size;
	if (color != NULL)
		frame->color = *color;
	if (border_width != NULL)
		frame->border_width = *border_width;
	if (relief != NULL)
		frame->relief = *relief;
	if (text != NULL)
		frame->text = *text;
	if (text_font != NULL)
		frame->text_font = *text_font;
	if (text_color != NULL)
		frame->text_color = *text_color;
	if (text_anchor != NULL)
		frame->text_anchor = *text_anchor;
	if (img != NULL)
		frame->img = *img;
	if (img_rect != NULL)
		frame->img_rect = *img_rect;
	if (img_anchor != NULL)
		frame->img_anchor = *img_anchor;
}

void			ei_button_configure			(ei_widget_t		widget,
								ei_size_t*		requested_size,
								const ei_color_t*	color,
								int*			border_width,
								int*			corner_radius,
								ei_relief_t*		relief,
								ei_string_t*		text,
								ei_font_t*		text_font,
								ei_color_t*		text_color,
								ei_anchor_t*		text_anchor,
								ei_surface_t*		img,
								ei_rect_ptr_t*		img_rect,
								ei_anchor_t*		img_anchor,
								ei_callback_t*		callback,
								ei_user_param_t*	user_param)
								{
	ei_impl_button_t* button = (ei_impl_button_t*) widget;
	if (requested_size != NULL)
		button -> widget.requested_size = *requested_size;
	if (color != NULL)
		button->color = *color;
	if (border_width != NULL)
		button->border_width = *border_width;
	if (corner_radius != NULL)
		button->corner_radius = *corner_radius;
	if (relief != NULL)
		button->relief = *relief;
	if (text != NULL)
		button->text = *text;
	if (text_font != NULL)
		button->text_font = *text_font;
	if (text_color != NULL)
		button->text_color = *text_color;
	if (text_anchor != NULL)
		button->text_anchor = *text_anchor;
	if (img != NULL)
		button->img = *img;
	if (img_rect != NULL)
		button->img_rect = *img_rect;
	if (img_anchor != NULL)
		button->img_anchor = *img_anchor;
	if (callback != NULL)
		button->callback = *callback;
	if (user_param != NULL)
		button->user_param = *user_param;
}

void 			ei_toplevel_configure		(ei_widget_t			widget,
							    ei_size_t*			requested_size,
							    ei_color_t*			color,
							    int*			border_width,
							    ei_string_t*		title,
							    bool*			closable,
							    ei_axis_set_t*		resizable,
							    ei_size_ptr_t*		min_size)
							    {
	ei_impl_toplevel_t* toplevel = (ei_impl_toplevel_t*) widget;
	if (requested_size != NULL)
		toplevel->widget.requested_size = *requested_size;
	if (color != NULL)
		toplevel->color = *color;
	if (border_width != NULL)
		toplevel->border_width = *border_width;
	if (title != NULL)
		toplevel->title = *title;
	if (closable != NULL)
		toplevel->closable = *closable;
	if (resizable != NULL)
		toplevel->resizable = *resizable;
	if (min_size != NULL)
		toplevel->min_size = *min_size;
}
