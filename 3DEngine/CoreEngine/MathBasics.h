#pragma once
//Includes
#include <math.h>

//Define basic math operations
//Define PI
#define PI (3.142)
//Degrees to radians function
#define TO_RADIANS(x) (float)(((x) * PI / 180.0f))
//Radians to Degrees function
#define TO_DEGREES(x) (float)(((x) * 180.0f / PI))
//Get the size of an array
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))