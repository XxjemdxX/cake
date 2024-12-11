#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;

class Plataforma {
public:
    Plataforma(b2World& world, const sf::Vector2f& position, const sf::Vector2f& size, float angle, const sf::Color& color) {
        b2BodyDef bodyDef;
        bodyDef.position.Set(position.x, position.y);
        bodyDef.angle = angle * (b2_pi / 180.0f);
        body = world.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(size.x / 2.0f, size.y / 2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.friction = 1.0f;
        body->CreateFixture(&fixtureDef);

        platform.setSize(size);
        platform.setOrigin(size.x / 2.0f, size.y / 2.0f);
        platform.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) {
        platform.setPosition(body->GetPosition().x, body->GetPosition().y);
        platform.setRotation(body->GetAngle() * 180.0f / b2_pi);
        window.draw(platform);
    }

private:
    b2Body* body;
    sf::RectangleShape platform;
};