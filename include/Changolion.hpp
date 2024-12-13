#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdexcept>

class Changolion {
public:
    Changolion(b2World& world, sf::Vector2f position, sf::Color color)
    : radius(0.5f), density(1.0f), friction(0.3f), color(color), initialPosition(position) {
    // Crear un cuerpo dinámico para Changolion
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

    if (!texture.loadFromFile("assets/images/chango.png")) {
        throw std::runtime_error("No se pudo cargar la textura chango.png");
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);
    // Establecer el origen del sprite al centro de la imagen
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

    void applyForce(const b2Vec2& force) {
        body->ApplyForceToCenter(force, true);
    }

    void jump(float impulse) {
        b2Vec2 impulseVector(0.0f, -impulse);
        body->ApplyLinearImpulse(impulseVector, body->GetWorldCenter(), true);
    }

    void draw(sf::RenderWindow& window) {
        sprite.setPosition(body->GetPosition().x, body->GetPosition().y);
        window.draw(sprite);
    }

    sf::Vector2f getPosition() const {
        return sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    }

    bool checkCollisionWithBola(const BolaDinamica& bola) {
        b2Vec2 changolionPos = body->GetPosition();
        b2Vec2 bolaPos = bola.getBody()->GetPosition();
        float distancia = (changolionPos - bolaPos).Length();
        float radioChangolion = radius;
        float radioBola = bola.getRadio();
        return distancia < (radioChangolion + radioBola);
    }

    void resetPosition() {
        body->SetTransform(b2Vec2(initialPosition.x, initialPosition.y), 0.0f);
    }

    // Método para verificar si está tocando el suelo
    bool isTouchingGround() {
        for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next) {
            if (edge->contact->IsTouching()) {
                return true;
            }
        }
        return false;
    }

private:
    b2Body* body;
    float radius;
    float density;
    float friction;
    sf::Color color;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f initialPosition;
};
