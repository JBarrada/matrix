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
model cube2;
model cube3;	
	
matrix tv_matrix;
	
void idle() {
	//mat_rotx(-0.003, &cube.transform, &cube.transform);
	//mat_roty(-0.005, &cube.transform, &cube.transform);
	//mat_rotz(-0.0002, &cube.transform, &cube.transform);
	//render();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		mat_rotx(0.1, &tv_matrix, &tv_matrix);
	}
	if (key == 'w') {
		mat_rotx(-0.1, &tv_matrix, &tv_matrix);
	}
	
	if (key == 'a') {
		mat_roty(0.1, &tv_matrix, &tv_matrix);
	}
	if (key == 'd') {
		mat_roty(-0.1, &tv_matrix, &tv_matrix);
	}
	
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &v_matrix);
	mat_translate(0, 0, -5, &tv_matrix, &v_matrix);
	
	mat_mult(&p_matrix, &v_matrix, &pv_matrix);
	
	/*
	if (key == '-') {
		mat_scale(1.1, 1.1, 1.1, &cube.scale, &cube.scale);
	}
	if (key == '=') {
		mat_scale(0.9, 0.9, 0.9, &cube.scale, &cube.scale);
	}
	*/

	render();
}

void draw() {
	clear_depth_buffer();
	draw_model(&cube);
	draw_model(&cube2);
	draw_model(&cube3);
}

void main() {
	//matrix p_matrix, v_matrix;
	pmatrix_o(2.0, 2.0, 100.0, 1.0, &p_matrix);
	//pmatrix_p(130, 100.0, 1.0, &p_matrix);
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &v_matrix);
	mat_rotx(-1.5708, &v_matrix, &v_matrix);
	mat_roty(-0.785398, &v_matrix, &v_matrix);
	mat_rotx(0.785398, &v_matrix, &v_matrix);

	mat_translate(0, 0, -5, &v_matrix, &v_matrix);
	
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &tv_matrix);
	
	threed_init(p_matrix, v_matrix, (vector){3, 0, 0}, 3.2, 2.0);
	
	memcpy(&cube, &cube_base, sizeof(cube_base));
	mat_scale(.5,.5,.5, &cube.transform, &cube.transform);
	//mat_translate(0, 0, 0, &cube.translate, &cube.translate);
	
	memcpy(&cube2, &cube_base, sizeof(cube_base));
	mat_scale(.5,.5,.5, &cube2.transform, &cube2.transform);
	mat_translate(0, 0, 1, &cube2.transform, &cube2.transform);
	cube2.color = 1; // red
	
	memcpy(&cube3, &cube_base, sizeof(cube_base));
	mat_scale(.5,.5,.5, &cube3.transform, &cube3.transform);
	mat_translate(1, 0, 0, &cube3.transform, &cube3.transform);
	cube3.color = 2; // blue
	
	
	
	init(idle, draw, keyboard);
}
