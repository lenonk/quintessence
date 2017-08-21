//
// Created by lenon on 8/11/17.
//

#include "screenmanager.h"
#include "splashscreen.h"

void
ScreenManager::update(float delta_time) {
    m_screens.top()->update(delta_time);
}


void
ScreenManager::popScreen() {
    //if (!m_screens.empty() && m_screens.top() != nullptr)
    m_screens.pop();
}

void
ScreenManager::pushScreen(std::shared_ptr<GameScreen> screen) {
    m_screens.push(screen);
}

void
ScreenManager::changeScreen(std::shared_ptr<GameScreen> screen) {
    popScreen();
    pushScreen(screen);
}
