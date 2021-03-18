#include "wolf.h"

sfColor color_new(int a, int r, int g, int b) {
    sfColor color;
    color.a = a;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}
