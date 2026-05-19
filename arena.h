#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    size_t size;        // Total size of the allocated memory block
    size_t offset;      // Current offset within the memory block
} mem_arena;

mem_arena *arena_create(size_t size);
void *arena_alloc(mem_arena *arena, size_t size);
void arena_reset(mem_arena *arena);
void arena_free(mem_arena *arena);

#endif