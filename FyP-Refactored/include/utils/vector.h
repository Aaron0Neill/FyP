#ifndef VECTOR_INCLUDE
#define VECTOR_INCLUDE

#include "globals.h"
#include <sstream>

#include <box2d/b2_math.h>
#include <SFML/System/Vector2.hpp>

class Vector 
{
public:
	float x, y;

	Vector	() = default;
	~Vector	() = default;
	Vector	(float t_x, float t_y)			: x(t_x), y(t_y) {};
	Vector	(b2Vec2 t_vec)					: x(t_vec.x), y(t_vec.y) {};
	Vector	(sf::Vector2f t_vec)				: x(t_vec.x), y(t_vec.y) {};
	Vector	(sf::Vector2i t_vec)				: x((float)t_vec.x), y((float)t_vec.y) {};
	Vector	(sf::Vector2u t_vec)				: x((float)t_vec.x), y((float)t_vec.y) {};


	inline Vector toWorldSpace()	{ return {x / PixelsPerMetre, y / PixelsPerMetre}; }

	inline Vector fromWorldSpace()	{ return { x * PixelsPerMetre, y * PixelsPerMetre }; }

	inline float magnitude()		{ return sqrt(powf(x, 2) + powf(y, 2)); }

	inline float direction()		{ return atan2f(y, x); }

	inline std::string toString()
	{
		std::stringstream ss;
		ss << x << ", " << y;
		return ss.str();
	}

	static inline float magnitude(Vector t_from, Vector t_to)
	{
		Vector diff = t_from - t_to;
		return sqrt(powf(diff.x,2) + powf(diff.y, 2));
	}

	Vector	operator-	(float t_rhs)	{ return { x - t_rhs, y - t_rhs }; }
	Vector	operator-	(Vector t_rhs)	{ return { x - t_rhs.x, y - t_rhs.y }; }
	Vector	operator*	(float t_rhs)	{ return { x * t_rhs, y * t_rhs }; }
	Vector	operator/	(float t_rhs)	{ return { x / t_rhs, y / t_rhs }; }
	void	operator+=	(Vector t_rhs)	{ x += t_rhs.x; y += t_rhs.y; }
	void	operator/=	(float t_rhs)	{ x /= t_rhs; y /= t_rhs; }

	// = operator
	Vector	operator=	(b2Vec2& t_rhs)			{ return { t_rhs }; };
	Vector	operator=	(sf::Vector2u& t_rhs)	{ return { t_rhs }; };

	// implicit conversion
	operator b2Vec2()			{ return { x,y }; };
	operator sf::Vector2f()		{ return { x,y }; };
	operator sf::Vector2i()		{ return { (int)x,(int)y }; };
};

#endif