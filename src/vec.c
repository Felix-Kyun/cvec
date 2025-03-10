#include "vec.h"
#include <stdio.h>

void vec_push_back(Vec *vec, void *data) {
  Vec_Item *item = (Vec_Item *)malloc(sizeof(Vec_Item));
  item->data = data;
  item->next = NULL;

  if (vec->head == NULL) {
    vec->head = item;
    vec->tail = item;
  } else {
    vec->tail->next = item;
    vec->tail = item;
  }

  vec->size++;
}

void vec_push_front(Vec *vec, void *data) {
  Vec_Item *item = (Vec_Item *)malloc(sizeof(Vec_Item));
  item->data = data;
  item->next = vec->head;

  vec->head = item;

  if (vec->tail == NULL) {
    vec->tail = item;
  }

  vec->size++;
}

void *vec_pop_front(Vec *vec) {
  if (vec->head == NULL) {
    vec_set_error(vec, VEC_ERROR_EMPTY_POP);
    return NULL;
  }

  Vec_Item *item = vec->head;
  void *data = item->data;

  vec->head = item->next;
  free(item);

  vec->size--;

  return data;
}

void *vec_pop_back(Vec *vec) {
  if (vec->head == NULL) {
    vec_set_error(vec, VEC_ERROR_EMPTY_POP);
    return NULL;
  }

  Vec_Item *item = vec->head;
  Vec_Item *prev = NULL;

  while (item->next != NULL) {
    prev = item;
    item = item->next;
  }

  if (prev == NULL) {
    vec->head = NULL;
    vec->tail = NULL;
  } else {
    prev->next = NULL;
    vec->tail = prev;
  }

  vec->size--;

  void *data = item->data;
  free(item);
  return data;
}

void *vec_get(Vec *vec, size_t index) {
  if (index >= vec->size) {
    vec_set_error(vec, VEC_ERROR_OUT_OF_BOUNDS);
    return NULL;
  }

  Vec_Item *item = vec->head;
  for (size_t i = 0; i < index; i++) {
    item = item->next;
  }

  return item->data;
}

void vec_set(Vec *vec, size_t index, void *data) {
  if (index >= vec->size) {
    vec_set_error(vec, VEC_ERROR_OUT_OF_BOUNDS);
    return;
  }

  Vec_Item *item = vec->head;
  for (size_t i = 0; i < index; i++) {
    item = item->next;
  }

  item->data = data;
}

void vec_insert(Vec *vec, size_t index, void *data) {
  if (index > vec->size) {
    vec_set_error(vec, VEC_ERROR_OUT_OF_BOUNDS);
    return;
  }

  if (index == 0) {
    vec_push_front(vec, data);
    return;
  }

  if (index == vec->size) {
    vec_push_back(vec, data);
    return;
  }

  Vec_Item *item = vec->head;
  for (size_t i = 0; i < index - 1; i++) {
    item = item->next;
  }

  Vec_Item *new_item = (Vec_Item *)malloc(sizeof(Vec_Item));
  new_item->data = data;
  new_item->next = item->next;

  item->next = new_item;

  vec->size++;
}

void vec_remove(Vec *vec, size_t index) {
  if (index >= vec->size) {
    vec_set_error(vec, VEC_ERROR_OUT_OF_BOUNDS);
    return;
  }

  if (index == 0) {
    vec_pop_front(vec);
    return;
  }

  if (index == vec->size - 1) {
    vec_pop_back(vec);
    return;
  }

  Vec_Item *item = vec->head;
  Vec_Item *prev = NULL;
  for (size_t i = 0; i < index; i++) {
    prev = item;
    item = item->next;
  }

  prev->next = item->next;

  if (item == vec->tail) {
    vec->tail = prev;
  }

  free(item);

  vec->size--;
}

void vec_clear(Vec *vec) {
  Vec_Item *item = vec->head;
  while (item != NULL) {
    Vec_Item *next = item->next;
    free(item);
    item = next;
  }

  vec->head = NULL;
  vec->tail = NULL;
  vec->size = 0;
}

void vec_destroy(Vec *vec) {
  vec_clear(vec);
  free(vec);
}

bool vec_empty(Vec *vec) { return vec->size == 0; }

bool vec_error(Vec *vec) { return vec->error != VEC_ERROR_NONE; }

void vec_set_error(Vec *vec, Vec_Error error) {
  vec->error = error;

#ifndef SOFT_ERROR
  printf("%s\n", vec_error_msg(vec));
  exit(-1);
#endif
}

Vec *vec_init(void) {
  Vec *vec = (Vec *)malloc(sizeof(Vec));
  vec->head = NULL;
  vec->tail = NULL;
  vec->error = VEC_ERROR_NONE;

  return vec;
}

char *vec_error_msg(Vec *vec) {
  switch (vec->error) {
  case VEC_ERROR_NONE:
    return "No error";
  case VEC_ERROR_ALLOC:
    return "Failed to allocate memory";
  case VEC_ERROR_OUT_OF_BOUNDS:
    return "Tried to access an index that doesn't exist";
  case VEC_ERROR_EMPTY_POP:
    return "Tried popping from an empty vector";
  default:
    return "Unknown error";
  }
}
