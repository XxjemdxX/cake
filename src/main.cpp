#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <SFML/Audio.hpp> 

#include <Musica.hpp>
#include <Plataforma.hpp>
#include <BolaDinamica.hpp>
#include <Fondo.hpp>

using namespace std;

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

    // Bucle principal del juego
    while (ventana.isOpen()) {
        // Procesar eventos
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

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}