#include "game.h"
#include "logger.h"
#include "object.h"
#include "exceptions.h"

#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>

cc::Game::Game(const std::string& name, int width, int height, bool fullScreen)
    : _name(name)
    , _width(width)
    , _height(height)
    , _window(NULL)
    , _renderer(NULL)
    , _font(NULL)
    , _quit(false)
    , _camera(Camera(width, height, 1.0f))
    , _frame(0)
    , _map(NULL)
    , _player(NULL)
{
    this->init(fullScreen);
    this->loadMedia();
    this->_timer.start();
}

cc::Game::~Game()
{
    this->deinit();
    this->unloadMedia();
}

void cc::Game::init(bool fullScreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw Exception("Failed to initialize SDL:", SDL_GetError());
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        Logger::log("Warning: Linear texture filtering not enabled!");
    int windowFlag = SDL_WINDOW_SHOWN;
    if(fullScreen)
        windowFlag |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    _window = SDL_CreateWindow(
        this->_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->_width, this->_height, windowFlag);
    if(_window == NULL)
        throw Exception("Window could not be created:", SDL_GetError());

    //_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(_renderer == NULL)
        throw Exception("Renderer could not be created:", SDL_GetError());

    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if((IMG_Init(imgFlags) & imgFlags) != imgFlags)
        throw Exception("SDL image could not be initialized!", IMG_GetError());

    if(TTF_Init() == -1)
        throw Exception("SDL ttf could not be initlalized!", TTF_GetError());
    Logger::log("Environment initialization finished.");
}

void cc::Game::deinit()
{
    cc::Logger::log("Clearing loaded resources ...");
    if(_renderer != NULL) {
        SDL_DestroyRenderer(_renderer);
        _renderer = NULL;
    }
    if(_window != NULL) {
        SDL_DestroyWindow(_window);
        _window = NULL;
    }
    if(this->_font != NULL) {
        TTF_CloseFont(this->_font);
        this->_font = NULL;
    }
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    cc::Logger::log("Game deinited!");
}

void cc::Game::loadMedia()
{
    this->_map = new cc::Map("../res/maps/2d.tmx", this->_renderer);
    cc::SpriteTexture::loadTexture("player1", "../res/players/player.png", this->_renderer, 90, 90, 4, 4);
    this->_player = new cc::Player("player1", _renderer);
    this->_player->moveTo(cc::Point(100, 100));
}

void cc::Game::unloadMedia()
{
    cc::Object::removeAll();
    cc::SpriteTexture::unloadTextures();
}

void cc::Game::handleEvents()
{
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT)
            this->_quit = true;
        else if(e.type == SDL_KEYDOWN)
            this->onKeyDown(e);
        else if(e.type == SDL_KEYUP)
            this->onKeyUp(e);
    }
}

void cc::Game::update()
{
    int deltaTime = this->_timer.getDeltaTime();
    cc::Object::updateObjects(deltaTime);
    ++this->_frame;
}

void cc::Game::render()
{
    SDL_SetRenderDrawColor(this->_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(this->_renderer);
    SDL_SetRenderDrawColor(this->_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    cc::Object::renderObjects(this->_camera);
    SDL_RenderPresent(this->_renderer);
}

void cc::Game::execute()
{
    while(!this->_quit) {
        this->handleEvents();
        this->update();
        this->render();
        // SDL_Delay(10);
    }
}
SDL_Window* cc::Game::getWindow()
{
    return this->_window;
}
SDL_Renderer* cc::Game::getRenderer()
{
    return this->_renderer;
}
TTF_Font* cc::Game::getFont()
{
    return this->_font;
}
const cc::Camera& cc::Game::getCamera() const
{
    return this->_camera;
}
void cc::Game::moveCamera(int x, int y)
{
    this->_camera.move(Point(x, y));
}
void cc::Game::scale(float p)
{
    float newScaling = this->_camera.getScaling() + p;
    if(newScaling > 3 || newScaling < 1 / 8.0f)
        return;
    this->_camera.scale(newScaling);
}
void cc::Game::onKeyDown(const SDL_Event& e)
{
    const int cameraSpeed = 5;
    switch(e.key.keysym.sym) {
    case SDLK_LEFT:
        this->moveCamera(cameraSpeed, 0);
        break;
    case SDLK_RIGHT:
        this->moveCamera(-cameraSpeed, 0);
        break;
    case SDLK_UP:
        this->moveCamera(0, cameraSpeed);
        break;
    case SDLK_DOWN:
        this->moveCamera(0, -cameraSpeed);
        break;
    case SDLK_LEFTBRACKET:
        this->scale(1 / 16.0f);
        break;
    case SDLK_RIGHTBRACKET:
        this->scale(-1 / 16.0f);
        break;
    case SDLK_w:
        this->_player->startMoving(cc::DIR_UP);
        break;
    case SDLK_s:
        this->_player->startMoving(cc::DIR_DOWN);
        break;
    case SDLK_a:
        this->_player->startMoving(cc::DIR_LEFT);
        break;
    case SDLK_d:
        this->_player->startMoving(cc::DIR_RIGHT);
        break;
    default:
        break;
    }
}

void cc::Game::onKeyUp(const SDL_Event& e)
{
    switch(e.key.keysym.sym) {
    case SDLK_w:
    case SDLK_s:
    case SDLK_a:
    case SDLK_d:
        this->_player->stopMoving();
        break;
    default:
        break;
    }
}
