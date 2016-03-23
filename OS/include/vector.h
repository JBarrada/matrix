#ifndef VECTOR_H
#define VECTOR_H

typedef struct vector_t{
	double x, y, z;
} vector;

vector v_add(vector *v1, vector *v2);
double v_dot(vector *v1, vector *v2);
double v_len(vector *v);

#endif