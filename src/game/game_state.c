#include <stdlib.h>
#include <string.h>

#include "wolf.h"

game_state_t *game_state_create(char *map_path) {
    game_state_t *state = malloc(sizeof(game_state_t));
    if (state == NULL)
        return NULL;
    memset(state, 0, sizeof(game_state_t));
    state->map = map_create_from_file(map_path);
    if (state->map == NULL)
        return NULL;
    state->context = rendering_context_create();
    if (state->context == NULL)
        return NULL;
    for (int i = 0; state->map->entities[i].type != 0; i++)
        if (state->map->entities[i].type == PLAYER)
            state->player = &state->map->entities[i];
    return state;
}

void game_state_free(game_state_t *state) {
    rendering_context_free(state->context);
    map_free(state->map);
    free(state);
}
