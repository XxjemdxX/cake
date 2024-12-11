#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;

class BallManager {
public:
    BallManager(b2World& world, const sf::Vector2f& position, float radius, float density, float friction, const sf::Color& color)
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

    void applyImpulse(const b2Vec2& impulse) {
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
    }

    void draw(sf::RenderWindow& window) {
        circleShape.setPosition(body->GetPosition().x, body->GetPosition().y);
        window.draw(circleShape);
    }

private:
    b2Body* body;
    float radius;
    sf::Color color;
    sf::CircleShape circleShape;
};
