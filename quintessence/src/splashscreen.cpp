//
// Created by lenon on 8/11/17.
//

#include "utilities.h"
#include "game.h"
#include "splashscreen.h"

SplashScreen::SplashScreen() : m_view{{0.0f, 0.0f, 800.0f, 600.0f}} {
    auto sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(Game::get().resources().get(Resource::Texture::Splash1));
    m_images.push_back(std::move(sprite));

    sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(Game::get().resources().get(Resource::Texture::Splash2));
    m_images.push_back(std::move(sprite));

    sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(Game::get().resources().get(Resource::Texture::Splash3));
    m_images.push_back(std::move(sprite));

    // TODO: View should be centerd at any resolution.  The math here is wrong
    // Create view and set it up
    sf::RenderWindow &window = Game::get().getWindow();
    m_view.setCenter(m_view.getSize().x / 2, m_view.getSize().y / 2);
    m_view.setViewport({(m_view.getSize().x / (float)window.getSize().x) / 2.0f,
                      (m_view.getSize().y / (float)window.getSize().y) / 2.0f,
                      m_view.getSize().x / (float)window.getSize().x,
                      m_view.getSize().y / (float)window.getSize().y});

    for (auto &image : m_images) {
        sf::Vector2u sprite_size = image->getTexture()->getSize();
        image->setScale(m_view.getSize().x / (float) sprite_size.x, m_view.getSize().y / (float) sprite_size.y);
    }

    m_animations.push_back(std::make_unique<FadeInAnimation>(sf::FloatRect{0.0f, 0.0f, 800.0f, 600.0f}));
    m_animations.push_back(std::make_unique<FadeOutAnimation>(sf::FloatRect{0.0f, 0.0f, 800.0f, 600.0f}));
}

SplashScreen::~SplashScreen() {
    m_animations.clear();
}

void
SplashScreen::update(float delta_time) {
    // Extracting the dumb pointer here is ok, as long as it doesn't get passed anywhere.
    FadeAnimation *anim = m_animations[m_animation_idx].get();

    if (!anim->isActive() && !anim->isComplete()) {
        anim->start(nullptr, nullptr);
    }

    anim->update(delta_time, *m_images[0]);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        m_space_pressed = true;

    if (!anim->isComplete())
        return;

    if (m_space_pressed) {
        Game::get().changeState(GameState::TitleState);
        return;
    }

    // Reset it before we use it again
    anim->reset();
    m_animation_idx++;

    if (m_animation_idx >= m_animations.size()) {
        // All the animations are complete.  Switch the image
        if (!m_images.empty()) {
            m_images.erase(m_images.begin());
            if (m_images.empty()) {
                Game::get().changeState(GameState::TitleState);
            }
        }

        // Go back to the first animation
        m_animation_idx = 0;
    }
}
