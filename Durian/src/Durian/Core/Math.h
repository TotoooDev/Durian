#pragma once

namespace Durian
{
	template <typename T>
	class Vec2
	{
	public:
		Vec2() = default;
		Vec2(T _x, T _y) : x(_x), y(_y)  {}
		Vec2(T _x) : x(_x), y(_x) {}

		T x, y;

		bool operator==(const Vec2& lhs) const { return x == lhs.x && y == lhs.y; }
		bool operator!=(const Vec2& lhs) const { return x != lhs.x || y != lhs.y; }
		const Vec2& operator+(const Vec2& lhs) const { return Vec2(x + lhs.x, y + lhs.y); }
		const Vec2& operator-(const Vec2& lhs) const { return Vec2(x - lhs.x, y - lhs.y); }
		template <typename U>
		const Vec2& operator*(const U& lhs) const { return Vec2(x * lhs, y * lhs); }
		template <typename U>
		const Vec2& operator/(const U& lhs) const { return Vec2(x / lhs, y / lhs); }
	};

	class Color
	{
	public:
		Color() = default;
		Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}
		Color(float x) : r(x), g(x), b(x), a(x) {}

		float r, g, b, a;

		bool operator==(const Color& lhs) const { return r == lhs.r && g == lhs.g && b == lhs.b && a == lhs.a; }
		bool operator!=(const Color& lhs) const { return r != lhs.r || g != lhs.g; }
		const Color& operator+(const Color& lhs) const { return Color(r + lhs.r, g + lhs.g, b + lhs.b, a + lhs.a); }
		const Color& operator-(const Color& lhs) const { return Color(r - lhs.r, g - lhs.g, b - lhs.b, a - lhs.a); }
	};
}