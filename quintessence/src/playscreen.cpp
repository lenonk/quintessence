//
// Created by lenon on 8/16/17.
//

#include <game.h>
#include "playscreen.h"

PlayScreen::PlayScreen() {
    sf::Sprite tmp;
    tmp.setTexture(Game::get().resources().get(Resource::Texture::Terrain));
    for (int32_t i{0}; i < 1024; i += 32) {
       for (int32_t j{0}; j < 1024; j+= 32) {
           tmp.setTextureRect({j, i, 32, 32});
           tmp.setPosition({float(j + (5 * j)), float(i + (5 * i))});
           m_sprites.push_back(tmp);
       }
    }
}