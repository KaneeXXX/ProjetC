//
// Created by kanee on 15/05/2023.
//

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widget_attributes.h"
#include "ei_implementation.h"
#include "ei_utils.h"

void ei_placer_forget(ei_widget_t widget){
	widget->placer_params = NULL;

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
				     float*			rel_height){
	if (widget->placer_params == NULL){
		struct ei_impl_placer_params_t* params = calloc(1, sizeof(struct ei_impl_placer_params_t));
		widget->placer_params = params;
	}


	if (anchor==NULL){widget->placer_params->anchor = 0;}else{widget->placer_params->anchor = *anchor;}
	if (x == NULL){ widget->placer_params->x = 0;}else {widget->placer_params->x = *x;}
	if(y == NULL){ widget->placer_params->y = 0;} else {widget->placer_params->y = *y;}
	if (width == NULL){ widget->placer_params->width = 0;}else{widget->placer_params->width = *width;}
	if(height == NULL){ widget->placer_params->height = 0;}else{widget->placer_params->height = *height;}
        if (rel_x == NULL){ widget->placer_params->rel_x = 0;}else {widget->placer_params->rel_x = *rel_x;}
	if (rel_y == NULL){ widget->placer_params->rel_y = 0;}else {widget->placer_params->rel_y = *rel_y;}
	if (rel_width == NULL){ widget->placer_params->rel_width = 0;}else {widget->placer_params->rel_width = *rel_width;}
	if (rel_height == NULL){ widget->placer_params->rel_height = 0;}else {widget->placer_params->rel_height = *rel_height;}
}

void ei_impl_placer_run(ei_widget_t widget) {
	/* Calcule le screen location du widget
	 * en fonction des placer_params*/
	if(widget->placer_params != NULL){

		// On récupère le content_rect du parent
		ei_widget_t parent = ei_widget_get_parent(widget);
		//const ei_rect_t *repere = ei_widget_get_content_rect(parent);
		//const ei_rect_t repere = {parent->screen_location.top_left, parent->requested_size};
		const ei_rect_t* repere = ei_widget_get_content_rect(parent);
		// On cherche les coordonnées du widget avant considération de
		// l'anchor
		// Coordonnées absolues par rapport au repère root
		ei_point_t top_left = repere->top_left;
		float rel_x = widget->placer_params->rel_x;
		int x = widget->placer_params->x;
		int x_coor_sans_anchor = top_left.x + rel_x * repere->size.width+ x;
		int y_coor_sans_anchor = top_left.y + widget->placer_params->rel_y * repere->size.height +
					 widget->placer_params->y;
		//largeur
		int largeur;
		if (widget->placer_params->width != 0) {
			largeur = widget->placer_params->width;
		} else {
			if (widget->placer_params->rel_width == 0) {
				if (widget->requested_size.width != 0){
					largeur = widget->requested_size.width;
				}else{
					largeur = 20;
				}
			} else {
				largeur = (int)(widget->placer_params->rel_width * repere->size.width);
			}
		}
		//longueur
		int longueur;
		if (widget->placer_params->height != 0) {
			longueur = widget->placer_params->height;
		} else {
			if (widget->placer_params->rel_height == 0) {
				if (widget->requested_size.height != 0){
					longueur = widget->requested_size.height;
				}else{
					longueur = 20;
				}

			} else {
				longueur = (int) ( widget->placer_params->rel_height * repere->size.height);
			}
		}

		ei_point_t top_left_widget;
		if (widget->placer_params->anchor == 0) {
			top_left_widget.x = x_coor_sans_anchor;
			top_left_widget.y = y_coor_sans_anchor;
		} else if (widget->placer_params->anchor == ei_anc_center) {
			top_left_widget.x = x_coor_sans_anchor - largeur / 2;
			top_left_widget.y = y_coor_sans_anchor - longueur / 2;
		} else if (widget->placer_params->anchor == ei_anc_north) {
			top_left_widget.x = x_coor_sans_anchor - largeur / 2;
			top_left_widget.y = y_coor_sans_anchor;
		} else if (widget->placer_params->anchor == ei_anc_south) {
			top_left_widget.x = x_coor_sans_anchor - largeur / 2;
			top_left_widget.y = y_coor_sans_anchor - longueur;
		} else if (widget->placer_params->anchor == ei_anc_east) {
			top_left_widget.x = x_coor_sans_anchor - largeur;
			top_left_widget.y = y_coor_sans_anchor - longueur / 2;
		} else if (widget->placer_params->anchor == ei_anc_west) {
			top_left_widget.x = x_coor_sans_anchor;
			top_left_widget.y = y_coor_sans_anchor - longueur / 2;
		} else if (widget->placer_params->anchor == ei_anc_northeast) {
			top_left_widget.x = x_coor_sans_anchor - largeur;
			top_left_widget.y = y_coor_sans_anchor;
		} else if (widget->placer_params->anchor == ei_anc_northwest) {
			top_left_widget.x = x_coor_sans_anchor;
			top_left_widget.y = y_coor_sans_anchor;
		} else if (widget->placer_params->anchor == ei_anc_southeast) {
			top_left_widget.x = x_coor_sans_anchor - largeur;
			top_left_widget.y = y_coor_sans_anchor - longueur;
		} else if (widget->placer_params->anchor == ei_anc_southwest) {
			top_left_widget.x = x_coor_sans_anchor;
			top_left_widget.y = y_coor_sans_anchor - longueur;
		}


		ei_rect_t screen_location;
		screen_location.top_left = top_left_widget;
		screen_location.size.width = largeur;
		screen_location.size.height = longueur;
		widget->screen_location = screen_location;

		if (strcmp(widget->wclass->name, "toplevel") == 0){
			ei_point_t content_rec_topleft = (ei_point_t) {widget->screen_location.top_left.x, widget->screen_location.top_left.y + 20};
			widget->content_rect = ei_rect(content_rec_topleft, ei_size(screen_location.size.width, screen_location.size.height - 20));
		} else {
			widget->content_rect = screen_location;
		}

	}

}


