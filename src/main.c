#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>

#include "wolf.h"

void draw(framebuffer_t *buffer) {
    framebuffer_draw_pixel(buffer, (sfVector2i){WIDTH / 5, HEIGHT / 2}, sfRed);
    framebuffer_draw_rectangle(buffer, (sfVector2i){2 * WIDTH / 5, HEIGHT / 2}, (sfVector2i){10, 10}, sfGreen);
    framebuffer_draw_line(buffer, (sfVector2i){3 * WIDTH / 5, HEIGHT / 2}, (sfVector2i){3 * WIDTH / 5, HEIGHT / 3}, sfBlue);
    framebuffer_draw_circle(buffer, (sfVector2i){4 * WIDTH / 5, HEIGHT / 2}, 30, color_new(255, 100, 100, 255));
}

int sfml_hello() {
    sfEvent event;

    /* Create the main window */
    sfRenderWindow *window = window_create("wolf", WIDTH, HEIGHT);
    if (!window)
        return 1;

    /* Create image used to display the framebuffer */
    image_t *framebuffer_image = image_create(WIDTH, HEIGHT);
    if (!framebuffer_image)
        return 1;

    /* Create the framebuffer */
    framebuffer_t *framebuffer = framebuffer_create(WIDTH, HEIGHT);
    if (!framebuffer)
        return 1;

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window)) {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event)) {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Draw the game */
        draw(framebuffer);
        image_update_from_framebuffer(framebuffer_image, framebuffer);
        display_image_on_window(window, framebuffer_image);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfRenderWindow_destroy(window);

    return 0;
}

int main(int argc, char **argv) {
    return sfml_hello();
}