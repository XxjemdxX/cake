#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;
class Fondo {
public:
    Fondo(const std::string& filepath) {
        if (!texture.loadFromFile(filepath)) {
            std::cerr << "Error al cargar la imagen de fondo desde " << filepath << std::endl;
            exit(-1);
        }
        sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};