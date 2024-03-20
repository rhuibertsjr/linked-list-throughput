internal Arena *
arena_initialize(u64 size)
{
  Arena *result = 0;

  void *backing_buffer = malloc(size);

  if (backing_buffer != NULL)
  {
    result = (Arena*) backing_buffer;

    result->buffer = backing_buffer;
    result->offset = sizeof(Arena); 
    result->size   = sizeof(Arena) + size;
  }

  return result;
}

internal void *
arena_allocate(Arena *arena, u64 size)
{
  void *result = 0;

  if (arena->offset + size <= arena->size)
  {
    result = (void*)((u64) arena->buffer + (u64) arena->offset);
    arena->offset += size;

    memset(result, 0, size);
  }

  return result;
}

internal void
arena_release(Arena *arena)
{
  arena->offset = 0;
}
