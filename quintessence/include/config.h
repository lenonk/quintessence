//
// Created by lenon on 8/10/17.
//

#ifndef QUINTESSENCE_CONFIG_H
#define QUINTESSENCE_CONFIG_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Config {
public:
    static Config &inst() {
        static Config instance;
        return instance;
    }

    sf::VideoMode   video_mode      { 1600, 1200, 24 };
    sf::Vector2u    window_size     { 1600, 1200 };
    sf::Vector2f    view_size       { 1600.0f, 1200.0f };
    sf::Uint32      window_style    { sf::Style::Titlebar | sf::Style::Close };
    sf::Uint32      frame_limit     { 240 };
    sf::Uint8       color_depth     { 24 };

    std::string     game_name       { "Quintessence" };

private:
    Config() = default;

    std::vector<std::vector<std::string>> contents, attributes;
};


#endif //QUINTESSENCE_CONFIG_H
