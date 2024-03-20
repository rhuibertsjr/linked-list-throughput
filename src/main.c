#include "base.h"

#include "arena.h"
#include "arena.c"

int
main(void)
{
  Arena *arena = arena_initialize(32);

  if (arena == 0) printf("Error arena\n");

  u64 *buffer = arena_push_array(arena, u64, 3);
  u64 *ptr = buffer;

  *buffer++ = 69;
  *buffer++ = 70;
  *buffer++ = 71;

  for (u8 index = 0; index < 3; index += 1)
  {
    printf("%llu ", *ptr++);
  }

  return 0;
}
