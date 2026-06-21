#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "Grafo.h"

using namespace std;

// Función para dibujar el grafo
void dibujarGrafo(sf::RenderWindow& window, Grafo& grafo) {
    // 1. Dibujar arcos (líneas)
    sf::VertexArray lineas(sf::PrimitiveType::Lines); 
    List<Arco>* arcos = grafo.getArcos();
    arcos->goToStart();
    while (!arcos->atEnd()) {
        Arco a = arcos->getElement();
        GNode n1 = grafo.getNodo(a.origen);
        GNode n2 = grafo.getNodo(a.destino);

        sf::Vertex v1(sf::Vector2f(static_cast<float>(n1.x), static_cast<float>(n1.y)));
        sf::Vertex v2(sf::Vector2f(static_cast<float>(n2.x), static_cast<float>(n2.y)));
        v1.color = sf::Color::White;
        v2.color = sf::Color::White;
        lineas.append(v1);
        lineas.append(v2);
        arcos->next();
    }
    window.draw(lineas);
    // 2. Dibujar nodos (círculos)
    for (int i = 0; i < grafo.getCantidadNodos(); i++) {
        GNode nodo = grafo.getNodo(i);
        sf::CircleShape circulo(20.f);
        circulo.setFillColor(sf::Color::Blue);
        circulo.setOutlineColor(sf::Color::Black);
        circulo.setOutlineThickness(2.f);
        circulo.setPosition(sf::Vector2f(static_cast<float>(nodo.x - 15),static_cast<float>(nodo.y - 15)));
        window.draw(circulo);
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // --- Pedir parámetros ---
    int numNodos, anchoVentana, altoVentana;
    double distanciaMax;
    int maxVecinos;

    cout << "----- Configuracion del grafo -----" << endl;
    cout << "Cantidad de nodos: ";
    cin >> numNodos;
    cout << "Ancho de la ventana (pixeles): ";
    cin >> anchoVentana;
    cout << "Alto de la ventana (pixeles): ";
    cin >> altoVentana;
    cout << "Distancia maxima para crear arcos: ";
    cin >> distanciaMax;
    cout << "Maximo de vecinos por nodo: ";
    cin >> maxVecinos;

    // --- Crear grafo ---
    Grafo grafo(numNodos);
    grafo.generarNodosAleatorios(anchoVentana, altoVentana);
    grafo.generarArcos(distanciaMax, maxVecinos);
    cout << "Grafo generado: " << grafo.getCantidadNodos()
        << " nodos, " << grafo.getCantidadArcos() << " arcos." << endl;

    // --- Ventana SFML ---
    sf::RenderWindow window(
        sf::VideoMode({ static_cast<unsigned int>(anchoVentana),
                       static_cast<unsigned int>(altoVentana) }),
                         "Visualizacion del grafo"
    );

    // --- Bucle principal ---
    while (window.isOpen()) {
        while (const auto& event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            //  añadir eventos
        }

        window.clear(sf::Color::Black);
        dibujarGrafo(window, grafo);
        window.display();
    }

    return 0;
}