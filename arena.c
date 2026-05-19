#include "arena.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARENA_BUFFER(arena) ((uint8_t *)(arena) + sizeof(mem_arena))

bool align_to_8(size_t value, size_t *out) {
    if (value > SIZE_MAX - 7) { return false; }
    *out = ((value + 7) >> 3) << 3;
    return true;
}

mem_arena *arena_create(size_t size) {
    if (size == 0) { return NULL; }

    size_t total_size = sizeof(mem_arena) + size;

    void *memory = malloc(total_size);
    if(memory == NULL) { return NULL; }

    mem_arena *arena = (mem_arena *)memory;
    arena->size = total_size;
    arena->offset = 0;

    return arena;
}

void *arena_alloc(mem_arena *arena, size_t size) {
    if (arena == NULL || size == 0) { return NULL; }

    size_t aligned_offset; 
    if (!align_to_8(arena->offset, &aligned_offset)) { return NULL; }

    size_t usable_capacity = arena->size - sizeof(mem_arena);

    if (size > usable_capacity || aligned_offset > usable_capacity - size) { return NULL; }

    void *ptr = ARENA_BUFFER(arena) + aligned_offset;
    arena->offset = aligned_offset + size;

    return ptr;
}

void arena_reset(mem_arena *arena) {
    if (arena != NULL) { 
        arena->offset = 0;
    }
}

void arena_free(mem_arena *arena) {
    if (arena != NULL) { free(arena); }
}