//
// Created by lenon on 8/11/17.
//

#ifndef QUINTESSENCE_SCREENMANAGER_H
#define QUINTESSENCE_SCREENMANAGER_H

#include <stack>
#include <memory>

#include <SFML/Graphics.hpp>

#include "gamescreen.h"

class ScreenManager : public sf::Drawable {
public:
    ScreenManager() = default;
    ~ScreenManager() override  = default;

    void update(float delta_time);

    void changeScreen(std::shared_ptr<GameScreen> screen);
    void pushScreen(std::shared_ptr<GameScreen> screen);
    void popScreen();

private:
    std::stack<std::shared_ptr<GameScreen>> m_screens;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(*m_screens.top(), states);
    }

};


#endif //QUINTESSENCE_SCREENMANAGER_H
