#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

int main()
{
    sf::Window window;
    window.create(sf::VideoMode(800, 600), "Art Prompt",
                  sf::Style::Titlebar | sf::Style::Close);

    sf::Event newEvent{};
    bool running = true;

    while (running)
    {
        while (window.pollEvent(newEvent))
        {
            // Close windows
            if (newEvent.type == sf::Event::Closed)
            {
                running = false;
            }
        }

        window.display();
    }

    return 0;
}
