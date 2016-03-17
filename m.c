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
	
	cube.n_points = 8;
	cube.n_normals = 6;
	cube.n_triangles = 12;
	cube.points = (vector[]){{-1,-1,-1}, {-1,-1,1}, {-1,1,-1}, {-1,1,1}, {1,-1,-1}, {1,-1,1}, {1,1,-1}, {1,1,1}};
	cube.normals = (vector[]){{0,0,1}, {0,0,-1}, {0,1,0}, {0,-1,0}, {1,0,0}, {-1,0,0}};
	cube.triangles = (triangle[]){{0,6,4,1}, {0,2,6,1}, {0,3,2,5}, {0,1,3,5}, {2,7,6,2}, {2,3,7,2}, {4,6,7,4}, {4,7,5,4}, {0,4,5,3}, {0,5,1,3}, {1,5,7,0}, {1,7,3,0}};
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &cube.transform);

	init(idle, draw, keyboard);
}
