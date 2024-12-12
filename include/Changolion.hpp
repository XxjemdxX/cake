#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdexcept>

class Changolion {
public:
    // Constructor que toma el mundo de Box2D, la posición y el color
    Changolion(b2World& world, sf::Vector2f position, sf::Color color)
        : radius(0.5f), density(1.0f), friction(0.3f), color(color), initialPosition(position)
    {
        // Crear un cuerpo dinámico para Changolion en el mundo de Box2D
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
        if (!texture.loadFromFile("assets/images/walk0.png")) {
            throw std::runtime_error("No se pudo cargar la textura Walk0.png");
        }

        // Configuración del sprite
        sprite.setTexture(texture);
        sprite.setPosition(position);  // Posición inicial del sprite
        sprite.setOrigin(radius, radius);  // Establecer el origen en el centro
    }

    // Mover al personaje aplicando una fuerza
    void applyForce(const b2Vec2& force) {
        body->ApplyForceToCenter(force, true);  // Aplica la fuerza al centro del cuerpo
    }

    // Salto
    void jump(float impulse) {
        // Aplica un impulso hacia arriba para simular el salto
        b2Vec2 impulseVector(0.0f, -impulse);
        body->ApplyLinearImpulse(impulseVector, body->GetWorldCenter(), true);
    }

    // Dibujar el sprite en la ventana, sincronizando su posición con el cuerpo físico
    void draw(sf::RenderWindow& window) {
        sprite.setPosition(body->GetPosition().x, body->GetPosition().y);  // Sincroniza la posición
        window.draw(sprite);  // Dibuja el sprite en la ventana
    }

    // Obtener la posición actual del personaje
    sf::Vector2f getPosition() const {
        return sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    }

    // Verificar colisión con una bola
    bool checkCollisionWithBola(const BolaDinamica& bola) {
        // Suponiendo que la bola tiene un cuerpo físico (Box2D)
        b2Vec2 changolionPos = body->GetPosition();
        b2Vec2 bolaPos = bola.getBody()->GetPosition();  // Suponiendo que tienes el cuerpo de la bola

        // Calcular la distancia entre los centros de Changolion y la bola
        float distancia = (changolionPos - bolaPos).Length();
        float radioChangolion = radius;  // Radio del Changolion
        float radioBola = bola.getRadio();  // Supuesto método getRadio() para obtener el radio de la bola

        // Si la distancia es menor que la suma de los radios, hay una colisión
        return distancia < (radioChangolion + radioBola);
    }

    // Resetear la posición de Changolion
    void resetPosition() {
        body->SetTransform(b2Vec2(initialPosition.x, initialPosition.y), 0.0f);
    }

private:
    b2Body* body;  // Cuerpo físico de Box2D
    float radius;   // Radio del cuerpo
    float density;  // Densidad del cuerpo
    float friction; // Fricción del cuerpo
    sf::Color color; // Color del sprite
    sf::Sprite sprite;  // Sprite que se dibuja en la pantalla
    sf::Texture texture; // Textura para el sprite
    sf::Vector2f initialPosition;  // Posición inicial de Changolion
};
