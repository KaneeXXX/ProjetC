/**
 *  @file	ei_draw.c
 *  @brief	Graphical primitives to draw lines, polygons, text, and operation of drawing
 *		surfaces.
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

void draw_line(ei_surface_t surface, ei_point_t point_un, ei_point_t point_deux, ei_color_t color){

	uint32_t* surface_buffer = (uint32_t*) hw_surface_get_buffer(surface);
	ei_size_t size = hw_surface_get_size(surface);
	int width = size.width;
	int delta_x = point_deux.x - point_un.x;
	int delta_y = point_deux.y - point_un.y;
        int x = point_un.x;
        int y = point_un.y;
        int E = 2*delta_y - delta_x;

	//if only on point in the array
        if((point_un.x == point_deux.x) && (point_un.y == point_deux.y)) {
        	u_int32_t* pixel = surface_buffer + width*y + x;
		draw_pixel(pixel, surface, color);
		return;
        }

        while(x < point_deux.x){
		u_int32_t* pixel = surface_buffer + width*y + x;
        	if (E > 0)
        	{
        		draw_pixel(pixel, surface, color);
        		y++;
        		E = E + 2*delta_y - 2*delta_x;
        	}
        	else
        	{
        		draw_pixel(pixel, surface, color);
        		E = E + 2*delta_y;
        	}
        	x++;
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







