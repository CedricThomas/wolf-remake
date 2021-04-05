#include <math.h>

#include "wolf.h"

hitbox_t hitbox_create(int x, int y, int horizontal_radius, int vertical_radius) {
    hitbox_t hitbox;
    hitbox.x = x;
    hitbox.y = y;
    hitbox.horizontal_radius = horizontal_radius;
    hitbox.vertical_radius = vertical_radius;
    return hitbox;
}

hitbox_t hitbox_create_from_map_position(sfVector2i position) {
    // TODO check if correct
    hitbox_t hitbox;
    hitbox.x = position.x * CHUNK_SIZE + CHUNK_SIZE / 2;
    hitbox.y = position.y * CHUNK_SIZE + CHUNK_SIZE / 2;
    hitbox.horizontal_radius = CHUNK_SIZE / 2;
    hitbox.vertical_radius = CHUNK_SIZE / 2;
    return hitbox;
}

int hitbox_overlap(hitbox_t *a, hitbox_t *b) {
    sfIntRect a_rect = (sfIntRect){
        a->x - a->horizontal_radius - 1,
        a->y - a->vertical_radius - 1,
        a->horizontal_radius * 2 + 1,
        a->vertical_radius * 2 + 1,
    };
    sfIntRect b_rect = (sfIntRect){
        b->x - b->horizontal_radius - 1,
        b->y - b->vertical_radius - 1,
        b->horizontal_radius * 2 + 1,
        b->vertical_radius * 2 + 1,

    };
    return sfIntRect_intersects(&a_rect, &b_rect, NULL);
}

