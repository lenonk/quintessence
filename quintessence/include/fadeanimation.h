//
// Created by lenon on 8/12/17.
//

#ifndef QUINTESSENCE_FADEANIMATION_H
#define QUINTESSENCE_FADEANIMATION_H

#include <iostream>
#include <functional>
#include "animation.h"

class FadeAnimation : public Animation {
public:
    explicit FadeAnimation(sf::FloatRect pos, float fade_speed = 0.75f, float min_alpha = 0.0f, float max_alpha = 1.0f) :
            m_fade_speed(fade_speed), m_coord(pos), m_min_alpha(min_alpha), m_max_alpha(max_alpha) { };

    void reset() override { Animation::reset(); m_alpha = 1.0f; }
    virtual void updateAlpha(float delta_time) {};

    void update(float delta_time, sf::Text &text) override {
        updateAlpha(delta_time);
        text.setFillColor({255, 255, 255, static_cast<sf::Uint8>(244 * m_alpha)});
    }

    void update(float delta_time, sf::Sprite &sprite) override {
        updateAlpha(delta_time);
        sprite.setColor({255, 255, 255, static_cast<sf::Uint8>(244 * m_alpha)});
    }

    void update(float delta_time, sf::Shape &shape) override {
        updateAlpha(delta_time);
        shape.setFillColor({255, 255, 255, static_cast<sf::Uint8>(244 * m_alpha)});
    }

protected:
    float m_fade_speed { 1.0f };
    float m_alpha { 1.0f };
    float m_min_alpha { 0.0f };
    float m_max_alpha { 1.0f };
    sf::FloatRect m_coord { 0.0f, 0.0f, 0.0f, 0.0f };

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override { }
};

class FadeOutAnimation : public FadeAnimation {
public:
    explicit FadeOutAnimation(sf::FloatRect pos, float fade_speed = 0.75f, float min_alpha = 0.0f, float max_alpha = 1.0f) :
            FadeAnimation(pos, fade_speed, min_alpha, max_alpha) {
        m_alpha = m_max_alpha;
        m_coord = pos;
    };

    void updateAlpha(float delta_time) override {
        if (!m_active)
            return;

        m_alpha -= m_fade_speed * delta_time;
        if (m_update_callback != nullptr) {
            sf::Uint8 alpha_data = static_cast<sf::Uint8>(255 * m_alpha);
            m_update_callback(static_cast<void *>(&alpha_data));
        }

        if (m_alpha <= std::max(m_min_alpha, 0.0f)) {
            m_alpha = std::max(m_min_alpha, 0.0f);
            m_active = false;
            m_complete = true;
            if (m_complete_callback != nullptr)
                m_complete_callback();
        }
    }

    void reset() override { Animation::reset(); m_alpha = m_max_alpha; }
};

class FadeInAnimation : public FadeAnimation {
public:
    explicit FadeInAnimation(sf::FloatRect pos, float fade_speed = 0.75f, float min_alpha = 0.0f, float max_alpha = 1.0f) :
            FadeAnimation(pos, fade_speed, min_alpha, max_alpha) {
        m_alpha = m_min_alpha;
        m_coord = pos;
    };

    void updateAlpha(float delta_time) override {
        if (!m_active)
            return;

        m_alpha += m_fade_speed * delta_time;
        if (m_update_callback != nullptr) {
            sf::Uint8 alpha_data = static_cast<sf::Uint8>(255 * m_alpha);
            m_update_callback(static_cast<void *>(&alpha_data));
        }

        if (m_alpha >= std::min(m_max_alpha, 1.0f)) {
            m_alpha = std::min(m_max_alpha, 1.0f);
            m_active = false;
            m_complete = true;
            if (m_complete_callback != nullptr)
                m_complete_callback();
        }
    }

    void reset() override { Animation::reset(); m_alpha = m_min_alpha; }
};

#endif //QUINTESSENCE_FADEANIMATION_H
