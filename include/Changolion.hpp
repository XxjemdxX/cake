#include <SFML/Graphics.hpp>
#include <stdexcept>

class Changolion
{
public:
    Changolion(sf::Vector2f position, sf::Color color)
    {
        shape.setSize(sf::Vector2f(17, 17)); // Tamaño inicial del rectángulo
        shape.setPosition(position);         // Posición inicial del rectángulo
        shape.setFillColor(color);

        // Cargar la textura desde un archivo
        if (!texture.loadFromFile("assets/images/arcade_2.png"))
        {
            throw std::runtime_error("No se pudo cargar la textura arcade_2.png");
        }

        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial del sprite
    }

    void move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY); // Mover el sprite
        shape.move(offsetX, offsetY);  // Sincronizar el rectángulo
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(this->shape);  // Dibujar el rectángulo
        window.draw(this->sprite); // Dibujar el sprite
    }

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition(); // Devuelve la posición del sprite
    }

    void setPosition(float x, float y)
    {
        sprite.setPosition(x, y); // Ajustar la posición del sprite
        shape.setPosition(x, y);  // Sincronizar el rectángulo
    }

    void right()
    {
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 3;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21) + 46, 67, 17, 17));
            clock.restart();
        }
    }

    void left()
    {
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 3;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21) + 65, 22, 17, 17));
            clock.restart();
        }
    }

    void stayd()
    {
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = 0; // Estado inactivo no necesita cambiar frames
            sprite.setTextureRect(sf::IntRect(96, 67, 17, 17));
            clock.restart();
        }
    }

    void jump(float offsetY)
    {
        sprite.move(0, offsetY); // Mover en el eje Y
        shape.move(0, offsetY); // Sincronizar el rectángulo

        // Animación de salto
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            sprite.setTextureRect(sf::IntRect(375, 23, 17, 17)); // Frame específico para salto
            clock.restart();
        }
    }

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre frames de animación
    int currentFrame = 0;
};