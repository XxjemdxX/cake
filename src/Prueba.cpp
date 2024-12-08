#include <SFML/Graphics.hpp>
#include<Changolion.hpp>
double velocidad = 0.05;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "DinoChrome");

    Changolion man1(sf::Vector2f(400, 300), sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            man1.left();
            man1.move(velocidad * -1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // Actualizar animacion man1chu
            man1.right();
            man1.move(velocidad, 0);
        }
        else
            man1.stayd();
        
        window.clear();
        man1.draw(window);
        window.display();
    }

    return 0;
}