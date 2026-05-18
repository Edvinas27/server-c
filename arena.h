#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint8_t *buffer;    // Start of the allocated memory block
    size_t size;        // Total size of the allocated memory block
    size_t offset;      // Current offset within the memory block
} Arena;

Arena arena_create(size_t size);
void *arena_alloc(Arena *arena, size_t size);
void arena_reset(Arena *arena);
void arena_free(Arena *arena);

#endif