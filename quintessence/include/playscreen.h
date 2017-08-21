//
// Created by lenon on 8/16/17.
//

#ifndef QUINTESSENCE_PLAYSCREEN_H
#define QUINTESSENCE_PLAYSCREEN_H

#include "gamescreen.h"

class PlayScreen : public GameScreen {
public:
    PlayScreen();
    ~PlayScreen() final = default;

    void update(float delta_time) final {}

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        for (auto &sprite : m_sprites)
            target.draw(sprite, states);

    }

    sf::Texture m_worldTextures;
    std::vector<sf::Sprite> m_sprites;
};


#endif //QUINTESSENCE_PLAYSCREEN_H
