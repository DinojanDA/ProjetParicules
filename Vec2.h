#ifndef VEC2_H_
#define VEC2_H_

// ------------------------------------------------

typedef struct Vec2 {
  float x;
  float y;
} Vec2;

// ------------------------------------------------

Vec2 *scal_mult(Vec2* vec, float scal);
Vec2 *sum(Vec2* vec1, Vec2* vec2);
Vec2 *substract(Vec2* vec1, Vec2* vec2);
float dot_product(Vec2* vec1, Vec2* vec2);
Vec2 *normal(Vec2* vec);

// ------------------------------------------------

#endif