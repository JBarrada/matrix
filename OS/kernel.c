#define KERNEL

#include <stddef.h>
#include <stdint.h>

#include <keyboard.h>
#include <io.h>

#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <pit.h>

#include <vga.h>
#include <gfx.h>
#include <string.h>
#include <debug.h>

#include <random.h>
#include <math.h>
#include <matrix.h>
#include <vector.h>
#include <threed.h>

#include <objects.h>

model cube;

extern uint8_t keystate;
int autorotate = 1;

uint8_t move_model() { 
	if (((keystate>>0)&1) == 1) { // left
		mat_roty(-0.05, &cube.transform, &cube.transform);
	}
	if (((keystate>>1)&1) == 1) { // right
		mat_roty(0.05, &cube.transform, &cube.transform);
	}
	
	if (((keystate>>2)&1) == 1) { // up
		mat_rotx(-0.05, &cube.transform, &cube.transform);
	}
	if (((keystate>>3)&1) == 1) { // down
		mat_rotx(0.05, &cube.transform, &cube.transform);
	}
	autorotate = 0;
	return 1;
}

void draw() {
	clear_depth_buffer();
	draw_model(&cube);
	flush();
}

void kernel_main() {
	gdt_init();
	idt_init();
	pic_init();
	
	pit_init();
	keyboard_init();

	asm("sti");
	
	vga_init();
	
	set_keyboard_callback(move_model);
	
	uint8_t newpallete[256*3];
	memset(newpallete, 0, 256*3);
	for (int i=0; i<32; i++) {
		newpallete[i*3+0] = 5;
		newpallete[i*3+1] = i*2;
		newpallete[i*3+2] = i;
	}
	gfx_set_palette(newpallete);
	
	
	matrix p_matrix, v_matrix;
	pmatrix_o(10.0, 10.0, 20.0, 0.0, &p_matrix);
	mat_new(4, 4, (double[]){1, 0, 0, 0,  0, 1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1}, &v_matrix);
	
	threed_init(p_matrix, v_matrix, (vector){20, 0, 20}, 3.2, 2.0);
	
	memcpy(&cube, &cow_base, sizeof(cow_base));
	
	mat_translate(0, -4, 0, &cube.transform, &cube.transform);
	
	clear();
	draw();
	
	for (;;) {
		if (autorotate == 1) {
			mat_rotx(-0.03, &cube.transform, &cube.transform);
			mat_roty(-0.05, &cube.transform, &cube.transform);
			mat_rotz(-0.002, &cube.transform, &cube.transform);
		}
		clear();
		draw();
		msleep(20);
	}

	for(;;) {
		asm("hlt");
	}
}
