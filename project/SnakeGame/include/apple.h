#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED
//Cuando se incluye nuevamente el código, el primer ifndef falla, lo que genera un archivo en blanco.
#include <SFML/Graphics.hpp>//Libreria de gráficos

class Apple {//Se le asigna la clase Apple al objeto para diferenciarlo del resto de elementos.
public://Al preceder una lista de miembros de una clase, la palabra clave pública especifica que esos miembros son accesibles desde cualquier función.
        //Esto se aplica a todos los miembros declarados hasta el siguiente especificador de acceso o el final de la clase.
    Apple(int blockSize);//Tamaño por segmentos.
    void respawn(int windowWidth, int windowHeight);//Regenerarse en otro lugar luego de ser comida.
    void draw(sf::RenderWindow &window);//Mostrar en pantalla.
    sf::Vector2f getPosition() const;//Utiliza vectores para dibujar la manzana, en vez de una imagen en pixeles

private://Al preceder una lista de miembros de la clase, la palabra clave privada
        //especifica que dichos miembros son accesibles solo desde funciones miembro y amigos de la clase.
    sf::CircleShape appleShape;//Se le asigna una forma de circulo a la manzana.
    int blockSize;//Segemnto.
};

#endif // APPLE_H_INCLUDED
