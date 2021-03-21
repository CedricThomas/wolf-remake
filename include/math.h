# pragma once

# include <SFML/System/Vector2.h>
# include <SFML/System/Vector3.h>

# define PI 3.1415

/* MATH */

typedef enum {
    SOLID,
    SOFT
} impact_type_e;

typedef enum {
    UP,
    LEFT,
    DOWN,
    RIGHT
} direction_e;

typedef struct {
    unsigned int distance;
    direction_e direction;
    sfVector2i origin;
    sfVector2i impact;
    sfVector2i subimpact;
} raycast_t;

// vector.c
sfVector2f vector2f_new(double x, double y);
float vector2f_norm(sfVector2f vec);
sfVector3f vector3f_new(double x, double y, double z);
sfVector2i vector2i_new(int x, int y);
