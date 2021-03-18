#include "wolf.h"

void framebuffer_draw_pixel(framebuffer_t *buffer, unsigned int x, unsigned int y, sfColor color) {
  if (x < buffer->width && y < buffer->height) {
      buffer->pixels[(buffer->width * y + x) * 4] = color.r;
      buffer->pixels[(buffer->width * y + x) * 4 + 1] = color.g;
      buffer->pixels[(buffer->width * y + x) * 4 + 2] = color.b;
      buffer->pixels[(buffer->width * y + x) * 4 + 3] = color.a;
    }
}
