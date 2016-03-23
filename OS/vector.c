#include <stdint.h>
#include <math.h>
#include <vector.h>

vector v_add(vector *v1, vector *v2) {
	return (vector){v1->x+v2->x, v1->y+v2->y, v1->z+v2->z};
}

double v_dot(vector *v1, vector *v2) {
	return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

double v_len(vector *v) {
	return sqrt((v->x*v->x)+(v->y*v->y)+(v->z*v->z));
}