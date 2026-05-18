#include <arena.h>

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


Arena arena_create(size_t size) {
    Arena arena;

    arena_setup(&arena, size);

    return arena;
}

void *arena_alloc(Arena *arena, size_t size) {
    size_t aligned_offset = next_highest_multiple_of_8(arena->offset);

    if ((aligned_offset > arena->size) || (size > arena->size - aligned_offset)) {
        return NULL;
    }

    void *ptr = arena->buffer + aligned_offset;
    arena->offset = aligned_offset + size;

    return ptr;
}

void arena_reset(Arena *arena) {
    arena->offset = 0;
}

void arena_free(Arena *arena) {
    free(arena->buffer);
    arena->buffer = NULL;
    arena->size = 0;
    arena->offset = 0;
}

bool arena_setup(Arena *arena, size_t size) {
    arena->buffer = NULL;
    arena->size = 0;
    arena->offset = 0;

    if (size == 0 || size > SIZE_MAX) {
        return false;
    }

    arena->buffer = (uint8_t *)malloc(size);
    
    if (arena->buffer == NULL) {
        return false;
    }
    
    arena->size = size;

    return true;
}

size_t next_highest_multiple_of_8(size_t value) {
    return ((value + 7) >> 3) << 3;
}