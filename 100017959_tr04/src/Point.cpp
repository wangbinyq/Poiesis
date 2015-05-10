// @file   Point.cpp
// @author Matheus Vieira Portela
// @date   31/03/2015
//
// @brief Rectangle in 2-dimensional space

#include "Point.h"

Point::Point() : x(0), y(0) {}

Point::Point(float x, float y) : x(x), y(y) {}

Point::Point(const Point& other) : x(other.x), y(other.y) {}

float Point::GetX() const
{
    return x;
}

void Point::SetX(float x)
{
    this->x = x;
}

float Point::GetY() const
{
    return y;
}

void Point::SetY(float y)
{
    this->y = y;
}

void Point::Set(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Point::Set(Point point)
{
    this->x = point.x;
    this->y = point.y;
}

void Point::SetPolar(float r, float ang)
{
    this->x = r*cos(ang);
    this->y = r*sin(ang);
}

void Point::Add(Point point)
{
    this->x += point.GetX();
    this->y += point.GetY();
}

void Point::Subtract(Point point)
{
    this->x -= point.GetX();
    this->y -= point.GetY();
}

void Point::Multiply(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
}

void Point::Divide(float scalar)
{
    if (scalar == 0.0)
    {
        LOG_E("[Point] Division by zero");
        exit(1);
    }

    this->x /= scalar;
    this->y /= scalar;
}

void Point::Negate()
{
    Multiply(-1);
}

float Point::CalculateDistance(Point point) const
{
    return hypot(point.x - x, point.y - y);
}

std::string Point::ToString() const
{
    char buffer[64];
    sprintf(buffer, "(%f, %f)", x, y);
    std::string stringBuffer = buffer;

    return stringBuffer;
}