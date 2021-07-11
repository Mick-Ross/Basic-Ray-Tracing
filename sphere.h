#include "vec3.h"
#include <stdbool.h>
/*
*
*
*   HITTABLE
*
*
*/

typedef struct {
    vec3 pointHit;
    vec3 normalOnSurface;
    float t;
    bool front_face;
} hittable;

void setFace (ray* r, vec3* outNormal, hittable* record);

/*
*
*
*   SPHERES
*
*
*/

typedef struct {
    vec3 center;
    float radius;
} Sphere;

Sphere makeSphere(vec3 c, float rad);

bool sphereHit(ray* r, float t_min, float t_max, Sphere s, hittable* record);