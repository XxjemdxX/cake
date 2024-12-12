#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;

class BolaDinamica {
public:
    BolaDinamica(b2World& world, const sf::Vector2f& position, float radius, float density, float friction, const sf::Color& color)
        : radius(radius), color(color) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);
        body = world.CreateBody(&bodyDef);

        b2CircleShape shape;
        shape.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        body->CreateFixture(&fixtureDef);

        circleShape.setRadius(radius);
        circleShape.setOrigin(radius, radius);
        circleShape.setFillColor(color);
    }

    // Método para obtener el cuerpo de la bola
    b2Body* getBody() const {
        return body;
    }

    // Método para obtener el radio de la bola
    float getRadio() const {
        return radius;
    }

    // Método para aplicar un impulso a la bola
    void applyImpulse(const b2Vec2& impulse) {
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    }

    // Método para dibujar la bola en la ventana
    void draw(sf::RenderWindow& window) {
        circleShape.setPosition(body->GetPosition().x, body->GetPosition().y);
        window.draw(circleShape);
    }

private:
    b2Body* body;  // Cuerpo de la bola en Box2D
    float radius;   // Radio de la bola
    sf::Color color; // Color de la bola
    sf::CircleShape circleShape; // Forma gráfica de la bola (para dibujarla en la ventana)
};
