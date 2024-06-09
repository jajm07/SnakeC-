#include <apple.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
//<cstdlib.h> Este encabezado se encontraba originalmente en la biblioteca estándar de C como <stdlib.h>
//Este encabezado proporciona utilidades diversas. Los símbolos definidos aquí son utilizados por varios componentes de la biblioteca
using namespace std;

Apple::Apple(int blockSize) : blockSize(blockSize) {
    appleShape.setRadius(blockSize / 2);//Para calcular el radio, parte a la mitad el ancho(diametro) de la hitbox.
    appleShape.setFillColor(sf::Color::Red);//Una librería de SFML que le asigna color a la manzana.
    respawn(800, 600); //Inicializar en una posición aleatoria dentro de los límites de la ventana.
}

void Apple::respawn(int windowWidth, int windowHeight) {//Regenerar manzana
    int maxX = (windowWidth / blockSize) - 1;
    int maxY = (windowHeight / blockSize) - 1;
    //Se regenera en una cordenada aleatoria.
    int x = rand() % maxX;
    int y = rand() % maxY;

    appleShape.setPosition(x * blockSize, y * blockSize);
}

void Apple::draw(sf::RenderWindow &window) {
    window.draw(appleShape);//Dibuja la forma de la manzana en la pantalla
}

sf::Vector2f Apple::getPosition() const {
    return appleShape.getPosition();
}
