#include <stdio.h>
#include "wolf.h"

int main(int argc, char **argv) {
    wolf_t map;
    int error;

    error = parse(argc, argv, &map);
    if (error != 0) {
        dprintf(2, "Can't parse the game map");
        return error;
    }
    return 0;
}