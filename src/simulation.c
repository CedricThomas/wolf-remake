#include "wolf.h"

void draw_look(game_state_t *state, framebuffer_t *buffer, sfVector2i position, sfVector2i size) {
    map_t *map = state->map;
    hitbox_t hitbox = state->player->hitbox;
    double look = state->player->look - (double)FOV / 2;
    double incr = (double)FOV / (double)WIDTH;

    for (int i = 0; i < WIDTH; i++) {
        raycast_t cast = raycast(map, (sfVector2i){hitbox.x, hitbox.y}, look);
        if (!cast.out) {
            double bloc_height = (double)size.y / (double)state->map->size.y;
            double bloc_width = (double)size.x / (double)state->map->size.x;
            framebuffer_draw_rectangle(
                buffer,
                (sfVector2i){
                position.x + cast.impact.x * bloc_width + 1,
                position.y + cast.impact.y * bloc_height + 1},
                        (sfVector2i){
                            bloc_width - 2,
                            bloc_height - 2},
                        sfGreen);
            sfVector2i real_position = (sfVector2i){
            position.x +  (double)(hitbox.x) / (double)(CHUNK_SIZE * state->map->size.x) * size.x,
            position.y +  (double)(hitbox.y) / (double)(CHUNK_SIZE * state->map->size.y) * size.y};
            sfVector2i ray_impact = (sfVector2i){
                real_position.x + cosd(look) * (cast.distance / (double)(CHUNK_SIZE * state->map->size.x) * size.x),
                real_position.y - sind(look) * (cast.distance / (double)(CHUNK_SIZE * state->map->size.y) * size.y)
            };
            framebuffer_draw_line(buffer, real_position, ray_impact, sfGreen);
        }
        look += incr;
    }
}

void draw_simulation(game_state_t *state, framebuffer_t *buffer, sfVector2i position, sfVector2i size) {
    double bloc_height = (double)size.y / (double)state->map->size.y;
    double bloc_width = (double)size.x / (double)state->map->size.x;

    for (int y = 0; state->map->map[y]; y++) {
        for (int x = 0; state->map->map[y][x]; x++) {
            if (state->map->map[y][x] == '1') {
                framebuffer_draw_rectangle(
                    buffer,
                    (sfVector2i){
                        position.x + x * bloc_width,
                        position.y + y * bloc_height},
                    (sfVector2i){
                        bloc_width,
                        bloc_height},
                    sfBlue);
                framebuffer_draw_rectangle(
                    buffer,
                    (sfVector2i){
                        position.x + x * bloc_width + 1,
                        position.y + y * bloc_height + 1},
                    (sfVector2i){
                        bloc_width - 2,
                        bloc_height - 2},
                    sfBlack);
            }
        }
    }
    for (int i = 0; state->map->entities[i].type; i++) {
        entity_t entity = state->map->entities[i];
        // calculate percentage of full map
        sfVector2i real_position = (sfVector2i){
            position.x +  (double)(entity.hitbox.x) / (double)(CHUNK_SIZE * state->map->size.x) * size.x,
            position.y +  (double)(entity.hitbox.y) / (double)(CHUNK_SIZE * state->map->size.y) * size.y};
        framebuffer_draw_circle(buffer, real_position, (double)(entity.hitbox.horizontal_radius) / (double)(CHUNK_SIZE * state->map->size.x) * size.x , sfRed);
    }
    draw_look(state, buffer, position, size);
}

void update_simulation(game_state_t *state, sfEvent *event) {
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        entity_try_move(state->player, state->map, (sfVector2i){0, -5});
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        entity_try_move(state->player, state->map, (sfVector2i){-5, 0});
    if (sfKeyboard_isKeyPressed(sfKeyS))
        entity_try_move(state->player, state->map, (sfVector2i){0, 5});
    if (sfKeyboard_isKeyPressed(sfKeyD))
        entity_try_move(state->player, state->map, (sfVector2i){5, 0});
    if (sfKeyboard_isKeyPressed(sfKeyE))
        entity_rotate(state->player, 5);
    if (sfKeyboard_isKeyPressed(sfKeyA))
        entity_rotate(state->player, -5);
}