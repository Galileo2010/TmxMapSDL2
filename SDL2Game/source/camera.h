#ifndef _CC_CAMERA_H_
#define _CC_CAMERA_H_

#include "point.h"

#include <SDL.h>

namespace cc
{
class Camera
{
public:
    Camera(float width, float height, float scaling = 1.0f)
        : _width(width)
        , _height(height)
        , _scaling(scaling)
    {
        this->_bound.x = 0;
        this->_bound.y = 0;
        this->_bound.w = this->_width;
        this->_bound.h = this->_height;
    }
    ~Camera()
    {
    }

public:
    void moveTo(float x, float y)
    {
        this->_bound.x = x;
        this->_bound.y = y;
    }
    void scale(float p)
    {
        this->_scaling = p;
    }
    const SDL_Rect& getBound() const
    {
        return this->_bound;
    }

    float getWidth() const
    {
        return this->_width;
    }

    float getHeight() const
    {
        return this->_height;
    }

    float getScaling() const
    {
        return this->_scaling;
    }

    void apply(const SDL_Rect& src, SDL_Rect* dest) const
    {
        dest->w = src.w * this->_scaling;
        dest->h = src.h * this->_scaling;
        dest->x = (dest->x - this->_bound.x) * this->_scaling;
        dest->y = (dest->y - this->_bound.y) * this->_scaling;
    }

    void apply(Point* point) const
    {
        point->setX((point->getX() - this->_bound.x) * this->_scaling);
        point->setY((point->getY() - this->_bound.y) * this->_scaling);
    }
    void move(const Point& delta)
    {
        this->_bound.x += delta.getX();
        this->_bound.y += delta.getY();
    }

protected:
    float _width;
    float _height;
    float _scaling;
    SDL_Rect _bound;
};
};
#endif