#pragma once

#include <cmath>
#include "../Prerequisites.h"

/**
 * @file CVector2.h
 * @brief Represents a custom 2D vector with common mathematical operations.
 */
class CVector2 {
public:
    float x;
    float y;

    // Constructors
    CVector2() : x(0.f), y(0.f) {}
    CVector2(float x, float y) : x(x), y(y) {}

    // Arithmetic operators
    CVector2 operator+(const CVector2& other) const { return CVector2(x + other.x, y + other.y); }
    CVector2 operator-(const CVector2& other) const { return CVector2(x - other.x, y - other.y); }
    CVector2 operator*(float scalar) const { return CVector2(x * scalar, y * scalar); }
    CVector2 operator/(float divisor) const { return CVector2(x / divisor, y / divisor); }

    // Compound assignment operators
    CVector2& operator+=(const CVector2& other) { x += other.x; y += other.y; return *this; }
    CVector2& operator-=(const CVector2& other) { x -= other.x; y -= other.y; return *this; }
    CVector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    CVector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    // Comparison
    bool operator==(const CVector2& other) const { return x == other.x && y == other.y; }
    bool operator!=(const CVector2& other) const { return !(*this == other); }

    // Index access
    float& operator[](int index) { return index == 0 ? x : y; }
    const float& operator[](int index) const { return index == 0 ? x : y; }

    // Geometric functions
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    float lengthSquared() const {
        return x * x + y * y;
    }

    float dot(const CVector2& other) const {
        return x * other.x + y * other.y;
    }

    float cross(const CVector2& other) const {
        return x * other.y - y * other.x;
    }

    CVector2 normalized() const {
        float len = length();
        return (len == 0.f) ? CVector2(0.f, 0.f) : (*this / len);
    }

    void normalize() {
        float len = length();
        if (len != 0.f) {
            x /= len;
            y /= len;
        }
    }

    // Static utility methods
    static float distance(const CVector2& a, const CVector2& b) {
        return (a - b).length();
    }

    static CVector2 lerp(const CVector2& a, const CVector2& b, float t) {
        if (t < 0.f) t = 0.f;
        if (t > 1.f) t = 1.f;
        return a + (b - a) * t;
    }

    static CVector2 zero() { return CVector2(0.f, 0.f); }
    static CVector2 one() { return CVector2(1.f, 1.f); }

    // Transform-style helpers
    void setPosition(const CVector2& position) { x = position.x; y = position.y; }
    void move(const CVector2& offset) { x += offset.x; y += offset.y; }
    void setScale(const CVector2& factors) { x = factors.x; y = factors.y; }
    void scale(const CVector2& factors) { x *= factors.x; y *= factors.y; }
    void setOrigin(const CVector2& origin) { x = origin.x; y = origin.y; }

private:
    // If you're implementing your own sqrt, move this to a utilities class
    float sqrt(float value) const {
        if (value <= 0.f) return 0.f;
        float guess = value / 2.f;
        for (int i = 0; i < 10; ++i)
            guess = 0.5f * (guess + value / guess);
        return guess;
    }
};
