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

void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_rect_t* clipper) {

    //lock the surface.
    hw_surface_lock(surface); 

    //Returns a pointer to the address of the pixel at coordinated (0, 0) of the surface.
    uint8_t* surface_buffer = hw_surface_get_buffer(surface);   //*surface_buffer = adresse pixel coordinate (0,0)

    //get size if the surface
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

    //unlock the surface
    hw_surface_unlock(surface);

    //Requests that a list of rectangular regions of the root surface be updated on screen. (NULL -> update all the screen)
    hw_surface_update_rects(surface, NULL);
}







