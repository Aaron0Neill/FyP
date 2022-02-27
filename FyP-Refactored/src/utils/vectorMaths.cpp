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

//**************************************************

float vector2Heading(const Vector& t_v)
{
	return atan2f(t_v.y, t_v.x);
}

//**************************************************

float angleBetween(const Vector& t_v1, const Vector& t_v2)
{
	return 0.0f;
}
