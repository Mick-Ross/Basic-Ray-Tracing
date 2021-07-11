// 3D Vector with Mathematical Operations

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef vec3 Color3;
typedef vec3 coord;

//we will malloc each vec3 in the constructor
vec3* constructor(float x, float y, float z);

void printV3(vec3* v);

vec3 constVec(float x, float y, float z);

//free function once we're done with the vector
void freeVec3(vec3* vector);

float length(vec3* v);

float lengthSquared(vec3* v);

vec3 vecAdd(vec3* vec1, vec3* vec2);

vec3 vecSub(vec3* vec1, vec3* vec2);

vec3 vecScalarMultiply(float t, vec3* vec);

float dotProduct(vec3* v1, vec3* v2);

vec3 unitVec(vec3* v);
//add more vector operations!

/*
    
    RAY STUFF BELOW
    
*/

typedef struct {
    coord origin;
    vec3 dir;
} ray;

//constructs Ray object, pointers or copies?
ray* rayConstructor(vec3* origin, vec3* dir);

void freeRay(ray* ray);

//finds the tip of a ray, t parametrizes direction vector
vec3 rayTip(float t, ray* ray1);
