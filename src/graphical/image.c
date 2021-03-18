#include <stdlib.h>
#include <stdio.h>
#include "wolf.h"

image_t *image_create(double width, double height) {
    image_t *image = malloc(sizeof(image_t));
    if (image == NULL)
        return NULL;
    image->sprite = sfSprite_create();
    image->texture = sfTexture_create(width, height);
    image->width = width;
    image->height = height;
    sfSprite_setTexture(image->sprite, image->texture, sfTrue);
    return image;
}

void display_image_on_window(sfRenderWindow *window, image_t *image) {
    if (window == NULL || image == NULL) {
        dprintf(2, "invalid window display from image");
    }
    sfRenderWindow_drawSprite(window, image->sprite, NULL);
}

void image_update_from_framebuffer(image_t *image, framebuffer_t *buffer) {
    if (image == NULL || buffer == NULL || image->width != buffer->width || image->height != buffer->height) {
        dprintf(2, "invalid image update from buffer");
    }
    sfTexture_updateFromPixels(image->texture, buffer->pixels, image->width, image->height, 0, 0);
}

void image_free(image_t *image) {
    sfSprite_destroy(image->sprite);
    sfTexture_destroy(image->texture);
    free(image);
}
