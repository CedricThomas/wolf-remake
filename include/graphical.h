# pragma once

# include <SFML/Graphics.h>

# define WIDTH  1920
# define HEIGHT 1080

/* GRAPHICAL */

typedef struct {
    sfUint8         *pixels;
    unsigned int    width;
    unsigned int    height;
} framebuffer_t;

typedef struct {
    sfTexture       *texture;
    sfSprite        *sprite;
    unsigned int    width;
    unsigned int    height;
} image_t;

// draw.c
void framebuffer_draw_pixel(framebuffer_t *buffer, sfVector2i position, sfColor color);
void framebuffer_draw_rectangle(framebuffer_t *buffer, sfVector2i origin, sfVector2i size, sfColor color);
void framebuffer_draw_line(framebuffer_t *buffer, sfVector2i from, sfVector2i to, sfColor color);
void framebuffer_draw_circle(framebuffer_t *buffer, sfVector2i center, int radius, sfColor color);

// framebuffer.c
framebuffer_t *framebuffer_create(int width, int height);
void framebuffer_free(framebuffer_t *buffer);
void framebuffer_clear(framebuffer_t *buff);

// image.c
image_t *image_create(double width, double height);
void image_update_from_framebuffer(image_t *image, framebuffer_t *buffer);
void display_image_on_window(sfRenderWindow *window, image_t *image);
void image_free(image_t *image);

// window.c
sfRenderWindow *window_create(char *name, int width, int height);

// tools.c
sfColor color_new(int a, int r, int g, int b);
