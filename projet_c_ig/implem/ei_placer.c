//
// Created by kanee on 15/05/2023.
//

#include "ei_types.h"
#include "ei_widget.h"
#include "ei_widget_attributes.h"
#include "ei_implementation.h"



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
        widget->placer_params->anchor = anchor;
	widget->placer_params->x = x;
	widget->placer_params->y = y;
	widget->placer_params->width = width;
	widget->placer_params->height = height;
	widget->placer_params->rel_x = rel_x;
	widget->placer_params->rel_y = rel_y;
	widget->placer_params->rel_width = rel_width;
	widget->placer_params->rel_height = rel_height;
}

void ei_impl_placer_run(ei_widget_t widget){
	/* Calcule le screen location du widget
	 * en fonction des placer_params*/
	if (widget->placer_params != NULL) {
		// On récupère le content_rect du parent
		ei_widget_t parent = ei_widget_get_parent(widget);
		ei_rect_t *repere = ei_widget_get_content_rect(parent);
		// On cherche les coordonnées du widget avant considération de
		// l'anchor
		// Coordonnées absolues par rapport au repère root
		ei_point_t top_left = repere->top_left;
		int x_coor_sans_anchor =
			top_left.x + *widget->placer_params->rel_x * repere->size.width + *widget->placer_params->x;
		int y_coor_sans_anchor =
			top_left.y + *widget->placer_params->rel_y * repere->size.height + *widget->placer_params->y;
		//largeur
		int largeur;
		if (widget->placer_params->width != NULL) {
			largeur = *widget->placer_params->width;
		} else {
			if (widget->placer_params->rel_width = NULL) {
				largeur = 0;
			} else {
				largeur = *widget->placer_params->rel_width * repere->size.width;
			}
		}
		//longueur
		int longueur;
		if (widget->placer_params->height != NULL) {
			longueur = *widget->placer_params->height;
		} else {
			if (widget->placer_params->rel_height = NULL) {
				longueur = 0;
			} else {
				longueur = *widget->placer_params->rel_height * repere->size.height;
			}
		}

		ei_point_t top_left_widget;
		if (*widget->placer_params->anchor == 0) {
			top_left_widget.x = x_coor_sans_anchor;
			top_left_widget.y = y_coor_sans_anchor;
		} else if (*widget->placer_params->anchor == ei_anc_center) {
			top_left_widget.x = x_coor_sans_anchor - largeur / 2;
			top_left_widget.y = y_coor_sans_anchor - longueur / 2;
		} else if (*widget->placer_params->anchor == ei_anc_north) {
			top_left_widget.x = x_coor_sans_anchor - largeur / 2;
			top_left_widget.y = y_coor_sans_anchor;
		} else if (*widget->placer_params->anchor == ei_anc_south) {
			top_left_widget.x = x_coor_sans_anchor - largeur / 2;
			top_left_widget.y = y_coor_sans_anchor - longueur;
		} else if (*widget->placer_params->anchor == ei_anc_east) {
			top_left_widget.x = x_coor_sans_anchor - largeur;
			top_left_widget.y = y_coor_sans_anchor - longueur / 2;
		} else if (*widget->placer_params->anchor == ei_anc_west) {
			top_left_widget.x = x_coor_sans_anchor;
			top_left_widget.y = y_coor_sans_anchor - longueur / 2;
		} else if (*widget->placer_params->anchor == ei_anc_northeast) {
			top_left_widget.x = x_coor_sans_anchor - largeur;
			top_left_widget.y = y_coor_sans_anchor;
		} else if (*widget->placer_params->anchor == ei_anc_northwest) {
			top_left_widget.x = x_coor_sans_anchor;
			top_left_widget.y = y_coor_sans_anchor;
		} else if (*widget->placer_params->anchor == ei_anc_southeast) {
			top_left_widget.x = x_coor_sans_anchor - largeur;
			top_left_widget.y = y_coor_sans_anchor - longueur;
		} else if (*widget->placer_params->anchor == ei_anc_southwest) {
			top_left_widget.x = x_coor_sans_anchor;
			top_left_widget.y = y_coor_sans_anchor - longueur;
		}
		ei_rect_t screen_location;
		screen_location.top_left = top_left_widget;
		screen_location.size.width = largeur;
		screen_location.size.height = longueur;

		widget->screen_location = screen_location;
	}

}


