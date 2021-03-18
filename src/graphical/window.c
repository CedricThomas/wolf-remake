# include <SFML/Graphics.h>

sfRenderWindow *window_create(char *name, int width, int height) {
    sfVideoMode mode;

    mode.width = width;
    mode.height = height;
    mode.bitsPerPixel = 32;
    return sfRenderWindow_create(mode, name, sfClose, NULL);
}
