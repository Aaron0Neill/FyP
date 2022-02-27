#ifndef VECTOR_MATHS_INCLUDE
#define VECTOR_MATHS_INCLUDE

#include "utils/vector.h"

/// <summary>
/// Calculate the length of a Vector 
/// </summary>
/// <param name="t_v1"> Vector to measure </param>
/// <returns> Length of the vector </returns>
float vectorLength(const Vector& t_v1);


float vectorLengthSquared(const Vector& t_v1);

float vector2Heading(const Vector& t_v);

float angleBetween(const Vector& t_v1, const Vector& t_v2);



#endif