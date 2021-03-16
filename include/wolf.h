#pragma once

typedef struct {
    char **map;
} wolf_t;

int parse(int argc, char **argv, wolf_t *map);
