#include "ei_draw.h"
#include "hw_interface.h"

void ei_fill(ei_surface_t surface, const ei_color_t* color, const ei_rect_t* clipper) {

    //lock the surface.
    hw_surface_lock(surface); 

    //Returns a pointer to the address of the pixel at coordinated (0, 0) of the surface.
    uint32_t* surface_buffer = hw_surface_get_buffer(surface); 

    //test if color is NULL
    if (color == NULL){
        //painted black (opaque).

    } else {
        //paint of the surface with color (don't take clipper into account for now)



    }

    //unlock the surface
    hw_surface_unlock(surface);

    //Requests that a list of rectangular regions of the root surface be updated on screen. (NULL -> update all the screen)
    hw_surface_update_rects(surface, NULL);
}





