#include <math.h>
#include <string.h>
#include "wolf.h"

static raycast_t horizontal_cast(map_t *map, sfVector2i position, double angle) {
    raycast_t raycast;
    sfVector2f ray_position;
    sfVector2f ray_step;
    sfVector2i map_position;

    memset(&raycast, 0, sizeof(raycast_t));
    raycast.distance = -1;
    raycast.origin = position;
    if (cosd(angle) == 1 || cosd(angle) == -1) {
        return raycast;
    }
    ray_position.y = (int)(position.y / CHUNK_SIZE) * CHUNK_SIZE - position.y;
    if (sind(angle) < 0)
        ray_position.y = (CHUNK_SIZE + ray_position.y);
    ray_position.x = -ray_position.y / tand(angle);
    ray_step.y = (sind(angle) >= 0 ? -CHUNK_SIZE : CHUNK_SIZE);
    ray_step.x = -ray_step.y / tand(angle);
    map_position.x = (ray_position.x + position.x) / CHUNK_SIZE;
    map_position.y = (ray_position.y + position.y + ray_step.y / 10) / CHUNK_SIZE;
    while (is_in_map_raw(map, map_position) && map->map[map_position.y][map_position.x] == '0')
        {
        ray_position.x += ray_step.x;
        ray_position.y += ray_step.y;
        map_position.x = (ray_position.x + position.x) / CHUNK_SIZE;
        map_position.y = (ray_position.y + position.y + ray_step.y / 10) / CHUNK_SIZE;
        }
    if (is_in_map_raw(map, map_position)) {
        raycast.impact = map_position;
        raycast.out = 0;
    } else {
        raycast.out = 1;
    }
    raycast.distance = sqrt(ray_position.x * ray_position.x + ray_position.y * ray_position.y);
    raycast.direction = (sind(angle) >= 0 ? UP : DOWN);
    return raycast;
}

static raycast_t vertical_cast(map_t *map, sfVector2i position, double angle) {
    raycast_t raycast;
    sfVector2f ray_position;
    sfVector2f ray_step;
    sfVector2i map_position;

    memset(&raycast, 0, sizeof(raycast_t));
    raycast.distance = -1;
    raycast.origin = position;
    if (sind(angle) == 1 || sind(angle) == -1) {
        return raycast;
    }
    ray_position.x = (int)(position.x / CHUNK_SIZE) * CHUNK_SIZE - position.x;
    if (cosd(angle) >= 0)
        ray_position.x = CHUNK_SIZE + ray_position.x;
    ray_position.y = -ray_position.x * tand(angle);
    ray_step.x = (cosd(angle) >= 0 ? CHUNK_SIZE : -CHUNK_SIZE);
    ray_step.y = -ray_step.x * tand(angle);
    map_position.x = (ray_position.x + position.x + ray_step.x / 10) / CHUNK_SIZE; // WEIRD FLEX HERE DUDE
    map_position.y = (ray_position.y + position.y) / CHUNK_SIZE;
    while (is_in_map_raw(map, map_position) && map->map[map_position.y][map_position.x] == '0') {
        ray_position.x += ray_step.x;
        ray_position.y += ray_step.y;
        map_position.x = (ray_position.x + position.x + ray_step.x / 10) / CHUNK_SIZE; // WEIRD FLEX HERE DUDE
        map_position.y = (ray_position.y + position.y) / CHUNK_SIZE;
    }
    if (is_in_map_raw(map, map_position)) {
        raycast.impact = map_position;
        raycast.out = 0;
    } else {
        raycast.out = 1;
    }
    raycast.distance = sqrt(ray_position.x * ray_position.x + ray_position.y * ray_position.y);
    raycast.direction = (cosd(angle) >= 0 ? LEFT : RIGHT);
    return raycast;
}

raycast_t raycast(map_t *map, sfVector2i position, double angle) {
    raycast_t horizontal_raycast = horizontal_cast(map, position, angle);
    raycast_t vertical_raycast = vertical_cast(map, position, angle);
    if ((vertical_raycast.distance > 0 && vertical_raycast.distance <= horizontal_raycast.distance) || horizontal_raycast.distance < 0) {
        return vertical_raycast;
    } else {
        return horizontal_raycast;
    } 
}