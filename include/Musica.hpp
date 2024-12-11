#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <iostream>

using namespace std;

class Musica {
public:
    Musica(const std::string& filepath) {
        if (!musica.openFromFile(filepath)) {
            std::cerr << "Error al cargar la musica desde " << filepath << std::endl;
            exit(-1);
        }
        musica.setLoop(true);
    }

    void play() {
        musica.play();
    }

    void stop() {
        musica.stop();
    }

private:
    sf::Music musica;
};