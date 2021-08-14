#include "wolf.h"

static void draw_game_background(game_state_t *state, framebuffer_t *buffer) {
    (void)(state);
    framebuffer_draw_rectangle(buffer, (sfVector2i){0, 0}, (sfVector2i){buffer->width, buffer->height / 2}, sfRed);
    framebuffer_draw_rectangle(buffer, (sfVector2i){0, buffer->height / 2}, (sfVector2i){buffer->width, buffer->height / 2}, sfBlue);
}

void draw_game(game_state_t *state, framebuffer_t *buffer) {
    draw_game_background(state, buffer);
}

void update_game(game_state_t *state, sfEvent *event) {
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