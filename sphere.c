#include "sphere.h"

// derivation found on website posted on main file

/*
*
*
*   HITTABLE
*
*
*/

void setFace (ray* r, vec3* outNormal, hittable* record) {
    record->front_face = (dotProduct(&(r->dir), outNormal) < 0);
    record->normalOnSurface = ((record->front_face) ? *outNormal : 
                                vecScalarMultiply(-1, outNormal));
}

void hitCompare (ray* r, float t_min, float t_max, hittable* lowest, hittable* record) {
    hittable temp;
    bool hit_anything = false;
    float closest_so_far = t_max;
}

/*
*
*
*   SPHERE
*
*
*/

Sphere makeSphere(vec3 c, float rad) {
    Sphere s;
    s.center = c;
    s.radius = rad;
    return s;
}

bool sphereHit(ray* r, float t_min, float t_max, Sphere* s, hittable* record) {
    vec3 rayOgToCenter = vecSub(&(r->origin), &(s->center));
    float a = dotProduct(&(r->dir), &(r->dir));
    float b = 2.0 * dotProduct(&rayOgToCenter, &(r->dir));
    float c = dotProduct(&rayOgToCenter, &rayOgToCenter) - (s->radius*s->radius);
    float discriminant = b*b - 4*a*c;

    // if there is no real solution, we have not hit the sphere
    if (discriminant < 0) {
        return false;
    }

    // checks for the closest root within the acceptable range
    // if either range fits in range, we won't count this ray
    float root = (-b - sqrt(discriminant)) / (2.0*a);
    if (root < t_min || root > t_max) {
        root = (-b + sqrt(discriminant)) / (2.0*a); 
        if (root < t_min || root > t_max) {
            return false;
        }
    }

    record->t = root;
    record->pointHit = rayTip(root, r);
    
    // finding the normal along the surface of the sphere
    vec3 centerToPoint = vecSub(&(record->pointHit), &(s->center));
    record->normalOnSurface = vecScalarMultiply(1/s->radius, &centerToPoint);

    return true;
}