#include "texture.h"
#include "exceptions.h"
#include "logger.h"
#include <SDL_image.h>
#include <string>

cc::Texture::Texture(SDL_Renderer* renderer)
    : _texture(NULL)
    , _renderer(renderer)
    , _width(0)
    , _height(0)
{
}

cc::Texture::~Texture()
{
    this->free();
}

bool cc::Texture::loadFromFile(const std::string& path)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL) {
        cc::Logger::error("Failed to load image", IMG_GetError());
        return false;
    }
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
    if(newTexture == NULL) {
        cc::Logger::error("Failed to create texture:", SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }
    _width = loadedSurface->w;
    _height = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    _texture = newTexture;
    return true;
}

bool cc::Texture::loadFromText(const std::string& text, TTF_Font* font, SDL_Color color)
{
    this->free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    if(textSurface == NULL) {
        cc::Logger::error("Could not create text surface!", TTF_GetError());
        return false;
    }
    newTexture = SDL_CreateTextureFromSurface(this->_renderer, textSurface);
    if(newTexture == NULL) {
        cc::Logger::error("Could not create texture from surface:", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return false;
    }
    this->_width = textSurface->w;
    this->_height = textSurface->h;
    SDL_FreeSurface(textSurface);
    this->_texture = newTexture;
    return true;
}

void cc::Texture::free()
{
    if(_texture == NULL)
        return;
    SDL_DestroyTexture(_texture);
    _texture = NULL;
    _width = 0;
    _height = 0;
}

void cc::Texture::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    SDL_SetTextureColorMod(this->_texture, r, g, b);
}

void cc::Texture::setAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(this->_texture, alpha);
}

void cc::Texture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(this->_texture, blending);
}

void cc::Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = { x, y, _width, _height };
    if(clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(_renderer, _texture, clip, &renderQuad, angle, center, flip);
}

int cc::Texture::getWidth()
{
    return this->_width;
}

int cc::Texture::getHeight()
{
    return this->_height;
}
void cc::Texture::render(const SDL_Rect& src, const SDL_Rect& dest)
{
    SDL_RenderCopy(_renderer, _texture, &src, &dest);
}
