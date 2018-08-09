#ifndef _CC_SPRITE_H_
#define _CC_SPRITE_H_

#include <string>
#include <SDL.h>

#include "point.h"
#include "sprite_texture.h"
#include "camera.h"

namespace cc
{
class Sprite
{
public:
    Sprite(const std::string& name, int groupIndex, int frameCount, int frameInterval);
    ~Sprite();

public:
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, const Camera& camera, const Point& position, bool animate = true);

protected:
    std::string _name;
    SpriteTexture* _texture;
    int _groupIndex;
    int _currentFrame;
    int _frameCount;
    float _frameInterval;
    float _frameTimeRemaining;
};
};
#endif