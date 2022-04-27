#pragma once

#include "SFML/Graphics.hpp"

using namespace sf;

enum class Pivots
{
	// L, CH, R
	// T, CV, R
	LT, CT, RT,
	LC, CC, RC,
	LB, CB, RB,
};

class Utils
{
public:
	static void SetOrigin(Text& text, Pivots preset);
	static void SetOrigin(Sprite& sprite, Pivots preset);
	static void SetOrigin(Shape& shape, Pivots preset);
	static void SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset);

	static int Random(int min, int max);

	static float GetLength(const Vector2f& vector);
	static Vector2f Normalize(Vector2f vector);
	static float GetAngle(const Vector2f& from, const Vector2f& to);
};

