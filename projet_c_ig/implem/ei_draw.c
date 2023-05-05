/**
*  @file      ei_draw.c
*  @brief     Graphical primitives to draw lines, polygons, text, and operation of drawing
*            surfaces.
*
*  \author
*  Created by Notre Groupe on 03.05.23.
*
*/

#include <stdint.h>
#include "ei_types.h"
#include "hw_interface.h"
#include "ei_draw.h"

//sans clipper ici
//lock before ei_fill call
//unlock before ei_fill call
//Requests that a list of rectangular regions of the root surface be updated on screen. (NULL -> update all the screen)
//hw_surface_update_rects(surface, NULL);
void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_rect_t* clipper) {

	//Returns a pointer to the address of the pixel at coordinated (0, 0) of the surface.
	uint32_t* surface_buffer = (uint32_t*) hw_surface_get_buffer(surface);   //surface_buffer = address pixel coordinate (0,0)
	//On a déclaré un pointeur sur 32bit (4 octets) quand on incrémente surface_buffer de 1 on se déplace de 4 octets dans la mémoire (d'un pixel à l'autre)

	//get size of the surface
	ei_size_t size = hw_surface_get_size(surface);
	int width = size.width;
	int height = size.height;

	int nb_pixel = width*height;

	//get order of colors in pixel
	int ir, ig, ib, ia;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

	//test if color is NULL
	if (color == NULL){
		//painted black (opaque)

		for(int i = 0; i <= nb_pixel - 1; i++){
			//treatment of pixel

			//create vector of 4 byte (4 octet)
			uint32_t pixel_value;
			//déclare pointeur vers pixel_value
			uint8_t* channel_ptr = (uint8_t*) &pixel_value;

			channel_ptr[ir] = 0x00;
			channel_ptr[ig] = 0x00;
			channel_ptr[ib] = 0x00;
			channel_ptr[ia] = 0xff;

			*surface_buffer++ = pixel_value; //<=> *surface_buffer=pixel_value; surface_buffer++
		}

	} else {
		//paint of the surface with color (don't take clipper into account for now)

		for(int i = 0; i <= nb_pixel - 1; i++){
			//treatment of pixel

			//create vector of 4 byte (4 octet)
			uint32_t pixel_value;
			//déclare pointeur vers pixel_value
			uint8_t* channel_ptr = (uint8_t*) &pixel_value;

			channel_ptr[ir] = color->red;
			channel_ptr[ig] = color->green;
			channel_ptr[ib] = color->blue;
			channel_ptr[ia] = color->alpha;

			*surface_buffer++ = pixel_value; //<=> *surface_buffer=pixel_value; surface_buffer++
		}
	}
}

void draw_pixel(u_int32_t* addr, ei_surface_t surface, ei_color_t color){



	//get order of colors in pixel
	int ir, ig, ib, ia;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

	uint32_t pixel_value;
	//déclare pointeur vers pixel_value
	uint8_t* channel_ptr = (uint8_t*) &pixel_value;

	channel_ptr[ir] = color.red;
	channel_ptr[ig] = color.green;
	channel_ptr[ib] = color.blue;
	channel_ptr[ia] = color.alpha;

	*addr = pixel_value;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a=*b;
	*b=temp;
}

void draw_line(ei_surface_t surface, ei_point_t point_un, ei_point_t point_deux, ei_color_t color) {

	uint32_t *surface_buffer = (uint32_t *) hw_surface_get_buffer(surface);
	ei_size_t size = hw_surface_get_size(surface);
	int width = size.width;

	int x0 = point_un.x;
	int y0 = point_un.y;
	int x1 = point_deux.x;
	int y1 = point_deux.y;

	int dx = x1 - x0;
	int dy = y1 - y0;

	int E = 0;

	//if only on point in the array
	if ((point_un.x == point_deux.x) && (point_un.y == point_deux.y)) {
		u_int32_t *pixel = surface_buffer + width * y0 + x0;
		draw_pixel(pixel, surface, color);
		return;
	}

	//vertical
	if (x0 == x1) {
		if (y1 < y0) {
			swap(&x0, &x1);
			swap(&y0, &y1);
		}
		while (y0 < y1) {
			u_int32_t *pixel = surface_buffer + width * y0 + x0;
			draw_pixel(pixel, surface, color);
			y0++;
		}
	}

	//horizontal
	if (y0 == y1) {
		if (x1 < x0) {
			swap(&x1, &x0);
			swap(&y0, &y1);
		}
		while (x0 < x1) {
			u_int32_t *pixel = surface_buffer + width * y0 + x0;
			draw_pixel(pixel, surface, color);
			x0++;
		}
	}


	if (((x0 < x1) && (y0 < y1)) || ((x1 < x0) && (y1 < y0))) {
		if (x1 < x0 && y1 < y0) {
			//inverser le role de (x0,y0) et (x1,y1)
			swap(&x0, &x1);
			swap(&y0, &y1);

		}
		dx=abs(dx);
		dy=abs(dy);
		if (abs(dx) > abs(dy)) {
			while (x0 < x1) {
				u_int32_t *pixel = surface_buffer + width * y0 + x0;
				draw_pixel(pixel, surface, color);
				x0 += 1;
				E += dy;
				if (2 * E > dx) {
					y0 += 1;
					E -= dx;
				}
			}
		} else {
			while (y0 < y1) {
				u_int32_t *pixel = surface_buffer + width * y0 + x0;
				draw_pixel(pixel, surface, color);
				y0 += 1;
				E += dx;
				if (2 * E > dy) {
					x0 += 1;
					E -= dy;
				}
			}
		}

	}

	if (((x1 < x0) && (y0 < y1)) || ((x0 < x1) && (y1 < y0))) {
		if (x1 < x0 && y0 < y1) {
			//inverser le role de (x0,y0) et (x1,y1)
			swap(&x0, &x1);
			swap(&y0, &y1);
		}
		dy = abs(dy); //dy négatif dans ce cas sinon
		if (abs(dx) > abs(dy)) {
			while (x0 < x1) {
				u_int32_t *pixel = surface_buffer + width * y0 + x0;
				draw_pixel(pixel, surface, color);
				x0 += 1;
				E += dy;
				if (2 * E > dx) {
					y0 -= 1;
					E -= abs(dx);
				}
			}
		} else {
			while (y0 > y1) {
				u_int32_t *pixel = surface_buffer + width * y0 + x0;
				draw_pixel(pixel, surface, color);
				y0 -= 1;
				E += abs(dx);
				if (2 * E > abs(dy)) {
					x0 += 1;
					E -= abs(dy);
				}
			}
		}
	}
}

void ei_draw_polyline(ei_surface_t surface, ei_point_t* point_array, size_t point_array_size, ei_color_t color, const ei_rect_t* clipper) {
	//point_array[0] donne le premier point

	//if empty array
	if (point_array_size == 0){
		return;
	}

	//1 point in the array
	if(point_array_size == 1){
		draw_line(surface, point_array[0], point_array[0], color);
	}

	for(uint32_t i = 0; i <= point_array_size - 2; i++){
		draw_line(surface, point_array[i], point_array[i+1], color);
	}
}

struct lc
{
    int        y_max; ///< ordonnée maximale
    int        x_ymin; ///< ordonnée minimale
    float un_sur_m; ///< 1/m, ce qu'il faut ajouter à x quand y progresse de 1
    struct lc *suiv; ///< suivant
};


struct minmax{
    int y_min;
    int y_max;
    ei_point_t p_min;
    int index_p_min;
    ei_point_t p_max;
    int index_p_max;
};

struct minmax min_max_sur_y(ei_point_t* point_array, size_t point_array_size){
	// Récupère les ordonnées minimale et maximale des points du tableau
	// en entrée ainsi que les points ayant ces ordonnées extrêmes
        // On retourne, par ailleurs, les indices dans le tableau de ces
        // points...

	int max = point_array[0].y;
	int min = point_array[0].y;
        ei_point_t p_min;
        int index_p_min;
        int index_p_max;
        ei_point_t p_max;
	for (size_t i = 0; i < point_array_size -1; i++ ){
		if (point_array[i].y > max){
			max = point_array[i].y;
			p_max = point_array[i];
			index_p_max = i;
		}
		if (point_array[i].y < min){
			min = point_array[i].y;
			p_min = point_array[i];
			index_p_min = i;

		}
	}
	struct minmax res = {min, max, p_min, index_p_min, p_max, index_p_max};
	return res;
}



ei_point_t* get_voisins(ei_point_t* point_array, size_t indice, size_t point_array_size){
	ei_point_t voisin_gauche;
	ei_point_t voisin_droite;
	if (indice != 0 && indice != point_array_size -1){
		voisin_gauche = point_array[(int)(indice -1)];
		voisin_droite = point_array[(int)(indice +1)];
	}
	if (indice == 0){
		voisin_gauche = point_array[(int)(point_array_size-1)];
		voisin_droite = point_array[1];
	}
	if (indice == point_array_size -1){
		voisin_gauche = point_array[(int)(indice -1)];
		voisin_droite = point_array[0];
	}

	ei_point_t* res = calloc(2, sizeof(ei_point_t));
	res[0] = voisin_gauche;
	res[1] = voisin_droite;

	return res;
}


void ei_draw_polygon (ei_surface_t surface, ei_point_t*  point_array, size_t point_array_size, ei_color_t color, const ei_rect_t* clipper) {

	struct minmax critical_pts = min_max_sur_y(point_array, point_array_size);

	// tableau de pointeurs de type struct lc * initialises à NULL de taille ymax -ymin +1

	int taille_tc = (critical_pts.y_max - critical_pts.y_min +1 );
	struct lc** tab_tc = calloc(taille_tc, sizeof(struct lc*));

	//Le point B sur le graphique et son indice dans le tableau point_array..
	ei_point_t point_plus_haut = critical_pts.p_min;
	size_t indice = critical_pts.index_p_min;



	// On parcourt le tableau tab_tc qu'on remplit par des listes chaînées...
	// i = 0 correspond à la scanline y = ymin... i= taille_tc -1 correspond à la
	// scanline y = ymax...
	// Pour un numéro de scanline y donné, sa position i dans le tableau tab_tc sera
	// i = y - ymin

	for(int i = 0; i < taille_tc; i++){

		ei_point_t* voisins = get_voisins(point_array, indice, point_array_size);
		


	}



}


