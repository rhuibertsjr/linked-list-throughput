#include "base.h"

#include "arena.h"
#include "arena.c"

typedef struct Message Message;
struct Message {
  Message *next; 
  uint8_t data[8];
};

typedef struct MessageList MessageList;
struct MessageList {
  Message *head; 
  Message *free; 
  u64 num_messages;
};

internal Message get_message(void);
internal Message * allocate_message(Arena *arena, MessageList *list);
internal void message_mark_as_read(MessageList *list, Message *message);

int
main(void)
{
  Arena *arena = arena_initialize(KB(1));
  MessageList *list = arena_push(arena, MessageList);

  u8 index = 0;

  do {

    Message *new_message = allocate_message(arena, list);
    *new_message = get_message();

    if (list->head == 0)
    {
      list->head = new_message;
    }

    else
    {
      new_message->next = list->head;
      list->head = new_message;
    }

    list->num_messages += 1;

    if (index == 4)
    {
      // rhjr: tell the mechanism that this message has been 'read' or 'freed'.
      message_mark_as_read(list, list->head->next);
    }

    index += 1;

  } while(1);

  return 0;
}

internal Message *
allocate_message(Arena *arena, MessageList *list)
{
  Message *result = list->free;

  if (result != 0)
  {
    list->free = list->free->next; 
    memory_zero_struct(result);
  }

  else
  {
    result = arena_push(arena, Message);
  }

  return result;
}

internal Message
get_message(void)
{
  Message result = {0, 0};
  return result;
}

internal void
message_mark_as_read(MessageList *list, Message *message)
{
  list->free = message;

  message->next = list->free;
  list->free = message;
}
