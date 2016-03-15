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

double tan(double x) {
	return sin(x)/cos(x);
}

double atan(double x) {
    return M_PI_4*x - x*(fabs(x) - 1)*(0.2447 + 0.0663*fabs(x));
}

double fabs(double x) {
	if (x < 0)
		return -1*x;
	else 
		return x;
}

double sqrt(const double fg) { 
	double n = fg / 2.0;
	double lstX = 0.0; 
	while(n != lstX) { 
		lstX = n;
		n = (n + fg/n) / 2.0; 
	}
	return n;
}  

double interpolate(double start, double end, double pos) {
	return ((end-start)*pos) + start;
}