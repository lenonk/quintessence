//
// Created by lenon on 8/11/17.
//

#ifndef QUINTESSENCE_SPLASHSCREEN_H
#define QUINTESSENCE_SPLASHSCREEN_H

#include "gamescreen.h"
#include "config.h"
#include "fadeanimation.h"

class SplashScreen : public GameScreen {
public:
    SplashScreen();
    ~SplashScreen() final;

    void update(float delta_time) final;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        if (!m_images.empty()) {
            target.setView(m_view);
            target.draw(*m_images[0], states);
            target.setView(target.getDefaultView());
        }
    }

    std::vector<std::unique_ptr<FadeAnimation>> m_animations;
    std::vector<std::unique_ptr<sf::Sprite>> m_images;

    bool m_space_pressed { false };
    sf::Uint8 m_animation_idx { 0 };
    sf::View m_view;
};


#endif //QUINTESSENCE_SPLASHSCREEN_H
