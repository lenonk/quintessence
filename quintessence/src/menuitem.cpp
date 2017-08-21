//
// Created by lenon on 8/13/17.
//

#include "menuitem.h"
#include "game.h"

MenuItem::MenuItem(const sf::String &n) {
    m_text.setString(n);
};

MenuItem::MenuItem(sf::String n, sf::String a, sf::Vector2f p, sf::Uint8 ax,
                   sf::Uint8 fs, sf::Font f, std::function<void()> cb, std::unique_ptr<Animation> ani) :
        m_text_align(a), m_axis(ax), m_font(f) {
    m_text.setString(n);
    m_text.setPosition(p);
    m_text.setCharacterSize(fs);
    m_text.setFont(m_font);
    m_text.setFillColor({255, 255, 255});
    m_on_click = cb;

    if (ani != nullptr)
        m_animations.push_back(std::move(ani));
};

MenuItem::~MenuItem() { }

void
MenuItem::setSelected(bool val) {
    if (!val) {
        for (auto &anim : m_animations) {
            anim->stop();
            anim->reset();
        }
        m_animation_idx = 0;
        m_text.setFillColor({255, 255, 255, 255});
    }

    m_is_selected = val;
}

void
MenuItem::update(float delta_time) {
    auto *anim = m_animations[m_animation_idx].get();

    if (!m_is_selected)
        return;

    sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(Game::get().getWindow()));
    if (getGlobalBounds().contains(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        m_on_click();
        return;
    }

    if (!anim->isActive() && !anim->isComplete())
        anim->start(nullptr, nullptr);

    anim->update(delta_time, m_text);

    if (anim->isComplete()) {
        anim->reset();
        m_animation_idx++;
        if (m_animation_idx >= m_animations.size())
            m_animation_idx = 0;
    }
}

