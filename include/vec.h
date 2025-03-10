#ifndef __VEC_H__
#define __VEC_H__

// use -DSOFT_ERROR to enable soft error handling
// soft error handling will not exit the program on error
// but seg fault will occur if the error is not handled properly

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// custom error enum
// for full message use vec_error_msg(enum Vec_Error)
typedef enum Vec_Error {
  VEC_ERROR_NONE,
  VEC_ERROR_ALLOC,
  VEC_ERROR_OUT_OF_BOUNDS,
  VEC_ERROR_EMPTY_POP,
} Vec_Error;

typedef struct Vec_Item {
  void *data;
  struct Vec_Item *next;
} Vec_Item;

typedef struct Vec {

  size_t size;
  Vec_Item *head;
  Vec_Item *tail;
  Vec_Error error;

} Vec;

// initialize a new Vec
// @return: pointer to Vec struct
Vec *vec_init(void);

// push data to the back of the Vec
// @param vec: pointer to Vec struct
// @param data: pointer to Vec_Item struct
void vec_push_back(Vec *vec, void *data);

// push data to the front of the Vec
// @param vec: pointer to Vec struct
// @param data: pointer to Vec_Item struct
void vec_push_front(Vec *vec, void *data);

// pop data from the back of the Vec
// @param vec: pointer to Vec struct
// @return: pointer to Vec_Item struct or NULL
void *vec_pop_back(Vec *vec);

// pop data from the front of the Vec
// @param vec: pointer to Vec struct
// @return: pointer to Vec_Item struct or NULL
void *vec_pop_front(Vec *vec);

// get data from the Vec at index
// @param vec: pointer to Vec struct
// @param index: index of the data
// @return: pointer to Vec_Item struct or NULL
void *vec_get(Vec *vec, size_t index);

// set data in the Vec at index
// @param vec: pointer to Vec struct
// @param index: index of the data
// @param data: pointer to Vec_Item struct
void vec_set(Vec *vec, size_t index, void *data);

// insert data in the Vec at index
// @param vec: pointer to Vec struct
// @param index: index of the data
// @param data: pointer to Vec_Item struct
void vec_insert(Vec *vec, size_t index, void *data);

// remove data in the Vec at index
// @param vec: pointer to Vec struct
// @param index: index of the data
void vec_remove(Vec *vec, size_t index);

// clear the Vec struct and free all the data, if any
// @param vec: pointer to Vec struct
void vec_clear(Vec *vec);

// free all data and the Vec struct itself
// @param vec: pointer to Vec struct
void vec_destroy(Vec *vec);

// helper function to check if the Vec is empty
bool vec_empty(Vec *vec);

/* error handling */

// check if there is an error
// @param vec: pointer to Vec struct
// @return: true if there is an error, false otherwise
bool vec_error(Vec *vec);

// set the error enum
// @param vec: pointer to Vec struct
// @param error: enum Vec_Error
void vec_set_error(Vec *vec, Vec_Error error);

// get the error message
// @param error: enum Vec_Error
// @return: error message
char *vec_error_msg(Vec *vec);

#endif // !__VEC_H__
