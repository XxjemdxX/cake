#include <SFML/Graphics.hpp>
#include<Changolion.hpp>
double velocidad = 0.05;
float gravity = 0.001f; // Gravedad que afecta al personaje
float jumpStrength = -0.4f; // Fuerza inicial del salto

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "DinoChrome");

    bool isJumping = false;  // Bandera para verificar si está saltando
    float velocityY = 0.0f;  // Velocidad vertical del personaje
    float groundLevel = 500.0f; // Nivel del suelo

    Changolion man1(sf::Vector2f(400, groundLevel), sf::Color::Red);

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
        else{
            man1.stayd();
        }
         // Detectar salto
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping)
        {
            isJumping = true;
            velocityY = jumpStrength; // Aplicar fuerza inicial hacia arriba
        }

        // Aplicar gravedad si está en el aire
        if (isJumping)
        {
            velocityY += gravity; // Incrementar velocidad hacia abajo por la gravedad
            man1.move(0, velocityY);

            // Detener el salto si el personaje toca el suelo
            if (man1.getPosition().y >= groundLevel)
            {
                man1.setPosition(man1.getPosition().x, groundLevel);
                isJumping = false;
                velocityY = 0.0f;
            }
        }
        window.clear();
        man1.draw(window);
        window.display();
    }

    return 0;
}