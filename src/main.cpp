#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <SFML/Audio.hpp> 

#include <Musica.hpp>
#include <Plataforma.hpp>
#include <BolaDinamica.hpp>
#include <Fondo.hpp>
#include <Changolion.hpp> 

using namespace std;

int main() {
    int fuerza = 1;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Las Mariguanadas de Mario ");

    // Manejar el fondo utilizando BackgroundManager
    Fondo fondo("assets/images/Cielo.png");

    // Manejar la música utilizando MusicManager
    Musica musicManager("assets/music/Audio.ogg");
    musicManager.play();

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 5.0f);
    b2World mundo(vectorGravedad);

    // Crear plataformas
    Plataforma plataforma1(mundo, {  0.0f, 500.0f}, {300.0f, 15.0f}, 0.0f, sf::Color::Red);
    Plataforma plataforma2(mundo, {600.0f, 400.0f}, {1000.0f, 15.0f}, -3.0f, sf::Color::Red);
    Plataforma plataforma3(mundo, {600.0f, 200.0f}, {1000.0f, 15.0f}, -3.0f, sf::Color::Red);
    Plataforma plataforma4(mundo, {100.0f, 300.0f}, {1000.0f, 15.0f}, 3.0f, sf::Color::Red);
    Plataforma plataforma5(mundo, {100.0f, 100.0f}, {1000.0f, 15.0f}, 3.0f, sf::Color::Red);
    Plataforma plataforma6(mundo, {  0.0f, 100.0f}, {300.0f, 15.0f}, 0.0f, sf::Color::Blue);

    Plataforma limiteIzquierdo(mundo, {0.0f, 10.0f}, {-10.0f, 10000.0f}, 0.0f, sf::Color::Black);
    Plataforma limiteDerecho(mundo, {800.0f, 10.0f}, {-10.0f, 10000.0f}, 0.0f, sf::Color::Black);

    // Crear el personaje Changolion
    Changolion changolion(mundo, {10.0f, 450.0f}, sf::Color::Blue); // Posición inicial de Changolion

    // Temporizador para crear bolas cada cierto tiempo
    sf::Clock relojGeneracion;
    float intervaloGeneracion = 3.0f; // Segundos entre la aparición de bolas

    // Crear un vector de bolas
    std::vector<BolaDinamica> bolas;

    // Bucle principal del juego
    while (ventana.isOpen()) {
        // Procesar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Obtener el estado de las teclas
        bool movingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool movingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool isJumping = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

        // Actualizar el movimiento de Changolion
        if (movingRight) {
            changolion.applyForce(b2Vec2(.5f, 0.0f));  // Aplicar una fuerza para mover a la derecha
        } else if (movingLeft) {
            changolion.applyForce(b2Vec2(-.5f, 0.0f));  // Aplicar una fuerza para mover a la izquierda
        }

        if (isJumping) {
            changolion.jump(.1f);  // Aplicar impulso para el salto
        }

        // Generar bolas cada cierto tiempo
        if (relojGeneracion.getElapsedTime().asSeconds() >= intervaloGeneracion) {
            // Crear una bola en una posición aleatoria
            bolas.push_back(BolaDinamica(mundo, {rand() % 800, 0.0f}, 15.0f, 0.01f, 0.7f, sf::Color::Red));
            relojGeneracion.restart();  // Reiniciar el temporizador
        }

        // Comprobar colisiones entre Changolion y las bolas
        for (auto& bola : bolas) {
            if (changolion.checkCollisionWithBola(bola)) {
                changolion.resetPosition();  // Reaparecer en la posición inicial
            }
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
        plataforma6.draw(ventana);
        limiteIzquierdo.draw(ventana);
        limiteDerecho.draw(ventana);

        // Dibujar las bolas
        for (auto& bola : bolas) {
            bola.draw(ventana);
        }

        // Dibujar Changolion
        changolion.draw(ventana);

        // Mostrar la ventana
        ventana.display();
    }
}
