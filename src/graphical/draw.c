#include "wolf.h"

void framebuffer_draw_pixel(framebuffer_t *buffer, sfVector2i position, sfColor color) {
    if (position.x < buffer->width && position.y < buffer->height) {
        buffer->pixels[(buffer->width * position.y + position.x) * 4] = color.r;
        buffer->pixels[(buffer->width * position.y + position.x) * 4 + 1] = color.g;
        buffer->pixels[(buffer->width * position.y + position.x) * 4 + 2] = color.b;
        buffer->pixels[(buffer->width * position.y + position.x) * 4 + 3] = color.a;
    }
}

void framebuffer_draw_rectangle(framebuffer_t *buffer, sfVector2i origin, sfVector2i size, sfColor color) {
    for (int x = origin.x; x < origin.x + size.x; x++) {
        for (int y = origin.y; y < origin.y + size.y; y++) {
            framebuffer_draw_pixel(buffer, (sfVector2i){x, y}, color);
        }
    }
}

void framebuffer_draw_line(framebuffer_t *buffer, sfVector2i from, sfVector2i to, sfColor color) {
    sfVector2f dir;
    sfVector2i pixel;
    double i;
    double norme;

    i = 0;
    dir.x = to.x - from.x;
    dir.y = to.y - from.y;
    norme = vector2f_norm(dir);
    dir.x /= norme;
    dir.y /= norme;
    while (i <= norme) {
        pixel.x = from.x + i * dir.x;
        pixel.y = from.y + i * dir.y;
        framebuffer_draw_pixel(buffer, pixel, color);
        i += 1;
    }
}

void framebuffer_draw_circle(framebuffer_t *buffer, sfVector2i center, int radius, sfColor color) {
    for (int x = 0; x <= radius * 2; x++) {
        for (int y = 0; y <= radius * 2; y++) {
            if (vector2f_norm(vector2f_create(x - radius, y - radius)) <= radius)
                framebuffer_draw_pixel(buffer, (sfVector2i){center.x - radius + x, center.y - radius + y}, color);
        }
    }
}