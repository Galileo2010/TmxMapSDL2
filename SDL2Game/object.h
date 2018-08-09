#ifndef _CC_OBJECT_H_
#define _CC_OBJECT_H_

#include <string>
#include <vector>
#include <SDL.h>

#include "point.h"
#include "camera.h"
#include "timer.h"

namespace cc
{
/* ______\|/______
 *       /|\
 * */
enum Direction { LEFT, RIGHT, UP, DOWN, LEFT_UP, LEFT_DOWN, RIGHT_UP, RIGHT_DOWN };
const static Point DIR_LEFT(-1.0f, 0.0f);
const static Point DIR_RIGHT(1.0f, 0.0f);
const static Point DIR_UP(0.0f, -1.0f);
const static Point DIR_DOWN(0.0f, 1.0f);
const static Point DIR_LEFT_UP(-1.0f, -1.0f);
const static Point DIR_LEFT_DOWN(-1.0f, 1.0f);
const static Point DIR_RIGHT_UP(1.0f, -1.0f);
const static Point DIR_RIGHT_DOWN(1.0f, 1.0f);

class Object
{
public:
    Object(const std::string& name,
           SDL_Renderer* renderer,
           float speed = 0.0f,
           const Point& position = Point(0.0f, 0.0f));
    virtual ~Object();

public:
    static std::vector<Object*> objects;
    static std::vector<Object*> addedObjects;
    static void applyAdd();
    static void removeDead();
    static void removeAll();
    static void renderObjects(const Camera& camera);
    static void updateObjects(float deltaTime);

public:
    virtual void remove();
    virtual void update(float deltaTime);
    virtual void render(const Camera& camera) = 0;

public:
    virtual void move(const Point& amount);
    virtual void moveTo(const Point& position)
    {
        this->_position = position;
    }
    virtual void startMoving(const Point& direction);
    virtual void stopMoving();
    Direction getDirection() const;
    Point getPosition() const
    {
        return this->_position;
    }
    float getSpeen() const
    {
        return this->_speed;
    }
    bool isDead() const
    {
        return _dead;
    }

protected:
    std::string _name;
    bool _dead;
    float _speed;
    Point _position;
    Point _direction;
    bool _moving;

    SDL_Renderer* _renderer;
    Timer _timer;
};
};
#endif