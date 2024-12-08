#include <SFML/Graphics.hpp>

class Changolion
{
public:
    Changolion(sf::Vector2f position, sf::Color color)
    {
        shape.setSize(sf::Vector2f(0, 0));
        shape.setPosition(position); // Posición inicial cuadro
        shape.setFillColor(color);

        // Cargar la imagen desde un archivo
        
        if (!texture.loadFromFile("assets/images/Donkey_Kong.png"))
        {
        
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial sprite
    }

    void move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
        shape.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(this->shape);
        window.draw(this->sprite);
    }

    void right(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 17;
            sprite.setTextureRect(sf::IntRect((currentFrame * 56.4)+2, 194, 33, 38));
            clock.restart();
        }
    }
    void left(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame - 1) % 17;
            sprite.setTextureRect(sf::IntRect((currentFrame * 48.3)+966, 347, 33, 38));
            clock.restart();
        }
    }
    void stayd(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 11;
            sprite.setTextureRect(sf::IntRect((currentFrame * 33.9)+7, 21, 35, 38));
            clock.restart();
        }
    }

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;
    int numFrames = 4; // Número total de frames en la animación
    int frameWidth = 32;
    int frameHeight = 32;};