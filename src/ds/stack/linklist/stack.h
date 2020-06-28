#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


typedef struct node_s {
  void *data;
  struct node_s *next;
} node_s;

typedef struct stack_s {
  size_t size;
  node_s *top;
} stack_s;


static
void
node_new(stack_s *const stack) {
  node_s *p = malloc(sizeof(node_s));
  p->data = malloc(stack->size);
  p->next = stack->top;
  stack->top = p;
}

static
void
node_free(node_s *node) {
  free(node->data);
  free(node);
}


int
stack_empty(stack_s *const stack) {
  return stack->top == 0;
}

stack_s*
stack_new(stack_s *stack, size_t size) {
  stack = calloc(1, sizeof(stack_s));
  if (stack) {
    stack->size = size;
  }
  return stack;  
}

void
stack_free(stack_s *stack) {
  if (!stack_empty(stack)) {
    node_s **p = &stack->top;
    do {
      node_s *next = (*p)->next;
      node_free(*p);
      *p = next;
    } while ((*p)->next);
  }

  free(stack);  
}

void
stack_push(stack_s *const stack, void *val) {
  node_new(stack);
  memcpy(stack->top->data, val, stack->size);
}

int
stack_pop(stack_s *const stack, void *val) {
  if (stack_empty(stack)) {
    return 0;
  }
  memcpy(val, stack->top->data, stack->size);
  node_s *top = stack->top;
  stack->top = stack->top->next;
  node_free(top);
  return 1;  
}


#endif /* end of _STACK_H_ */