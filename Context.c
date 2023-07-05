#include "Context.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// ------------------------------------------------

Particle getParticle(Context* context, int id)
{
  return context->particles[id];
}

// ------------------------------------------------

void addParticle(Context* context, float x, float y, float radius, float mass, int draw_id)
{
    assert(context->num_particles<context->capacity_particles); // currently no resize in context
    context->particles[context->num_particles].position.x = x;
    context->particles[context->num_particles].position.y = y;
    context->particles[context->num_particles].velocity.x = 0.0F;
    context->particles[context->num_particles].velocity.y = 0.0F;
    context->particles[context->num_particles].inv_mass = 1.0F/mass;
    context->particles[context->num_particles].radius = radius;
    context->particles[context->num_particles].draw_id = draw_id;
    context->num_particles += 1;
}

// ------------------------------------------------

void setDrawId(Context* context, int sphere_id, int draw_id)
{
  context->particles[sphere_id].draw_id = draw_id;
}

// ------------------------------------------------

SphereCollider getGroundSphereCollider(Context* context, int id)
{
  return context->ground_spheres[id];
}

// ------------------------------------------------

PlaneCollider getGroundPlaneCollider(Context* context)
{
  return context->plane[0];
}

// ------------------------------------------------

Context* initializeContext(int capacity)
{
  Context* context = malloc(sizeof(Context));
  context->num_particles = 0;
  context->capacity_particles = capacity;
  context->particles = malloc(capacity*sizeof(Particle));
  memset(context->particles,0,capacity*sizeof(Particle));

  context->num_ground_sphere = 3;
  context->ground_spheres = malloc(3*sizeof(SphereCollider));
  Vec2 p0 = {-5.0f, 2.5f};
  context->ground_spheres[0].center = p0;
  context->ground_spheres[0].radius = 1.7;
  Vec2 p1 = {5.0f, 2.5f};
  context->ground_spheres[1].center = p1;
  context->ground_spheres[1].radius = 1.7;
  Vec2 p2 = {0.0f, -2.5f};
  context->ground_spheres[2].center = p2;
  context->ground_spheres[2].radius = 1.7;

  context->plane = malloc(sizeof(PlaneCollider));
  Vec2 norm = {0.1f, 0.8f};
  Vec2 point = {0.0f, -8.0f};
  context->plane[0].normal = norm;
  context->plane[0].point = point;
  return context;
}

// ------------------------------------------------

void updatePhysicalSystem(Context* context, float dt, int num_constraint_relaxation)
{
  applyExternalForce(context, dt);
  dampVelocities(context);
  updateExpectedPosition(context, dt);
  addDynamicContactConstraints(context);
  addStaticContactConstraints(context);
 
  for(int k=0; k<num_constraint_relaxation; ++k) {
    projectConstraints(context);
  }

  updateVelocityAndPosition(context, dt);
  applyFriction(context);

  deleteContactConstraints(context);
}

// ------------------------------------------------

void applyExternalForce(Context* context, float dt)
{
  if (context->num_particles==0) return;
  Particle *p = context->particles;
  for (int i=0; i<context->num_particles; ++i){
    Vec2 force = {0, -dt*(p+i)->inv_mass * 9.81};
    (p+i)->velocity = *(sum(&((p+i)->velocity), &force)); 
  }
}

void dampVelocities(Context* context)
{
   
}

void updateExpectedPosition(Context* context, float dt)
{
  if (context->num_particles==0) return;
  Particle *p = context->particles;
  for (int i=0; i<context->num_particles; ++i) {
    (p+i)->next_pos = *sum(scal_mult(&((p+i)->velocity), dt), &((p+i)->position));
  }
}

void addDynamicContactConstraints(Context* context)
{
  if (context->num_particles==0) return;
  Particle* p = context->particles;
  for (int i = 0; i < context->num_particles; ++i) {
    for (int j = 0; j < context->num_particles; ++j) {
      checkContactWithParticle(context, i, j);
    }
  }
}

void addStaticContactConstraints(Context* context)
{
  if (context->num_particles == 0) return; 
  Particle* p = context->particles;
  PlaneCollider* plane = context->plane;
  for (int i = 0; i < context->num_particles; ++i) {
    checkContactWithPlane(context, i, plane);
    for (int j = 0; j < context->num_ground_sphere; ++j) {
      SphereCollider collider = context->ground_spheres[j];
      checkContactWithSphere(context, i, &collider);
    }
  }
}

void projectConstraints(Context* context)
{
}

void updateVelocityAndPosition(Context* context, float dt)
{
  if (context->num_particles==0) return;
  Particle *p = context->particles;
  for (int i=0; i<context->num_particles; ++i){
    (p+1)->velocity = *scal_mult(substract(&((p+i)->next_pos), &((p+i)->position)), (1.0/dt));
    (p+i)->position = (p+i)->next_pos;
  }
}

void applyFriction(Context* context)
{
}

void deleteContactConstraints(Context* context)
{
}

// ------------------------------------------------
