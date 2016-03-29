#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix_t{
	int h, w; 
	double x[16];
} matrix;

int mat_new(int w, int h, double *x, matrix *r);
int mat_mult44_14(matrix *a, matrix *b, matrix *c);
int mat_mult(matrix *a, matrix *b, matrix *c);


int mat_rotx(double val, matrix *a, matrix *c);
int mat_roty(double val, matrix *a, matrix *c);
int mat_rotz(double val, matrix *a, matrix *c);

int mat_scale(double x, double y, double z, matrix *a, matrix *c);
int mat_translate(double x, double y, double z, matrix *a, matrix *c);

int mat_getvector(matrix *a, matrix *b);

int pmatrix_o(double w, double h, double zf, double zn, matrix *pmatrix);
int pmatrix_p(double fov, double zf, double zn, matrix *pmatrix);

#endif