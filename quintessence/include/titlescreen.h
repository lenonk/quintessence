//
// Created by lenon on 8/11/17.
//

#ifndef QUINTESSENCE_TITLESCREEN_H
#define QUINTESSENCE_TITLESCREEN_H

#include "gamescreen.h"
#include "config.h"
#include "fadeanimation.h"
#include "menuitem.h"


class TitleScreen : public GameScreen {
public:
    TitleScreen();
    ~TitleScreen() final;

    void update(float delta_time) final;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        // Draw the background
        target.clear();
        target.draw(m_sprite, states);

        // TODO: Made the menu look the same at any resolution
        for (auto &item : m_menu_items)
            target.draw(*item, states);
    }

    sf::Font m_font;
    std::vector<std::unique_ptr<MenuItem>> m_menu_items;

    sf::Int8 m_selected_idx { 0 };
    sf::Texture m_background;
    sf::Sprite m_sprite;
};


#endif //QUINTESSENCE_TITLESCREEN_H
