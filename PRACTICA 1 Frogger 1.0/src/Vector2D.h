#pragma once
#include <iostream>
#include <vector>
#include "Vector2D.h"


template <class T>
class Vector2D {
public:
	T x;
	T y;

	Vector2D() : x(0), y(0) {}
	Vector2D(T x, T y) : x(x), y(y) {}
	Vector2D(const Vector2D<T>& v) : x(v.x), y(v.y) {}

	Vector2D<T> operator+(const Vector2D<T>& v) const {
		return Vector2D<T>(x + v.x, y + v.y);
	}

	Vector2D<T> operator-(const Vector2D<T>& v) const {
		return Vector2D<T>(x - v.x, y - v.y);
	}

	Vector2D<T> operator*(T n) const {
		return Vector2D<T>(x * n, y * n);
	}

	Vector2D<T> operator/(T n) const {
		return Vector2D<T>(x / n, y / n);
	}

	Vector2D<T>& operator+=(const Vector2D<T>& v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2D<T>& operator-=(const Vector2D<T>& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}

	Vector2D<T>& operator*=(T n) {
		x *= n;
		y *= n;
		return *this;
	}

	Vector2D<T>& operator/=(T n) {
		x /= n;
		y /= n;
		return *this;
	}

	bool operator==(const Vector2D<T>& v) const {
		return x == v.x && y == v.y;
	}

	bool operator!=(const Vector2D<T>& v) const {
		return x != v.x || y != v.y;
	}

	bool operator<(const Vector2D<T>& v) const {
		return x < v.x && y < v.y;
	}

	bool operator>(const Vector2D<T>& v) const {
		return x > v.x && y > v.y;
	}

	bool operator<=(const Vector2D<T>& v) const {
		return x <= v.x && y <= v.y;
	}

	bool operator>=(const Vector2D<T>& v) const {
		return x >= v.x && y >= v.y;
	}

	Vector2D<T> operator-() const {
		return Vector2D<T>(-x, -y);

	}

	//getters
	T getX() const { return x; }
	T getY() const { return y; }

	//setters
	void setX(T x) { this->x = x; }
	void setY(T y) { this->y = y; }

};
using Point2D = Vector2D<int>;
