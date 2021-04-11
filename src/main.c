#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>

#include "wolf.h"

void draw(game_state_t *state, framebuffer_t *buffer) {
    draw_simulation(
        state,
        buffer,
        (sfVector2i){
            0,
            0
        }, (sfVector2i){
            300,
            300
        });
}

void update(game_state_t *state, sfEvent *event) {
    update_simulation(state, event);
}

int run() {
    sfEvent event;

    time_tracker_t update_tracker = time_tracker_create(100);

    /* Create the main window */
    sfRenderWindow *window = window_create("wolf", WIDTH, HEIGHT);
    if (!window)
        return 1;

    /* Create image used to display the framebuffer */
    game_state_t *state = game_state_create(NULL);
    if (!state)
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
        framebuffer_clear(framebuffer);

        /* Update the game only when the time tracker is updatable*/
        if (time_tracker_update(&update_tracker))
            update(state, &event);

        /* Draw the game */
        draw(state, framebuffer);
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
    return run();
}