#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <gfx.h>
#include <time.h>

#include <matrix.h>
#include <vector.h>

#define PI 3.14159265

matrix pmatrix, pvmatrix;

double rotationx = 0.0;
double rotationy = 0.0;

double depth_buffer[200*200];

vector cube[8] = {{-1,-1,-1}, {-1,-1,1}, {-1,1,-1}, {-1,1,1}, {1,-1,-1}, {1,-1,1}, {1,1,-1}, {1,1,1}};
int triangles[12][3] = {{1,7,5}, {1,3,7}, {1,4,3}, {1,2,4}, {3,8,7}, {3,4,8}, {5,7,8}, {5,8,6}, {1,5,6}, {1,6,2}, {2,6,8}, {2,8,4}};
char colors[12] = {0x7, 0x7, 0xf, 0xf, 0x70, 0x70, 0xf0, 0xf0, 0xff, 0xff, 0x77, 0x77};


vector proj[8] = {{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}};
					
void idle() {
	/*
	rotation += 0.001;
	if (rotation > M_2_PI) {
		rotation = 0;
	}
	render();
	*/
	//usleep(1000000/30.0);
}

void keyboard(unsigned char key, int x, int y) {
	//printf("%c\n", key);
	
	if (key == 'w') {
		rotationy += 0.01;
	}
	if (key == 's') {
		rotationy -= 0.01;
	}
	
	if (rotationy > M_2_PI) {
		rotationy = 0;
	}
	if (rotationy < 0) {
		rotationy = M_2_PI;
	}
	
	
	if (key == 'd') {
		rotationx += 0.01;
	}
	if (key == 'a') {
		rotationx -= 0.01;
	}
	
	if (rotationx > M_2_PI) {
		rotationx = 0;
	}
	if (rotationx < 0) {
		rotationx = M_2_PI;
	}
	render();
	
	//printf("%f\n", rotation);
	
	for (int i=0; i<8; i++) {
		//printf("(%d,%d,%2.1f) ", (int)proj[i].x, (int)proj[i].y, proj[i].z);
	}
	//printf("\n");
}

void draw_point(vector a, char color) {
	int offset = a.y*200+a.x;
	if (a.z < depth_buffer[offset]) {
		set_pixel(a.x, a.y, color);
		depth_buffer[offset] = a.z;
	}
}

double interpolate(double start, double end, double pos) {
	return ((end-start)*pos) + start;
}

void scan_line(int y, vector pa, vector pb, vector pc, vector pd, char color) {
	double gradient1 = (pa.y != pb.y) ? (y-pa.y) / (pb.y-pa.y) : 0;
    double gradient2 = (pc.y != pd.y) ? (y-pc.y) / (pd.y-pc.y) : 0;
	
	
    int sx = (int)interpolate(pa.x, pb.x, gradient1);
    int ex = (int)interpolate(pc.x, pd.x, gradient2);
	
	if (ex-sx == 0) {
		printf("fuck");
	}

    // starting Z & ending Z
    double z1 = interpolate(pa.z, pb.z, gradient1);
    double z2 = interpolate(pc.z, pd.z, gradient2);

    // drawing a line from left (sx) to right (ex) 
    for (int x = sx; x < ex; x++) {
        double gradient = (x - sx) / (double)(ex - sx);

        double z = interpolate(z1, z2, gradient);
        draw_point((vector){x, y, z}, color);
    }
}

int draw_triangle(vector p1, vector p2, vector p3, char color) {
	if (p1.y > p2.y) {
        vector temp = p2;
        p2 = p1;
        p1 = temp;
    }

    if (p2.y > p3.y) {
        vector temp = p2;
        p2 = p3;
        p3 = temp;
    }

    if (p1.y > p2.y) {
        vector temp = p2;
        p2 = p1;
        p1 = temp;
    }

    double dP1P2, dP1P3;
    if ((p2.y-p1.y) > 0) {
		dP1P2 = (p2.x - p1.x) / (p2.y - p1.y);
	}
    else {
		dP1P2 = 0.0;
	}

    if ((p3.y-p1.y) > 0) {
	    dP1P3 = (p3.x - p1.x) / (p3.y - p1.y);	
	}
    else {
		dP1P3 = 0.0;
	}
	
	int count = 0;
	
    if (dP1P2 > dP1P3) {
        for (int y = (int)p1.y; y<=(int)p3.y; y++) {
            if (y < p2.y) {
                scan_line(y, p1, p3, p1, p2, color);
            } 
			else {
                scan_line(y, p1, p3, p2, p3, color);
            }
			count++;
        }
    }
    else {
        for (int y = (int)p1.y; y <= (int)p3.y; y++) {
            if (y < p2.y) {
                scan_line(y, p1, p2, p1, p3, color);
            }
			else {
                scan_line(y, p2, p3, p1, p3, color);
            }
			count++;
        }
    }
	return count;
}
					
void draw() {
	for (int d=0; d<200*200; d++) {
		depth_buffer[d] = 100.0;
	}
	
	for (int i=0; i<8; i++) {
		// to worldspace
		double cm[] = {cube[i].x, cube[i].y, cube[i].z, 1};
		matrix tmatrix;
		mat_new(1, 4, cm, &tmatrix);
		
		mat_roty(rotationy, &tmatrix, &tmatrix);
		mat_rotx(rotationx, &tmatrix, &tmatrix);
		//mat_rotz(rotation, &tmatrix, &tmatrix);
		
		// to projectionview space
		matrix mpvmatrix;
		mat_mult(&pvmatrix, &tmatrix, &mpvmatrix);

		int xmap = (mpvmatrix.x[0]+2.0)*50.0;
		int ymap = (mpvmatrix.x[1]+2.0)*50.0;
		
		proj[i].x = xmap;
		proj[i].y = ymap;
		proj[i].z = mpvmatrix.x[2];
	}
	
	
	for (int t=0; t<2; t++) {
		int count = draw_triangle(proj[triangles[t][0]-1], proj[triangles[t][1]-1], proj[triangles[t][2]-1], colors[t]);
		printf("T%d: %d ", t, count);
	}
	printf("\n");
}

void main() {
	pmatrix_o(2.0, 2.0, 10.0, 0.0, &pmatrix);
	mat_translate(0, 0, -5.0, &pmatrix, &pvmatrix);
	
	init(idle, draw, keyboard);
}
