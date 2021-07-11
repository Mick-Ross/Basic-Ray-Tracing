#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "vec3.h"

// if curious about the process/math, check out:
// https://raytracing.github.io/books/RayTracingInOneWeekend.html#rays,asimplecamera,andbackground
// Warning: code in C++

// vector P = generic point, vector C = center of sphere
// remember that a ray is parametrized in terms of t:
// P(t) = origin + t*dir

// vector P-C must satisfy (P-C)dot(P-C) = radius^2
// vector dotted with itself is squaring the magnitude (same direction & mag.)
float hitSphere(vec3* center, float radius, ray* r) {
    vec3 rayOgToCenter = vecSub(&(r->origin), center);
    float a = dotProduct(&(r->dir), &(r->dir));
    float b = 2.0 * dotProduct(&rayOgToCenter, &(r->dir));
    float c = dotProduct(&rayOgToCenter, &rayOgToCenter) - radius*radius;
    float discriminant = b*b - 4*a*c;

    // if there is no real solution, we have not hit the sphere
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}

// here we use the value of t for our ray that intersects with the sphere
Color3 calculateLighting(float t, ray* r, vec3* sphereCenter) {
    vec3 rayEnd = rayTip(t, r);
    vec3 pointSphereMinusCenterSphere = vecSub(&rayEnd, sphereCenter);
    vec3 normal = unitVec(&pointSphereMinusCenterSphere);

    vec3 fakePointSource = constVec(-0.3, 0, -0.6);
    vec3 pointSphereToLight = vecSub(&fakePointSource, &rayEnd);
    vec3 normalizeLight = unitVec(&pointSphereToLight);

    // this is between -1 and 1
    float magChannels = dotProduct(&normal, &normalizeLight);

    // slides the channels, red ceiling = 1 (255), green = 0.537 (137)
    // restricts 0 < magChannels < 1 linearly, this is a poor lighting model
    Color3 color = constVec((magChannels+1)/2, (magChannels+1)/3.7226, 0.3333);
    return vecScalarMultiply(0.5, &color);
}

// if hit sphere, ray(t=t'), t' is intersection w/ sphere,
// transforms to rgb space for pixel color depending on normal vector
Color3 calculateSphereNormalColor(float t, ray* r, vec3* sphereCenter) {
    vec3 rayEnd = rayTip(t, r);
    vec3 pointSphereMinusCenterSphere = vecSub(&rayEnd, sphereCenter);
    vec3 normal = unitVec(&pointSphereMinusCenterSphere);
    
    // mapping normal vec components to RGB color space
    Color3 color = constVec(normal.x + 1, normal.y + 1, normal.z + 1);
    return vecScalarMultiply(0.5, &color);
}


Color3 ray_color(ray* r, int flag) {
    vec3 newSphereCenter = constVec(-0.5, 0.39, -1);
    vec3 newSphereCenter2 = constVec(2, -0.5, -2.5);
    vec3 newSphereCenter3 = constVec(20, -100.5, -1);

    //finds the t parameter of a given ray that allows it to intersect
    //with our default sphere
    float t = hitSphere(&newSphereCenter, 0.5, r);
    if (t > 0.0) {
        vec3 v;
        v = ((flag == 1) ? calculateSphereNormalColor(t, r, &newSphereCenter) :
                          calculateLighting(t, r, &newSphereCenter));
        return v;
    }
    t = hitSphere(&newSphereCenter2, 0.34, r);
    if (t > 0.0) {
        vec3 v;
        v = ((flag == 1) ? calculateSphereNormalColor(t, r, &newSphereCenter2) :
                          calculateLighting(t, r, &newSphereCenter2));
        return v;
    }
    t = hitSphere(&newSphereCenter3, 100, r);
    if (t > 0.0) {
        vec3 v;
        v = ((flag == 1) ? calculateSphereNormalColor(t, r, &newSphereCenter3) :
                          calculateLighting(t, r, &newSphereCenter3));
        return v;
    }
    
    

    // otherwise, fills in the sky in the background
    vec3 unit_direction = unitVec(&(r->dir));
    t = 0.5*((unit_direction.y) + 1.0);
    //printf("%f\n", unit_direction.y);

    // creating our two colors we want to blend between, normalizing between 0-1
    Color3 white = constVec(1.0, 1.0, 1.0);
    Color3 babyOrange = constVec(1.0, 0.788, 0.36);

    // linearly interpolate between full blue and full white
    // depending on the y value of the normalized ray vector
    vec3 amtWhite = vecScalarMultiply((1.0-t), &white);
    vec3 amtOg = vecScalarMultiply(t, &babyOrange);
    return vecAdd(&amtWhite, &amtOg);
}

int main(int argc, char* argv[]) {

    if (argc < 2 || argc > 3) {
        printf("Must have one argument for the file name our PPM");
        printf("image will be saved to.\n");
        printf("There is only 1 valid additional command, '-normal', ");
        printf("which renders the normals of each sphere in RGB space.\n");
        return 1;
    }
    int normalFlag = 0;
    if (argc == 3) {
        if (!strcmp(argv[2], "-normal")) {
            normalFlag = 1;
        } else {
            printf("Only valid command is '-normal'. Try again.\n");
            return 1;
        }
    }

    // Defining image dimensions
    const float aspect_ratio = 16.0/9.0;
    const int pixelWidth = 1000;
    const int pixelHeight = (int)(pixelWidth/aspect_ratio);

    // Defining our camera at the origin, shoots rays through
    // each pixel of the near clip plane of our view frustum
    float nearPlane_height = 2.0;
    float nearPlane_width = aspect_ratio * nearPlane_height;
    float focal_length = 1.0; //distance between projection plane and proj. pt.

    coord originV = constVec(0, 0, 0);
    vec3 horizontal = constVec(nearPlane_width, 0, 0);
    vec3 halfHorizontal = constVec(nearPlane_width/2.0, 0, 0);
    vec3 vertical = constVec(0, nearPlane_height, 0);
    vec3 halfVertical = constVec(0, nearPlane_height/2.0, 0);
    vec3 focal = constVec(0, 0, focal_length);

    // Calculating the bottom left coordinate of near clip plane.
    vec3 minX = vecSub(&originV, &halfHorizontal); 
    vec3 minXY = vecSub(&minX, &halfVertical);
    vec3 minXYZ = vecSub(&minXY, &focal);
    
    // creating the ray to be used for each pixel along our screen
    ray r;
    r.origin = originV;

    // Rendering the image
    FILE* outputPPM = fopen(argv[1], "w");
    fprintf(outputPPM, "P3 %u %u %u\n", pixelWidth, pixelHeight, 255);
    
    for (int j = pixelHeight - 1; j >= 0; j--) {
        //printf("Scanlines remaining: %u\n", j);
        for (int i = 0; i < pixelWidth; i++) {
            float uCoord = (float)(i) / (pixelWidth - 1);
            float vCoord = (float)(j) / (pixelHeight - 1);

            vec3 horizontalComp = vecScalarMultiply(uCoord, &horizontal);
            vec3 verticalComp = vecScalarMultiply(vCoord, &vertical);
            vec3 direction1 = vecAdd(&minXYZ, &horizontalComp);
            vec3 direction2 = vecAdd(&direction1, &verticalComp);
            vec3 direction = vecSub(&direction2, &originV);
            //printV3(&direction);

            r.dir = direction;

            Color3 pixelCol = ray_color(&r, normalFlag);

            int red = (int)(255.999 * pixelCol.x);
            int green = (int)(255.999 * pixelCol.y);
            int blue = (int)(255.999 * pixelCol.z);
            fprintf(outputPPM, "%u %u %u\n", red, green, blue);
        }
    }

    return 0;
}