#include "Utils.h"
#include <random>

void Utils::SetOrigin(Text& text, Pivots preset)
{
	SetOrigin(text, text.getLocalBounds(), preset);
}

void Utils::SetOrigin(Sprite& sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);
}

void Utils::SetOrigin(Shape& shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}

void Utils::SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset)
{
	float wc = bounds.width * 0.5f;
	float hc = bounds.height * 0.5f;

	float w = bounds.width;
	float h = bounds.height;

	switch (preset)
	{
	case Pivots::LT:
		tr.setOrigin(0.f, 0.f);
		break;
	case Pivots::CT:
		tr.setOrigin(wc, 0.f);
		break;
	case Pivots::RT:
		tr.setOrigin(w, 0.f);
		break;
	case Pivots::LC:
		tr.setOrigin(0.f, hc);
		break;
	case Pivots::CC:
		tr.setOrigin(wc, hc);
		break;
	case Pivots::RC:
		tr.setOrigin(w, hc);
		break;
	case Pivots::LB:
		tr.setOrigin(0.f, h);
		break;
	case Pivots::CB:
		tr.setOrigin(wc, h);
		break;
	case Pivots::RB:
		tr.setOrigin(w, h);
		break;
	default:
		break;
	}
}

int Utils::Random(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int radios = max - min;
	return min + gen() % radios;
}

float Utils::GetLength(const Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);;
}

Vector2f Utils::Normalize(Vector2f vector)
{
	float length = GetLength(vector);
	if (length != 0.f)
	{
		return vector /= length;
	}
	return vector;
}

float Utils::GetAngle(const Vector2f& from, const Vector2f& to)
{
	Vector2f dir = to - from;
	float radian = atan2(dir.y, dir.x);
	float degree = radian * 180.f / 3.141592f;
	return degree;
}

