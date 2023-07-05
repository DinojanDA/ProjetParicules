#include "Constraint.h"

void checkContactWithPlane(Context *context, int particle_id, PlaneCollider* collider) {
  Vec2 normal = collider->normal;
  Vec2 point = collider->point;
  Vec2  dir = {normal.y, -1*normal.x};
  Particle *p = context->particles;
  int i = particle_id;
  float r = (p+i)->radius;
  Vec2 pc = {(p+i)->next_pos.x, point.y + ((p+i)->next_pos.x - point.x)*dir.y/dir.x};
  Vec2 *vec = substract(&((p+i)->next_pos), &pc);
  float value = dot_product(vec, &normal);
  if (value<r) {
    Vec2 *move = scal_mult(&normal, r-value);
    (p+i)->next_pos = *(sum(&((p+i)->next_pos), move));
  }
}

void checkContactWithSphere(Context *context, int particle_id, SphereCollider* collider) {
  Particle *p = context->particles;
  int i = particle_id;
  Vec2 *vec = substract(&((p+i)->next_pos), &(collider->center));
  float sdf = sqrt(dot_product(vec, vec)) - ((collider->radius)+((p+i)->radius));
  if (sdf<0){
    Vec2 *vec2 = normal(vec);
    vec2 = scal_mult(vec2, (collider->radius)+((p+i)->radius));
    (p+i)->next_pos = *(sum(&(collider->center), vec2));
  }
} 

void checkContactWithParticle(Context *context, int particle_id1, int particle_id2) {
  if (particle_id1 != particle_id2) {
    Particle *p = context->particles;
    int i = particle_id1;
    int j = particle_id2;
    Vec2* x = substract(&((p+i)->next_pos), &((p+j)->next_pos));
    float C = sqrt(dot_product(x, x)) - ((p+i)->radius + (p+j)->radius);
    if (C<0) {
      float sigmai = ((p+i)->inv_mass * C) / ((p+i)->inv_mass + (p+j)->inv_mass);
      float sigmaj = ((p+j)->inv_mass * C) / ((p+i)->inv_mass + (p+j)->inv_mass);

      (p+i)->next_pos = *sum(scal_mult(normal(x), -1*sigmai), &(p+i)->next_pos);
      (p+j)->next_pos = *sum(scal_mult(normal(x), sigmaj), &(p+j)->next_pos);
    }
  }
}