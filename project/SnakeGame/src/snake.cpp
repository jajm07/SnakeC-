#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <snake.h>
#include <apple.h>
//<cstdlib.h>Este encabezado se encontraba originalmente en la biblioteca estándar de C como <stdlib.h>
//Este encabezado proporciona utilidades diversas. Los símbolos definidos aquí son utilizados por varios componentes de la biblioteca
using namespace std;

Snake::Snake(int blockSize) : dir(Direction::Right), blockSize(blockSize) {
    for (int i = 0; i < 3; ++i) {// Inicializar la serpiente con 3 segmentos.
        sf::RectangleShape segment(sf::Vector2f(blockSize - 1, blockSize - 1));//Utiliza vectores para dibujar la serpiente, en vez de una imagen en pixeles
        segment.setFillColor(sf::Color::Green);
        segment.setPosition(blockSize * (3 - i), 0);
        body.push_back(segment);
    }
}

void Snake::move() {
    sf::Vector2f newPosition = body.front().getPosition();//Utiliza vectores para dibujar la serpiente, en vez de una imagen en pixeles

    switch (dir) {
        case Direction::Up: newPosition.y -= blockSize; break;
        case Direction::Down: newPosition.y += blockSize; break;
        case Direction::Left: newPosition.x -= blockSize; break;
        case Direction::Right: newPosition.x += blockSize; break;
    }

    // Teletransporte de la serpiente cuando choca con los bordes
    if (newPosition.x < 0) {
        newPosition.x = 800 - blockSize; // Suponiendo una ventana de 800x600
    } else if (newPosition.x >= 800) {
        newPosition.x = 0;
    }

    if (newPosition.y < 0) {
        newPosition.y = 600 - blockSize; // Suponiendo una ventana de 800x600
    } else if (newPosition.y >= 600) {
        newPosition.y = 0;
    }

    sf::RectangleShape newSegment(sf::Vector2f(blockSize, blockSize));
    newSegment.setFillColor(sf::Color::Green);
    newSegment.setPosition(newPosition);
    body.push_front(newSegment);

    // Eliminar el último segmento solo si no hemos crecido.
    if (!hasGrown) {
        body.pop_back();
    } else {
        hasGrown = false; // Resetear la bandera de crecimiento.
    }
}//Esto es necesario para evitar que el juego no termine cuando la serpiente coma
//Ya que a la vez esta crece, puede presentarse una colición

void Snake::changeDirection(Direction newDirection) {
    // Evitar que la serpiente se mueva en la dirección opuesta directamente
    if ((dir == Direction::Up && newDirection != Direction::Down) ||
        (dir == Direction::Down && newDirection != Direction::Up) ||
        (dir == Direction::Left && newDirection != Direction::Right) ||
        (dir == Direction::Right && newDirection != Direction::Left)) {
        dir = newDirection;
    }//Se utilizan muchos operadores OR, es para determinar que se esté cumpliendo almenos una de las condiciones
}

void Snake::draw(sf::RenderWindow &window) {
    for (const auto &segment : body) {//Cuando declaras un puntero con const auto, estás declarando efectivamente un puntero a un objeto const. Esto significa que el puntero en sí no se puede modificar, pero el objeto al que apunta sí se puede modificar.
        window.draw(segment);
    }
}

void Snake::grow() {
    hasGrown = true; // Marcar que hemos crecido para evitar eliminar el último segmento en el próximo movimiento.
}

bool Snake::checkAppleCollision(const Apple &apple) {
    sf::Vector2f headPosition = body.front().getPosition();
    sf::Vector2f applePosition = apple.getPosition();

    if (headPosition == applePosition) {
        grow(); // Hacer crecer la serpiente
        return true;
    }

    return false;
}

bool Snake::checkSelfCollision() {
    sf::Vector2f headPosition = body.front().getPosition();

    // Comprueba si la cabeza colisiona con cualquier segmento del cuerpo
    for (auto it = next(body.begin()); it != body.end(); ++it) {
        if (headPosition == it->getPosition()) {
            // La cabeza de la serpiente ha colisionado con su propio cuerpo
            return true;
        }
    }

    return false;
}

void Snake::reset() {
    body.clear();

    for (int i = 0; i < 3; ++i) {// Inicializar la serpiente con 3 segmentos.
        sf::RectangleShape segment(sf::Vector2f(blockSize - 1, blockSize - 1));
        segment.setFillColor(sf::Color::Green);
        segment.setPosition(blockSize * (3 - i), 0);
        body.push_back(segment);
    }

    dir = Direction::Right;
}
