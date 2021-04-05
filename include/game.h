#pragma once

#include "geometry.h"
#include "graphical.h"

#define FOV 60
#define CHUNK_SIZE 15

/* GAME */

typedef enum {
    PLAYER = '2',
    TREE = '3',
} entity_type_e;

typedef struct {
    unsigned int id;
    hitbox_t hitbox;
    float look;
    entity_type_e type;
} entity_t;

typedef struct {
    entity_t *entities;
    char **map;
    sfVector2i size;
} map_t;

typedef struct {
    unsigned long last_time;
    unsigned long interval;
} time_tracker_t;

// we load map of premade chunks
// The real map dimensions are:
// (number of chunks in width * chunk_size) x (number of chunks in height * chunk_size)
typedef struct {
    map_t *map;
    entity_t *player;
} game_state_t;

// simulation.c
void draw_simulation(game_state_t *state, framebuffer_t *buffer, sfVector2i position, sfVector2i size);
void update_simulation(game_state_t *game_state, sfEvent *event);

// game_state.c
game_state_t *game_state_create(char *map_path);
void game_state_free(game_state_t *state);

// time.c
time_tracker_t time_tracker_create(unsigned long interval);
int time_tracker_update(time_tracker_t *tracker);

// entity.c
entity_t entity_create(entity_type_e type, sfVector2i new_real_position, unsigned int id);
int entity_is_valid_type(entity_type_e type);
void entity_try_move(entity_t *entity, map_t *map, sfVector2i real_delta);
void entity_rotate(entity_t *entity, float delta);
sfVector2i entity_get_map_position(entity_t *entity);

// map.c
map_t *map_create_from_file(char *path);
int is_in_map_raw(map_t *map, sfVector2i position);
int is_in_map_real(map_t *map, sfVector2i real_position);
void map_free(map_t *map);
