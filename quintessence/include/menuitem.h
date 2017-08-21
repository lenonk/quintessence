//
// Created by lenon on 8/13/17.
//

#ifndef QUINTESSENCE_MENUITEM_H
#define QUINTESSENCE_MENUITEM_H

#include <SFML/Graphics.hpp>
#include "animation.h"
#include <memory>

class MenuItem : public sf::Drawable {
public:
	MenuItem() = default;
    explicit MenuItem(const sf::String &n);

    MenuItem(sf::String n, sf::String a, sf::Vector2f p, sf::Uint8 ax, sf::Uint8 fs,
             sf::Font f, std::function<void()> cb = nullptr, std::unique_ptr<Animation> ani = nullptr);

    ~MenuItem() override;

    void update(float delta_time);

    // Accessors
    sf::FloatRect getGlobalBounds() { return m_text.getGlobalBounds(); }
    sf::FloatRect getLocalBounds() { return m_text.getLocalBounds(); }

    // Manipulators
    void setTextAlign(sf::String &a) { m_text_align = a; }
    void setAxis(sf::Uint8 &a) { m_axis = a; }
    void setAlpha(sf::Uint8 &a) { m_axis = a; }
    void setFont(sf::Font &f) { m_font = f; }
    void setText(sf::Text &t) { m_text = t; }
    void setPosition(sf::Vector2f &pos) { m_text.setPosition(pos); }
    void setCharacterSize(sf::Uint8 fs) { m_text.setCharacterSize(fs); }
    void setSelected(bool val);
    void setCallback(std::function<void()> f) { m_on_click = f; }
    bool SelectItemAt(sf::Vector2i pos) {
        if (m_text.getGlobalBounds().contains(static_cast<sf::Vector2f>(pos))) {
            if (m_is_selected)
                return false;
            return (m_is_selected = true);
        }
        return false;
    }

    bool getSelected() { return m_is_selected; }

    void addAnimation(std::unique_ptr<Animation>a) { m_animations.push_back(std::move(a)); }

protected:
    sf::String m_text_align { "" };
    sf::Uint8 m_axis = { 0 };
    sf::Font m_font;
    sf::Text m_text;
    bool m_is_selected { false };

    sf::Uint8 m_animation_idx { 0 };
    std::vector<std::unique_ptr<Animation>> m_animations;
    std::function<void()> m_on_click = nullptr;

    // TODO: Add text color, and font style.  Also add sf::Texture for images, and image align

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        sf::Text ltext = m_text;
        target.draw(ltext, states);
    }
};

#endif //QUINTESSENCE_MENUITEM_H
