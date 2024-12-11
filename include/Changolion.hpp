#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stdexcept>

class Changolion {
public:
    // Constructor que toma el mundo de Box2D y la posición
    Changolion(b2World& world, sf::Vector2f position, sf::Color color)
        : frameTime(0.1f), currentFrame(0)
    {
        // Crear un cuerpo dinámico para Changolion en el mundo de Box2D
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;  // Cuerpo dinámico para que sea afectado por la física
        bodyDef.position.Set(position.x, position.y);
        body = world.CreateBody(&bodyDef);

        // Forma del cuerpo (un rectángulo) que corresponde al sprite
        b2PolygonShape shape;
        shape.SetAsBox(8.5f, 8.5f);  // Un rectángulo de 17x17 px dividido en 2 (por la mitad)
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;  // Densidad estándar
        fixtureDef.friction = 0.3f; // Fricción normal
        body->CreateFixture(&fixtureDef);

        // Cargar la textura para el sprite
        if (!texture.loadFromFile("assets/images/arcade_2.png")) {
            throw std::runtime_error("No se pudo cargar la textura arcade_2.png");
        }

        // Configuración del sprite
        sprite.setTexture(texture);
        sprite.setPosition(position);  // Posición inicial del sprite
    }

    // Mover al personaje aplicando fuerzas
    void move(float offsetX, float offsetY) {
        // Aplica una fuerza al cuerpo para moverlo
        b2Vec2 force(offsetX, offsetY);
        body->ApplyForceToCenter(force, true);  // Aplica la fuerza al centro del cuerpo
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

    // Establecer la posición del cuerpo y sincronizar el sprite
    void setPosition(float x, float y) {
        body->SetTransform(b2Vec2(x, y), 0.0f);  // Cambia la posición en el mundo físico
        sprite.setPosition(x, y);  // Actualiza la posición del sprite
    }

    // Animación hacia la derecha
    void right() {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = (currentFrame + 1) % 3;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21) + 46, 67, 17, 17));
            clock.restart();
        }
    }

    // Animación hacia la izquierda
    void left() {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = (currentFrame + 1) % 3;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21) + 65, 22, 17, 17));
            clock.restart();
        }
    }

    // Animación de estar quieto
    void stayd() {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = 0;  // Estado inactivo no necesita cambiar frames
            sprite.setTextureRect(sf::IntRect(96, 67, 17, 17));
            clock.restart();
        }
    }

    // Salto
    void jump(float offsetY) {
        // Aplica un impulso hacia arriba para simular el salto
        b2Vec2 impulse(0.0f, offsetY); 
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

        // Animación de salto
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            sprite.setTextureRect(sf::IntRect(375, 23, 17, 17)); // Frame específico para salto
            clock.restart();
        }
    }

private:
    sf::Sprite sprite;  // Sprite que se dibuja en la pantalla
    sf::Texture texture; // Textura para el sprite
    sf::Clock clock; // Reloj para controlar la animación
    int currentFrame; // El número de la animación actual
    float frameTime; // Tiempo entre frames de animación
    b2Body* body;  // Cuerpo físico de Box2D
};