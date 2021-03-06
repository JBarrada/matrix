#ifndef __GFX_H_
#define __GFX_H_

#include <stdint.h>

void set_pixel(int x, int y, uint8_t c);

void gfx_clear_palette();
int in_palette(uint8_t *color);
int gfx_register_palette(uint8_t *palette, uint8_t *remap);
int gfx_register_color(uint8_t *color);

uint8_t* gfx_get_palette();
void gfx_set_palette(uint8_t *palette);
void fade_palette(uint8_t *dest, int delay);

void circle_filled(int cx, int cy, int r, uint8_t c);
void clear();
void flush();

#endif