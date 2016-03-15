#ifndef GFX_H
#define GFX_H

#define WIDTH_W 320
#define HEIGHT_W 200

typedef struct point {
	double x, y;
} point;

void set_pixel(int x, int y, unsigned char c);
void line(int x1,int y1,int x2,int y2, unsigned char c);
void circle(int cx, int cy, double r, unsigned char c);
void circle_filled(int cx, int cy, int r, unsigned char c);
void poly_filled(point points[], int num_points, unsigned char c);
void rectangle_filled(int x, int y, int width, int height, unsigned char c);

void render();
void init(void (*idle)(), void (*draw)(), void (*keyboard)(unsigned char key, int x, int y));

#endif