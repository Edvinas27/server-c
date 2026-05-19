#include "arena.h"
#include <stdio.h>

#define KiB(n) ((uint64_t)(n) << 10)
#define MiB(n) ((uint64_t)(n) << 20)
#define GiB(n) ((uint64_t)(n) << 30) 

int main(void) {
    mem_arena *arena = arena_create(KiB(4));

    if (arena == NULL) {
        printf("Failed to create memory arena\n");
        return 1;
    }

    int *arr = (int *)arena_alloc(arena, 1000 * sizeof(int));

    if(arr == NULL) {
        printf("Failed to allocate memory from arena\n");
        arena_free(arena);
        return 1;
    }

    for (int i = 0; i < 1000; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    arena_free(arena);

    printf("Arena offset after free: %zu\n", arena->offset);
    printf("Arena size: %zu bytes\n", arena->size);
}