#pragma once
#include <math.h>

#define PI (3.142)
#define TO_RADIANS(x) (float)(((x) * PI / 180.0f))
#define TO_DEGREES(x) (float)(((x) * 180.0f / PI))
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))