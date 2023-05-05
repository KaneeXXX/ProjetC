/**
*  @file      ei_draw.c
*  @brief     Graphical primitives to draw lines, polygons, text, and operation of drawing
*            surfaces.
*
*  \author
*  Created by Notre Groupe.
*
*/

#include <stdint.h>
#include "ei_types.h"
#include "hw_interface.h"
#include "ei_draw.h"

//NO CLIPPING for the moment (ei_fill, ei_draw_polyline and ei_draw_polygon)
//hw_surface_update_rects(surface, NULL) (NULL -> update all the screen)

void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_rect_t* clipper)
{
	//Returns a pointer pointing at the address of the pixel at coordinates (0, 0) of the surface.
	uint32_t* surface_buffer = (uint32_t*) hw_surface_get_buffer(surface); //surface_buffer = address pixel coordinate (0,0)
	//When surface_buffer++, move to the next pixel (+4 bytes in memory)

	//get size of the surface
	ei_size_t size = hw_surface_get_size(surface);
	int nb_pixel = size.width*size.height;

	//get order of colors in pixel
	int ir, ig, ib, ia;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

	if (color == NULL) { //then draw in black
		for(int i = 0; i <= nb_pixel - 1; i++){
			//Treatment of pixel
			uint32_t pixel_value; //vector of 4 bytes
			uint8_t* channel_ptr = (uint8_t*) &pixel_value; //pointer to that vector (pixel_value)
			channel_ptr[ir] = channel_ptr[ig] = channel_ptr[ib] = 0x00; //BLACK
			channel_ptr[ia] = 0xff; //OPAQUE
			*surface_buffer++ = pixel_value; //<=> *surface_buffer=pixel_value; surface_buffer++
		}
	} else {
		for(int i = 0; i <= nb_pixel - 1; i++) {
			//Treatment of pixel
			uint32_t pixel_value; //vector of 4 bytes
			uint8_t* channel_ptr = (uint8_t*) &pixel_value; //pointer to that vector (pixel_value)
			channel_ptr[ir] = color->red;
			channel_ptr[ig] = color->green;
			channel_ptr[ib] = color->blue;
			channel_ptr[ia] = color->alpha;
			*surface_buffer++ = pixel_value; //<=> *surface_buffer=pixel_value; surface_buffer++
		}
	}
}

void draw_pixel(u_int32_t* addr, ei_surface_t surface, ei_color_t color)
{
	//Get order of colors in pixel because it's not always the same
	int ir, ig, ib, ia;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

	uint32_t pixel_value;
	uint8_t* channel_ptr = (uint8_t*) &pixel_value; //ptr to pixel_value
	channel_ptr[ir] = color.red;
	channel_ptr[ig] = color.green;
	channel_ptr[ib] = color.blue;
	channel_ptr[ia] = color.alpha;
	*addr = pixel_value;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a=*b;
	*b=temp;
}

void draw_line(ei_surface_t surface, ei_point_t pt1, ei_point_t pt2, ei_color_t color)
{
	uint32_t *surface_buffer = (uint32_t *) hw_surface_get_buffer(surface);
	ei_size_t size = hw_surface_get_size(surface);
	int width = size.width;
	int x0 = pt1.x;
	int y0 = pt1.y;
	int x1 = pt2.x;
	int y1 = pt2.y;
	int dx = x1 - x0;
	int dy = y1 - y0;
	int E = 0;

	if ((x0 == x1) && (y0 == y1)) { //pt1==pt2 (draw point)
		u_int32_t *pixel = surface_buffer + width * y0 + x0;
		draw_pixel(pixel, surface, color);
		return;
	}
	else if (x0 == x1) { //vertical
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
	else if (y0 == y1) { //horizontal
		if (x1 < x0) {
			swap(&x0, &x1);
			swap(&y0, &y1);
		}
		while (x0 < x1) {
			u_int32_t *pixel = surface_buffer + width * y0 + x0;
			draw_pixel(pixel, surface, color);
			x0++;
		}
	}
	else if (((x0 < x1) && (y0 < y1)) || ((x1 < x0) && (y1 < y0))) {
		if (x1 < x0 && y1 < y0) {
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
	else { //(((x1 < x0) && (y0 < y1)) || ((x0 < x1) && (y1 < y0)))
		if (x1 < x0 && y0 < y1) {
			swap(&x0, &x1);
			swap(&y0, &y1);
		}
		dy = abs(dy); //dy<0 in this case
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

void ei_draw_polyline(ei_surface_t surface, ei_point_t* point_array, size_t point_array_size, ei_color_t color, const ei_rect_t* clipper)
{
	if (point_array_size == 0) { //empty array
		return;
	}
	else if (point_array_size == 1) { //draw a point
		draw_line(surface, point_array[0], point_array[0], color);
	}
	else {
		for (int i = 0; i <= point_array_size - 2; i++) {
			draw_line(surface, point_array[i], point_array[i+1], color);
		}
	}
}

typedef struct lc {
	int        			y_max; // max ord
	int        			x_ymin; // min ord
	float 				one_on_m; // when y++, x+=1/m
	struct 				lc *next; // next
} lc;

typedef struct minmax {
	int 				y_min;
	int 				y_max;
	ei_point_t 			p_min;
	int 				index_p_min;
	ei_point_t 			p_max;
	int 				index_p_max;
} minmax;

struct minmax min_max_sur_y (ei_point_t* point_array, size_t point_array_size) {
	//Recupere les ordonnees minimale et maximale des points du tableau, les points ayant ces ordonnees extremes
        // et les indices dans le tableau de ces points
        // PK ON SE BALADE AVEC L'INDICE ET LA VALEUR SACHANT EN MEME TEMPS? ON A LE POINT EN PLUS!
	int max = point_array[0].y;
	int min = point_array[0].y;
        ei_point_t p_min;
	ei_point_t p_max;
        int index_p_min;
        int index_p_max;
	for (size_t i = 0; i < point_array_size - 1; i++) {
		if (point_array[i].y > max) {
			max = point_array[i].y;
			p_max = point_array[i];
			index_p_max = i;
		}
		else if (point_array[i].y < min) {
			min = point_array[i].y;
			p_min = point_array[i];
			index_p_min = i;

		}
	}
	struct minmax res = {min, max, p_min, index_p_min, p_max, index_p_max};
	return res;
}

ei_point_t* get_neighbors(ei_point_t* point_array, size_t index, size_t point_array_size)
{
	ei_point_t left_neighbor;
	ei_point_t right_neighbor;
	if (index == 0) { //left neighbor of first element is last element
		left_neighbor = point_array[(int)(point_array_size-1)];
		right_neighbor = point_array[1];
	}
	else if (index == point_array_size -1) { //right neighbor of last element is first element
		left_neighbor = point_array[(int)(index-1)];
		right_neighbor = point_array[0];
	}
	else { //(index != 0 && index != point_array_size-1)
		left_neighbor = point_array[(int)(index-1)];
		right_neighbor = point_array[(int)(index+1)];
	}
	ei_point_t* res = calloc(2, sizeof(ei_point_t));
	res[0] = left_neighbor;
	res[1] = right_neighbor;
	return res;
}

void ei_draw_polygon (ei_surface_t surface, ei_point_t*  point_array, size_t point_array_size, ei_color_t color, const ei_rect_t* clipper)
{
	minmax critical_pts = min_max_sur_y(point_array, point_array_size);
	// tableau de pointeurs de type struct lc * initialises à NULL de taille ymax -ymin +1
	int length_tc = (critical_pts.y_max - critical_pts.y_min +1 );
	lc** tab_tc = calloc(length_tc, sizeof(lc*));
	//Le point B sur le graphique et son index dans le tableau point_array..
	ei_point_t point_plus_haut = critical_pts.p_min;
	size_t index = critical_pts.index_p_min;

	// On parcourt le tableau tab_tc qu'on remplit par des listes chaînées...
	// i = 0 correspond à la scanline y = ymin... i= taille_tc -1 correspond à la
	// scanline y = ymax...
	// Pour un numéro de scanline y donné, sa position i dans le tableau tab_tc sera
	// i = y - ymin

	for(int i = 0; i < length_tc; i++) {

		ei_point_t* voisins = get_neighbors(point_array, index, point_array_size);


	}
}



