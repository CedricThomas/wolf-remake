# pragma once

# include <SFML/Graphics.h>

# define WIDTH 800
# define HEIGHT 600

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
void framebuffer_draw_pixel(framebuffer_t *buffer, unsigned int x, unsigned int y, sfColor color);

// framebuffer.c
framebuffer_t *framebuffer_create(int width, int height);
void framebuffer_free(framebuffer_t *buffer);
void clean_buff(framebuffer_t *buff);

// image.c
image_t *image_create(double width, double height);
void image_update_from_framebuffer(image_t *image, framebuffer_t *buffer);
void display_image_on_window(sfRenderWindow *window, image_t *image);
void image_free(image_t *image);

// window.c
sfRenderWindow *window_create(char *name, int width, int height);

// tools.c
sfVector2f vector2f_new(double x, double y);
sfVector3f vector3f_new(double x, double y, double z);
sfVector2i vector2i_new(int x, int y);
sfColor color_new(int a, int r, int g, int b);