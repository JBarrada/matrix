#include <math.h>

double cos(double x) {
	if(x < 0.0) 
		x = -x;
	while(M_PI < x)
		x -= M_2_PI;
	return 1.0 - (x*x/2.0)*(1.0 - (x*x/12.0) * (1.0 - (x*x/30.0) * (1.0-x*x/56.0)));
}
 
double sin(double x) {
	return cos(x-M_PI_2);
}