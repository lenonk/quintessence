//
// Created by lenon on 8/16/17.
//

#ifndef QUINTESSENCE_GAME_H
#define QUINTESSENCE_GAME_H

#include <SFML/Graphics.hpp>

#include "config.h"
#include "screenmanager.h"
#include "resourcemanager.h"

enum GameState {
    None,
    SplashState,
    TitleState,
    PlayState,
};

class Game {
public:
    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;

    static Game &get() {
        static Game instance;
        return instance;
    }

    ~Game() = default;

    void run();
    void input_phase();
    void update_phase(float delta_time);
    void draw_phase();
    void stop();

    void addState(GameState state);
    void popState();
    void changeState(GameState state);

    sf::RenderWindow &getWindow() { return m_window; }
    Resource::ResourceManager &resources() { return m_resource_manager; };

private:
    enum ChangeMode {
        None,
        Push,
        Pop,
        Change
    };

    GameState m_state = GameState::None;
    ChangeMode m_change_mode = ChangeMode::None;
    std::shared_ptr<ScreenManager> m_screen_manager;
    Resource::ResourceManager m_resource_manager;

    sf::RenderWindow m_window{Config::inst().video_mode, "Quintessence"};
    bool m_running{false};

    Game() {
        m_resource_manager.initialize();
        m_window.setFramerateLimit(Config::inst().frame_limit);
        m_window.setKeyRepeatEnabled(false);
    }
};

#endif //QUINTESSENCE_GAME_H
