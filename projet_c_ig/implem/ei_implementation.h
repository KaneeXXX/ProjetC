/**
 * @file	ei_implementation.h
 *
 * @brief 	Private definitions.
 *
 */

#ifndef EI_IMPLEMENTATION_H
#define EI_IMPLEMENTATION_H

#include "hw_interface.h"
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_draw.h"
#include "ei_widget_configure.h"


/**
 * \brief	Converts the red, green, blue and alpha components of a color into a 32 bits integer
 * 		than can be written directly in the memory returned by \ref hw_surface_get_buffer.
 * 		The surface parameter provides the channel order.
 *
 * @param	surface		The surface where to store this pixel, provides the channels order.
 * @param	color		The color to convert.
 *
 * @return 			The 32 bit integer corresponding to the color. The alpha component
 *				of the color is ignored in the case of surfaces that don't have an
 *				alpha channel.
 */
uint32_t ei_impl_map_rgba(ei_surface_t surface, ei_color_t color);



/**
 * \brief	A structure storing the placement parameters of a widget.
 *		You have to define this structure: no suggestion provided.
 */

struct ei_impl_placer_params_t {
    ei_anchor_t		anchor;
    int			x;
    int			y;
    int			width;
    int			height;
    float			rel_x;
    float			rel_y;
    float			rel_width;
    float			rel_height;
};




/**
 * \brief	Tells the placer to recompute the geometry of a widget.
 *		The widget must have been previsouly placed by a call to \ref ei_place.
 *		Geometry re-computation is necessary for example when the text label of
 *		a widget has changed, and thus the widget "natural" size has changed.
 *
 * @param	widget		The widget which geometry must be re-computed.
 */
void ei_impl_placer_run(ei_widget_t widget);



/**
 * \brief	Fields common to all types of widget. Every widget classes specializes this base
 *		class by adding its own fields.
 */
typedef struct ei_impl_widget_t {
    ei_widgetclass_t*	wclass;		///< The class of widget of this widget. Avoids the field name "class" which is a keyword in C++.
    uint32_t		pick_id;	///< Id of this widget in the picking offscreen.
    ei_color_t*		pick_color;	///< pick_id encoded as a color.
    void*			user_data;	///< Pointer provided by the programmer for private use. May be NULL.
    ei_widget_destructor_t	destructor;	///< Pointer to the programmer's function to call before destroying this widget. May be NULL.

    /* Widget Hierachy Management */
    ei_widget_t		parent;		///< Pointer to the parent of this widget.
    ei_widget_t		children_head;	///< Pointer to the first child of this widget.	Children are chained with the "next_sibling" field.
    ei_widget_t		children_tail;	///< Pointer to the last child of this widget.
    ei_widget_t		next_sibling;	///< Pointer to the next child (of this widget's parent widget.)

    /* Geometry Management */
    struct ei_impl_placer_params_t* placer_params;	///< Pointer to the placer parameters for this widget. If NULL, the widget is not currently managed and thus, is not displayed on the screen.
    ei_size_t		requested_size;	///< Size requested by the widget (big enough for its label, for example), or by the programmer. This can be different than its screen size defined by the placer.
    ei_rect_t		screen_location;///< Position and size of the widget expressed in the root window reference.
    ei_rect_t		content_rect;	///< Where to place children, when this widget is used as a container. By defaults, points to the screen_location.
} ei_impl_widget_t;



/**
 * @brief	Draws the children of a widget.
 * 		The children are draw withing the limits of the clipper and
 * 		the widget's content_rect.
 *
 * @param	widget		The widget which children are drawn.
 * @param	surface		A locked surface where to draw the widget's children.
 * @param	pick_surface	The picking offscreen.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle
 *				(expressed in the surface reference frame).
 */
void ei_impl_widget_draw_children      (ei_widget_t		widget,
					ei_surface_t		surface,
					ei_surface_t		pick_surface,
					ei_rect_t*		clipper);


typedef struct {
    ei_point_t* 				tab;
    int 					length;
} tab_and_length;

tab_and_length arc(ei_point_t center, int radius, int angle_start, int angle_end);

tab_and_length rounded_frame(ei_rect_t rectangle, int radius, ei_relief_t relief);

void draw_button(ei_surface_t surface,
		 ei_rect_t rectangle,
		 const ei_color_t color,
		 int border_width,
		 int corner_radius,
		 ei_relief_t relief,
		 ei_string_t text,
		 ei_font_t text_font,
		 ei_color_t text_color,
		 ei_surface_t img,
		 ei_rect_ptr_t img_rect);

void draw_toplevel(ei_surface_t surface,
		   ei_rect_t rectangle,
		   ei_color_t color,
		   int border_width,
		   ei_string_t title,
		   bool closable,
		   ei_axis_set_t resizable,
		   ei_size_ptr_t* min_size);

/**
 * Def Button class
 */
typedef struct ei_impl_button_t {
    ei_impl_widget_t widget; //Common to all widgets
    /*Attributes*/
    ei_color_t	color;
    int border_width;
    int corner_radius;
    ei_relief_t relief;
    ei_string_t	text;
    ei_font_t text_font;
    ei_color_t text_color;
    ei_anchor_t text_anchor;
    ei_surface_t img;
    ei_rect_ptr_t img_rect;
    ei_anchor_t img_anchor;
    ei_callback_t callback;
    ei_user_param_t user_param;
} ei_impl_button_t;

/**
 * Def TopLevel class
 */
typedef struct ei_impl_toplevel_t {
    ei_impl_widget_t widget;
    /*Attributes*/
    ei_color_t color;
    int border_width;
    ei_string_t	title;
    bool closable;
    ei_axis_set_t resizable;
    ei_size_ptr_t min_size;

} ei_impl_toplevel_t;

/**
 * Def Frame class
 */
typedef struct ei_impl_frame_t {
    ei_impl_widget_t widget;
    /*Attributes*/
    ei_color_t color;
    int border_width;
    ei_relief_t relief;
    ei_string_t text;
    ei_font_t text_font;
    ei_color_t	text_color;
    ei_anchor_t text_anchor;
    ei_surface_t img;
    ei_rect_ptr_t img_rect;
    ei_anchor_t img_anchor;

} ei_impl_frame_t;

bool alreadyRegistered(char* class_name);

void create_widgetclass_frame();
void create_widgetclass_toplevel();
void create_widgetclass_button();

void initlistclassToNull();

bool is_point_in_rect(ei_rect_t rect, ei_point_t point);

extern uint32_t pick_id;
extern ei_point_t current_pointer_pos;

ei_surface_t get_picksurface();

tab_and_length concatenate_four_point_lists(ei_point_t* list1, ei_point_t* list2, ei_point_t* list3, ei_point_t* list4, int length1, int length2, int length3, int length4);

tab_and_length arc2(ei_point_t centre, int radius, int angle_start, int angle_end);

void set_defhandle_func_toNULL();

#endif
