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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.141592654

bool is_pixel_drawable(uint32_t * addr, ei_surface_t surface, const ei_rect_t* clipper){



	// On récupère les informations de la surface
	ei_size_t size = hw_surface_get_size(surface);
	uint32_t* surface_buffer = (uint32_t*) hw_surface_get_buffer(surface);

	// On récupère les informations du clipper
	int largeur = clipper->size.width;
	int hauteur = clipper->size.height;
	int origine_x0 = clipper->top_left.x;
	int origine_y0 = clipper->top_left.y;

	//On récupère les informations du point
	int point_y = (addr - surface_buffer)/size.width;
	int point_x = (addr - surface_buffer)%size.width;

	// Vérifications que le pixel est bien dans le rectangle

	bool verif_abs = (point_x >= origine_x0) && (point_x <= largeur);
	bool verif_ord = (point_y >= origine_y0) && (point_y <= hauteur);
	return verif_abs && verif_ord;
}

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

void draw_pixel(u_int32_t* addr, ei_surface_t surface, ei_color_t color, const ei_rect_t* clipper)
{
	//Get order of colors in pixel because it's not always the same
	int ir, ig, ib, ia;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

       if ((clipper == NULL)||(is_pixel_drawable(addr, surface, clipper)))
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

void swap(int *a, int *b)
{
	int temp = *a;
	*a=*b;
	*b=temp;
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
		return;
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

minmax_t min_max_sur_y(ei_point_t* point_array, size_t point_array_size){
	// Récupère les ordonnées minimale et maximale des points du tableau
	// en entrée ainsi que les points ayant ces ordonnées extrêmes
        // On retourne, par ailleurs, les indices dans le tableau de ces
        // points...
	int max = point_array[0].x;
	//trouver une solution pour mettre genre min = plus infini
	int min = point_array[0].y;

	for (size_t i = 1; i < point_array_size -1; i++){
		if (point_array[i].y > max){
			max = point_array[i].y;
		}
		if (point_array[i].y <= min){
			min = point_array[i].y;
		}
	}
	minmax_t res = {min, max};
	return res;
}

//petit function pour print_TC
void print_chain(int indice_in_TC, lc_t** tab_TC) {
	//tab_TC est un tableau de pointeur vers des struct lc_t
	if(tab_TC[indice_in_TC] == NULL) { //Cas pour F et D par exemple, ils n'ont pas de voisin "sous eux".
		printf("indice_TC= %i | NULL\n", indice_in_TC);
		return;
	}
	lc_t cell = *(tab_TC[indice_in_TC]);
	printf("indice_TC = %i | ymax=%i | x_ymin=%i | abs_dx=%i | abs_dy=%i | E=%i ", indice_in_TC, cell.y_max, cell.x_ymin, cell.abs_dx, cell.abs_dy, cell.E);
	while (cell.next != NULL) {
		printf("- > ");
		cell = *(cell.next);
		printf("indice_TC = %i | ymax=%i | x_ymin=%i | abs_dx=%i | abs_dy=%i | E=%i\n", indice_in_TC, cell.y_max, cell.x_ymin, cell.abs_dx, cell.abs_dy, cell.E);
	}
	printf("\n");
}

//return True is TC empty
bool isTC_empty(lc_t** tab_TC, int size_tc){
	for(int i = 0; i < size_tc; i++) {
		if(tab_TC[i] != NULL) {
			return false;
		}
	}
	return true;
}

//ajouter à TCA des cotés à la suite du chainage
void add_to_TCA(lc_t** TCA, lc_t* chaine) {
	if(*TCA == NULL){ //On ajoute la ou les deux cellules de chaine de facon ordonnée (croissance selon x_ymin)
		lc_t* ptrfirst_cell_in_chain = chaine;
		if (ptrfirst_cell_in_chain -> next != NULL) { //s'il existe une deuxième cellule au chainage "chaine"
			lc_t* ptrsecond_cell_in_chain = ptrfirst_cell_in_chain -> next;
			if(ptrfirst_cell_in_chain -> x_ymin <= ptrsecond_cell_in_chain -> x_ymin)  { //si dans dbon ordre
				*TCA = chaine; //rien a faire
			} else { // inverser les deux cellules
				ptrsecond_cell_in_chain -> next = ptrfirst_cell_in_chain;
				lc_t* tmp = ptrsecond_cell_in_chain; //tmp
				ptrfirst_cell_in_chain ->next = NULL;
				*TCA = tmp;
			}

		} else { // s'il n'existe pas de deuxième cellule au chainage "chaine"
			*TCA = chaine;

		}
		return;
	}
	if(chaine == NULL){
		return;
	}

	//Cas si TCA contient dejà des cellules, on doit ajouter les cellules de chainées pour garder ordrer trié selon x_ymin
	//pour chaque élement (2 au plus) de "chaine" on le place au bon endroit dans TCA (déjà trié).
	lc_t* ptrfirst_cell_in_chain = chaine;
	lc_t* ptrseconde_cell_in_chain = chaine ->next; //POssiblement NULL

	for(int i = 0; i < 2; i++) { //faire 2 fois car deux cellules, au plus, in "chaine"
		lc_t *ptr_previous = *TCA;
		lc_t *ptr_current_cell_TCA = *TCA; //init à première cellule
		bool entete = true;
		bool placed=false;
		while (ptr_current_cell_TCA != NULL && placed==false) {

			if (ptr_current_cell_TCA->x_ymin >= ptrfirst_cell_in_chain->x_ymin) {
				if(entete) {
					*TCA = ptrfirst_cell_in_chain;
					ptrfirst_cell_in_chain -> next = ptr_current_cell_TCA;

				} else {
					ptr_previous -> next = ptrfirst_cell_in_chain;
					ptrfirst_cell_in_chain->next = ptr_current_cell_TCA;
					placed=true;
				}
			}
			ptr_previous = ptr_current_cell_TCA;
			ptr_current_cell_TCA = ptr_current_cell_TCA->next; //On avance dans chain
			entete = false;
		}
		if(ptrseconde_cell_in_chain == NULL) { //s'il n'y a PAS de deuxième cellule
			return;
		} //sinon
		ptrfirst_cell_in_chain = ptrseconde_cell_in_chain; //On passe à la 2e cell de "chaine"
	}

}

//supprimer de TCA les cotés tel que ymax (contenu dans les cellules de TCA) = scanline_num
int delete_side_TCA(lc_t** TCA, int scanline_num) {
	if (*TCA == NULL) {
		return 0;
	}
	int size_TCA = 0; //Going to be increased while going through the loop.
	lc_t* ptr_previous = *TCA;
	lc_t* ptr_current_side = *TCA; //init à première cellule
	bool entete = true;
	while (ptr_current_side != NULL) {
		if(ptr_current_side -> y_max == scanline_num){
			if(entete){
				*TCA = ptr_current_side ->  next;
				lc_t* to_free = ptr_current_side;
				ptr_current_side = ptr_current_side -> next;
				free(to_free);

				continue;
			} else {
				//ptr_previous = ptr_current_side -> next;
				//free(ptr_current_side); //On supprime ici une cellule type lc_t
				//ptr_current_side = ptr_previous; //On raccroche
				ptr_previous->next = ptr_current_side->next;
				free(ptr_current_side);
				size_TCA--;
				continue;
			}
		}
		ptr_previous = ptr_current_side;
		ptr_current_side = ptr_current_side -> next; //On avance dans chain

		size_TCA++;
		entete = false;
	}
	return size_TCA;
}

enum draw_state {IN, OUT};

//Colorier un scanline du polygone
void draw_scanline(lc_t** TCA, int size_TCA, int y,ei_surface_t surface, ei_color_t color, const ei_rect_t *clipper) {
	lc_t* ptr_current_cell = *TCA;
	enum draw_state state = IN; //Entrée d'intervalle

	double x_to_color1 = 0.0; //On init deux abscisses qui seront changé par la suite, ce sont le début et la fin d'un segment à colorier.
	double x_to_color2 = 0.0;

	//Parcours de TCA
	for(int i = 0; i < size_TCA; i++) {
		//Les x_ymin de chaque cellule de TCA represente les intersections avec la scanline, pas forcement entiers
		double x_ymin = ptr_current_cell -> x_ymin;
		if(state == IN){
			//On arrondi x_ymin à l'entier supérieur
			x_to_color1 = ceil(x_ymin);
			state = OUT;
		} else { //State = OUT, on est en sortie d'intervalle
			//On arrondi x_ymin à l'entier inférieur
			x_to_color2 = floor(x_ymin);
			ei_point_t p1 = {x_to_color1, y};
			ei_point_t p2 = {x_to_color2, y};
			draw_line(surface, p1, p2, color, clipper);
			state = IN;
		}
		ptr_current_cell = ptr_current_cell -> next; //On avance dans TCA
	}
}

void update_x_ymin_sides(lc_t** TCA) {
	lc_t* current_cell = *TCA;
	while (current_cell != NULL) {
		//update x_ymin
		enum direction dir = current_cell->dir;
		int abs_dx = current_cell->abs_dx;
		int abs_dy = current_cell->abs_dy;

		if (abs_dx == 0) {
			current_cell = current_cell->next;
			continue;
		}

		if(abs_dy == 0){
			// ?
			continue;
		}

		if (dir == RIGHT) {
			current_cell->E += abs_dx;
			while (2 * (current_cell->E) > abs_dy) {
				(current_cell->x_ymin) += 1;
				current_cell->E -= abs_dy;
			}
		} else {
			current_cell->E += abs_dx;
			while (2 * (current_cell->E) > abs_dy) {
				(current_cell->x_ymin) -= 1;
				current_cell->E -= abs_dy;
			}
		}
		current_cell = current_cell->next;
	}
}

void add_to_chain(lc_t* prem_cell, lc_t* cell_to_add){

	lc_t* current = prem_cell;
	while(current -> next != NULL){
		current = current -> next;
	}
	current -> next = cell_to_add;
}

//Je réutilise getVoisins et min_max simplifiée
void ei_draw_polygon (ei_surface_t surface, ei_point_t*  point_array, size_t point_array_size, ei_color_t color, const ei_rect_t* clipper)
{
	/*//Remplissage d'une copie étant une liste(tableau) telle que copy_point_array[i]=[{i, point_array[i]}
	//"L'ordre" des points reste ici unchanged.
	//I) Creation pointeur vers cette liste.
	pt_and_index * copy_point_array = calloc(point_array_size, sizeof(pt_and_index));
	//II) Fill the list
	for (size_t i = 0; i < point_array_size; i++) {
		pt_and_index temp;
		temp.index= i;
		temp.pt=point_array[i];
		copy_point_array[i]=temp;
	}
	//III) sort the list par y des points croissants
	qsort(copy_point_array, point_array_size, sizeof(pt_and_index), compareFunction);

	//IV) Création de TC et init des valeurs clé (ymin, ...) that we need.
	minmax_t critical_pts = min_max_sur_y(point_array, point_array_size);
	int y_min = critical_pts.y_min;
	//y_max pas besoin ici
	// tableau de pointeurs de type struct lc * initialises à NULL de taille ymax -ymin +1
	int taille_tc = (critical_pts.y_max - critical_pts.y_min + 1);
	lc_t** tab_TC = calloc(taille_tc, sizeof(lc_t*));

	int previous_scanline = 0;
	//V) On itére sur les structures pt_and_index (rangé par y croissant)
	for (size_t i = 0; i < point_array_size; i++) {
		//get the current pt_and_index structure
		pt_and_index current_pt_and_indexe_structure = copy_point_array[i];
		//get the point
		ei_point_t current_point = current_pt_and_indexe_structure.pt;
		//get the indexe in point_array
		int index_in_point_array = current_pt_and_indexe_structure.index;

		//nous allons maintenant générer la liste chainée associée à current_point

		//1) On récupère ces voisins (au nombre de 2)
		ei_point_t* current_voisins = get_voisins(point_array, index_in_point_array, point_array_size);
		ei_point_t voisin_gauche = current_voisins[0];
		ei_point_t voisin_droite = current_voisins[1];

		bool is_same_scanline_than_previous = false;
		if(current_point.y == previous_scanline){ //Point sur même scanline qui point traité precedement
			is_same_scanline_than_previous = true;
		}

		bool has_voisin_gauche = false;
		if (voisin_gauche.y >= current_point.y) {
			//create cell for this border of the polygone and complete
			lc_t* current_v_g = calloc(1, sizeof(lc_t));
			current_v_g->y_max = voisin_gauche.y;
			current_v_g->x_ymin = current_point.x;
			current_v_g->abs_dx = abs(voisin_gauche.x-current_point.x);
			current_v_g->abs_dy = abs(voisin_gauche.y-current_point.y);
			current_v_g->E = 0;
			current_v_g->dir = (voisin_gauche.x > current_point.x) ? RIGHT : LEFT;
			current_v_g->next = NULL;
			if(is_same_scanline_than_previous == false) {
				tab_TC[current_point.y - y_min] = current_v_g;
			} else {
				add_to_chain(tab_TC[previous_scanline - y_min], current_v_g);
			}
			has_voisin_gauche = true;

		}
		if (voisin_droite.y >= current_point.y) {
			lc_t* current_v_d = calloc(1, sizeof(lc_t));
			current_v_d->y_max = voisin_droite.y;
			current_v_d->x_ymin = current_point.x;
			current_v_d->abs_dx = abs(voisin_droite.x-current_point.x);
			current_v_d->abs_dy = abs(voisin_droite.y-current_point.y);
			current_v_d->E = 0;
			current_v_d->dir = (voisin_droite.x > current_point.x) ? RIGHT : LEFT;
			current_v_d->next = NULL;

			if(is_same_scanline_than_previous == false) {
				//complete the chains if 2 sides to consider
				if (has_voisin_gauche == true) {
					tab_TC[current_point.y - y_min]->next = current_v_d;
				} else {
					tab_TC[current_point.y - y_min] = current_v_d;
				}
			} else {
				add_to_chain(tab_TC[previous_scanline - y_min], current_v_d);
			}
		}
		if(is_same_scanline_than_previous == false) {
			print_chain(current_point.y - y_min, tab_TC);
		} else {
			print_chain(previous_scanline - y_min, tab_TC);
		}
		//Attention: Le cas ou deux points voisins on le même y n'est pas traité (d'après le sujet pas besoin)

		previous_scanline = current_point.y;
	}

	//On libère la mémoire associé à cette liste intermédiaire.
	free(copy_point_array);
	//End of building of TC.*/

	minmax_t critical_pts = min_max_sur_y(point_array, point_array_size);
	int y_min = critical_pts.y_min;
	int size_tc = (critical_pts.y_max - critical_pts.y_min + 1);
	lc_t** tab_TC = calloc(size_tc, sizeof(lc_t*));
	ei_point_t p1;
	ei_point_t p2;

	for(size_t i = 0; i < point_array_size; i++) {
		if(i == point_array_size - 1) { //Dernier point
			 p1 = point_array[i];
			 p2 = point_array[0];
		} else {
			//Récupère deux point du segment
			p1 = point_array[i];
			p2 = point_array[i + 1];
		}
		if(p1.y == p2.y){
			//On fait rien
		} else {
			int ymax, x_ymin, x_up, y_up, x_down;

			if(p1.y > p2.y) {
				x_up = p2.x;
				y_up = p2.y;
				x_down = p1.x;

				ymax = p1.y;
				x_ymin = p2.x;

			} else { //p1.y < p2.y
				x_up = p1.x;
				y_up = p1.y;
				x_down = p2.x;

				ymax = p2.y;
				x_ymin = p1.x;
			}

			lc_t* side = calloc(1, sizeof(lc_t));

			side -> y_max = ymax;
			side -> x_ymin = x_ymin;
			side -> abs_dx = abs(p1.x - p2.x);
			side -> abs_dy = abs(p1.y - p2.y);
			side -> E = 0;
			side->dir = (x_up > x_down) ? LEFT : RIGHT;
			side -> next = NULL;

			int indice_in_TC = y_up - y_min;

			if(tab_TC[indice_in_TC] == NULL){
				tab_TC[indice_in_TC] = side;
			} else {
				add_to_chain(tab_TC[indice_in_TC], side);
			}
		}
	}
	for(int i = 0; i< size_tc; i++){
		print_chain(i, tab_TC);
	}

	printf("fin TC\n");

	//déclarer TCA pointeur
	lc_t** TCA = malloc(sizeof(lc_t));
	*TCA = NULL; //TCA pointe vers NULL au début
	//Init le numero de scan line à la premiere scanline qui intersecte le polygone
	int scanline_num = y_min;

	//Tant TC et TCA non vide, c'est à dire tant que l'un des deux n'est pas vide
	while((isTC_empty(tab_TC, size_tc)==false) || (*TCA != NULL)){
		//jusque la tout marche

		//deplacer les coté de TC(scanline_num) dans TCA -> "les delete de TC"
		//On les rajouter dans TCA
		lc_t* current_list_chaine = tab_TC[scanline_num - y_min];
		add_to_TCA(TCA, current_list_chaine);
		//On remplace le pointeur par NULL dans TC à la scanline "scanline_num"
		tab_TC[scanline_num - y_min] = NULL;

		//supprimer de TCA les cotés tel que ymax (contenu dans les cellules de TCA) = y (scanline_num)
		int size_TCA = delete_side_TCA(TCA, scanline_num); //On a besoin taille pour qsort

		//trier TCA par abscisse croissant des intersection de côté avec la scanline (trier par x_ymin croissant)
		//Ne pas utiliser qsort -> qsort marche sur les tableaux pas sur les listes chainées
		//pas de trie car on fait rentrer les cell dans TCA dans le bon ordre.

		//Modifier les pixels de l’image sur la scanline, dans les intervalles intérieurs au polygone
		draw_scanline(TCA, size_TCA, scanline_num, surface, color, clipper);

		//incrémenter y.
		scanline_num++;

		//Mettre à jour les abscisses d’intersections des côtés de TCA avec la nouvelle scanline (les x_ymin)
		//On calcul les nouveaux x_ymin dans TCA
		update_x_ymin_sides(TCA);
	}
	free(TCA);
	free(tab_TC);
	//zaeaz
}

typedef struct {
    ei_point_t* 				tab; //index of the point in the *original* array
    int 					length;
} tab_and_length;

/*Returns array of points forming an arc*/
tab_and_length arc(ei_point_t center, int radius, float starting_angle, float ending_angle)
{
	int nb_of_points=ending_angle-starting_angle;
	ei_point_t* arr=calloc(nb_of_points+1, sizeof(ei_point_t));

	//Add the other points to the array
	float current_angle=starting_angle;
	for (int i=0; i<nb_of_points; i++) {
		ei_point_t new_point = {center.x + (int)(radius*cos(current_angle*PI/180)), center.y + (int)(radius*sin(current_angle*PI/180))};
		arr[i]=new_point;
		current_angle++;
	}

	tab_and_length arr_and_length = {arr, nb_of_points};
	return arr_and_length;
}

void print_l_p(ei_point_t* points_list, int length)
{
	//REMOVE AT THE END
	for (int i=0; i<length; i++) {
		printf("(x=%i, y=%i) | ", points_list[i].x, points_list[i].y);
	}
}

/*Returns array of points forming a rounded frame*/
ei_point_t* rounded_frame(ei_surface_t surface, ei_rect_t rectangle, int radius, ei_relief_t partie)
{
	int button_width = rectangle.size.width;
	int button_height = rectangle.size.height;
	int offset_width = rectangle.top_left.x;
	int offset_height = rectangle.top_left.y;
	float angle_origin=0.; //<=>0 of the trigonometric circle (at the extreme right of the circle)

	//Get the 4 centers of the 4 round edges
	ei_point_t center_top_right={offset_width+(int)(button_width-radius), offset_height+(int)(radius)};
	ei_point_t center_bottom_right={offset_width+(int)(button_width-radius), offset_height+(int)(button_height-radius)};
	ei_point_t center_bottom_left={offset_width+(int)(radius), offset_height+(int)(button_height-radius)};
	ei_point_t center_top_left={offset_width+(int)(radius), offset_height+(int)(radius)};

	//Build the 4 arcs of the rectangle
	tab_and_length arc1=arc(center_top_right, radius, angle_origin+270., angle_origin+360.);
	tab_and_length arc2=arc(center_bottom_right, radius, angle_origin, angle_origin+90.);
	tab_and_length arc3=arc(center_bottom_left, radius, angle_origin+90., angle_origin+180.);
	tab_and_length arc4=arc(center_top_left, radius, angle_origin+180., angle_origin+270.);

	ei_color_t color_arbitraire = { 0, 255, 0, 0 };
	//Principe: on construit 4 arcs (qui sont des tableaux), puis on les concatène
	float angle_arbitraire=0.;
	int lol=50;
	ei_point_t centre={(int)(rectangle.size.width+100), (int)(rectangle.size.height+100)};
	tab_and_length arc11=arc(centre, lol, angle_origin+270., angle_origin+360.);
	tab_and_length arc22=arc(centre, lol, angle_origin, angle_origin+90.);
	tab_and_length arc33=arc(centre, lol, angle_origin+90., angle_origin+180.);
	tab_and_length arc44=arc(centre, lol, angle_origin+180., angle_origin+270.);

	//DEBUG: TRACE UN CERCLE
	ei_draw_polyline(surface, arc11.tab, arc11.length, color_arbitraire, NULL);
	ei_draw_polyline(surface, arc22.tab, arc22.length, color_arbitraire, NULL);
	ei_draw_polyline(surface, arc33.tab, arc33.length, color_arbitraire, NULL);
	ei_draw_polyline(surface, arc44.tab, arc44.length, color_arbitraire, NULL);


	//Return an array of the 4 arcs
	int length_arc=arc1.length; //supposing the lengths of all arcs are equal
	int length_arr=4*length_arc;
	ei_point_t* arr=calloc(length_arr, sizeof(ei_point_t));
	for (int i=0; i<length_arc; i++) { //add arc1 to tab
		arr[i]=arc11.tab[i];
	}

	int two_times_length_arc=2*length_arc;
	for (int i=length_arc; i<two_times_length_arc; i++) { //add arc2 to tab
		arr[i]=arc22.tab[i-length_arc];
	}

	int three_times_length_arc=3*length_arc;
	for (int i=two_times_length_arc; i<three_times_length_arc; i++) { //add arc3 to tab
		arr[i]=arc33.tab[i-two_times_length_arc];
	}

	int four_times_length_arc=4*length_arc;
	for (int i=three_times_length_arc; i<four_times_length_arc; i++) { //add arc4 to tab
		arr[i]=arc44.tab[i-three_times_length_arc];
	}
	ei_color_t grey = { 128, 128, 128, 255 };
	ei_draw_polygon(surface, arr, (size_t)length_arr, grey, NULL);
	ei_color_t purple = { 0, 0, 0, 255 };
	ei_draw_polyline(surface, arc1.tab, arc1.length, purple, NULL);
	ei_draw_polyline(surface, arc2.tab, arc2.length, purple, NULL);
	ei_draw_polyline(surface, arc3.tab, arc3.length, purple, NULL);
	ei_draw_polyline(surface, arc4.tab, arc4.length, purple, NULL);
	print_l_p(arc1.tab, length_arc);
	printf("\n");
	print_l_p(arc2.tab, length_arc);
	printf("\n");
	print_l_p(arc3.tab, length_arc);
	printf("\n");
	print_l_p(arc4.tab, length_arc);
	printf("\n");
	print_l_p(arr, length_arr);
	return arr;
}


int  ei_copy_surface(ei_surface_t destination, const ei_rect_t* dst_rect, ei_surface_t source, const ei_rect_t* src_rect, bool alpha){


	if (dst_rect==NULL) { //according to function documentation
		ei_size_t sizedest = hw_surface_get_size(destination);
		uint32_t* addr_dest = hw_surface_get_buffer(destination);
		if (src_rect==NULL) { //according to function documentation
			ei_size_t sizesrc  = hw_surface_get_size(source);
			uint32_t * addr_src = hw_surface_get_buffer(source);
			if (sizedest.width*sizedest.height != sizesrc.width*sizesrc.height){
				return 1;
			} else {
				uint32_t * final_adrr = addr_src + sizesrc.width*sizesrc.height + sizesrc.width;
                                uint32_t * current_pixel = addr_src;
				while(current_pixel <= final_adrr){
					*addr_dest = *current_pixel;
					current_pixel++;
					addr_dest++;
				}
				return 0;
			}

		}else {
			uint32_t * addr_src = hw_surface_get_buffer(source);
			ei_size_t sizesrc  = hw_surface_get_size(source);
			uint32_t* addr_top_left_src_rect = addr_src + sizesrc.width*(src_rect->top_left.y) + src_rect->top_left.x;
			if(src_rect->size.width*src_rect->size.height != sizedest.width*sizedest.height){
				return 1;
			} else {
				ei_point_t bottom_right_src_rect = { src_rect->top_left.x + src_rect->size.width, src_rect->top_left.y +src_rect->size.height};
				uint32_t * final_addr = addr_src + sizesrc.width*bottom_right_src_rect.y + bottom_right_src_rect.x;
				uint32_t* addr_dest = hw_surface_get_buffer(destination);
				while(addr_top_left_src_rect <= final_addr){
					if (is_pixel_drawable(addr_top_left_src_rect, source, src_rect)){
						*addr_dest = *addr_top_left_src_rect;
					}
				        addr_top_left_src_rect++;
					addr_dest++;
				}
				return 0;
			}
	       }

	}else {
		uint32_t * addr_dest = hw_surface_get_buffer(destination);
		ei_size_t sizedest = hw_surface_get_size(destination);
		uint32_t * addr_top_left_dest_rect = addr_dest + sizedest.width*dst_rect->top_left.y + dst_rect->top_left.x;
		if (src_rect==NULL) { //according to function documentation
			ei_size_t sizesrc  = hw_surface_get_size(source);
			uint32_t * addr_src = hw_surface_get_buffer(source);
			if (sizesrc.width*sizesrc.height != dst_rect->size.width*dst_rect->size.height){
				return 1;
			}else {
				uint32_t * final_adrr = addr_src + sizesrc.width*sizesrc.height + sizesrc.width;

				while(addr_src <= final_adrr){
					if (is_pixel_drawable(addr_top_left_dest_rect, destination, dst_rect)){
						*addr_top_left_dest_rect = *addr_src;
					}
					addr_src++;
					addr_top_left_dest_rect++;
				}
				return 0;

			}
		} else {
			if (dst_rect->size.width*dst_rect->size.height != src_rect->size.width*src_rect->size.height){
				return 1;
			}else {
				uint32_t * addr_dest = hw_surface_get_buffer(destination);
				ei_size_t sizedest = hw_surface_get_size(destination);
				uint32_t * addr_top_left_dest_rect = addr_dest + sizedest.width*dst_rect->top_left.y + dst_rect->top_left.x;
				uint32_t * addr_src = hw_surface_get_buffer(source);
				ei_size_t sizesrc  = hw_surface_get_size(source);
				uint32_t* addr_top_left_src_rect = addr_src + sizesrc.width*(src_rect->top_left.y) + src_rect->top_left.x;
				ei_point_t bottom_right_src_rect = { src_rect->top_left.x + src_rect->size.width, src_rect->top_left.y +src_rect->size.height};
				uint32_t * final_addr = addr_src + sizesrc.width*bottom_right_src_rect.y + bottom_right_src_rect.x;
				while(addr_top_left_src_rect <= final_addr){
					bool verif_one = is_pixel_drawable(addr_top_left_src_rect, source, src_rect);
					bool verif_two = is_pixel_drawable(addr_top_left_dest_rect, destination, dst_rect);
					if (verif_one&&verif_two){
						*addr_top_left_dest_rect = *addr_top_left_src_rect;
					}
					addr_top_left_src_rect++;
					addr_top_left_dest_rect++;
				}
				return 0;

			}

		}

	}


}

//void draw_button(ei_surface_t surface, ei_rect_t rectangle, int rayon, ei_relief_t partie)
//{
//	//Principe: on met une rounded_frame, puis on en remet une par-dessus tel que la distance entre une bordure de cette rounded_frame et une bordure de
//	//la 1e rounded_frame soit de 5%
//	int rayon_arbitraire=10;
//	ei_point_t*  point_array= rounded_frame(rectangle, rayon_arbitraire, ei_relief_raised);
//	ei_color_t color = { 0x80, 0x80, 0x80, 0xff };
//	point_array[0]=point_array[1]; //Bricolage
//	ei_draw_polygon (surface, point_array, point_array[0].x, color, NULL);
//}

//ei_font_t hw_text_font_create		(ei_const_string_t	filename,
//					      ei_fontstyle_t		style,
//					      int			size);
//
//void hw_text_font_free(ei_font_t font);

void ei_draw_text(ei_surface_t	surface, const ei_point_t* where, ei_const_string_t text, ei_font_t font, ei_color_t color, const ei_rect_t* clipper)
{
	/*
	 * Theory: create surface of text, take its associated rectangle, take the rectangle associated
	 * with the original surface starting at the where point, paste the text rectangle to that rectangle.
	 */
	if (text==NULL) { //according to function documentation
		printf("Text is NULL.\n");
	}
	ei_surface_t surface_of_text = hw_text_create_surface(text, font, color);

	//Check if clipping is possible
	ei_size_t surface_size = hw_surface_get_size(surface);
	ei_size_t surface_of_text_size = hw_surface_get_size(surface_of_text);
	if ((clipper!=NULL)&&(surface_size.width!=surface_of_text_size.width)&&(surface_size.height!=surface_of_text_size.height)) {
		printf("Clipping not possible because surface sizes are different.\n");
	}

	ei_rect_t src_rec = hw_surface_get_rect(surface_of_text);
	ei_point_t* origin = surface;
	hw_surface_set_origin(surface, *where);
	ei_rect_t dst_rec = hw_surface_get_rect(surface);
	hw_surface_set_origin(surface, *origin);
	int copy_done = ei_copy_surface(surface, &dst_rec, surface_of_text, &src_rec, false);
	if (copy_done==0) { //copy_done==1 => success, copy_done==0 => fail
		printf("Copy has failed.\n");
	}
}