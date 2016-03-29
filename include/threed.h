#ifndef THREED_H
#define THREED_H

#define SCREEN_W 320
#define SCREEN_H 200

#include <vector.h>
#include <matrix.h>

typedef struct triangle_t {
	int a, b, c, normal;
} triangle;

typedef struct model_t {
	int n_points, n_normals, n_triangles;
	vector *points;
	vector *normals;
	triangle *triangles;
	
	matrix transform;
	unsigned char color;
} model;

extern matrix p_matrix;
extern matrix v_matrix;
extern matrix pv_matrix;


void threed_init(matrix p, matrix v, vector l, double r_w, double r_h);
void draw_model(model *m);
void clear_depth_buffer();
#endif