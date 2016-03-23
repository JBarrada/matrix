#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <gfx.h>
#include <time.h>

#include <matrix.h>
#include <vector.h>
#include <threed.h>

#include <objects.h>

model cube;
	
void idle() {

}

void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		mat_rotx(0.1, &cube.transform, &cube.transform);
	}
	if (key == 'w') {
		mat_rotx(-0.1, &cube.transform, &cube.transform);
	}
	
	if (key == 'a') {
		mat_roty(0.1, &cube.transform, &cube.transform);
	}
	if (key == 'd') {
		mat_roty(-0.1, &cube.transform, &cube.transform);
	}

	render();
}

void draw() {
	clear_depth_buffer();
	draw_model(&cube);
}

void main() {
	matrix p_matrix, v_matrix;
	pmatrix_o(3.0, 3.0, 10.0, 0.0, &p_matrix);
	//pmatrix_p(130, 10.0, 0.0, &p_matrix);
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &v_matrix);
	
	threed_init(p_matrix, v_matrix, (vector){2, 0, 2}, 3.2, 2.0);
	
	memcpy(&cube, &icosahedron_base, sizeof(icosahedron_base));
	
	init(idle, draw, keyboard);
}
