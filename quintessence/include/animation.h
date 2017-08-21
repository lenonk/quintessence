//
// Created by lenon on 8/12/17.
//

#ifndef QUINTESSENCE_ANIMATION_H
#define QUINTESSENCE_ANIMATION_H


#include <SFML/Graphics.hpp>
#include <functional>

class Animation : public sf::Drawable {
public:
    // Constructors
    Animation() = default;
    Animation(Animation const &) = delete;
    Animation(Animation const &&) = delete;
    Animation &operator=(Animation const &) = delete;
    Animation &operator=(Animation const &&) = delete;

    // Destructors
    ~Animation() override = default;

    // Common to all Animation types
    virtual void start(std::function<void()> cc, std::function<void(void *)> uc) {
        m_active = true;
        m_complete_callback = std::move(cc);
        m_update_callback = std::move(uc);
    }

    virtual void stop() { m_active = false; m_complete_callback = nullptr; m_update_callback = nullptr; }
    virtual void reset() { m_complete = false; m_active = false; m_complete_callback = nullptr; m_update_callback = nullptr; };
    virtual bool isComplete() { return m_complete; }
    virtual bool isActive() { return m_active; }

    // Pure virtuals
    virtual void update(float delta_time) {}
    virtual void update(float delta_time, sf::Text &text) {}
    virtual void update(float delta_time, sf::Sprite &sprite) {}
    virtual void update(float delta_time, sf::Shape &shape) {}

protected:
    bool m_complete { false };
    bool m_active { false };
    std::function<void()> m_complete_callback = nullptr;
    std::function<void(void *)> m_update_callback = nullptr;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
};


#endif //QUINTESSENCE_ANIMATION_H
