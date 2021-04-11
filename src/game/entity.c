#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "wolf.h"

static const char ENTITIES_AVAILABLES[] = {
    PLAYER,
    TREE};

static const entity_t ENTITIES_MODELS[] = {
    {0,
        (hitbox_t){0, 0, 7, 7},
     0.0,
     PLAYER},
    {0,(hitbox_t){0, 0, 7, 7},
     0.0,
     TREE}};

entity_t entity_create(entity_type_e type, sfVector2i real_position, unsigned int id) {
    entity_t entity;
    memset(&entity, 0, sizeof(entity_t));
    char *occurence = strchr(ENTITIES_AVAILABLES, type);
    int entity_model_idx = (int)(occurence - ENTITIES_AVAILABLES);
    // TODO test is idx valid
    entity.id = id;
    entity.hitbox = ENTITIES_MODELS[entity_model_idx].hitbox;
    entity.look = ENTITIES_MODELS[entity_model_idx].look;
    entity.type = ENTITIES_MODELS[entity_model_idx].type;
    entity.hitbox.x = real_position.x;
    entity.hitbox.y = real_position.y;
    return entity;
}

int entity_is_valid_type(entity_type_e type) {
    return is_in(type, ENTITIES_AVAILABLES);
}


void entity_try_move(entity_t *entity, map_t *map, sfVector2i real_delta) {
    if (!entity)
        return;
    
    sfVector2i new_real_position = vector2i_create(
        entity->hitbox.x + real_delta.x,
        entity->hitbox.y + real_delta.y
    );
    entity_t fake_entity = entity_create(entity->type, new_real_position, entity->id);
    
    // Test global position
    if (!is_in_map_real(map, new_real_position))
        return;
    // Test map position
    sfVector2i new_map_position = entity_get_map_position(&fake_entity);
    if (!is_in_map_raw(map, new_map_position) || map->map[new_map_position.y][new_map_position.x] != '0')
        return;

    // Positions to test
    sfVector2i map_positions_to_test[] = {
        {new_map_position.x - 1, new_map_position.y - 1},
        {new_map_position.x, new_map_position.y - 1},
        {new_map_position.x + 1, new_map_position.y - 1},
        {new_map_position.x + 1, new_map_position.y},
        {new_map_position.x + 1, new_map_position.y + 1},
        {new_map_position.x, new_map_position.y + 1},
        {new_map_position.x - 1, new_map_position.y + 1},
        {new_map_position.x - 1, new_map_position.y},
    };
    // TODO map overlap correctly
    for (int i = 0; i < 8; i++) {
        sfVector2i pos = map_positions_to_test[i];
        if (!is_in_map_raw(map, pos))
         continue;
        hitbox_t hitbox = hitbox_create_from_map_position(pos);
        if (map->map[pos.y][pos.x] != '0' && hitbox_overlap(&fake_entity.hitbox, &hitbox))
            return;
    }
    
    // Test entities
    for (int i = 0; map->entities[i].type != 0; i++) {
        if (map->entities[i].id == fake_entity.id)
            continue;
        if (hitbox_overlap(&fake_entity.hitbox, &map->entities[i].hitbox))
            return;
    }
    // Move
    entity->hitbox.x = new_real_position.x;
    entity->hitbox.y = new_real_position.y;
}

void entity_rotate(entity_t *entity, double delta) {
    if (!entity)
        return;
    entity->look += delta;
}

sfVector2i entity_get_map_position(entity_t *entity) {
    if (!entity)
        return (sfVector2i){-1, -1};
    return (sfVector2i){entity->hitbox.x / CHUNK_SIZE, entity->hitbox.y / CHUNK_SIZE};
}
