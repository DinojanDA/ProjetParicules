#include "Vec2.h"
#include <math.h>
#include <stdlib.h>

// ------------------------------------------------

Vec2 *scal_mult(Vec2* vec, float scal) {
  Vec2* new_vec = (Vec2*) malloc(sizeof(Vec2));
  new_vec->x = scal * (vec->x);
  new_vec->y = scal * (vec->y);
  return new_vec;
}

// ------------------------------------------------

Vec2 *sum(Vec2* vec1, Vec2* vec2) {
  Vec2* new_vec = (Vec2*) malloc(sizeof(Vec2));
  new_vec->x = vec1->x + vec2->x;
  new_vec->y = vec1->y + vec2->y;
  return new_vec;
}

// ------------------------------------------------

Vec2 *substract(Vec2* vec1, Vec2* vec2) {
  Vec2* new_vec = (Vec2*) malloc(sizeof(Vec2));
  new_vec->x = vec1->x - vec2->x;
  new_vec->y = vec1->y - vec2->y;
  return new_vec;
}

// ------------------------------------------------

float dot_product(Vec2* vec1, Vec2* vec2) {
  float result = (vec1->x)*(vec2->x) + (vec1->y)*(vec2->y);
  return result;
}

// ------------------------------------------------

Vec2 *normal(Vec2* vec){
    float norm = sqrt(dot_product(vec, vec));
    Vec2 *new_vec = scal_mult(vec, (1/norm));
    return new_vec;
}

// ------------------------------------------------
