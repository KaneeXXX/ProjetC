/**
*  @file      ei_draw.c
*  @brief     Graphical primitives to draw lines, polygons, text, and operation of drawing
*            surfaces.
*
*  \author
*  Created by Notre Groupe.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ei_types.h"
#include "hw_interface.h"
#include "ei_draw.h"
#include "ei_implementation.h"
#define PI 3.141592654

//Check if pixel is in the clipped rectangle of the surface
bool is_pixel_drawable(uint32_t * pixel_addr, ei_surface_t surface, const ei_rect_t* clipper){

	uint32_t* surface_buffer = (uint32_t*) hw_surface_get_buffer(surface);
	int width = hw_surface_get_size(surface).width; //because variable used twice
	uint32_t addr_minus_addr0 = pixel_addr - surface_buffer; //used twice

	int point_x = addr_minus_addr0 % width;
	int point_y = addr_minus_addr0 / width;

	bool check_abs = (clipper->top_left.x <= point_x) && (point_x <= clipper->top_left.x+ clipper->size.width);
	bool check_ord = (clipper->top_left.y <= point_y) && (point_y <= clipper->top_left.y +clipper->size.height);
	return check_abs && check_ord;
}

void draw_pixel(u_int32_t* addr, ei_surface_t surface, ei_color_t color, const ei_rect_t* clipper)
{
	//Get order of colors in pixel because it's not always the same
	int ir, ig, ib, ia;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

	if ((clipper == NULL) || (is_pixel_drawable(addr, surface, clipper)))
	{
		uint32_t pixel_value;
		uint8_t *channel_ptr = (uint8_t *) &pixel_value; //ptr to pixel_value
		channel_ptr[ir] = color.red;
		channel_ptr[ig] = color.green;
		channel_ptr[ib] = color.blue;
		channel_ptr[ia] = color.alpha;
		*addr = pixel_value;
	}
}

void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_rect_t* clipper)
{
	uint32_t* surface_buffer = (uint32_t*) hw_surface_get_buffer(surface); //surface_buffer is pointing at address pixel coordinate (0,0)
	//When surface_buffer++, move to the next pixel (+4 bytes in memory)

	ei_size_t size = hw_surface_get_size(surface);
	int nb_pixel = size.width * size.height;
	ei_color_t noir = { 0, 0, 0, 255};
	if (color == NULL){
		for(int i = 0; i <= nb_pixel - 1; i++){
			draw_pixel(surface_buffer, surface, noir, clipper);
			surface_buffer++;
		}


	}else {
		for(int i = 0; i <= nb_pixel - 1; i++){
			draw_pixel(surface_buffer, surface, *color, clipper);
			surface_buffer++;
		}
	}

	//Get order in which colors are stored in pixel because it is not always RGBA
	/*if (color == NULL) { //then draw in black
		if (clipper == NULL) {
			for(int i = 0; i <= nb_pixel - 1; i++) {
				uint32_t pixel_value; //vector of 4 bytes
				uint8_t* channel_ptr = (uint8_t*) &pixel_value; //pointer to that vector (pixel_value)
				channel_ptr[ir] = channel_ptr[ig] = channel_ptr[ib] = 0x00; //BLACK
				channel_ptr[ia] = 0xff; //OPAQUE
				*surface_buffer++ = pixel_value; //<=> *surface_buffer = pixel_value; surface_buffer++
			}
		}
		else {
			for(int i = 0; i <= nb_pixel - 1; i++) {
				uint32_t pixel_value; //vector of 4 bytes
				uint8_t* channel_ptr = (uint8_t*) &pixel_value; //pointer to that vector (pixel_value)
				if (is_pixel_drawable(surface_buffer, surface, clipper)) {
					channel_ptr[ir] = channel_ptr[ig] = channel_ptr[ib] = 0x00; //BLACK
					channel_ptr[ia] = 0xff; //OPAQUE
				}
				*surface_buffer++ = pixel_value; //<=> *surface_buffer = pixel_value; surface_buffer++
			}
		}
	}
	else {
		if (clipper == NULL) {
			for(int i = 0; i <= nb_pixel - 1; i++) {
				uint32_t pixel_value;
				uint8_t* channel_ptr = (uint8_t*) &pixel_value;
				channel_ptr[ir] = color->red;
				channel_ptr[ig] = color->green;
				channel_ptr[ib] = color->blue;
				channel_ptr[ia] = color->alpha;
				*surface_buffer++ = pixel_value;
			}
		}
		else {
			for(int i = 0; i <= nb_pixel - 1; i++) {
				uint32_t pixel_value;
				uint8_t* channel_ptr = (uint8_t*) &pixel_value;
				if (is_pixel_drawable(surface_buffer, surface, clipper)) {
					channel_ptr[ir] = color->red;
					channel_ptr[ig] = color->green;
					channel_ptr[ib] = color->blue;
					channel_ptr[ia] = color->alpha;
				}
				*surface_buffer++ = pixel_value;
			}
		}
	}*/
}



void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void draw_line(ei_surface_t surface, ei_point_t pt1, ei_point_t pt2, ei_color_t color, const ei_rect_t* clipper)
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
		draw_pixel(pixel, surface, color, clipper);
	}
	else if (x0 == x1) { //vertical
		if (y1 < y0) {
			swap(&x0, &x1);
			swap(&y0, &y1);
		}
		while (y0 < y1) {
			u_int32_t *pixel = surface_buffer + width * y0 + x0;
			draw_pixel(pixel, surface, color, clipper);
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
			draw_pixel(pixel, surface, color, clipper );
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
		if (abs(dx) > abs(dy)) { // |dx| > |dy|
			while (x0 < x1) {
				u_int32_t *pixel = surface_buffer + width * y0 + x0;
				draw_pixel(pixel, surface, color, clipper);
				x0 += 1;
				E += dy;
				if (2 * E > dx) {
					y0 += 1;
					E -= dx;
				}
			}
		} else { // |dx| < |dy|
			while (y0 < y1) {
				u_int32_t *pixel = surface_buffer + width * y0 + x0;
				draw_pixel(pixel, surface, color, clipper);
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
		if (abs(dx) > abs(dy)) { // |dx| > |dy|
			while (x0 < x1) {
				u_int32_t *pixel = surface_buffer + width * y0 + x0;
				draw_pixel(pixel, surface, color, clipper);
				x0 += 1;
				E += dy;
				if (2 * E > dx) {
					y0 -= 1;
					E -= abs(dx);
				}
			}
		} else { // |dx| < |dy|
			while (y0 > y1) {
				u_int32_t *pixel = surface_buffer + width * y0 + x0;
				draw_pixel(pixel, surface, color, clipper);
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
		draw_line(surface, point_array[0], point_array[0], color, clipper);
	}
	else {
		for (uint32_t i = 0; i <= point_array_size - 2; i++) {
			draw_line(surface, point_array[i], point_array[i+1], color, clipper);
		}
	}
}

enum direction {LEFT, RIGHT};

typedef struct lc_t lc_t;

struct lc_t {
	int        			y_max; // max ord
	int        			x_ymin; // min ord
	int 				E;
	int 				abs_dx;
	int 				abs_dy;
	enum direction 			dir;
	lc_t 				*next; // next
};

typedef struct {
	int 				y_min;
	int 				y_max;
} minmax_t;

//Return the min and max y-coordinate of an array of points
minmax_t min_max_y(ei_point_t* point_array, size_t point_array_size)
{
	int max = point_array[0].y;
	int min = point_array[0].y;
	for (size_t i = 1; i < point_array_size - 1; i++){
		if (point_array[i].y > max){
			max = point_array[i].y;
		}
		if (point_array[i].y <= min){
			min = point_array[i].y;
		}
	}
	return (minmax_t) {min, max};
}

//Check if TC is empty
bool isTC_empty(lc_t** tab_tc, int size_tc)
{
	for (int i = 0; i < size_tc; i++) {
		if (tab_tc[i] != NULL) {
			return false;
		}
	}
	return true;
}

//Add to TCA the sides after chaining
void add_to_TCA(lc_t** TCA, lc_t* chain) {
	if (*TCA == NULL) { //Add the cell(s) of chain sorted by increasing x_ymin
		lc_t* ptr_first_cell_in_chain = chain;
		if (ptr_first_cell_in_chain->next != NULL) { //if there is a 2nd cell to chaining "chain"
			lc_t* ptr_second_cell_in_chain = ptr_first_cell_in_chain->next;
			if (ptr_first_cell_in_chain->x_ymin <= ptr_second_cell_in_chain->x_ymin) { //if ordered
				*TCA = chain; //nothing to do
			} else { //swap the 2 cells
				ptr_second_cell_in_chain->next = ptr_first_cell_in_chain;
				lc_t* tmp = ptr_second_cell_in_chain;
				ptr_first_cell_in_chain->next = NULL;
				*TCA = tmp;
			}
		}
		else {
			*TCA = chain;
		}
		return;
	}
	if (chain == NULL) {
		return;
	}
	//Cas if TCA already has cells, the new element(s) (2 at max) of "chain" must be added in the right place of TCA (already sorted)
	lc_t* ptr_first_cell_in_chain = chain;
	lc_t* ptr_second_cell_in_chain = chain->next; //possibly NULL
	for(int i = 0; i < 2; i++) { //twice car 2 cells at max in "chain"
		lc_t *ptr_previous = *TCA;
		lc_t *ptr_current_cell_TCA = *TCA; //init to first cell
		bool header = true;
		bool placed=false;
		while (ptr_current_cell_TCA != NULL && placed == false) {
			if (ptr_current_cell_TCA->x_ymin >= ptr_first_cell_in_chain->x_ymin) {
				if (header) {
					*TCA = ptr_first_cell_in_chain;
					ptr_first_cell_in_chain->next = ptr_current_cell_TCA;

				}
				else {
					ptr_previous->next = ptr_first_cell_in_chain;
					ptr_first_cell_in_chain->next = ptr_current_cell_TCA;
					placed=true;
				}
			}
			ptr_previous = ptr_current_cell_TCA;
			ptr_current_cell_TCA = ptr_current_cell_TCA->next;
			header = false;
		}
		if (ptr_second_cell_in_chain == NULL) { //if there is no 2nd cell
			return;
		}
		ptr_first_cell_in_chain = ptr_second_cell_in_chain; //go to 2nd cell of "chain"
	}
}

//Remove from TCA the sides for which ymax = y (scanline_num)
int delete_side_TCA(lc_t** TCA, int scanline_num)
{
	if (*TCA == NULL) {
		return 0;
	}
	int size_TCA = 0; //will increase in the loop.
	lc_t* ptr_previous = *TCA;
	lc_t* ptr_current_side = *TCA; //init to first cell
	bool header = true;
	while (ptr_current_side != NULL) {
		if (ptr_current_side->y_max == scanline_num) {
			if (header) {
				*TCA = ptr_current_side->next;
				lc_t* to_free = ptr_current_side;
				ptr_current_side = ptr_current_side->next;
				free(to_free);
			}
			else {
				//ptr_previous = ptr_current_side->next;
				//free(ptr_current_side); //ptr_current_side is of type lc_t
				//ptr_current_side = ptr_previous; //hang up
				ptr_previous->next = ptr_current_side->next;
				free(ptr_current_side);
				size_TCA--;
			}
		}
		else {
			ptr_previous = ptr_current_side;
			ptr_current_side = ptr_current_side->next;
			size_TCA++;
			header = false;
		}
	}
	return size_TCA;
}

enum draw_state {IN, OUT};

//Draw a scanline of a polygon
void draw_scanline(lc_t** TCA, int size_TCA, int y,ei_surface_t surface, ei_color_t color, const ei_rect_t *clipper) {
	lc_t* ptr_current_cell = *TCA;
	enum draw_state state = IN;
	double x_to_color1 = 0.0; //start of segment to draw
	double x_to_color2 = 0.0; //end of segment to draw
	//Visit TCA
	for (int i = 0; i < size_TCA; i++) {
		double x_ymin = ptr_current_cell -> x_ymin; //for each cell of TCA, x_ymin = intersections with scanline, not always int
		if (state == IN) {
			x_to_color1 = ceil(x_ymin); //round up
			state = OUT;
		} else { //state == OUT, interval exit
			x_to_color2 = floor(x_ymin); //round down
			draw_line(surface, (ei_point_t) {x_to_color1, y}, (ei_point_t) {x_to_color2, y}, color, clipper);
			state = IN;
		}
		ptr_current_cell = ptr_current_cell->next;
	}
}

void update_x_ymin_sides(lc_t** TCA)
{
	lc_t* current_cell = *TCA;
	while (current_cell != NULL) {
		enum direction dir = current_cell->dir;
		int abs_dx = current_cell->abs_dx;
		int abs_dy = current_cell->abs_dy;
		if (abs_dx == 0) {
			current_cell = current_cell->next;
		}
		else if(abs_dy == 0) {
			// ?
		}
		else {
			int incr = (dir == RIGHT) ? 1 : -1;
			current_cell->E += abs_dx;
			while (2 * (current_cell->E) > abs_dy) {
				(current_cell->x_ymin) += incr;
				current_cell->E -= abs_dy;
			}
			current_cell = current_cell->next;
		}
	}
}

void add_to_chain(lc_t* first_cell, lc_t* cell_to_add)
{
	lc_t* current = first_cell;
	while (current -> next != NULL) {
		current = current -> next;
	}
	current -> next = cell_to_add;
}

void ei_draw_polygon (ei_surface_t surface, ei_point_t*  point_array, size_t point_array_size, ei_color_t color, const ei_rect_t* clipper)
{
	//Build TC
	minmax_t critical_pts = min_max_y(point_array, point_array_size);
	int y_min = critical_pts.y_min;
	int size_tc = critical_pts.y_max - y_min + 1;
	lc_t** tab_TC = calloc(size_tc, sizeof(lc_t*));
	ei_point_t p1;
	ei_point_t p2;
	for (size_t i = 0; i < point_array_size; i++) {
		if (i == point_array_size - 1) { //because "next" point of last point is first point
			 p1 = point_array[i];
			 p2 = point_array[0];
		}
		else {
			p1 = point_array[i];
			p2 = point_array[i + 1];
		}
		if (p1.y != p2.y) {
			int ymax, x_ymin, x_up, y_up, x_down;
			if (p1.y > p2.y) {
				x_up = p2.x;
				y_up = p2.y;
				x_down = p1.x;
				ymax = p1.y;
				x_ymin = p2.x;
			}
			else { //p1.y < p2.y
				x_up = p1.x;
				y_up = p1.y;
				x_down = p2.x;
				ymax = p2.y;
				x_ymin = p1.x;
			}
			lc_t* side = calloc(1, sizeof(lc_t));
			side->y_max = ymax;
			side->x_ymin = x_ymin;
			side->abs_dx = abs(p1.x - p2.x);
			side->abs_dy = abs(p1.y - p2.y);
			side->E = 0;
			side->dir = (x_up > x_down) ? LEFT : RIGHT;
			side->next = NULL;
			int index_in_TC = y_up - y_min;
			if (tab_TC[index_in_TC] == NULL) {
				tab_TC[index_in_TC] = side;
			}
			else {
				add_to_chain(tab_TC[index_in_TC], side);
			}
		}
	}
	//Build TCA
	lc_t** TCA = malloc(sizeof(lc_t));
	*TCA = NULL; //TCA initially points to NULL
	int scanline_num = y_min; //first scanline that touches the polygon
	while ((isTC_empty(tab_TC, size_tc)==false) || (*TCA != NULL)) { //stops when TC is empty or TCA is empty
		//Move sides of TC to TCA (remove from TC, add to TCA)
		lc_t* current_linked_list = tab_TC[scanline_num - y_min];
		add_to_TCA(TCA, current_linked_list);
		tab_TC[scanline_num - y_min] = NULL; //pointer to that scanline becomes NULL in TC
		//Remove from TCA the sides for which ymax = y (scanline_num)
		int size_TCA = delete_side_TCA(TCA, scanline_num);
		//Draw the pixels that are inside the polygon for the current scanline
		draw_scanline(TCA, size_TCA, scanline_num, surface, color, clipper);
		scanline_num++; //y++
		update_x_ymin_sides(TCA); //new scanline => new x_ymin, find the new x_ymin in TCA
	}
	free(TCA);
	free(tab_TC);
}

//Concatenate 4 lists, we didn't implement it so that we concatenate twice 2 lists because this function is not meant to be used elsewhere
tab_and_length concatenate_four_point_lists(ei_point_t* list1, ei_point_t* list2, ei_point_t* list3, ei_point_t* list4, int length1, int length2, int length3, int length4) {
	int total_length = length1 + length2 + length3 + length4;
	ei_point_t * list_points = calloc(total_length, sizeof(ei_point_t));
	for(int i = 0; i < length1; i++) {
		list_points[i] = list1[i];
	}
	for(int i = 0; i < length2; i++) {
		list_points[length1 + i] = list2[i];
	}
	int length12 = length1 + length2; //save 1 addition per iteration
	for(int i = 0; i < length3; i++) {
		list_points[length12 + i] = list3[i];
	}
	int length123 = length12 + length3; //save 2 additions per iteration
	for(int i = 0; i < length4; i++) {
		list_points[length123 + i] = list4[i];
	}
	return (tab_and_length) {list_points, total_length};
}

int ei_copy_surface(ei_surface_t destination, const ei_rect_t* dst_rect, ei_surface_t source, const ei_rect_t* src_rect, bool alpha)
{
	int success = 0;
	if (!alpha) {
		hw_surface_lock(destination);
		hw_surface_lock(source);
		if (dst_rect == NULL) { //according to function documentation
			ei_size_t sizedest = hw_surface_get_size(destination);
			uint32_t *addr_dest = (uint32_t *) hw_surface_get_buffer(destination);
			if (src_rect == NULL) { //according to function documentation
				ei_size_t sizesrc = hw_surface_get_size(source);
				uint32_t *addr_src = (uint32_t *) hw_surface_get_buffer(source);
				if((sizedest.width != sizesrc.width) || ( sizedest.height != sizesrc.height)) {
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 1;
				}
				else {
					for (int xsrc = 0, xdest = 0;
					     xsrc <= sizesrc.width && xdest <= sizedest.width; xsrc++, xdest++) {
						for (int ysrc = 0, ydest = 0; ysrc <= sizesrc.height && ydest <=
													sizedest.height; ysrc++, ydest++) {
							uint32_t *current_src = addr_src + sizesrc.width * ysrc + xsrc;
							uint32_t *current_dst =
								addr_dest + sizedest.width * ydest + xdest;
							*current_dst = *current_src;
						}
						hw_surface_unlock(destination);
						hw_surface_unlock(source);
						success = 0;
					}
				}
			}
			else {
				uint32_t *addr_src = (uint32_t *) hw_surface_get_buffer(source);
				ei_size_t sizesrc = hw_surface_get_size(source);
				ei_point_t top_left_rect_src = src_rect->top_left;
				if ((src_rect->size.width != sizedest.width) ||( src_rect->size.height != sizedest.height)) {
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 1;
				}
				else {
					ei_point_t bottom_right_src_rect = {src_rect->top_left.x + src_rect->size.width,
									    src_rect->top_left.y +
									    src_rect->size.height};
					for (int xsrc = top_left_rect_src.x, xdest = 0;
					     xsrc <= bottom_right_src_rect.x && xdest <= sizedest.width; xsrc++, xdest++) {
						for (int ysrc = top_left_rect_src.y, ydest = 0;
						     ysrc <= sizesrc.height && ydest <=
									       bottom_right_src_rect.y; ysrc++, ydest++) {
							uint32_t *current_src = addr_src + sizesrc.width * ysrc + xsrc;
							uint32_t *current_dst =
								addr_dest + sizedest.width * ydest + xdest;
							*current_dst = *current_src;
						}
					}
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 0;
				}
			}
		}
		else {
			uint32_t *addr_dest = (uint32_t *) hw_surface_get_buffer(destination);
			ei_size_t sizedest = hw_surface_get_size(destination);
			ei_point_t top_left_rect_dst = dst_rect->top_left;
			if (src_rect == NULL) { //according to function documentation
				ei_size_t sizesrc = hw_surface_get_size(source);
				uint32_t *addr_src = (uint32_t *) hw_surface_get_buffer(source);
				if ((sizesrc.width != dst_rect->size.width) || ( sizesrc.height != dst_rect->size.height)) {
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 1;
				}
				else {
					ei_point_t bottom_right_rect_dst = {dst_rect->size.width+top_left_rect_dst.x, dst_rect->size.height+top_left_rect_dst.y};

					for (int xsrc = 0, xdest = top_left_rect_dst.x;
					     xsrc <= sizesrc.width && xdest <= bottom_right_rect_dst.x; xsrc++, xdest++) {
						for (int ysrc = 0, ydest = top_left_rect_dst.y; ysrc <= sizesrc.height && ydest <=
													bottom_right_rect_dst.y; ysrc++, ydest++) {
							uint32_t *current_src = addr_src + sizesrc.width * ysrc + xsrc;
							uint32_t *current_dst =
								addr_dest + sizedest.width * ydest + xdest;
							*current_dst = *current_src;
						}

					}
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 0;

				}
			}
			else {
				if ((dst_rect->size.width != src_rect->size.width) ||
					(src_rect->size.height != dst_rect->size.height)) {
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 1;
				}
				else {
					uint32_t *addr_dest = (uint32_t *) hw_surface_get_buffer(destination);
					ei_size_t sizedest = hw_surface_get_size(destination);
					ei_point_t top_left_src_rect = src_rect->top_left;
					uint32_t *addr_src = (uint32_t *) hw_surface_get_buffer(source);
					ei_size_t sizesrc = hw_surface_get_size(source);

					ei_point_t bottom_right_src_rect = {src_rect->top_left.x + src_rect->size.width,
									    src_rect->top_left.y +
									    src_rect->size.height};
					ei_point_t bottom_right_dst_rect = {top_left_rect_dst.x+dst_rect->size.width, top_left_rect_dst.y+dst_rect->size.height};

					for (int xsrc = top_left_src_rect.x, xdest = top_left_rect_dst.x;
					     xsrc <= bottom_right_src_rect.x && xdest <= bottom_right_dst_rect.x; xsrc++, xdest++) {
						for (int ysrc = top_left_src_rect.y, ydest = top_left_rect_dst.y;
						     ysrc <= bottom_right_src_rect.y && ydest <=
											bottom_right_dst_rect.y; ysrc++, ydest++) {
							uint32_t *current_src = addr_src + sizesrc.width * ysrc + xsrc;
							uint32_t *current_dst =
								addr_dest + sizedest.width * ydest + xdest;
							*current_dst = *current_src;
						}
					}
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 0;
				}
			}
		}
	}
	else {
		hw_surface_lock(destination);
		hw_surface_lock(source);
		if (dst_rect == NULL) { //according to function documentation
			ei_size_t sizedest = hw_surface_get_size(destination);
			uint32_t *addr_dest = (uint32_t *) hw_surface_get_buffer(destination);
			if (src_rect == NULL) { //according to function documentation
				ei_size_t sizesrc = hw_surface_get_size(source);
				uint32_t *addr_src = (uint32_t *) hw_surface_get_buffer(source);
				if((sizedest.width != sizesrc.width) || ( sizedest.height != sizesrc.height)) {
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 1;
				} else {
					int ir, ig, ib, ia, ir2, ig2, ib2, ia2;
					hw_surface_get_channel_indices(source, &ir, &ig, &ib, &ia);
					hw_surface_get_channel_indices(destination, &ir2, &ig2, &ib2, &ia2);

					for (int xsrc = 0, xdest = 0;
					     xsrc <= sizesrc.width && xdest <= sizedest.width; xsrc++, xdest++) {
						for (int ysrc = 0, ydest = 0; ysrc <= sizesrc.height && ydest <=
													sizedest.height; ysrc++, ydest++) {
							uint32_t *current_src = addr_src + sizesrc.width * ysrc + xsrc;
							uint32_t *current_dst =
								addr_dest + sizedest.width * ydest + xdest;
							uint8_t *channel_ptr_src = (uint8_t *) current_src;
							uint8_t *channel_ptr_dst = (uint8_t *) current_dst;
							channel_ptr_dst[ir2] = (channel_ptr_src[ia]*channel_ptr_src[ir]+(255-channel_ptr_src[ia])*channel_ptr_dst[ir2])/255;
							channel_ptr_dst[ig2]= (channel_ptr_src[ia]*channel_ptr_src[ig]+(255-channel_ptr_src[ia])*channel_ptr_dst[ig2])/255;
							channel_ptr_dst[ib2] = (channel_ptr_src[ia]*channel_ptr_src[ib]+(255-channel_ptr_src[ia])*channel_ptr_dst[ib2])/255;
						}
						hw_surface_unlock(destination);
						hw_surface_unlock(source);
						success = 0;
					}
				}

			} else {
				uint32_t *addr_src = (uint32_t *) hw_surface_get_buffer(source);
				ei_size_t sizesrc = hw_surface_get_size(source);
				ei_point_t top_left_rect_src = src_rect->top_left;
				if ((src_rect->size.width != sizedest.width) ||( src_rect->size.height != sizedest.height)) {
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 1;
				} else {
					ei_point_t bottom_right_src_rect = {src_rect->top_left.x + src_rect->size.width,
									    src_rect->top_left.y +
									    src_rect->size.height};
					int ir, ig, ib, ia, ir2, ig2, ib2, ia2;
					hw_surface_get_channel_indices(source, &ir, &ig, &ib, &ia);
					hw_surface_get_channel_indices(destination, &ir2, &ig2, &ib2, &ia2);
					for (int xsrc = top_left_rect_src.x, xdest = 0;
					     xsrc <= bottom_right_src_rect.x && xdest <= sizedest.width; xsrc++, xdest++) {
						for (int ysrc = top_left_rect_src.y, ydest = 0;
						     ysrc <= sizesrc.height && ydest <=
									       bottom_right_src_rect.y; ysrc++, ydest++) {
							uint32_t *current_src = addr_src + sizesrc.width * ysrc + xsrc;
							uint32_t *current_dst =
								addr_dest + sizedest.width * ydest + xdest;
							uint8_t *channel_ptr_src = (uint8_t *) current_src;
							uint8_t *channel_ptr_dst = (uint8_t *) current_dst;
							channel_ptr_dst[ir2] = (channel_ptr_src[ia]*channel_ptr_src[ir]+(255-channel_ptr_src[ia])*channel_ptr_dst[ir2])/255;
							channel_ptr_dst[ig2]= (channel_ptr_src[ia]*channel_ptr_src[ig]+(255-channel_ptr_src[ia])*channel_ptr_dst[ig2])/255;
							channel_ptr_dst[ib2] = (channel_ptr_src[ia]*channel_ptr_src[ib]+(255-channel_ptr_src[ia])*channel_ptr_dst[ib2])/255;
						}
					}
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 0;
				}
			}

		} else {
			uint32_t *addr_dest = (uint32_t *) hw_surface_get_buffer(destination);
			ei_size_t sizedest = hw_surface_get_size(destination);
			ei_point_t top_left_rect_dst = dst_rect->top_left;
			if (src_rect == NULL) { //according to function documentation
				ei_size_t sizesrc = hw_surface_get_size(source);
				uint32_t *addr_src = (uint32_t *) hw_surface_get_buffer(source);
				if ((sizesrc.width != dst_rect->size.width) || ( sizesrc.height != dst_rect->size.height)) {
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 1;
				} else {
					ei_point_t bottom_right_rect_dst = {dst_rect->size.width+top_left_rect_dst.x, dst_rect->size.height+top_left_rect_dst.y};
					int ir, ig, ib, ia, ir2, ig2, ib2, ia2;
					hw_surface_get_channel_indices(source, &ir, &ig, &ib, &ia);
					hw_surface_get_channel_indices(destination, &ir2, &ig2, &ib2, &ia2);

					for (int xsrc = 0, xdest = top_left_rect_dst.x;
					     xsrc <= sizesrc.width && xdest <= bottom_right_rect_dst.x; xsrc++, xdest++) {
						for (int ysrc = 0, ydest = top_left_rect_dst.y; ysrc <= sizesrc.height && ydest <=
															  bottom_right_rect_dst.y; ysrc++, ydest++) {
							uint32_t *current_src = addr_src + sizesrc.width * ysrc + xsrc;
							uint32_t *current_dst =
								addr_dest + sizedest.width * ydest + xdest;
							uint8_t *channel_ptr_src = (uint8_t *) current_src;
							uint8_t *channel_ptr_dst = (uint8_t *) current_dst;
							channel_ptr_dst[ir2] = (channel_ptr_src[ia]*channel_ptr_src[ir]+(255-channel_ptr_src[ia])*channel_ptr_dst[ir2])/255;
							channel_ptr_dst[ig2]= (channel_ptr_src[ia]*channel_ptr_src[ig]+(255-channel_ptr_src[ia])*channel_ptr_dst[ig2])/255;
							channel_ptr_dst[ib2] = (channel_ptr_src[ia]*channel_ptr_src[ib]+(255-channel_ptr_src[ia])*channel_ptr_dst[ib2])/255;
						}

					}
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 0;

				}
			} else {
				if ((dst_rect->size.width != src_rect->size.width) ||
				    (src_rect->size.height != dst_rect->size.height)) {
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 1;
				} else {
					uint32_t *addr_dest = (uint32_t *) hw_surface_get_buffer(destination);
					ei_size_t sizedest = hw_surface_get_size(destination);
					ei_point_t top_left_src_rect = src_rect->top_left;
					uint32_t *addr_src = (uint32_t *) hw_surface_get_buffer(source);
					ei_size_t sizesrc = hw_surface_get_size(source);

					ei_point_t bottom_right_src_rect = {src_rect->top_left.x + src_rect->size.width,
									    src_rect->top_left.y +
									    src_rect->size.height};
					ei_point_t bottom_right_dst_rect = {top_left_rect_dst.x + dst_rect->size.width,
									    top_left_rect_dst.y +
									    dst_rect->size.height};
					int ir, ig, ib, ia, ir2, ig2, ib2, ia2;
					hw_surface_get_channel_indices(source, &ir, &ig, &ib, &ia);
					hw_surface_get_channel_indices(destination, &ir2, &ig2, &ib2, &ia2);

					for (int xsrc = top_left_src_rect.x, xdest = top_left_rect_dst.x;
					     xsrc <= bottom_right_src_rect.x &&
					     xdest <= bottom_right_dst_rect.x; xsrc++, xdest++) {
						for (int ysrc = top_left_src_rect.y, ydest = top_left_rect_dst.y;
						     ysrc <= bottom_right_src_rect.y && ydest <=
											bottom_right_dst_rect.y; ysrc++, ydest++) {
							uint32_t *current_src = addr_src + sizesrc.width * ysrc + xsrc;
							uint32_t *current_dst =
								addr_dest + sizedest.width * ydest + xdest;
							uint8_t *channel_ptr_src = (uint8_t *) current_src;
							uint8_t *channel_ptr_dst = (uint8_t *) current_dst;
							channel_ptr_dst[ir2] =
								(channel_ptr_src[ia] * channel_ptr_src[ir] +
								 (255 - channel_ptr_src[ia]) * channel_ptr_dst[ir2]) /
								255;
							channel_ptr_dst[ig2] =
								(channel_ptr_src[ia] * channel_ptr_src[ig] +
								 (255 - channel_ptr_src[ia]) * channel_ptr_dst[ig2]) /
								255;
							channel_ptr_dst[ib2] =
								(channel_ptr_src[ia] * channel_ptr_src[ib] +
								 (255 - channel_ptr_src[ia]) * channel_ptr_dst[ib2]) /
								255;
						}
					}
					hw_surface_unlock(destination);
					hw_surface_unlock(source);
					success = 0;
				}
			}
		}
	}
	return success;
}

void ei_draw_text(ei_surface_t	surface, const ei_point_t* where, ei_const_string_t text, ei_font_t font, ei_color_t color, const ei_rect_t* clipper)
{
	/*
	 * Theory: create surface of text, take its associated rectangle, take the rectangle associated
	 * with the original surface starting at the where point, paste the text rectangle to that rectangle.
	 */
	if (text == NULL) { //according to function documentation
		printf("Text is NULL.\n");
	}
	ei_surface_t surface_of_text = hw_text_create_surface(text, font, color);

	//Check if clipping is possible
	ei_size_t surface_size = hw_surface_get_size(surface);
	ei_size_t surface_of_text_size = hw_surface_get_size(surface_of_text);
	if ((clipper!=NULL) && (surface_size.width!=surface_of_text_size.width) && (surface_size.height!=surface_of_text_size.height)) {
		printf("Clipping not possible because surface sizes are different.\n");
	}

	ei_rect_t src_rec = hw_surface_get_rect(surface_of_text);
	ei_size_t size_rect = {src_rec.size.width, src_rec.size.height};
	ei_rect_t dst_rec = {*where, size_rect};
	int copy_done = ei_copy_surface(surface, &dst_rec, surface_of_text, NULL, true);
	if (copy_done==1) { //copy_done==0 => success, copy_done==1 => fail
		printf("Copy has failed in ei_draw_text.\n");
	}
}

/*Returns array of points forming an arc*/
tab_and_length arc(ei_point_t center, int radius, int angle_start, int angle_end)
{
	int d_theta = radius;
	double radian_step = (d_theta * PI) / 180;
	double radian_start_angle = (angle_start * PI) / 180;  //precondition: angle_start <= angle_end
	double radian_end_angle = (angle_end * PI) / 180;
	int nb_of_points = abs(angle_end - angle_start) / d_theta + 1;
	ei_point_t* array = calloc((nb_of_points), sizeof(ei_point_t));
	double current_theta = radian_start_angle;
	int num_point_in_list = 0;
	while (current_theta <= radian_end_angle) {
		ei_point_t p = {center.x + radius * cos(current_theta), center.y + radius * sin(current_theta)};
		array[num_point_in_list] = p;
		current_theta += radian_step;
		num_point_in_list++;
	}
	return (tab_and_length) {array, num_point_in_list};
}

tab_and_length rounded_frame(ei_rect_t rectangle, int radius, ei_relief_t relief)
{
	tab_and_length conc;
	ei_point_t top_left_point = rectangle.top_left;
	int height = rectangle.size.height;
	int width = rectangle.size.width;

	ei_point_t center_top_left = {top_left_point.x + radius, top_left_point.y + radius};
	tab_and_length t1 = arc(center_top_left, radius, 180, 270);

	ei_point_t center_top_right;

	ei_point_t center_bottom_right = {top_left_point.x + (width - radius), top_left_point.y + (height - radius)};
	tab_and_length t3 = arc(center_bottom_right, radius, 0, 90);

	ei_point_t center_bottom_left;

	if (relief == ei_relief_none) {
		center_top_right = (ei_point_t) {top_left_point.x + (width - radius) + 1, top_left_point.y + radius};
		tab_and_length t2 = arc(center_top_right, radius, 270, 360);
		center_bottom_left = (ei_point_t) {top_left_point.x + radius, top_left_point.y + (height - radius)};
		tab_and_length t4 = arc(center_bottom_left, radius, 90, 180);
		conc = concatenate_four_point_lists(t1.tab, t2.tab, t3.tab, t4.tab, t1.length, t2.length, t3.length, t4.length);
	}
	else if (relief == ei_relief_raised) {
		center_top_right = (ei_point_t) {top_left_point.x + (width - radius) + 1, top_left_point.y + radius};
		tab_and_length t2 = arc(center_top_right, radius, 270, 325);
		center_bottom_left = (ei_point_t) {top_left_point.x + radius, top_left_point.y + (height - radius)};
		tab_and_length t4 = arc(center_bottom_left, radius, 135, 180);
		//+2 interior points
		ei_point_t * list_2points = calloc(2, sizeof(ei_point_t));
		int h = (width < height) ? width/2 : height/2;
		ei_point_t p1 = {top_left_point.x + (width - h), top_left_point.y + h};
		list_2points[0] = p1;
		ei_point_t p2 = {top_left_point.x + h, top_left_point.y + h};
		list_2points[1] = p2;
		conc = concatenate_four_point_lists(t1.tab, t2.tab, list_2points, t4.tab, t1.length, t2.length, 2, t4.length);
	}
	else { //ei_relief_sunken
		center_top_right = (ei_point_t) {top_left_point.x + (width - radius) + 1, top_left_point.y + radius};
		tab_and_length t2 = arc(center_top_right, radius, 315, 360);
		center_bottom_left = (ei_point_t) {top_left_point.x + radius, top_left_point.y + (height - radius)};
		tab_and_length t4 = arc(center_bottom_left, radius, 90, 145);
		//+2 interior points
		ei_point_t * list_2points = calloc(2, sizeof(ei_point_t));
		int h = (width < height) ? width/2 : height/2;
		ei_point_t p1 = {top_left_point.x + (width - h), top_left_point.y + h};
		list_2points[1] = p1;
		ei_point_t p2 = {top_left_point.x + h, top_left_point.y + h};
		list_2points[0] = p2;
		conc = concatenate_four_point_lists(t4.tab, list_2points, t2.tab, t3.tab, t4.length, 2, t2.length, t3.length);
	}
	return conc;
}

void draw_button(ei_surface_t surface, ei_rect_t rectangle, int rayon, ei_relief_t relief)
{
	//Create colors
	ei_color_t color_outside_dark = { 108, 109, 112, 0xff};
	ei_color_t color_outside_bright = { 188, 189, 192, 0xff};
	ei_color_t color_inside = { 147, 149, 152, 0xff};
	ei_color_t default_color_text = { 255, 255, 255, 0xff};
	//Create edges
	tab_and_length arr_upper = rounded_frame(rectangle, rayon, ei_relief_raised);
	tab_and_length arr_lower = rounded_frame(rectangle, rayon, ei_relief_sunken);
	int width = rectangle.size.width;
	int height = rectangle.size.height;
	int min_size = (width < height) ? width : height;
	int size_text = min_size / 4;
	ei_point_t where; //arbitrary values
	if (relief == ei_relief_none) {
		where = (ei_point_t) {rectangle.top_left.x + width / 3 - size_text / 2, rectangle.top_left.y + height / 2 - 3 * size_text / 4};
		ei_draw_polygon(surface, arr_upper.tab, arr_upper.length, color_inside, NULL);
		ei_draw_polygon(surface, arr_lower.tab, arr_lower.length, color_inside, NULL);
	}
	else if (relief == ei_relief_raised) {
		where = (ei_point_t) {rectangle.top_left.x + width / 3 - 3 * size_text / 4, rectangle.top_left.y + height / 2 - 3 * size_text / 4};
		ei_draw_polygon(surface, arr_upper.tab, arr_upper.length, color_outside_bright, NULL);
		ei_draw_polygon(surface, arr_lower.tab, arr_lower.length, color_outside_dark, NULL);
	}
	else { //ei_relief_sunken
		where = (ei_point_t) {rectangle.top_left.x + width / 3 - size_text / 2, rectangle.top_left.y + height / 2 - size_text / 2};
		ei_draw_polygon(surface, arr_upper.tab, arr_upper.length, color_outside_dark, NULL);
		ei_draw_polygon(surface, arr_lower.tab, arr_lower.length, color_outside_bright, NULL);
	}
	//Create centered rounded frame
	int dist = 0.020 * width;
	ei_point_t p_inside = {rectangle.top_left.x + dist, rectangle.top_left.y + dist};
	ei_size_t size_inside = {width - 2 * dist, height - 2 * dist};
	ei_rect_t inside_rec = {p_inside, size_inside};
	tab_and_length arr_inside_rect = rounded_frame(inside_rec, rayon, ei_relief_none);
	ei_draw_polygon(surface, arr_inside_rect.tab, arr_inside_rect.length, color_inside, NULL);
	//Add the text
	ei_const_string_t default_text = "Bouton";
	ei_font_t default_font = hw_text_font_create(ei_default_font_filename, ei_style_bold, size_text);
	ei_draw_text(surface, &where, default_text, default_font, default_color_text, NULL);
}