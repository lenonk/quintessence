//
// Created by lenon on 8/19/17.
//

#ifndef QUINTESSENCE_RESOURCEMANAGER_H
#define QUINTESSENCE_RESOURCEMANAGER_H

#include <type_traits>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define REGISTER_FONT(x, y)
#define REGISTER_TEXTURE(x, y)
#define REGISTER_SOUND(x, y)

namespace Resource {
    // Ugly code beyond, but damn handy
    #undef REGISTER_FONT
    #define REGISTER_FONT(x, y) x,
    enum Font {
        #include "resources.h"
        NumFonts
    };
    #undef REGISTER_FONT
    #define REGISTER_FONT(x, y)

    #undef REGISTER_TEXTURE
    #define REGISTER_TEXTURE(x, y) x,
    enum Texture {
        #include "resources.h"
        NumTextures
    };
    #undef REGISTER_TEXTURE
    #define REGISTER_TEXTURE(x, y)

    #undef REGISTER_SOUND
    #define REGISTER_SOUND(x, y) x,
    enum Sound {
        #include "resources.h"
        NumSounds
    };
    #undef REGISTER_SOUND
    #define REGISTER_SOUND(x, y)

    class ResourceManager {
    public:
        ResourceManager() = default;
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager &) = delete;
        ResourceManager(ResourceManager &&) = delete;
        ResourceManager &operator=(const ResourceManager &) = delete;
        ResourceManager &operator=(ResourceManager &&) = delete;

        bool initialize() {
            sf::Font f;
            sf::Texture t;
            sf::SoundBuffer s;

            #undef REGISTER_FONT
            #define REGISTER_FONT(x, y)                     \
            if (!f.loadFromFile(y))                         \
                return false;                               \
            m_fonts.emplace(x, f);
            #include "resources.h"
            #undef REGISTER_FONT
            #define REGISTER_FONT(x, y)

            #undef REGISTER_TEXTURE
            #define REGISTER_TEXTURE(x, y)                  \
            if (!t.loadFromFile(y))                         \
                return false;                               \
            m_textures.emplace(x, t);
            #include "resources.h"
            #undef REGISTER_TEXTURE
            #define REGISTER_TEXTURE(x, y)

            #undef REGISTER_SOUND
            #define REGISTER_SOUND(x, y)                    \
            if (!s.loadFromFile(y))                         \
                return false;                               \
            m_sounds.emplace(x, s);
            #include "resources.h"
            #undef REGISTER_SOUND
            #define REGISTER_SOUND(x, y)

            return true;
        }

        void add(Font name, sf::Font font) { m_fonts.emplace(name, font); };
        void add(Texture name, sf::Texture tex) { m_textures.emplace(name, tex); };
        void add(Sound name, sf::SoundBuffer sound) { m_sounds.emplace(name, sound); };

        sf::Font &get(Font name) { return m_fonts.find(name)->second; }
        sf::Texture &get(Texture name) { return m_textures.find(name)->second; };
        sf::SoundBuffer &get(Sound name) { return m_sounds.find(name)->second; };

    private:
        std::map<Font, sf::Font> m_fonts;
        std::map<Texture, sf::Texture> m_textures;
        std::map<Sound, sf::SoundBuffer> m_sounds;
    };
}

#endif //QUINTESSENCE_RESOURCEMANAGER_H
