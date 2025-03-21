#include "ext/int.h"

// helper conversion functions

// alloc: int -> void *
static void *alloc_int(int data) {
  int *data_ptr = (int *)malloc(sizeof(int));
  *data_ptr = data;
  return data_ptr;
}

// dealloc: void * -> int , Vec* for error handling
static int dealloc_int(void *data) {
  int data_val = *(int *)data;  
  free(data);
  return data_val;
}

void int_vec_push_back(Vec *vec, int data) {
  vec_push_back(vec, alloc_int(data));
}

void int_vec_push_front(Vec *vec, int data) {
  vec_push_front(vec, alloc_int(data));
}

int int_vec_pop_front(Vec *vec) {
  return dealloc_int(vec_pop_front(vec));
}

int int_vec_pop_back(Vec *vec) {
  return dealloc_int(vec_pop_back(vec));
}

int* to_int_array(Vec *vec) {
  int *arr = (int *)malloc(vec->size * sizeof(int));
  for (size_t i = 0; i < vec->size; i++) {
    arr[i] = *(int *)vec_get(vec, i);
  }
  return arr;
}

int int_vec_get(Vec *vec, int index) {
  return *(int *)vec_get(vec, index);
}
