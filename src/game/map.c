#include <string.h>
#include <stdlib.h>

#include "wolf.h"

static const char *fake_map[] = {
    "1111111111111111111",
    "1000000000000000001",
    "1000000000000000001",
    "1000000000000000001",
    "1011111111111111101",
    "1010000000000000101",
    "1010000000000000101",
    "1010000000000000101",
    "1010000002000000101",
    "1010000000000000101",
    "1010000000000000101",
    "1010000000000000101",
    "1011111110111111101",
    "1000000000000000001",
    "1000000000000000001",
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
    int count = count_entities(map);
    entity_t *entities = malloc((count + 1) * sizeof(entity_t));
    if (entities == NULL)
        return NULL;
    memset(entities, 0, (count + 1) * sizeof(entity_t));
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++) {
            if (entity_is_valid_type(map[y][x])) {
                count--;
                entities[count] = entity_create(map[y][x], (sfVector2i){
                    CHUNK_SIZE * x + entities[count].position.x,
                    CHUNK_SIZE * y + entities[count].position.y,
                });
                map[y][x] = '0';
            }
        }
    }
    return entities;
}

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
    return map;
}

void map_free(map_t *map) {
    for (int y = 0; map->map[y]; y++) {
        free(map->map[y]);
    }
    free(map->map);
    free(map->entities);
    free(map);
}
