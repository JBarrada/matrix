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
	
model cubes[5];

double viewx=0, viewy=0;
	
void idle() {
	//mat_rotx(-0.003, &cube.transform, &cube.transform);
	//mat_roty(-0.005, &cube.transform, &cube.transform);
	//mat_rotz(-0.004, &cubes[0].transform, &cubes[0].transform);
	//render();
}

void keyboard(unsigned char key, int x, int y) {
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &v_matrix);
	mat_rotx(-1.5708, &v_matrix, &v_matrix);
	mat_roty(-0.785398, &v_matrix, &v_matrix);
	mat_rotx(0.785398,  &v_matrix, &v_matrix);
	
	if (key == 's') {
		viewy -= 0.1;
	}
	if (key == 'w') {
		viewy += 0.1;
	}
	
	if (key == 'a') {
		viewx -= 0.1;
	}
	if (key == 'd') {
		viewx += 0.1;
	}
	
	//mat_translate(viewx, viewy, -5, &v_matrix, &v_matrix);
	
	mat_mult(&p_matrix, &v_matrix, &pv_matrix);
	
	
	if (key == '-') {
		mat_rotz(-0.004, &cubes[0].transform, &cubes[0].transform);
	}
	if (key == '=') {

	}
	

	render();
}

void draw() {
	clear_depth_buffer();
	
	for (int i=0; i<1; i++) {
		draw_model(&cubes[i]);
	}
}

void setup_cube(model *m, double x, double y, double z, uint8_t color) {
	memcpy(m, &cube_base, sizeof(cube_base));
	mat_translate(x, y, z, &m->transform, &m->transform);
	m->color = color; // blue
}

void main() {
	pmatrix_o(2.0, 2.0, 100.0, 1.0, &p_matrix);
	
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &v_matrix);
	mat_rotx(-1.5708, &v_matrix, &v_matrix);
	mat_roty(-0.785398, &v_matrix, &v_matrix);
	mat_rotx(0.785398, &v_matrix, &v_matrix);

	mat_translate(0, 0, -5, &v_matrix, &v_matrix);

	threed_init(p_matrix, v_matrix, (vector){3, 0, 0}, 3.2, 2.0);
	
	setup_cube(&cubes[0], 0, 0, 0, 3);
	setup_cube(&cubes[1], 2, 0, 0, 0);
	setup_cube(&cubes[2], 4, 0, 0, 0);
	setup_cube(&cubes[3], 0, 2, 0, 0);
	setup_cube(&cubes[4], 0, 4, 0, 0);
	init(idle, draw, keyboard);
}
