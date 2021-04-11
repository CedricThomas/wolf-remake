# pragma once

# include <SFML/System/Vector2.h>
# include <SFML/System/Vector3.h>

# define PI 3.1415

/* MATH */

typedef enum {
    UP,
    LEFT,
    DOWN,
    RIGHT
} direction_e;

typedef struct {
    double distance;
    direction_e direction;
    sfVector2i origin;
    sfVector2i impact;
    int out;
} raycast_t;

typedef struct {
    int x;
    int y;
    int horizontal_radius;
    int vertical_radius;
} hitbox_t;

// vector.c
sfVector2f vector2f_create(double x, double y);
float vector2f_norm(sfVector2f vec);
sfVector3f vector3f_create(double x, double y, double z);
sfVector2i vector2i_create(int x, int y);

// hitbox.c
hitbox_t hitbox_create(int x, int y, int horizontal_radius, int vertical_radius);
hitbox_t hitbox_create_from_map_position(sfVector2i position);
int hitbox_overlap(hitbox_t *a, hitbox_t *b);

// trigo.c
double cosd(double angle);
double sind(double angle);
double tand(double angle);
