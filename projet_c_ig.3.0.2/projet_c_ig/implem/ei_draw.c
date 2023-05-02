#include "ei_draw.h"
#include "hw_interface.h"

void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_rect_t* clipper) {

    //lock the surface.
    hw_surface_lock(surface); 

    //Returns a pointer to the address of the pixel at coordinated (0, 0) of the surface.
    uint8_t* surface_buffer = hw_surface_get_buffer(surface); 

    //test if color is NULL
    if (color == NULL){
        //painted black (opaque).

    } else {
        //paint with color and the drawing is restricted within the rectangle (clipper)
        

    }

    //unlock the surface
    hw_surface_unlock(surface);
}





