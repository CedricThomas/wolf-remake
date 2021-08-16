#include <string.h>
#include <stdlib.h>

#include "wolf.h"

rendering_context_t *rendering_context_create() {
    rendering_context_t *rendering_context = malloc(sizeof(rendering_context_t));
    if (rendering_context == NULL)
        return NULL;
    memset(rendering_context, 0, sizeof(rendering_context_t));
    return rendering_context;
}

void rendering_context_free(rendering_context_t *rendering_context) {
    free(rendering_context);
}
