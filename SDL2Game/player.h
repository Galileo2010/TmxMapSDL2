#ifndef _CC_PLAYER_H_
#define _CC_PLAYER_H_

#include "object.h"
#include "sprite.h"

#include <string>
#include <SDL.h>

namespace cc
{

class Player : public Object
{
public:
    Player(const std::string& name, SDL_Renderer* renderer);
    virtual ~Player();

public:
    virtual void render(const Camera& camera);
    virtual void update(float deltaTime);
protected:
    virtual Sprite* getCurrentSprite();

protected:
    Sprite _movingLeftSprite;
    Sprite _movingRightSprite;
    Sprite _movingUpSprite;
    Sprite _movingDownSprite;
};
};

#endif