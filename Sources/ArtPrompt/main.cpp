#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window.hpp"

int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 600), "Art Prompt",
                  sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen())
    {
        sf::Event newEvent;
        while (window.pollEvent(newEvent))
        {
            // Close windows
            if (newEvent.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        sf::Texture texture;
        if (!texture.loadFromFile(RESOURCES_DIR "/Emoji/2694.png"))
        {
        }

        sf::Sprite sprite;
        sprite.setTexture(texture);

        sf::Vector2u windowSize = window.getSize();

        sprite.setPosition(windowSize.x / 2, windowSize.y / 2);
        sprite.setOrigin(36.f, 36.f);
        sprite.setScale(5.f, 5.f);

        window.draw(sprite);
        window.display();
    }

    return 0;
}
