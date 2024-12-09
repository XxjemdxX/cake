#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;

int main() {
    int fuerza = 1;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Ejemplo de Física con Box2D y SFML");

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 10.0f); // Gravedad hacia abajo
    b2World mundo(vectorGravedad);

    // Crear el primer suelo 
    // inferior 
    b2BodyDef cuerpoSuelo1Def;
    cuerpoSuelo1Def.position.Set(0.0f, 500.0f); // Posición del primer suelo
    cuerpoSuelo1Def.angle = 0.0f; // Sin rotación
    b2Body* cuerpoSuelo1 = mundo.CreateBody(&cuerpoSuelo1Def);

    b2PolygonShape formaSuelo1;
    int boxWidth1 = 300; // Ancho del primer suelo
    int boxHeight1 = -10; // Alto del primer suelo
    formaSuelo1.SetAsBox(boxWidth1 / 2.0f, boxHeight1 / 2.0f);

    b2FixtureDef fixtureSuelo1Def;
    fixtureSuelo1Def.shape = &formaSuelo1;
    fixtureSuelo1Def.friction = 1.0f;
    cuerpoSuelo1->CreateFixture(&fixtureSuelo1Def);

    sf::RectangleShape suelo1(sf::Vector2f(boxWidth1, boxHeight1));
    suelo1.setOrigin(boxWidth1 / 2.0f, boxHeight1 / 2.0f);
    suelo1.setFillColor(sf::Color::Green); // Color del primer suelo

    // Crear el segundo suelo
    // Derecha
    b2BodyDef cuerpoSuelo2Def;
    cuerpoSuelo2Def.position.Set(600.0f, 400.0f); // Posición del segundo suelo
    cuerpoSuelo2Def.angle = -3.0f * (b2_pi / 180.0f); // Rotación de 5 grados
    b2Body* cuerpoSuelo2 = mundo.CreateBody(&cuerpoSuelo2Def);

    b2PolygonShape formaSuelo2;
    int boxWidth2 = 1000; // Ancho del segundo suelo
    int boxHeight2 = 10; // Alto del segundo suelo
    formaSuelo2.SetAsBox(boxWidth2 / 2.0f, boxHeight2 / 2.0f);

    b2FixtureDef fixtureSuelo2Def;
    fixtureSuelo2Def.shape = &formaSuelo2;
    fixtureSuelo2Def.friction = 1.0f;
    cuerpoSuelo2->CreateFixture(&fixtureSuelo2Def);

    sf::RectangleShape suelo2(sf::Vector2f(boxWidth2, boxHeight2));
    suelo2.setOrigin(boxWidth2 / 2.0f, boxHeight2 / 2.0f);
    suelo2.setFillColor(sf::Color::Green); // Color del segundo suelo

    // Crear el tercer suelo
    //Derecha
    b2BodyDef cuerpoSuelo3Def;
    cuerpoSuelo3Def.position.Set(600.0f, 200.0f); // Posición del tercer suelo
    cuerpoSuelo3Def.angle = -3.0f * (b2_pi / 180.0f); // Rotación de -5 grados
    b2Body* cuerpoSuelo3 = mundo.CreateBody(&cuerpoSuelo3Def);

    b2PolygonShape formaSuelo3;
    int boxWidth3 = 1000; // Ancho del tercer suelo
    int boxHeight3 = 10; // Alto del tercer suelo
    formaSuelo3.SetAsBox(boxWidth3 / 2.0f, boxHeight3 / 2.0f);

    b2FixtureDef fixtureSuelo3Def;
    fixtureSuelo3Def.shape = &formaSuelo3;
    fixtureSuelo3Def.friction = 1.0f;
    cuerpoSuelo3->CreateFixture(&fixtureSuelo3Def);

    sf::RectangleShape suelo3(sf::Vector2f(boxWidth3, boxHeight3));
    suelo3.setOrigin(boxWidth3 / 2.0f, boxHeight3 / 2.0f);
    suelo3.setFillColor(sf::Color::Green); // Color del tercer suelo

   // Crear el cuarto suelo
   // Izquierda
    b2BodyDef cuerpoSuelo4Def;
    cuerpoSuelo4Def.position.Set(100.0f, 300.0f); // Posición del cuarto suelo
    cuerpoSuelo4Def.angle = 3.0f * (b2_pi / 180.0f); // Rotación de 5 grados
    b2Body* cuerpoSuelo4 = mundo.CreateBody(&cuerpoSuelo4Def);

    b2PolygonShape formaSuelo4;
    int boxWidth4 = 1000; // Ancho del cuarto suelo
    int boxHeight4 = 10; // Alto del cuarto suelo
    formaSuelo4.SetAsBox(boxWidth4 / 2.0f, boxHeight4 / 2.0f);

    b2FixtureDef fixtureSuelo4Def;
    fixtureSuelo4Def.shape = &formaSuelo4;
    fixtureSuelo4Def.friction = 1.0f;
    cuerpoSuelo4->CreateFixture(&fixtureSuelo4Def);

    sf::RectangleShape suelo4(sf::Vector2f(boxWidth4, boxHeight4));
    suelo4.setOrigin(boxWidth4 / 2.0f, boxHeight4 / 2.0f);
    suelo4.setFillColor(sf::Color::Green); // Color del cuarto suelo

  // Crear el quinto suelo
  //Izaquierda
    b2BodyDef cuerpoSuelo5Def;
    cuerpoSuelo5Def.position.Set(100.0f, 100.0f); // Posición del quinto suelo
    cuerpoSuelo5Def.angle = 3.0f * (b2_pi / 180.0f); // Rotación de 5 grados
    b2Body* cuerpoSuelo5 = mundo.CreateBody(&cuerpoSuelo5Def);

    b2PolygonShape formaSuelo5;
    int boxWidth5 = 1000; // Ancho del quinto suelo
    int boxHeight5 = 10; // Alto del quinto suelo
    formaSuelo5.SetAsBox(boxWidth5 / 2.0f, boxHeight5 / 2.0f);

    b2FixtureDef fixtureSuelo5Def;
    fixtureSuelo5Def.shape = &formaSuelo5;
    fixtureSuelo5Def.friction = 1.0f;
    cuerpoSuelo5->CreateFixture(&fixtureSuelo5Def);

    sf::RectangleShape suelo5(sf::Vector2f(boxWidth5, boxHeight5));
    suelo5.setOrigin(boxWidth5 / 2.0f, boxHeight5 / 2.0f);
    suelo5.setFillColor(sf::Color::Green); // Color del tercer suelo

 // Crear el Limite izquierdo

    b2BodyDef cuerpoSuelo6Def;
    cuerpoSuelo6Def.position.Set(0.0f, 10.0f); // Posición del quinto suelo
    cuerpoSuelo6Def.angle = 0.0f * (b2_pi / 180.0f); // Rotación de 0 grados
    b2Body* cuerpoSuelo6 = mundo.CreateBody(&cuerpoSuelo6Def);

    b2PolygonShape formaSuelo6;
    int boxWidth6 = -10; // Ancho del limite
    int boxHeight6 = 10000; // Alto del limite
    formaSuelo6.SetAsBox(boxWidth6 / 2.0f, boxHeight6 / 2.0f);

    b2FixtureDef fixtureSuelo6Def;
    fixtureSuelo6Def.shape = &formaSuelo6;
    fixtureSuelo6Def.friction = 1.0f;
    cuerpoSuelo6->CreateFixture(&fixtureSuelo6Def);

    sf::RectangleShape suelo6(sf::Vector2f(boxWidth6, boxHeight6));
    suelo6.setOrigin(boxWidth6 / 2.0f, boxHeight6 / 2.0f);
    suelo6.setFillColor(sf::Color::Black); // Color del tercer suelo

// Crear el Limite derecho

    b2BodyDef cuerpoSuelo7Def;
    cuerpoSuelo7Def.position.Set(800.0f, 10.0f); // Posición del limite
    cuerpoSuelo7Def.angle = 0.0f * (b2_pi / 180.0f); // Rotación de 0 grados
    b2Body* cuerpoSuelo7 = mundo.CreateBody(&cuerpoSuelo7Def);

    b2PolygonShape formaSuelo7;
    int boxWidth7 = -10; // Ancho del limite
    int boxHeight7 = 10000; // Alto del limite
    formaSuelo7.SetAsBox(boxWidth7 / 2.0f, boxHeight7 / 2.0f);

    b2FixtureDef fixtureSuelo7Def;
    fixtureSuelo7Def.shape = &formaSuelo7;
    fixtureSuelo7Def.friction = 1.0f;
    cuerpoSuelo7->CreateFixture(&fixtureSuelo7Def);

    sf::RectangleShape suelo7(sf::Vector2f(boxWidth7, boxHeight7));
    suelo7.setOrigin(boxWidth7 / 2.0f, boxHeight7 / 2.0f);
    suelo7.setFillColor(sf::Color::Black); // Color del tercer suelo


    // Crear un cuerpo dinámico (la bola)
    b2BodyDef cuerpoBolaDef;
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position.Set(400.0f, 100.0f); // Posición inicial de la bola
    b2Body* cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    b2CircleShape formaBola;
    formaBola.m_radius = 25.0f;

    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.7f;
    cuerpoBola->CreateFixture(&fixtureBolaDef);

    // Bucle principal del juego
    while (ventana.isOpen()) {
        // Procesar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Controlar la bola con el teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(-fuerza, 0), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(fuerza, 0), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, -fuerza), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, fuerza), cuerpoBola->GetWorldCenter(), true);

        // Actualizar el mundo de Box2D
        mundo.Step(1.0f / 60.0f, 6, 2);

        // Limpiar la ventana
        ventana.clear();

        // Dibujar los suelos
        suelo1.setPosition(cuerpoSuelo1->GetPosition().x, cuerpoSuelo1->GetPosition().y);
        suelo1.setRotation(cuerpoSuelo1->GetAngle() * 180.0f / b2_pi);
        ventana.draw(suelo1);

        suelo2.setPosition(cuerpoSuelo2->GetPosition().x, cuerpoSuelo2->GetPosition().y);
        suelo2.setRotation(cuerpoSuelo2->GetAngle() * 180.0f / b2_pi);
        ventana.draw(suelo2);

        suelo3.setPosition(cuerpoSuelo3->GetPosition().x, cuerpoSuelo3->GetPosition().y);
        suelo3.setRotation(cuerpoSuelo3->GetAngle() * 180.0f / b2_pi);
        ventana.draw(suelo3);

        suelo4.setPosition(cuerpoSuelo4->GetPosition().x, cuerpoSuelo4->GetPosition().y);
        suelo4.setRotation(cuerpoSuelo4->GetAngle() * 180.0f / b2_pi);
        ventana.draw(suelo4);

        suelo5.setPosition(cuerpoSuelo5->GetPosition().x, cuerpoSuelo5->GetPosition().y);
        suelo5.setRotation(cuerpoSuelo5->GetAngle() * 180.0f / b2_pi);
        ventana.draw(suelo5);

        suelo6.setPosition(cuerpoSuelo6->GetPosition().x, cuerpoSuelo6->GetPosition().y);
        suelo6.setRotation(cuerpoSuelo6->GetAngle() * 180.0f / b2_pi);
        ventana.draw(suelo6);

        suelo7.setPosition(cuerpoSuelo7->GetPosition().x, cuerpoSuelo7->GetPosition().y);
        suelo7.setRotation(cuerpoSuelo7->GetAngle() * 180.0f / b2_pi);
        ventana.draw(suelo7);

        // Dibujar la bola
        sf::CircleShape bola(formaBola.m_radius);
        bola.setOrigin(formaBola.m_radius, formaBola.m_radius);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(cuerpoBola->GetPosition().x, cuerpoBola->GetPosition().y);
        ventana.draw(bola);

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}