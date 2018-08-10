#include "player.h"
#include "logger.h"

cc::Player::Player(const std::string& name, SDL_Renderer* renderer)
    : cc::Object(name, renderer, 1.2)
    , _movingLeftSprite(cc::Sprite(name, 1, 4, 200))
    , _movingRightSprite(cc::Sprite(name, 2, 4, 200))
    , _movingUpSprite(cc::Sprite(name, 3, 4, 200))
    , _movingDownSprite(cc::Sprite(name, 0, 4, 200))
{
}

cc::Player::~Player()
{
}

void cc::Player::render(const Camera& camera)
{
    cc::Sprite* sprite = this->getCurrentSprite();
    if(sprite != NULL)
        sprite->render(this->_renderer, camera, this->_position, this->_moving);
}
void cc::Player::update(float deltaTime)
{
    cc::Object::update(deltaTime);
    cc::Sprite* sprite = this->getCurrentSprite();
    if(sprite != NULL)
        sprite->update(deltaTime);
}
cc::Sprite* cc::Player::getCurrentSprite()
{
    cc::Direction d = this->getDirection();
    switch(d) {
    case UP:
        return &this->_movingUpSprite;
    case DOWN:
        return &this->_movingDownSprite;
        break;
    case LEFT:
        return &this->_movingLeftSprite;
        break;
    case RIGHT:
        return &this->_movingRightSprite;
        break;
    default:
        break;
    }
    return NULL;
}
