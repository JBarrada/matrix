#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <gfx.h>
#include <time.h>

#include <matrix.h>
#include <vector.h>
#include <threed.h>

model cube;

	
void idle() {

}

void keyboard(unsigned char key, int x, int y) {
	if (key == 's') {
		mat_rotx(0.1, &cube.transform, &cube.transform);
	}
	if (key == 'w') {
		mat_rotx(-0.1, &cube.transform, &cube.transform);
	}
	
	if (key == 'a') {
		mat_roty(0.1, &cube.transform, &cube.transform);
	}
	if (key == 'd') {
		mat_roty(-0.1, &cube.transform, &cube.transform);
	}

	render();
}

void draw() {
	clear_depth_buffer();
	draw_model(&cube);
	printf("RENDERED\n");
}

/*
void draw_point(vector a, char color) {
	int offset = a.y*200+a.x;
	if (a.z < depth_buffer[offset]) {
		set_pixel(a.x, a.y, color);
		depth_buffer[offset] = a.z;
	}
}

void scan_line(int y, vector pa, vector pb, vector pc, vector pd, char color) {
	double gradient1 = (pa.y != pb.y) ? (y-pa.y) / (pb.y-pa.y) : 0;
    double gradient2 = (pc.y != pd.y) ? (y-pc.y) / (pd.y-pc.y) : 0;
	
	
    int sx = (int)interpolate(pa.x, pb.x, gradient1);
    int ex = (int)interpolate(pc.x, pd.x, gradient2);
	
	if (sx > ex) {
		int temp = sx;
		sx = ex;
		ex = temp;
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
		double cm[] = {p[i].x, p[i].y, p[i].z, 1};
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
	
	vector light = (vector){2,0,2};
	double angles[6];
	for (int i=0; i<6; i++) {
		double lm[] = {n[i].x, n[i].y, n[i].z, 1};
		matrix lmatrix;
		mat_new(1, 4, lm, &lmatrix);
		mat_roty(rotationy, &lmatrix, &lmatrix);
		mat_rotx(rotationx, &lmatrix, &lmatrix);
		vector temp_l = {lmatrix.x[0], lmatrix.x[1], lmatrix.x[2]};
		
		angles[i] = (((v_dot(&light, &temp_l))/(v_len(&light)*v_len(&temp_l)))+1.0)/2.0;
		//angles[i] = (((v_dot(&light, &n[i]))/(v_len(&light)*v_len(&n[i])))+1.0)/2.0;
		printf("%2.2f ", angles[i]);
		
	}
	
	for (int t=0; t<12; t++) {
		uint8_t color = angles[normals[t]]*7;
		int count = draw_triangle(proj[triangles[t][0]-1], proj[triangles[t][1]-1], proj[triangles[t][2]-1], color<<2);
	}
	printf("\n");
}
*/

void main() {
	matrix p_matrix, v_matrix;
	//pmatrix_o(3.0, 3.0, 10.0, 0.0, &p_matrix);
	pmatrix_p(130, 10.0, 0.0, &p_matrix);
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &v_matrix);
	
	threed_init(p_matrix, v_matrix, (vector){2, 0, 2}, 3.2, 2.0);
	
	cube.n_points = 8;
	cube.n_normals = 6;
	cube.n_triangles = 12;
	cube.points = (vector[]){{-1,-1,-1}, {-1,-1,1}, {-1,1,-1}, {-1,1,1}, {1,-1,-1}, {1,-1,1}, {1,1,-1}, {1,1,1}};
	cube.normals = (vector[]){{0,0,1}, {0,0,-1}, {0,1,0}, {0,-1,0}, {1,0,0}, {-1,0,0}};
	cube.triangles = (triangle[]){{0,6,4,1}, {0,2,6,1}, {0,3,2,5}, {0,1,3,5}, {2,7,6,2}, {2,3,7,2}, {4,6,7,4}, {4,7,5,4}, {0,4,5,3}, {0,5,1,3}, {1,5,7,0}, {1,7,3,0}};
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &cube.transform);
	
	init(idle, draw, keyboard);
}
