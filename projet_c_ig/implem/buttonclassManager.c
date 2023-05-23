
//
// Created by serafith on 12/05/2023.
//

/*This file contains the methods of ei_widget_class_t button*/

#include "ei_widgetclass.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "ei_implementation.h"
#include "ei_widget_configure.h"
#include "ei_utils.h"
#include "ei_event.h"
#include "ei_application.h"
#include "ei_types.h"
#include "ei_widget.h"

ei_widget_t alloc_button()
{
	ei_impl_button_t* bouton = calloc(1, sizeof(ei_impl_button_t));
	return (ei_widget_t) bouton;
}

void release_button(ei_widget_t widget)
{
	ei_impl_button_t* button = (ei_impl_button_t*) widget;
	free(button);
}

void drawbutton(ei_widget_t		widget,
		 ei_surface_t		surface,
		 ei_surface_t		pick_surface,
		 ei_rect_t*		clipper)
		 {
	ei_impl_button_t* button = (ei_impl_button_t*) widget;
	draw_button(surface,
	     (ei_rect_t) {widget->screen_location.top_left, widget->requested_size},
	     button->color,
	     button->border_width,
	     button->corner_radius,
	     button->relief,
	     button->text,
	     button->text_font,
	     button->text_color,
	     button->img,
	     NULL
	     );

	//dessiner dans l'offscreen
	 draw_button(pick_surface,
		     (ei_rect_t) {widget->screen_location.top_left, widget->requested_size},
		     *(widget->pick_color),
		     button->border_width,
		     button->corner_radius,
		     ei_relief_none,
		     NULL,
		     button->text_font,
		     button->text_color,
		     NULL,
		     NULL
	 );
	 ei_impl_widget_draw_children(widget, ei_app_root_surface(), get_picksurface(), NULL);
}

void setdefaults_button(ei_widget_t widget){
	//configure avec valeur par default
	ei_size_t sizedef = ei_size(50, 30);
	const ei_color_t color_inside = { 147, 149, 152, 0xff};
	int border_width = 4;
	int border_radius = 5;
	ei_relief_t reliefdef = ei_relief_raised;
	ei_string_t textdef = "default text";
	ei_font_t fontdef = ei_default_font;
	ei_color_t black = {0,0,0,0xff};
	ei_anchor_t anchordef = ei_anc_center;
	ei_button_configure(widget, &sizedef, &color_inside, &border_width, &border_radius, &reliefdef, &textdef, &fontdef, &black, &anchordef, NULL, NULL, NULL, NULL, NULL);
}

void geomnotify_button(ei_widget_t widget){

}

//traitant interne de la calsse button
bool handle_button(ei_widget_t widget_manipulated,  ei_event_t* event) {

	switch (event->type) {
		case ei_ev_mouse_buttondown:

			ei_event_set_active_widget(widget_manipulated); //Full attention focused on this amazing widget !
			ei_relief_t relief_pushed = ei_relief_sunken;
			ei_button_configure(widget_manipulated, NULL, NULL, NULL, NULL, &relief_pushed, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

			ei_impl_button_t* button = (ei_impl_button_t*) widget_manipulated;
			button->callback(widget_manipulated, event, event->param.application.user_param);
			return true;
			break;
		case ei_ev_mouse_buttonup:
			printf("");
			ei_relief_t relief_raised = ei_relief_raised;
			ei_button_configure(widget_manipulated, NULL, NULL, NULL, NULL, &relief_raised, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			ei_event_set_active_widget(NULL); //We are no longer manipulating the amazing widget, so the attention is no longer focus on it !
			return true;
			break;

			/*case ei_ev_mouse_move:
				widget_manipulated->wclass->handlefunc(widget_manipulated, event_listener);
				break;*/
		default:
			break;
	}

	return false;
}

void create_widgetclass_button(){
	ei_widgetclass_t* button = calloc(1, sizeof(ei_widgetclass_t));
	ei_widgetclass_name_t name = "button";
	strcpy(button->name, name);
	button->allocfunc = &alloc_button;
	button-> releasefunc = &release_button;
	button->drawfunc = &drawbutton;
	button->setdefaultsfunc = &setdefaults_button;
	button->geomnotifyfunc = &geomnotify_button;
	button->handlefunc = &handle_button;
	button->next = NULL;

	ei_widgetclass_register(button);
}
