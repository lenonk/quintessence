//
// Created by lenon on 8/11/17.
//

#ifndef QUINTESSENCE_GAMESCREEN_H
#define QUINTESSENCE_GAMESCREEN_H

#include <iostream>

#include <SFML/Graphics.hpp>

class GameScreen : public sf::Drawable {
public:
    GameScreen() = default;
    virtual ~GameScreen() = default;

    virtual void update(float delta_time) = 0;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;

private:
};

#endif //QUINTESSENCE_GAMESCREEN_H
