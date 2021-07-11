#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "vec3.h"

vec3* constructor(float x1, float y1, float z1) {
    vec3* vector = (vec3*) malloc(sizeof(vec3));
    vector->x = x1;
    vector->y = y1;
    vector->z = z1;

    return vector;
}
 
void printV3(vec3* v) {
    printf("x: %f, y: %f, z: %f\n", v->x, v->y, v->z);
}

vec3 constVec(float x1, float y1, float z1) {
    vec3 v;
    v.x = x1;
    v.y = y1;
    v.z = z1;
    return v;
}

void freeVec3(vec3* vector) {
    free(vector);
}

float length(vec3* v) {
    return sqrt(lengthSquared(v));
}

float lengthSquared(vec3* v) {
    return ((v->x)*(v->x) + (v->y)*(v->y) + (v->z)*(v->z));
}

// make sure to free vec1 and vec2 afterwards once done with them!
vec3 vecAdd(vec3* vec1, vec3* vec2) {
    return constVec(vec1->x + vec2->x, vec1->y + vec2->y, vec1->z + vec2->z);
}

vec3 vecSub(vec3* vec1, vec3* vec2) {
    return constVec(vec1->x - vec2->x, vec1->y - vec2->y, vec1->z - vec2->z);
}

vec3 vecScalarMultiply(float t, vec3* vec) {
    return constVec(t*(vec->x), t*(vec->y), t*(vec->z));
}

float dotProduct(vec3* v1, vec3* v2) {
    return (v1->x)*(v2->x)+(v1->y)*(v2->y)+(v1->z)*(v2->z);
}

vec3 unitVec(vec3* v) {
    return vecScalarMultiply((1/length(v)), v);
}


// RAY STUFF BELOW


//put pointers to vectors or copies of vectors as argument???
ray* rayConstructor(vec3* og, vec3* direct) {
    ray* ray1 = (ray*) malloc(sizeof(ray));
    ray1->origin = *og;
    ray1->dir = *direct;
    return ray1;
}

//should I do this??? is this correct??
void freeRay(ray* ray) {
    free(ray);
}

vec3 rayTip(float t, ray* ray1) {
    vec3 parametrizedDir = vecScalarMultiply(t, &(ray1->dir));
    vec3 v = vecAdd(&(ray1->origin), &parametrizedDir);
    return v;
}
