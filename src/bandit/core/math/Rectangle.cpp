#include "bandit/core/math/Rectangle.h"

Rectangle::Rectangle() :
    vector(0, 0), w(0), h(0)
{
}

Rectangle::Rectangle(float x, float y) :
    vector(Vector(x, y)), w(0), h(0)
{
}

Rectangle::Rectangle(const Vector& vector) :
    vector(vector), w(0), h(0)
{
}

Rectangle::Rectangle(float x, float y, float w, float h) :
    vector(Vector(x, y)), w(w), h(h)
{
}

Rectangle::Rectangle(const Vector& vector, float w, float h) :
    vector(vector), w(w), h(h)
{
}

float Rectangle::GetW() const
{
    return w;
}

void Rectangle::SetW(float w)
{
    this->w = w;
}

float Rectangle::GetH() const
{
    return h;
}

void Rectangle::SetH(float h)
{
    this->h = h;
}

void Rectangle::SetCenter(const Vector& centerPoint)
{
    this->vector.SetX(centerPoint.GetX() - w/2.0);
    this->vector.SetY(centerPoint.GetY() - h/2.0);
}

Vector Rectangle::GetCenter() const
{
    Vector centerPoint;
    centerPoint.SetX(vector.GetX() + w/2.0);
    centerPoint.SetY(vector.GetY() + h/2.0);
    return centerPoint;
}

void Rectangle::SetCenterAndDimensions(const Vector& centerPoint, float w, float h)
{
    this->vector.SetX(centerPoint.GetX() - w/2.0);
    this->vector.SetY(centerPoint.GetY() - h/2.0);
    this->w = w;
    this->h = h;
}

Vector Rectangle::GetTopLeft() const
{
    return vector;
}

void Rectangle::SetTopLeft(const Vector& vector)
{
    this->vector = vector;
}

Vector Rectangle::GetTopRight() const
{
    return Vector(vector.GetX() + w, vector.GetY());
}

Vector Rectangle::GetBottomLeft() const
{
    return Vector(vector.GetX(), vector.GetY() + h);
}

Vector Rectangle::GetBottomRight() const
{
    return Vector(vector.GetX() + w, vector.GetY() + h);
}

bool Rectangle::IsInside(const Vector& vector) const
{
    return (vector.GetX() >= this->vector.GetX() and vector.GetX() <= this->vector.GetX() + w and
            vector.GetY() >= this->vector.GetY() and vector.GetY() <= this->vector.GetY() + h);
}

bool Rectangle::Overlaps(const Rectangle& other) const
{
    if (IsInside(other.GetTopLeft()) || IsInside(other.GetTopRight()) ||
        IsInside(other.GetBottomLeft()) || IsInside(other.GetBottomRight()))
        return true;

    return false;
}

std::string Rectangle::ToString() const
{
    char buffer[64];
    sprintf(buffer, "(x: %f, y: %f, w: %f, h: %f)", vector.GetX(), vector.GetY(), w, h);
    std::string stringBuffer = buffer;

    return stringBuffer;
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle)
{
    os << rectangle.ToString();
    return os;
}