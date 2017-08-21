//
// Created by lenon on 8/11/17.
//

#include <iostream>
#include "utilities.h"
#include "game.h"
#include "titlescreen.h"

TitleScreen::TitleScreen() {
    m_sprite.setTexture(Game::get().resources().get(Resource::Texture::TitleBackground));

    std::vector<sf::String> names {"New Game", "Load Game", "Options", "Credits", "Exit"};
    sf::Uint8 start_y = 150;
    for (auto name : enumerate(names)) {
        auto mi = std::make_unique<MenuItem>(name.item, "",
                                            sf::Vector2f(100, start_y + (float)(name.index) * 75.f), 0, 60,
                                             Game::get().resources().get(Resource::Font::Default));

        if (name.item == "Exit") {
            mi->setCallback([]() { Game::get().stop(); });
        }
        else if (name.item == "New Game") {
            mi->setCallback([]() {
                Game::get().changeState(GameState::PlayState);
            });
        }

        mi->addAnimation(std::make_unique<FadeOutAnimation>(mi->getGlobalBounds(), 0.60f, 0.30f, 1.f));
        mi->addAnimation(std::make_unique<FadeInAnimation>(mi->getGlobalBounds(), 0.60f, 0.30f, 1.f));

        m_menu_items.push_back(std::move(mi));
    }

    sf::RenderWindow &window = Game::get().getWindow();
    // TODO: Scale this image so that it looks the same at any resolution
    sf::Vector2u sprite_size = m_sprite.getTexture()->getSize();
    m_sprite.setScale(window.getSize().x / (float)sprite_size.x, window.getSize().y / (float)sprite_size.y);
}

TitleScreen::~TitleScreen() { }

void
TitleScreen::update(float delta_time) {
    static sf::Clock clock;
    static float key_delta = 0;
    float timeout = 250;

    key_delta += clock.restart().asMilliseconds();

    if ((key_delta >= timeout) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_menu_items[m_selected_idx]->setSelected(false);
        m_selected_idx--;
        if (m_selected_idx < 0)
            m_selected_idx = static_cast<sf::Int8>(m_menu_items.size() - 1);

        key_delta = 0;
    }

    if ((key_delta >= timeout) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_menu_items[m_selected_idx]->setSelected(false);
        m_selected_idx++;
        if (m_selected_idx >= m_menu_items.size())
            m_selected_idx = 0;

        key_delta = 0;
    }

    // TODO:  Handle side by side menus

    for (auto item : enumerate(m_menu_items)) {
        if (item.item->SelectItemAt(sf::Mouse::getPosition(Game::get().getWindow()))) {
            m_menu_items[m_selected_idx]->setSelected(false);
            m_selected_idx = static_cast<sf::Uint8>(item.index);
        }
    }

    m_menu_items[m_selected_idx]->setSelected(true);
    for (auto &item : m_menu_items)
        item->update(delta_time);
}
