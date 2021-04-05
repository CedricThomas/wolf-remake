#include <math.h>

#include "wolf.h"

sfVector2f vector2f_create(double x, double y) {
    sfVector2f vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

float vector2f_norm(sfVector2f vec) {
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

sfVector3f vector3f_create(double x, double y, double z) {
    sfVector3f vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

sfVector2i vector2i_create(int x, int y) {
    sfVector2i vec;
    vec.x = x;
    vec.y = y;
    return vec;
}
