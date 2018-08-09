#include "map.h"
#include "exceptions.h"
#include "logger.h"

cc::Map::Map(const std::string& path, SDL_Renderer* renderer)
    : cc::Object("", renderer)
    , _path(path)
    , _showGrid(false)
{
    ;
    if(!this->_map.load(this->_path))
        throw cc::Exception("Failed to parse map:", this->_path.c_str());
    this->loadMedia();
}

cc::Map::~Map()
{
    for(std::vector<cc::Texture*>::iterator iter = this->_mapTilesets.begin(); iter < this->_mapTilesets.end();) {
        cc::Texture* temp = (*iter);
        this->_mapTilesets.erase(iter);
        delete temp;
        iter = this->_mapTilesets.begin();
    }
}

void cc::Map::loadMedia()
{
    /*std::vector<tmx::Tileset*> tilesets = this->_map.GetTilesets();
    for(unsigned int i = 0; i < tilesets.size(); i++) {
        const tmx::Tileset* tileset = tilesets.at(i);
        cc::Texture* texture = new cc::Texture(this->_renderer);
        this->_mapTilesets.push_back(texture);
        if(!texture->loadFromFile(tileset->GetImage()->GetSource()))
            throw cc::Exception("Failed to load image:", tileset->GetImage()->GetSource().c_str());
    }*/
	// 初始化_mapTilesets
	const std::vector<tmx::Tileset>& tilesets = this->_map.getTilesets();
	for (const auto& item : tilesets)
	{
		cc::Texture* texture = new cc::Texture(this->_renderer);
		this->_mapTilesets.push_back(texture);
		if (!texture->loadFromFile(item.getImagePath()))
			throw cc::Exception("Failed to load image:", item.getImagePath().c_str());
	}
}

void cc::Map::render(const cc::Camera& camera)
{
    /*std::vector<tmx::Layer*> layers = this->_map.GetLayers();
    for(std::vector<tmx::Layer*>::iterator iter = layers.begin(); iter != layers.end(); ++iter) {
        tmx::Layer* layer = (*iter);
        if(layer->IsVisible())
            this->drawLayer(layer, camera);
    }
    this->drawGrid(camera);*/

	// 渲染
	const auto layers = this->_map.getLayers();
	for (const auto& layer : layers)
	{
		if (layer->getVisible())
			this->drawLayer(layer, camera);
	}
	this->drawGrid(camera);
}
void cc::Map::drawLayer(const tmx::Layer::Ptr& layer, const cc::Camera& camera)
{
    if(layer->getType() == tmx::Layer::Type::Tile)
        this->drawTileLayer(dynamic_cast<tmx::TileLayer*>layer, camera);
}
void cc::Map::drawTileLayer(tmx::TileLayer* layer, const cc::Camera& camera)
{
    SDL_Rect srcRect, destRect;
    int offset = (this->_map.getTileSize().x / 2.0f) * (_map.getBounds().height) / 2;
    for(int x = 0; x < layer->GetWidth(); x++) {
        for(int y = 0; y < layer->GetHeight(); y++) {
            tmx::MapTile tile = layer->GetTile(x, y);

            if(tile.gid != 0) {
                cc::Texture* texture = this->_mapTilesets.at(tile.tilesetId);
                const tmx::Tileset* tileset = this->_map.GetTileset(tile.tilesetId);
                int tileIndex = tile.gid - tileset->GetFirstGid();
                // TODO: if map version < 0.15 then GetColumns() returns 0
                int tileX = tileIndex % tileset->GetColumns(), tileY = tileIndex / tileset->GetColumns();
                srcRect.x = tileset->GetTileWidth() * tileX;
                srcRect.y = tileset->GetTileHeight() * tileY;
                srcRect.w = tileset->GetTileWidth();
                srcRect.h = tileset->GetTileHeight();
                Point p = this->projection(x, y);
                destRect.x = p.getX();
                destRect.y = p.getY();
                if(this->_map.getOrientation() == tmx::Orientation::Isometric)
                    destRect.x += offset;

                destRect.x -= tileset->GetTileOffset()->GetX();
                destRect.y -= tileset->GetTileOffset()->GetY();

                camera.apply(srcRect, &destRect);

                texture->render(srcRect, destRect);
            }
        }
    }
}

// 计算点（x,y）在屏幕上的投影 
cc::Point cc::Map::projection(int x, int y)
{
    Point p;
    if(this->_map.getOrientation() == tmx::Orientation::Isometric) {
        // isometric
        // x = (tile_width /2)*(i-j)
        // y = (tile_height/2)*(i+j)
        // i = 0.5*(y/(tile_height/2)+x/(tile_width/2))
        // j = 0.5*(y/(tile_height/2)-x/(tile_width/2))

        p.setX((this->_map.getTileSize().x / 2.0f) * (x - y));
        p.setY((this->_map.getTileSize().y / 2.0f) * (x + y));
    }
    if(this->_map.getOrientation() == tmx::Orientation::Orthogonal) {
        p.setX(this->_map.getTileSize().x * x);
        p.setY(this->_map.getTileSize().y * y);
    }
    return p;
}
void cc::Map::drawGrid(const cc::Camera& camera)
{
    int mapOffset = (this->_map.getTileSize().x / 2.0f) * (_map.getBounds().height) / 2;
    float tileOffset = this->_map.getTileSize().x / 2.0f;
    int offset = tileOffset;
    if(this->_map.getOrientation() == tmx::Orientation::Isometric)
        offset += mapOffset;
    for(int x = 0; x <= this->_map.getBounds().width; x++) {
        Point p1 = this->projection(x, 0);
        Point p2 = this->projection(x, _map.getBounds().height);

        p1.setX(p1.getX() + offset);
        p2.setX(p2.getX() + offset);
        camera.apply(&p1);
        camera.apply(&p2);
        SDL_RenderDrawLine(this->_renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
    for(int y = 0; y <= _map.getBounds().height; y++) {
        Point p1 = this->projection(0, y);
        Point p2 = this->projection(_map.getBounds().width, y);

        p1.setX(p1.getX() + offset);
        p2.setX(p2.getX() + offset);
        camera.apply(&p1);
        camera.apply(&p2);
        SDL_RenderDrawLine(this->_renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
}
