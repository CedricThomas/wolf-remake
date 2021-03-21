#include <stdlib.h>
#include <string.h>

#include "wolf.h"

static const char ENTITIES_AVAILABLES[] = {
    PLAYER,
    TREE};

static const entity_t ENTITIES_MODELS[] = {
    {(sfVector2i){0, 0},
     (sfVector2i){0, 0},
     0.0,
     PLAYER},
    {(sfVector2i){0, 0},
     (sfVector2i){0, 0},
     0.0,
     TREE}};

entity_t entity_create(entity_type_e type, sfVector2i position) {
    entity_t entity;
    memset(&entity, 0, sizeof(entity_t));
    char *occurence = strchr(ENTITIES_AVAILABLES, type);
    int entity_model_idx = (int)(occurence - ENTITIES_AVAILABLES);
    // TODO test is valid
    const entity_t *source = &ENTITIES_MODELS[entity_model_idx];
    entity.hitbox = source->hitbox;
    entity.position = position;
    entity.look = source->look;
    entity.type = source->type;
    return entity;
}

int entity_is_valid_type(entity_type_e type) {
    return is_in(type, ENTITIES_AVAILABLES);
}

void entity_try_move(entity_t *entity, map_t *map, sfVector2i delta) {
    // TODO implement
}

void entity_rotate(entity_t *entity, float delta) {
    // TODO implement
}

sfVector2i entity_get_map_position(entity_t *entity) {
    // TODO implement
    return (sfVector2i){entity->position.x / CHUNK_SIZE, entity->position.y / CHUNK_SIZE};
}
