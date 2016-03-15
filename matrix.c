#include <string.h>

#include <matrix.h>
#include <math.h>
 
int mat_new(int w, int h, double *x, matrix *r) {
	r->h = h;
	r->w = w;
	memset(r->x, 0, sizeof(double)*16);
	memcpy(r->x, x, sizeof(double)*16);
	
	return 1;
}

int mat_mult44_14(matrix *a, matrix *b, matrix *c) {
	memset(c->x, 0, sizeof(double)*16);
	c->w = b->w;
	c->h = a->h;
	
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			c->x[i] += a->x[i*4+j]*b->x[j];

	return 1;
}

int mat_mult(matrix *a, matrix *b, matrix *c) {
	double t[16];
	memcpy(t, b->x, sizeof(double)*16);
	memset(c->x, 0, sizeof(double)*16);
	c->w = b->w;
	c->h = a->h;
	
	for (int i=0; i<a->h; i++)
		for (int j=0; j<b->w; j++)
			for (int k=0; k<b->h; k++)
				c->x[i*c->w+j] += a->x[i*a->w+k]*t[k*b->w+j];
			
	return 1;
}

int mat_rotx(double val, matrix *a, matrix *c) {
	double rm[] = {1, 0, 0, 0,  0, cos(val), -sin(val), 0,  0, sin(val), cos(val), 0,  0, 0, 0, 1};
	matrix rmatrix;
	mat_new(4, 4, rm, &rmatrix);
	mat_mult(&rmatrix, a, c);
	return 1;
}

int mat_roty(double val, matrix *a, matrix *c) {
	double rm[] = {cos(val), 0, sin(val), 0,  0, 1, 0, 0,  -sin(val), 0, cos(val), 0,  0, 0, 0, 1};
	matrix rmatrix;
	mat_new(4, 4, rm, &rmatrix);
	mat_mult(&rmatrix, a, c);
	return 1;
}

int mat_rotz(double val, matrix *a, matrix *c) {
	double rm[] = {cos(val), -sin(val), 0, 0,  sin(val), cos(val), 0, 0,  0, 0, 1, 0,  0, 0, 0, 1};
	matrix rmatrix;
	mat_new(4, 4, rm, &rmatrix);
	mat_mult(&rmatrix, a, c);
	return 1;
}

int mat_scale(double x, double y, double z, matrix *a, matrix *c) {
	double sm[] = {x, 0, 0, 0,  0, y, 0, 0,  0, 0, z, 0,  0, 0, 0, 1};
	matrix smatrix;
	mat_new(4, 4, sm, &smatrix);
	mat_mult(&smatrix, a, c);
	return 1;
}

int mat_translate(double x, double y, double z, matrix *a, matrix *c) {
	double tm[] = {1, 0, 0, x,  0, 1, 0, y,  0, 0, 1, z,  0, 0, 0, 1};
	matrix tmatrix;
	mat_new(4, 4, tm, &tmatrix);
	mat_mult(&tmatrix, a, c);
	return 1;
}

int pmatrix_o(double w, double h, double zf, double zn, matrix *pmatrix) {
	double pm[] = {1.0/w, 0, 0, 0,  0, 1.0/h, 0, 0,  0, 0, -2/(zf-zn), -(zf+zn)/(zf-zn),  0, 0, 0, 1};
	mat_new(4, 4, pm, pmatrix);
	return 1;
}

int pmatrix_p(double fov, double zf, double zn, matrix *pmatrix) {
	double s = atan(((fov/2.0)*(M_PI/180.0)));
	double pm[] = {s, 0, 0, 0,  0, s, 0, 0,  0, 0, -1*(zf+zn)/(zf-zn), -2*(zf*zn)/(zf-zn),  0, 0, -1, 0};
	mat_new(4, 4, pm, pmatrix);
	return 1;
}