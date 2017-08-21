//
// Created by lenon on 8/16/17.
//

#include "game.h"
#include "splashscreen.h"
#include "titlescreen.h"
#include "playscreen.h"

void
Game::run() {
    m_running = true;

    float delta_time = 0;
    sf::Clock clock;

    m_screen_manager = std::make_shared<ScreenManager>();

    addState(GameState::SplashState);

    while (m_running) {
        delta_time = clock.restart().asSeconds();
        m_window.clear(sf::Color::Black);

        input_phase();
        update_phase(delta_time);
        draw_phase();
    }

    m_window.close();
}

void
Game::stop() {
    m_running = false;
}

void
Game::input_phase() {
    sf::Event e;

    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_running = false;
            break;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) m_running = false;
}

void
Game::update_phase(float delta_time) {
    std::function<void(std::shared_ptr<GameScreen>)> changeFunc = nullptr;

    switch (m_change_mode) {
        case ChangeMode::Push:
            changeFunc = std::bind(&ScreenManager::pushScreen, m_screen_manager, std::placeholders::_1);
            break;
        case ChangeMode::Change:
            changeFunc = std::bind(&ScreenManager::changeScreen, m_screen_manager, std::placeholders::_1);
            break;
        case ChangeMode::Pop:
            m_screen_manager->popScreen();
            m_change_mode = ChangeMode::None;
            // TODO:  Gamestate should change to whatever state was next on the stack
            m_state = GameState::None;
            changeFunc = nullptr;
            break;
        case ChangeMode::None:
        default:
            changeFunc = nullptr;
            break;
    }
    m_change_mode = ChangeMode::None;

    if (changeFunc != nullptr) {
        switch (m_state) {
            case GameState::TitleState:
                changeFunc(std::make_shared<TitleScreen>());
                m_state = GameState::TitleState;
                break;
            case GameState::SplashState:
                changeFunc(std::make_shared<SplashScreen>());
                m_state = GameState::SplashState;
                break;
            case GameState::PlayState:
                changeFunc(std::make_shared<PlayScreen>());
                m_state = GameState::PlayState;
                break;
            case GameState::None:
            default:
                break;

        }

        changeFunc = nullptr;
    }

    m_screen_manager->update(delta_time);
}

void
Game::draw_phase() {
    m_window.draw(*m_screen_manager);
    m_window.display();
}

void
Game::addState(GameState state) {
    m_change_mode = ChangeMode::Push;
    m_state = state;
}

void
Game::popState() {
    m_change_mode = ChangeMode::Pop;
    m_state = GameState::None;
}

void
Game::changeState(GameState state) {
    m_change_mode = ChangeMode::Change;
    m_state = state;
}
