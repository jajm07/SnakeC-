#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
//Cuando se incluye nuevamente el código, el primer ifndef falla, lo que genera un archivo en blanco.
#include <SFML/Graphics.hpp>//Libreria de gráficos
#include <list>//std::list es un contenedor que admite la inserción y eliminación en tiempo constante de elementos desde cualquier parte del contenedor.
#include <iostream>
#include <apple.h>

using namespace std;

enum class Direction { Up, Down, Left, Right };//Arriba, Abajo, Izquierda, Derecha.

class Snake {//Se le asigna la clase Snake al objeto para diferenciarlo del resto de elementos.
public:
    Snake(int blockSize);//Cantidad de segmentos
    void move();//Movimiento
    void changeDirection(Direction newDirection);//Cambiar de dirección
    void draw(sf::RenderWindow &window);//Dibuja la forma de la serpiente en la pantalla
    void grow();//Crecimiento de la serpiente
    bool checkAppleCollision(const Apple &apple);//Comprobar si se ha comido la manzana
    bool checkSelfCollision();//Chocar con ella misma
    void reset();//Reiniciar

private:
    list<sf::RectangleShape> body;//El contenedor que ocupará los segmentos de la serpiente
    Direction dir;
    int blockSize;//Los segmentos en la pantalla que ocupará la serpiente
    bool hasGrown = false; // Añadir la variable hasGrown para controlar el crecimiento
};

#endif // SNAKE_H_INCLUDED
