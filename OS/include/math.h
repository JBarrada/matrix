#ifndef MATH_H
#define MATH_H

#define M_PI 3.14159265
#define M_PI_2 1.57079632
#define M_PI_4 0.78539816
#define M_2_PI 6.28318530

double cos(double x);
double sin(double x);
double tan(double x);
double atan(double x);

double fabs(double x);
double sqrt(const double fg);
double interpolate(double start, double end, double pos);

#endif