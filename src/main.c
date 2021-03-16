#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <stdio.h>
#include "wolf.h"

int sfml_hello() {
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow* window;
    sfEvent event;

    /* Create the main window */
    window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    /* Start the game loop */
    while (sfRenderWindow_isOpen(window))
    {
        /* Process events */
        while (sfRenderWindow_pollEvent(window, &event))
        {
            /* Close window : exit */
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        /* Clear the screen */
        sfRenderWindow_clear(window, sfBlack);

        /* Update the window */
        sfRenderWindow_display(window);
    }

    /* Cleanup resources */
    sfRenderWindow_destroy(window);

    return 0;
}

int main(int argc, char **argv) {
    wolf_t map;
    int error;

    error = parse(argc, argv, &map);
    if (error != 0) {
        dprintf(2, "Can't parse the game map");
        return error;
    }
    return sfml_hello();
}