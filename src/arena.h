#ifndef ARENA_H
#define ARENA_H

typedef struct Arena Arena;
struct Arena {
  u64 *buffer;
  u64 offset;
  u64 size;
};

internal Arena * arena_initialize(u64 size);

internal void * arena_allocate(Arena *arena, u64 size);
internal void   arena_release(Arena *arena);

//= rhjr: arena helpers

#define arena_push_array(arena, type, count) \
  (type*) arena_allocate((arena), sizeof(type) * (count))

#define arena_push(arena, type) \
  (type*) arena_allocate((arena), sizeof(type))

//= rhjr: memory helpers

#define memory_zero(s,z)       memset((s), 0, (z))
#define memory_zero_struct(s)  memory_zero((s), sizeof(*(s)))

#endif // ARENA_H
