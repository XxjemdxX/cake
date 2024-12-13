#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <SFML/Audio.hpp> 

#include <Musica.hpp>
#include <Plataforma.hpp>
#include <BolaDinamica.hpp>
#include <Fondo.hpp>
#include <Changolion.hpp>
#include <bandera.hpp>


using namespace std;

int main() {
    int fuerza = 1;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Las aventuras del changolion ");

    // Manejar el fondo utilizando BackgroundManager
    Fondo fondo("assets/images/Cielo.png");

    // Manejar la música utilizando MusicManager
    Musica musicManager("assets/music/Audio.ogg");
    musicManager.play();

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 5.0f);
    b2World mundo(vectorGravedad);

    // Cargar la textura para las bolas
    sf::Texture bolaTexture;
    if (!bolaTexture.loadFromFile("assets/images/Fuego.png")) {
        cerr << "Error al cargar la textura de la bola" << endl;
        return -1;
    }

    // Crear plataformas

    Plataforma plataforma5(mundo, {100.0f, 100.0f}, {1000.0f, 15.0f}, 3.0f, sf::Color::Red);
    Plataforma plataforma3(mundo, {600.0f, 200.0f}, {1000.0f, 15.0f}, -3.0f, sf::Color::Red);
    Plataforma plataforma4(mundo, {100.0f, 300.0f}, {1000.0f, 15.0f}, 3.0f, sf::Color::Red);
    Plataforma plataforma2(mundo, {600.0f, 400.0f}, {1000.0f, 15.0f}, -3.0f, sf::Color::Red);
    Plataforma plataforma6(mundo, {  0.0f, 500.0f}, {1250.0f, 15.0f}, 3.0f, sf::Color::Red);
    Plataforma plataforma1(mundo, {  800.0f, 500.0f}, {300.0f, 15.0f}, 0.0f, sf::Color::Red);
    Plataforma limiteIzquierdo(mundo, {0.0f, 10.0f}, {10.0f, 10000.0f}, 0.0f, sf::Color::Black);
    Plataforma limiteDerecho(mundo, {800.0f, 10.0f}, {10.0f, 10000.0f}, 0.0f, sf::Color::Black);

    // Crear el personaje Changolion
    Changolion changolion(mundo, {750.0f, 450.0f}, sf::Color::Blue);

    bandera bandera(mundo, {20.0f, 37.0f}, sf::Color::Blue);

    // Temporizador para crear bolas cada cierto tiempo
    sf::Clock relojGeneracion;
    float intervaloGeneracion = 1.5f; // Segundos entre la aparición de bolas

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
            changolion.applyForce(b2Vec2(.5f, 0.0f));
        } else if (movingLeft) {
            changolion.applyForce(b2Vec2(-.5f, 0.0f));
        }

        if (isJumping) {
            changolion.jump(.1f);
        }

        // Generar bolas cada cierto tiempo
        if (relojGeneracion.getElapsedTime().asSeconds() >= intervaloGeneracion) {
            // Crear una bola en una posición aleatoria
            BolaDinamica nuevaBola(mundo, {static_cast<float>(rand() % 800), 0.0f}, 13.0f, 0.01f, 0.7f, sf::Color::White);
            nuevaBola.setTexture(bolaTexture); // Aplicar textura a la bola
            bolas.push_back(nuevaBola);
            relojGeneracion.restart();
        }
        // Verificar si Changolion ha caído del mapa
        if (changolion.getPosition().y > 600) {
            changolion.resetPosition();
        }

        // Verificar si Changolion ha llegado a la coordenada (50, 50)
        if (changolion.getPosition().x <= 50.0f && changolion.getPosition().y <= 50.0f) {
          changolion.resetPosition();
            break;
        }

        // Comprobar colisiones entre Changolion y las bolas
        for (auto& bola : bolas) {
            if (changolion.checkCollisionWithBola(bola)) {
                changolion.resetPosition();
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

        bandera.draw(ventana);

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}
