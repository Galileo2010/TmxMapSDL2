#ifndef _GAME_H_
#define _GAME_H_

#include "camera.h"
#include "map.h"
#include "timer.h"
#include "player.h"

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

namespace cc
{
enum GameState { PLAYING, PAUSED, GAMEOVER, READY };

class Game
{
public:
    Game(const std::string& name, int width, int height, bool fullScreen = false);
    ~Game();

private:
    void init(bool fullScreen);
    void deinit();
    void loadMedia();
    void unloadMedia();

public:
    SDL_Window* getWindow();
    SDL_Renderer* getRenderer();
    TTF_Font* getFont();
    const Camera& getCamera() const;

public:
    void handleEvents();
    void update();
    void render();
    void execute();

private:
    void onKeyDown(const SDL_Event& e);
    void onKeyUp(const SDL_Event& e);

public:
    void moveCamera(int x, int y);
    void scale(float p);

private:
    std::string _name;
    int _width;
    int _height;

    SDL_Window* _window;
    SDL_Renderer* _renderer;
    TTF_Font* _font;

    bool _quit;

    Camera _camera;
    Timer _timer;
    int _frame;

    Map* _map;
    Player* _player;
};
};

#endif