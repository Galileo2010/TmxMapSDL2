#ifndef _CC_TEXTURE_H_
#define _CC_TEXTURE_H_

#include <string>
#include <inttypes.h>
#include <SDL.h>
#include <SDL_ttf.h>

namespace cc
{
class Texture
{
public:
    Texture(SDL_Renderer* renderer);
    virtual ~Texture();

public:
    virtual bool loadFromFile(const std::string& path);
    virtual bool loadFromText(const std::string& text, TTF_Font* font, SDL_Color color);
    virtual void free();
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(uint8_t alpha);
    void render(int x,
                int y,
                SDL_Rect* clip = NULL,
                double angle = 0.0,
                SDL_Point* center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
    void render(const SDL_Rect& src, const SDL_Rect& dest);
    int getWidth();
    int getHeight();

protected:
    SDL_Texture* _texture;
    SDL_Renderer* _renderer;
    int _width;
    int _height;
};
};
#endif