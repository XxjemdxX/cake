#include <Box2D/Box2D.h>
#include <iostream>
#include <SFML/Audio.hpp> 

#include <Musica.hpp>
#include <Plataforma.hpp>
#include <BolaDinamica.hpp>
#include <Fondo.hpp>

// Definición de la clase Changolion para la física
class Changolion {
public:
    Changolion(b2World& world, sf::Vector2f position, sf::Color color)
        : frameTime(0.1f), currentFrame(0)
    {
        // Crear el cuerpo dinámico
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(position.x, position.y);
        body = world.CreateBody(&bodyDef);

        // Forma rectangular
        b2PolygonShape shape;
        shape.SetAsBox(8.5f, 8.5f); // Rectángulo 17x17
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        body->CreateFixture(&fixtureDef);

        // Cargar la textura
        if (!texture.loadFromFile("assets/images/arcade_2.png")) {
            throw std::runtime_error("No se pudo cargar la textura arcade_2.png");
        }

        sprite.setTexture(texture);
        sprite.setPosition(position);  // Posición inicial
    }

    void move(float offsetX, float offsetY) {
        // Aplica una fuerza
        b2Vec2 force(offsetX, offsetY);
        body->ApplyForceToCenter(force, true);
    }

    void draw(sf::RenderWindow& window) {
        sprite.setPosition(body->GetPosition().x, body->GetPosition().y); // Sincroniza sprite y cuerpo
        window.draw(sprite);  // Dibuja el sprite
    }

    sf::Vector2f getPosition() const {
        return sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    }

    void setPosition(float x, float y) {
        body->SetTransform(b2Vec2(x, y), 0.0f);  // Actualiza la posición física
        sprite.setPosition(x, y);  // Sincroniza el sprite
    }

    void right() {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = (currentFrame + 1) % 3;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21) + 46, 67, 17, 17));
            clock.restart();
        }
    }

    void left() {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = (currentFrame + 1) % 3;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21) + 65, 22, 17, 17));
            clock.restart();
        }
    }

    void stayd() {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = 0;
            sprite.setTextureRect(sf::IntRect(96, 67, 17, 17));
            clock.restart();
        }
    }

    void jump(float offsetY) {
        // Aplica un impulso para el salto
        b2Vec2 impulse(0.0f, offsetY);
        body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);

        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            sprite.setTextureRect(sf::IntRect(375, 23, 17, 17));
            clock.restart();
        }
    }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    int currentFrame;
    float frameTime;
    b2Body* body;
};

int main() {
    int fuerza = 1;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Ejemplo de Física con Box2D y SFML");

    // Manejar el fondo utilizando BackgroundManager
    Fondo fondo("assets/images/Cielo.png");

    // Manejar la música utilizando MusicManager
    Musica musicManager("assets/music/Audio.ogg");
    musicManager.play();

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    // Crear plataformas
    Plataforma plataforma1(mundo, {0.0f, 500.0f}, {300.0f, -10.0f}, 0.0f, sf::Color::Red);
    Plataforma plataforma2(mundo, {600.0f, 400.0f}, {1000.0f, 10.0f}, -3.0f, sf::Color::Red);
    Plataforma plataforma3(mundo, {600.0f, 200.0f}, {1000.0f, 10.0f}, -3.0f, sf::Color::Red);
    Plataforma plataforma4(mundo, {100.0f, 300.0f}, {1000.0f, 10.0f}, 3.0f, sf::Color::Red);
    Plataforma plataforma5(mundo, {100.0f, 100.0f}, {1000.0f, 10.0f}, 3.0f, sf::Color::Red);
    Plataforma limiteIzquierdo(mundo, {0.0f, 10.0f}, {-10.0f, 10000.0f}, 0.0f, sf::Color::Black);
    Plataforma limiteDerecho(mundo, {800.0f, 10.0f}, {-10.0f, 10000.0f}, 0.0f, sf::Color::Black);

    // Crear la bola
    BolaDinamica bola(mundo, {100.0f, 100.0f}, 15.0f, 0.01f, 0.7f, sf::Color::Red);

    // Crear el personaje Changolion
    Changolion changolion(mundo, {10.0f, 400.0f}, sf::Color::Blue);

    // Bucle principal del juego
    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Actualizar el mundo de Box2D
        mundo.Step(1.0f / 60.0f, 6, 2);

        // Limpiar la ventana
        ventana.clear();

        // Dibujar el fondo
        fondo.draw(ventana);

        // Dibujar las plataformas
        plataforma1.draw(ventana);
        plataforma2.draw(ventana);
        plataforma3.draw(ventana);
        plataforma4.draw(ventana);
        plataforma5.draw(ventana);
        limiteIzquierdo.draw(ventana);
        limiteDerecho.draw(ventana);

        // Dibujar la bola
        bola.draw(ventana);

        // Dibujar el personaje
        changolion.draw(ventana);

        // Manejar entradas para movimiento
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            changolion.move(2.0f, 0.0f);  // Mover a la derecha
            changolion.right();  // Animación de derecha
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            changolion.move(-2.0f, 0.0f);  // Mover a la izquierda
            changolion.left();  // Animación de izquierda
        } else {
            changolion.stayd();  // Animación de quieto
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            changolion.jump(-5.0f);  // Salto
        }

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}