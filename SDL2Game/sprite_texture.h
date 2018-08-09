#ifndef _CC_SPRITE_TEXTURE_H_
#define _CC_SPRITE_TEXTURE_H_

#include "exceptions.h"
#include "texture.h"

#include <map>

namespace cc
{
class SpriteTexture : public Texture
{
public:
    SpriteTexture(const std::string& name, SDL_Renderer* renderer)
        : Texture(renderer)
        , _tileWidth(0)
        , _tileHeight(0)
        , _rows(0)
        , _columns(0)
    {
    }
    virtual ~SpriteTexture()
    {
    }

public:
    static std::map<std::string, SpriteTexture*> textures;
    static void loadTexture(const std::string& name,
                            const std::string& path,
                            SDL_Renderer* renderer,
                            int tileWdth,
                            int tileHeight,
                            int rows,
                            int columns)
    {
        SpriteTexture* texture = new SpriteTexture(name, renderer);

        if(!texture->loadFromFile(path))
            throw cc::Exception("Texture could not be loaded!", path.c_str());

        texture->_tileWidth = tileWdth;
        texture->_tileHeight = tileHeight;
        texture->_rows = rows;
        texture->_columns = columns;

        textures[name] = texture;
    }
    static void unloadTextures()
    {
        std::map<std::string, SpriteTexture*> textures;
        for(std::map<std::string, SpriteTexture*>::iterator iter = textures.begin(); iter != textures.end();) {
            SpriteTexture* temp = (iter->second);
            delete temp;
            textures.erase(iter++);
        }
    }

public:
    int getTileWidth() const
    {
        return this->_tileWidth;
    }
    int getTileHeight() const
    {
        return this->_tileHeight;
    }
    int getRows() const
    {
        return this->_rows;
    }
    int getColumns() const
    {
        return this->_columns;
    }

protected:
    int _tileWidth;
    int _tileHeight;
    int _rows;
    int _columns;
};
};

#endif