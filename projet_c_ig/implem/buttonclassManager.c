
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
	tab_and_length tabandlenght = rounded_frame((ei_rect_t) {widget->screen_location.top_left, widget->requested_size}, button->corner_radius, ei_relief_none);
	ei_draw_polygon(pick_surface, tabandlenght.tab, tabandlenght.length, *(widget->pick_color),NULL);
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
bool handle_button(ei_widget_t widget, struct ei_event_t* event){

	printf("not implemented %s\n", __func__ );
	exit(1);

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




