#include <stdint.h>
#include <math.h>
#include <vector.h>
#include <matrix.h>
#include <gfx.h>

#include <threed.h>

#include <stdio.h>

matrix p_matrix;
matrix v_matrix;
matrix pv_matrix;

vector light;

double render_width, render_height;
double depth_buffer[SCREEN_W*SCREEN_H];


void threed_init(matrix p, matrix v, vector l, double r_w, double r_h) {
	p_matrix = p;
	v_matrix = v;
	mat_mult(&p_matrix, &v_matrix, &pv_matrix);
	light = l;
	render_width = r_w;
	render_height = r_h;
}

void draw_point(vector a, char color) {
	int offset = a.y*SCREEN_W+a.x;
	if (a.z < depth_buffer[offset]) {
		set_pixel(a.x, a.y, color);
		depth_buffer[offset] = a.z;
	}
}

/*
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
	
	//printf("%d,%d\n", sx, ex);
	
    double z1 = interpolate(pa.z, pb.z, gradient1);
    double z2 = interpolate(pc.z, pd.z, gradient2);
	
    for (int x = sx; x < ex; x++) {
        double gradient = (x - sx) / (double)(ex - sx);
        double z = interpolate(z1, z2, gradient);
        draw_point((vector){x, y, z}, color);
    }
}

void draw_triangle(vector p1, vector p2, vector p3, char color) {
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

	double dP1P2 = ((p2.y-p1.y) > 0)?(p2.x-p1.x)/(p2.y-p1.y):0.0;
	double dP1P3 = ((p3.y-p1.y) > 0)?(p3.x-p1.x)/(p3.y-p1.y):0.0;
	

    if (dP1P2 > dP1P3) {
        for (int y = (int)p1.y; y<= (int)p3.y; y++) {
            if (y < p2.y)
                scan_line(y, p1, p3, p1, p2, color);
			else
                scan_line(y, p1, p3, p2, p3, color);
        }
    }
    else {
        for (int y = (int)p1.y; y <= (int)p3.y; y++) {
            if (y < p2.y)
                scan_line(y, p1, p2, p1, p3, color);
			else
                scan_line(y, p2, p3, p1, p3, color);
        }
    }
}
*/


void swap(vector* a, vector* b) {
	vector temp = *a;
	*a = *b;
	*b = temp;
}

void threed_line(vector pa, vector pb, char color) {
	if (pa.x > pb.x) swap(&pa, &pb);
	for (int x=(int)pa.x; x<(int)pb.x; x++) {
		double z = interpolate(pa.z, pb.z, (x-pa.x)/(pb.x-pa.x));
		draw_point((vector){x, (int)pa.y, z}, color);
	}
}

void tft(vector pa, vector pb, vector pc, char color) {
	for (int y=(int)pc.y; y<(int)pa.y; y++) {
		double gradient = (y-(int)pc.y)/(double)((int)pa.y-(int)pc.y);
		double x1 = interpolate(pc.x, pa.x, gradient);
		double x2 = interpolate(pc.x, pb.x, gradient);
		double z1 = interpolate(pc.z, pa.z, gradient);
		double z2 = interpolate(pc.z, pb.z, gradient);
		threed_line((vector){x1, y, z1}, (vector){x2, y, z2}, color);
	}
}

void bft(vector pa, vector pb, vector pc, char color) {
	for (int y=(int)pa.y; y>=(int)pb.y; y--) {
		double gradient = ((int)pa.y-y)/(double)((int)pa.y-(int)pb.y);
		double x1 = interpolate(pa.x, pb.x, gradient);
		double x2 = interpolate(pa.x, pc.x, gradient);
		double z1 = interpolate(pa.z, pb.z, gradient);
		double z2 = interpolate(pa.z, pc.z, gradient);
		threed_line((vector){x1, y, z1}, (vector){x2, y, z2}, color);
	}
}

void draw_triangle(vector p1, vector p2, vector p3, char color) {
	if ((int)p1.y==(int)p2.y && (int)p1.y==(int)p3.y) return;
	if ((int)p1.x==(int)p2.x && (int)p1.x==(int)p3.x) return;
	
	if (p3.y > p1.y) swap(&p1, &p3);
	if (p2.y > p1.y) swap(&p1, &p2);
	if (p3.y > p2.y) swap(&p2, &p3);
	
	if (p2.y == p3.y) {
		bft(p1, p2, p3, color);
	} else if (p1.y == p2.y) {
		tft(p1, p2, p3, color);
	} else {
		double xi = interpolate(p3.x, p1.x, (p2.y-p3.y)/(p1.y-p3.y));
		double zi = interpolate(p3.z, p1.z, (p2.y-p3.y)/(p1.y-p3.y));
		bft(p1, (vector){xi, p2.y, zi}, p2, color);
		tft(p2, (vector){xi, p2.y, zi}, p3, color);
	}
}

void draw_model(model *m) {
	vector projected[m->n_points];
	for (int p=0; p<m->n_points; p++) {
		matrix temp;
		mat_new(1, 4, (double[]){m->points[p].x, m->points[p].y, m->points[p].z, 1}, &temp);
		mat_mult(&m->transform, &temp, &temp);
		mat_mult(&pv_matrix, &temp, &temp);
		projected[p] = (vector){(temp.x[0]+(render_width/2.0))*(SCREEN_W/render_width), (temp.x[1]+(render_height/2.0))*(SCREEN_W/render_width), temp.x[2]};
	}
	
	double light_angles[m->n_normals];
	for (int n=0; n<m->n_normals; n++) {
		matrix temp;
		mat_new(1, 4, (double[]){m->normals[n].x, m->normals[n].y, m->normals[n].z, 1}, &temp);
		mat_mult(&m->transform, &temp, &temp);
		
		vector transformed = {temp.x[0], temp.x[1], temp.x[2]};
		light_angles[n] = (((v_dot(&light, &transformed))/(v_len(&light)*v_len(&transformed)))+1.0)/2.0;
	}
	
	for (int t=0; t<m->n_triangles; t++) {
		uint8_t color = light_angles[m->triangles[t].normal]*5 + 2; // do stuff with angles
		draw_triangle(projected[m->triangles[t].a], projected[m->triangles[t].b], projected[m->triangles[t].c], color<<5);
	}
}

void clear_depth_buffer() {
	for (int d=0; d<SCREEN_W*SCREEN_H; d++) {
		depth_buffer[d] = 100.0;
	}
}