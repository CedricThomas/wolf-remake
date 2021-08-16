#include <string.h>

#include "wolf.h"

static void draw_game_background(game_state_t *state) {
    framebuffer_t *buffer = state->context->buffer;
    framebuffer_draw_rectangle(buffer, (sfVector2i){0, 0}, (sfVector2i){buffer->width, buffer->height / 2}, sfRed);
    framebuffer_draw_rectangle(buffer, (sfVector2i){0, buffer->height / 2}, (sfVector2i){buffer->width, buffer->height / 2}, sfBlue);
}

static sfVector2i get_stripe_coords_from_hit(game_state_t *state, raycast_t hit) {

    // Calculate perpWallDist
    double perpWallDist = hit.distance * cosd(state->context->look - state->player->look) / CHUNK_SIZE;

    // Calculate height of line to draw on screen
    int lineHeight = (int)(HEIGHT / perpWallDist);
    lineHeight = lineHeight < 0 ? 0 : lineHeight;

    // Calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + HEIGHT / 2;
    if (drawStart < 0) {
        drawStart = 0;
    }
    int drawEnd = lineHeight / 2 + HEIGHT / 2;
    if (drawEnd >= HEIGHT) {
        drawEnd = HEIGHT - 1;
    }
    return (sfVector2i){drawStart, drawEnd};
}

static void draw_stripes(game_state_t *state) {
    rendering_context_t *context = state->context;
    sfVector2i stripeCoords = get_stripe_coords_from_hit(state, context->hits_history[1]);
    const int isTransition = \
        context->hits_history[0].direction != NONE && \
        ( \
            (
                context->hits_history[0].impact.x != context->hits_history[1].impact.x && \
                context->hits_history[0].impact.y != context->hits_history[1].impact.y
            ) \
            || \
            context->hits_history[0].direction != context->hits_history[1].direction \
        );
    
    framebuffer_draw_line(context->buffer, (sfVector2i){context->stripe_idx, stripeCoords.x}, (sfVector2i){context->stripe_idx, stripeCoords.y}, sfWhite);
    framebuffer_draw_pixel(context->buffer, (sfVector2i){context->stripe_idx, stripeCoords.x}, sfBlack);
    framebuffer_draw_pixel(context->buffer, (sfVector2i){context->stripe_idx, stripeCoords.y}, sfBlack);
    if (isTransition) {
        if (context->hits_history[0].distance < context->hits_history[1].distance) {
            stripeCoords = get_stripe_coords_from_hit(state, context->hits_history[0]);
            framebuffer_draw_line(context->buffer, (sfVector2i){context->stripe_idx - 1, stripeCoords.x}, (sfVector2i){context->stripe_idx - 1, stripeCoords.y}, sfBlack);
        } else {
            stripeCoords = get_stripe_coords_from_hit(state, context->hits_history[1]);
            framebuffer_draw_line(context->buffer, (sfVector2i){context->stripe_idx, stripeCoords.x}, (sfVector2i){context->stripe_idx, stripeCoords.y}, sfBlack);
        }
    }
}

static void draw_game_obstacles(game_state_t *state) {
    map_t *map = state->map;
    hitbox_t hitbox = state->player->hitbox;
    rendering_context_t *context = state->context;

    context->look = state->player->look - (double)FOV / 2;
    context->look_incr = (double)FOV / (double)WIDTH;
    memset(context->hits_history, 0, sizeof(context->hits_history));
    context->stripe_idx = 0;
    while (context->stripe_idx < WIDTH) {
        raycast_t cast = raycast(map, (sfVector2i){hitbox.x, hitbox.y}, context->look);
        if (!cast.out) {
            context->hits_history[0] = context->hits_history[1];
            context->hits_history[1] = cast;
            draw_stripes(state);
        }
        context->look += context->look_incr;
        context->stripe_idx += 1;
    }
} 

void draw_game(game_state_t *state) {
    draw_game_background(state);
    draw_game_obstacles(state);
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
        entity_rotate(state->player, -5);
    if (sfKeyboard_isKeyPressed(sfKeyA))
        entity_rotate(state->player, 5);
}