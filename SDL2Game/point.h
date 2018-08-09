#ifndef _CC_POINT_H_
#define _CC_POINT_H_

#include <math.h>

namespace cc
{
class Point
{
public:
    Point(float x = 0.0f, float y = 0.0f)
        : _x(x)
        , _y(y)
    {
    }
    Point(const Point& p)
    {
        this->_x = p._x;
        this->_y = p._y;
    }
    ~Point(){};

public:
    float getX() const
    {
        return this->_x;
    };
    float getY() const
    {
        return this->_y;
    }
    void setX(float x)
    {
        this->_x = x;
    }
    void setY(float y)
    {
        this->_y = y;
    }

    Point operator+(const Point& v)
    {
        Point p;
        p._x = _x + v._x;
        p._y = _y + v._y;
        return p;
    }
    Point operator*(const Point& v)
    {
        Point p;
        p._x = _x * v._x;
        p._y = _y * v._y;
        return p;
    }
    void operator=(const Point& v)
    {
        _x = v._x;
        _y = v._y;
    }

    void operator+=(const Point& v)
    {
        _x += v._x;
        _y += v._y;
    }

    float length() const
    {
        return sqrt(_x * _x + _y * _y);
    }
    void normalize()
    {
        float length = this->length();
        if(length < 0)
            return;
        _x /= length;
        _y /= length;
    }

protected:
    float _x;
    float _y;
};

};
#endif