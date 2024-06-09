#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//SFML (Simple and Fast Multimedia Library) es una biblioteca multimedia de código abierto escrita en C++ que proporciona una interfaz simple para crear aplicaciones gráficas 2D.
//Está diseñada para ser fácil de usar, eficiente y portable.
//SFML es adecuada para desarrollar juegos, aplicaciones gráficas y cualquier otra aplicación que requiera gráficos 2D, sonido y manejo de entrada/salida.
#include <snake.h>
#include <apple.h>

using namespace std;
//Las clases de SFML usualmente empiezan en sf::...
int main() {
    int score=0,highscore=0,c=0;//Puntuación.
    int scores[1000];//Lista de puntuaciones
    sf::RenderWindow window(sf::VideoMode(800, 600),"Snake Game");
    //sf::RenderWindow es una clase de SFML que se utiliza para crear una ventana que puede renderizar gráficos 2D.
    //sf::VideoMode es otra clase de SFML que define una modalidad de video (resolución de la pantalla).
    bool gameOver = false;//Esto permitira saber si el jugador ha perdido o no.

    Snake snake(20);
    Apple apple(20);

    sf::Clock clock;
    //sf::Clock es una clase proporcionada por SFML que se utiliza para medir el tiempo transcurrido.

    srand(static_cast<unsigned int>(time(nullptr)));//Se utiliza para inicializar el generador de números aleatorios en C++.
    //time es una función de la biblioteca estándar de C que devuelve el tiempo actual del sistema en segundos desde una época (normalmente el 1 de enero de 1970, también conocido como el "epoch" Unix).
    //nullptr se pasa a time para indicar que no estamos interesados en almacenar el tiempo en una variable time_t.
    sf::Font font;//Se le asigna la clase a la variable para que sea una fuente de texto.
    font.loadFromFile("gnu-free-font/FreeMono.ttf");//Fuente de texto.
    sf::Text scoretext;//Formato de texto.
    scoretext.setFont(font);//Darle una fuente tipográfica al texto.
    scoretext.setCharacterSize(24);//Tamaño de texto
    scoretext.setFillColor(sf::Color::White);//Color de texto
    scoretext.setPosition(10, 10);//Posición y coordenadas del texto
    sf::Text highscoretext;
    highscoretext.setFont(font);
    highscoretext.setCharacterSize(24);
    highscoretext.setFillColor(sf::Color::White);
    highscoretext.setPosition(10, 50);
    sf::Text restarttext;
    restarttext.setFont(font);restarttext.setCharacterSize(36);
    restarttext.setFillColor(sf::Color::Yellow);restarttext.setPosition(100, 100);
    //Sonido
    sf::SoundBuffer Chipmunk;//Asignar la clase de sonido almacenado a la variable
    Chipmunk.loadFromFile("ost/music/chipmunk's brainrot from iraq.ogg");//Se almacena un sonido de la fuente
    sf::SoundBuffer EatApple;
    EatApple.loadFromFile("ost/sfx/eatin'.ogg");
    sf::SoundBuffer Crashitself;
    Crashitself.loadFromFile("ost/sfx/stop.ogg");
    sf::Sound Background;Background.setBuffer(Chipmunk);//Se le asigna una clase que se encarga de reproducir en sonido almacenado
    sf::Sound Point;Point.setBuffer(EatApple);
    sf::Sound Stop;Stop.setBuffer(Crashitself);
    Background.setLoop(true);
    Background.play();//Ejecuta la variable de sonido
    while (window.isOpen()) {//Confirma si la ventana está abierta
        sf::Event event;//La clase sf::Event representa un evento que puede ocurrir en la ventana de la aplicación, como el cierre de la ventana, la pulsación de una tecla, el movimiento del ratón, etc.
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }//Si se presiona el icono de cerrar, la ventana se cierra, valga la redundancia.
        }
        if (gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {//sf::Keyboard se explicará mas adelante.
                // Reiniciar el juego
                snake.reset();
                apple.respawn(800, 600);
                score=0;
                gameOver = false;
                clock.restart();//Se reinicia el tiempo
                continue; // Saltar el resto del bucle y empezar de nuevo
            }
        } else {
            //sf::Keyboard::isKeyPressed permite identificar que boton del teclado se persiona.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) snake.changeDirection(Direction::Up);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) snake.changeDirection(Direction::Down);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) snake.changeDirection(Direction::Left);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) snake.changeDirection(Direction::Right);
            //sf::Keyboard determina la tecla accionada en isKeyPressed.
            //changedDirection asigna al objeto snake una dirección orientación para moverse en la pantalla.
            if (clock.getElapsedTime().asSeconds() > 0.1f) {//Si el tiempo transcurrido es menor que 0.1 segundos, el código dentro de este bloque no se ejecutará.
                //Esta línea de código asegura que ciertas partes del juego, como
                //el movimiento de la serpiente o la verificación de colisiones, se realicen a una velocidad
                //constante y predecible, independientemente de la velocidad de procesamiento del equipo en el que se ejecute el juego.
                //Esto evita que el juego se ejecute demasiado rápido o demasiado lento en diferentes dispositivos.

                snake.move();
                if (snake.checkAppleCollision(apple)) {//Determina si el objeto snake chocó con la manzana.
                    score+=10;//Se suman puntos por chocar y comer la mansana
                    Point.play();
                    apple.respawn(800, 600);//Aparece en una posición aleatoria
                }
                if (snake.checkSelfCollision()) {//Determina si el objeto snake chocó él mismo.
                    Stop.play();
                    cout << "Juego Terminado! La serpiente ha chocado con ella misma, presiona R para continuar" << endl;
                    gameOver = true;
                    cout << "Puntuacion: " << score << endl;
                    scores[c]=score;
                    c+=1;
                    for (int i = 0; i < c; ++i) {
                        cout << "Puntuacion "<<i+1<<": "<<scores[i]<<endl;
                        if (scores[i]>highscore){
                            highscore=scores[i];
                        }
                    }
                    cout << "Puntuacion mas alta: " << highscore << endl;
                }
                clock.restart();//El tiempo se reinicia
            }

            window.clear();
            snake.draw(window);
            apple.draw(window);
            // Dibujar el texto en la ventana
            if(gameOver==true){
                restarttext.setString("Presiona R para continuar");
                window.draw(restarttext);
            }
            scoretext.setString("Puntaje: " + to_string(score));
            highscoretext.setString("Puntaje mas alto: " + to_string(highscore));
            window.draw(scoretext);
            window.draw(highscoretext);

            window.display();
        }
    }

    return 0;
}
