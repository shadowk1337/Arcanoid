#pragma once

#include "Scrap.h"
#include <utility>

struct Point {
    float x = 0;
    float y = 0;

    friend Point operator+(const Point& lhs, const Point& rhs) {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    friend Point operator+(const Point& lhs, const float& rhs) {
        return {lhs.x + rhs, lhs.y + rhs};
    }


    friend Point operator*(const Point& lhs, const float& rhs) {
        return {lhs.x * rhs, lhs.y * rhs};
    }

    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    bool operator!() const {
        return x == 0.0 && y == 0.0;
    }

    Point operator-() const {
        return {-x, -y};
    }

    float Dot(const Point& other) const {
        return x * other.x + y * other.y;
    }

    float Magnitude() const {
        return std::sqrt(Dot(*this));
    }

    Point Normalize() const {
        auto magnitude = Magnitude();
        return Point{x / magnitude, y / magnitude};
    }

    void SimpleReflect(bool isHorizontal) {
        if (isHorizontal) {
            y = -y;
        } else {
            x = -x;
        }
    }

    static Point Random(float x0 = 0.0f, float x1 = 1.0f, float y0 = 0.0f, float y1 = 1.0f) {
        return Point{RandomFloat(x0, x1), RandomFloat(y0, y1)};
    }

    // To find orientation of ordered triplet (p, q, r).
    // The function returns following values
    // 0 --> p, q and r are collinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    static int Orientation(Point p, Point q, Point r) {
        float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (val == 0.0f) return 0;  // collinear
        return (val > 0.0f) ? 1 : 2; // clock or counterclock wise
    }
};

class Vector {
public:
    Vector(const Point& start, const Point& end)
            : m_start(start)
            , m_end(end) {

    }

    Vector(Point&& start, Point&& end)
            : m_start(start)
            , m_end(end) {

    }

    bool OnVector(const Point& point) const {
        if (point.x <= std::max(m_start.x, m_end.x) && point.x >= std::min(m_start.x, m_end.x) &&
            point.y <= std::max(m_start.y, m_end.y) && point.y >= std::min(m_start.y, m_end.y))
            return true;

        return false;
    }

    bool IsIntersect(const Vector& other) const
    {
        // Find the four orientations needed for general and special cases
        int o1 = Point::Orientation(m_start, m_end, other.m_start);
        int o2 = Point::Orientation(m_start, m_end, other.m_end);
        int o3 = Point::Orientation(other.m_start, other.m_end, m_start);
        int o4 = Point::Orientation(other.m_start, other.m_end, m_end);

        // General case
        if (o1 != o2 && o3 != o4)
            return true;

        // Special Cases
        // m_start, m_end and other.m_start are collinear and other.m_start lies on segment m_startm_end
        if (o1 == 0 && OnVector(other.m_start)) return true;

        // m_start, m_end and other.m_end are collinear and other.m_end lies on segment m_startm_end
        if (o2 == 0 && OnVector(other.m_end)) return true;

        // other.m_start, other.m_end and m_start are collinear and m_start lies on segment other.m_startother.m_end
        if (o3 == 0 && other.OnVector(m_start)) return true;

        // other.m_start, other.m_end and m_end are collinear and m_end lies on segment other.m_startother.m_end
        if (o4 == 0 && other.OnVector(m_end)) return true;

        return false; // Doesn't fall in any of the above cases
    }

    bool IsHorizontal() const { return m_start.y == m_end.y; }

    bool IsVertical() const { return m_start.x == m_end.x; }

private:
    Point m_start = {};
    Point m_end = {};
};