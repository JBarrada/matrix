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
	mat_rotx(-0.003, &cube.transform, &cube.transform);
	mat_roty(-0.005, &cube.transform, &cube.transform);
	mat_rotz(-0.0002, &cube.transform, &cube.transform);
	render();
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
	pmatrix_o(10.0, 10.0, 20.0, 0.0, &p_matrix);
	//pmatrix_p(130, 10.0, 0.0, &p_matrix);
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &v_matrix);
	
	threed_init(p_matrix, v_matrix, (vector){12, 0, 12}, 3.2, 2.0);
	
	memcpy(&cube, &cow_base, sizeof(cow_base));
	
	mat_translate(0, -4, 0, &cube.transform, &cube.transform);
	
	init(idle, draw, keyboard);
}
