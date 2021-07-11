#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "vec3.h"

Color3 ray_color(ray* r) {
    vec3 unit_direction = unitVec(&(r->dir));
    float t = 0.5*((unit_direction.y) + 1.0);
    printf("%f\n", unit_direction.y);

    // creating our two colors we want to blend between, normalizing between 0-1
    Color3 white = constVec(1.0, 1.0, 1.0);
    Color3 babyBlue = constVec(0.5, 0.7, 1.0);

    //linearly interpolate between full blue and full white
    //depending on the y value of the normalized ray vector
    vec3 amtWhite = vecScalarMultiply((1.0-t), &white);
    vec3 amtBlue = vecScalarMultiply(t, &babyBlue);
    return vecAdd(&amtWhite, &amtBlue);
}

int main() {
    vec3 v1 = constVec(2.0, 1.0, 3.0);
    printV3(&v1);
    vec3 v2 = constVec(1.0, 4.0, 5.0);

    vec3 v3 = vecAdd(&v1, &v2);
    printV3(&v3);

    vec3 v4 = vecScalarMultiply(2.0, &v3);
    printV3(&v4);

    vec3 vNorm = constVec(1, 1, 1);
    vec3 vNorm2 = unitVec(&vNorm);
    printV3(&vNorm2);

    // everything above works so far!!

    //vec3 origin = constVec(0, 0, 0);

    return 0;
}