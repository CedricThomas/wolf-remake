#include <string.h>
#include <stdlib.h>

#include "wolf.h"

static const char *fake_map[] = {
    "1111111111111111111",
    "1000000000000000001",
    "1021000000000000001",
    "1011000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000101",
    "1000000000000001101",
    "1000000000000000001",
    "1111111111111111111",
    NULL};

// TODO implement real loading
static char **load_map(char *path) {
    int i = 0;
    while (fake_map[i] != NULL)
        i++;
    char **map = malloc((i + 1) * sizeof(char *));
    if (map == NULL)
        return NULL;
    for (int j = 0; j < i; j++) {
        map[j] = strdup(fake_map[j]);
        if (map[j] == NULL)
            return NULL;
    }
    map[i] = NULL;
    return map;
}

static int count_entities(char **map) {
    int count = 0;

    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++) {
            if (entity_is_valid_type(map[y][x])) {
                count++;
            }
        }
    }
    return count;
}

static entity_t *extract_entities(char **map) {
    int id = 0;
    int count = count_entities(map);
    entity_t *entities = malloc((count + 1) * sizeof(entity_t));
    if (entities == NULL)
        return NULL;
    memset(entities, 0, (count + 1) * sizeof(entity_t));
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++) {
            if (entity_is_valid_type(map[y][x])) {
                entities[id] = entity_create(map[y][x], (sfVector2i){
                    CHUNK_SIZE * x + CHUNK_SIZE / 2,
                    CHUNK_SIZE * y + CHUNK_SIZE / 2,
                }, id);
                map[y][x] = '0';
                id++;
            }
        }
    }
    return entities;
}

// TODO check if correct
map_t *map_create_from_file(char *path) {
    map_t *map = malloc(sizeof(map_t));
    if (map == NULL)
        return NULL;

    map->map = load_map(path);
    if (map->map == NULL)
        return NULL;

    map->entities = extract_entities(map->map);
    if (map->entities == NULL)
        return NULL;

    int y = 0;
    while (map->map[y])
        y++;
    if (y == 0) {
        return NULL;
    }
    int x = 0;
    while (map->map[0][x])
        x++;
    map->size = (sfVector2i){x, y}; 
    return map;
}

// TODO check if correct
int is_in_map_real(map_t *map, sfVector2i real_position) {
    return real_position.x >= 0 && real_position.x < map->size.x * CHUNK_SIZE && real_position.y >= 0 && real_position.y < map->size.y * CHUNK_SIZE; 
}

// TODO check if correct
int is_in_map_raw(map_t *map, sfVector2i position) {
    return position.x >= 0 && position.x < map->size.x && position.y >= 0 && position.y < map->size.y; 
}

void map_free(map_t *map) {
    for (int y = 0; map->map[y]; y++) {
        free(map->map[y]);
    }
    free(map->map);
    free(map->entities);
    free(map);
}
