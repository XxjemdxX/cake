#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdexcept>

class bandera {
public:
    // Constructor que toma el mundo de Box2D, la posición y el color
    bandera(b2World& world, sf::Vector2f position, sf::Color color)
        : radius(0.5f), density(0.0f), friction(0.3f), color(color), initialPosition(position)
    {
        // Crear un cuerpo dinámico en el mundo de Box2D
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;  // Cuerpo dinámico para que sea afectado por la física
        bodyDef.position.Set(position.x, position.y);
        body = world.CreateBody(&bodyDef);

        // Forma del cuerpo (un círculo) que corresponde al sprite
        b2CircleShape shape;
        shape.m_radius = radius;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;  // Densidad estándar
        fixtureDef.friction = friction; // Fricción normal
        body->CreateFixture(&fixtureDef);

        // Cargar la textura para el sprite
        if (!texture.loadFromFile("assets/images/bandera.png")) {
            throw std::runtime_error("No se pudo cargar la textura casa.png");
        }

        // Configuración del sprite
        sprite.setTexture(texture);
        sprite.setPosition(position);  // Posición inicial del sprite
        sprite.setOrigin(radius, radius);  // Establecer el origen en el centro   
    }

    void draw(sf::RenderWindow& window) {
        sprite.setPosition(body->GetPosition().x, body->GetPosition().y);  // Sincroniza la posición
        window.draw(sprite);  // Dibuja el sprite en la ventana
    }

private:
    b2Body* body;  // Cuerpo físico de Box2D
    float radius;   // Radio del cuerpo
    float density;  // Densidad del cuerpo
    float friction; // Fricción del cuerpo
    sf::Color color; // Color del sprite
    sf::Sprite sprite;  // Sprite que se dibuja en la pantalla
    sf::Texture texture; // Textura para el sprite
    sf::Vector2f initialPosition;  // Posición inicial
};

