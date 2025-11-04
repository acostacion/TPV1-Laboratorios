#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <iostream>

/**
 * Vector bidimensional genérico.
 */
template<typename T = float>
class Vector2D
{
	T x, y;

public:
	Vector2D(T x, T y) : x(x), y(y) { }
	Vector2D() : Vector2D(0, 0) { }

	Vector2D<T> operator+(const Vector2D<T>& v) const {
		return Vector2D<T>(x + v.x, y + v.y);
	}

	Vector2D<T> operator-(const Vector2D<T>& v) const {
		return Vector2D<T>(x - v.x, y - v.y);
	}

	Vector2D<T> operator*(T n) const {
		return Vector2D<T>(x * n, y * n);
	}

	Vector2D<T> operator*(const Vector2D<T>& v) const {
		return Vector2D<T>(x * v.getX(), y * v.getY());
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

	// Operadores de entrada/salida
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v) {
		return out << '{' << v.x << ", " << v.y << '}';
	}

	//getters
	T getX() const { return x; }
	T getY() const { return y; }

	//setters
	void setX(T x) { this->x = x; }
	void setY(T y) { this->y = y; }
	void set(T t) { setX(t); setY(t); }
	void set(T x, T y) { setX(x); setY(y); }
};

using Point2D = Vector2D<int>;
#endif // VECTOR2D_H
