#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_

#include "Vec2.h"
#include "Context.h"

typedef struct Context Context;

// ------------------------------------------------

typedef struct SphereCollider {
  Vec2 center;
  float radius;
} SphereCollider;

typedef struct PlaneCollider {
  Vec2 normal;
  Vec2 point;
} PlaneCollider;

// ------------------------------------------------

void checkContactWithPlane(Context* context, int particle_id, PlaneCollider* collider);
void checkContactWithSphere(Context* context, int particle_id, SphereCollider* collider);
void checkContactWithParticle(Context* context, int particle_id1, int particle_id2);

#endif