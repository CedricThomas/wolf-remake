#include <stdlib.h>
#include "wolf.h"

framebuffer_t *framebuffer_create(int width, int height) {
    framebuffer_t *buffer = malloc(sizeof(framebuffer_t));
    if (buffer == NULL)
        return NULL;
    buffer->pixels = malloc(width * height * 4 * sizeof(sfUint8));
    if (buffer->pixels == NULL)
        return NULL;
    for (int i = 0; i < (width * height * 4); i ++) {
      buffer->pixels[i] = 0;
    }
    buffer->height = height;
    buffer->width = width;
    return buffer;
}

void framebuffer_free(framebuffer_t *buffer) {
    free(buffer->pixels);
    free(buffer);
}

void clean_buff(framebuffer_t *buff) {
    for (int i = 0; i < (buff->width * buff->height * 4); i++) {
        buff->pixels[i] = 0;
    }
}
