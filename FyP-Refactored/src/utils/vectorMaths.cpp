#include "utils/vectorMaths.h"

float vectorLength(const Vector& t_v1)
{
	return sqrt(vectorLengthSquared(t_v1));
}

//**************************************************

float vectorLengthSquared(const Vector& t_v1)
{
	return powf(t_v1.x, 2) + powf(t_v1.y, 2);
}
