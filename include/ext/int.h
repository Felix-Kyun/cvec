#ifndef __INT_VEC_H__
#define __INT_VEC_H__

#include "vec.h"

void int_vec_push_back(Vec *vec, int data);

void int_vec_push_front(Vec *vec, int data);

int int_vec_pop_front(Vec *vec);

int int_vec_pop_back(Vec *vec);

int* to_int_array(Vec *vec);

int int_vec_get(Vec *vec, int index);

#endif
