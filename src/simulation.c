#include "wolf.h"

static const char *map[] = {
    "1111111111111111111",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1011111111111111101",
    "1010000000000000101",
    "1010000000000000101",
    "1010000000000000101",
    "1010000000000000101",
    "1010000000000000101",
    "1010000000000000101",
    "1010000000000000101",
    "1011111110111111101",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1111111111111111111",
    NULL};

void draw_simulation(game_state_t *state, framebuffer_t *buffer, sfVector2i position, sfVector2i size) {
    int width = 0;
    int height = 0;

    for (; map[height]; height++)
        ;
    for (; map[0][width]; width++)
        ;

    int bloc_height = size.y / height;
    int bloc_width = size.x / width;

    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++) {
            if (map[y][x] == '1') {
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
    // calculate percentage of full map
    sfVector2i real_position = (sfVector2i){
        position.x +  (double)(state->player->position.x) / (double)(CHUNK_SIZE * width) * size.x,
        position.y +  (double)(state->player->position.y) / (double)(CHUNK_SIZE * height) * size.y};
    framebuffer_draw_circle(buffer, real_position, bloc_width / 4, sfRed);
}

void update_simulation(game_state_t *state, sfEvent *event) {
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        state->player->position.y -= 1;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        state->player->position.x -= 1;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        state->player->position.y += 1;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        state->player->position.x += 1;
    if (sfKeyboard_isKeyPressed(sfKeyE))
        state->player->look += 1;
    if (sfKeyboard_isKeyPressed(sfKeyA))
        state->player->look -= 1;
}