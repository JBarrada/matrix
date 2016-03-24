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
model lght;
	
void idle() {
	//mat_rotx(-0.003, &cube.transform, &cube.transform);
	//mat_roty(-0.005, &cube.transform, &cube.transform);
	//mat_rotz(-0.0002, &cube.transform, &cube.transform);
	//render();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		mat_rotx(0.1, &cube.rotate, &cube.rotate);
	}
	if (key == 'w') {
		mat_rotx(-0.1, &cube.rotate, &cube.rotate);
	}
	
	if (key == 'a') {
		mat_roty(0.1, &cube.rotate, &cube.rotate);
	}
	if (key == 'd') {
		mat_roty(-0.1, &cube.rotate, &cube.rotate);
	}
	
	if (key == '-') {
		mat_scale(1.1, 1.1, 1.1, &cube.scale, &cube.scale);
	}
	if (key == '=') {
		mat_scale(0.9, 0.9, 0.9, &cube.scale, &cube.scale);
	}

	render();
}

void draw() {
	clear_depth_buffer();
	draw_model(&cube);
	//draw_model(&lght);
}

void main() {
	matrix p_matrix, v_matrix;
	pmatrix_o(2.0, 2.0, 100.0, 1.0, &p_matrix);
	//pmatrix_p(130, 100.0, 1.0, &p_matrix);
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, -5, 1}, &v_matrix);
	
	threed_init(p_matrix, v_matrix, (vector){12, 0, 12}, 3.2, 2.0);
	
	memcpy(&cube, &sqrt_base, sizeof(sqrt_base));
	mat_scale(.5,.5,.5, &cube.scale, &cube.scale);
	
	//memcpy(&lght, &cube_base, sizeof(cube_base));
	//mat_translate(12, 0, 0, &lght.transform, &lght.transform);
	
	mat_translate(0, -2, 0, &cube.translate, &cube.translate);
	
	init(idle, draw, keyboard);
}
