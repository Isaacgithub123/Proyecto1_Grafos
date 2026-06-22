#include <iostream>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>
#include "Grafo.h"
#include "Algoritmos.h"
#include "LinkedList.h"

using namespace std;

// Variables globales para 
LinkedList<Arco> arcosResaltados;
bool hayResultado = false;
int nodoOrigen = -1;

// Función para dibujar el grafo 
void dibujarGrafo(sf::RenderWindow& window, Grafo& grafo,
    sf::Font& font,
    const LinkedList<Arco>& arcosExtra) {
    // Dibujar arcos normales (gris)
    sf::VertexArray lineas(sf::PrimitiveType::Lines);
    List<Arco>* arcos = grafo.getArcos();
    arcos->goToStart();
    while (!arcos->atEnd()) {
        Arco a = arcos->getElement();
        GNode n1 = grafo.getNodo(a.origen);
        GNode n2 = grafo.getNodo(a.destino);
        sf::Vertex v1(sf::Vector2f(static_cast<float>(n1.x), static_cast<float>(n1.y)));
        sf::Vertex v2(sf::Vector2f(static_cast<float>(n2.x), static_cast<float>(n2.y)));
        v1.color = sf::Color(80, 80, 80);
        v2.color = sf::Color(80, 80, 80);
        lineas.append(v1);
        lineas.append(v2);
        arcos->next();
    }
    window.draw(lineas);
    // Dibujar arcos resaltados (si hay)
    if (arcosExtra.getSize() > 0) {  // <--- CORREGIDO
        sf::VertexArray lineasResaltadas(sf::PrimitiveType::Lines);
        // Recorrer la LinkedList manualmente (no tiene iteradores)
        LinkedList<Arco>* lista = const_cast<LinkedList<Arco>*>(&arcosExtra);
        lista->goToStart();
        while (!lista->atEnd()) {
            Arco a = lista->getElement();
            GNode n1 = grafo.getNodo(a.origen);
            GNode n2 = grafo.getNodo(a.destino);
            sf::Vertex v1(sf::Vector2f(static_cast<float>(n1.x), static_cast<float>(n1.y)));
            sf::Vertex v2(sf::Vector2f(static_cast<float>(n2.x), static_cast<float>(n2.y)));
            v1.color = sf::Color::Yellow;
            v2.color = sf::Color::Yellow;
            lineasResaltadas.append(v1);
            lineasResaltadas.append(v2);
            lista->next();
        }
        window.draw(lineasResaltadas);
    }

    // Dibujar nodos
    for (int i = 0; i < grafo.getCantidadNodos(); i++) {
        GNode nodo = grafo.getNodo(i);
        sf::CircleShape circulo(20.f);
        sf::Color colorNodo = sf::Color::Blue;
        circulo.setFillColor(colorNodo);
        circulo.setOutlineColor(sf::Color::Black);
        circulo.setOutlineThickness(2.f);
        circulo.setPosition(sf::Vector2f(static_cast<float>(nodo.x - 20), static_cast<float>(nodo.y - 20)));
        window.draw(circulo);

        // Etiqueta (número)
        sf::Text texto(font);
        texto.setString(std::to_string(nodo.id));
        texto.setCharacterSize(14);
        texto.setFillColor(sf::Color::White);
        auto rect = texto.getLocalBounds();
        texto.setOrigin(sf::Vector2f(rect.position.x + rect.size.x / 2.f, rect.position.y + rect.size.y / 2.f));
        texto.setPosition(sf::Vector2f(static_cast<float>(nodo.x), static_cast<float>(nodo.y)));
        window.draw(texto);
    }
}


int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    // Pedir parámetros 
    int numNodos, anchoVentana, altoVentana;
    double distanciaMax;
    int maxVecinos;
    int nodoDestino = -1;
    bool nodoDestinoFlag = false;

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

    // Crear grafo
    Grafo grafo(numNodos);
    grafo.generarNodosAleatorios(anchoVentana, altoVentana);
    grafo.generarArcos(distanciaMax, maxVecinos);
    cout << "Grafo generado: " << grafo.getCantidadNodos() << endl;
    cout << "\n----------CONTROLES----------:\n";
    cout << "B (BFS) | F (DFS) | D (Dijkstra)\n";
    cout << "P (Prim) | K (Kruskal) | C (Limpiar)\n";
    cout << "----------------------------- " << endl;

    // Ventana SFML
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cerr << "Error: no se pudo cargar arial.ttf" << std::endl;
        return -1;
    }

    sf::RenderWindow window(
        sf::VideoMode({ static_cast<unsigned int>(anchoVentana),
                        static_cast<unsigned int>(altoVentana) }),
        "Visualizacion del grafo"
    );

    // Variables de interacción
    int nodoSeleccionado = -1;
    bool nodoSeleccionadoFlag = false;

    // Bucle principal
    while (window.isOpen()) {
        // Manejo de eventos
        while (const auto& event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    sf::Vector2i mousePos = mousePressed->position;
                    nodoSeleccionado = -1;
                    nodoSeleccionadoFlag = false;
                    for (int i = 0; i < grafo.getCantidadNodos(); ++i) {
                        GNode nodo = grafo.getNodo(i);
                        float dx = static_cast<float>(nodo.x) - mousePos.x;
                        float dy = static_cast<float>(nodo.y) - mousePos.y;
                        float dist = sqrt(dx * dx + dy * dy);
                        if (dist <= 20.f) {
                            nodoSeleccionado = i;
                            nodoSeleccionadoFlag = true;
                            cout << "Nodo " << i << " seleccionado." << endl;
                            break;
                        }
                    }
                    if (!nodoSeleccionadoFlag) {
                        arcosResaltados.clear();
                        hayResultado = false;
                    }
                }
                else if (mousePressed->button == sf::Mouse::Button::Right) {
                    sf::Vector2i mousePos = mousePressed->position;
                    nodoDestino = -1;
                    nodoDestinoFlag = false;
                    for (int i = 0; i < grafo.getCantidadNodos(); ++i) {
                        GNode nodo = grafo.getNodo(i);
                        float dx = static_cast<float>(nodo.x) - mousePos.x;
                        float dy = static_cast<float>(nodo.y) - mousePos.y;
                        float dist = sqrt(dx * dx + dy * dy);
                        if (dist <= 20.f) {
                            nodoDestino = i;
                            nodoDestinoFlag = true;
                            cout << "Destino seleccionado: " << i << endl;
                            break;
                        }
                    }
                }
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (!nodoSeleccionadoFlag) {
                    cout << "Primero selecciona un nodo con clic izquierdo." << endl;
                    continue;
                }
                int origen = nodoSeleccionado;
                // Tecla B: BFS
                if (keyPressed->code == sf::Keyboard::Key::B) {
                    cout << "Ejecutando BFS desde nodo " << origen << endl;
                    LinkedList<Arco> arbol;
                    ArrayList<int>* orden = Algoritmos::BFS(grafo, origen, arbol);
                    // Mostrar orden en consola (opcional)
                    cout << "Orden BFS: ";
                    for (int i = 0; i < orden->getSize(); ++i) {
                        orden->goToPos(i);
                        cout << orden->getElement() << " ";
                    }
                    cout << endl;
                    arcosResaltados.clear();
                    arbol.goToStart();
                    while (!arbol.atEnd()) {
                        arcosResaltados.append(arbol.getElement());
                        arbol.next();
                    }
                    hayResultado = true;
                    delete orden;
                }
                // Tecla F: DFS 
                else if (keyPressed->code == sf::Keyboard::Key::F) {
                    cout << "Ejecutando DFS desde nodo " << origen << endl;
                    LinkedList<Arco> arbol;
                    ArrayList<int>* orden = Algoritmos::DFS(grafo, origen, arbol);
                    cout << "Orden DFS: ";
                    for (int i = 0; i < orden->getSize(); ++i) {
                        orden->goToPos(i);
                        cout << orden->getElement() << " ";
                    }
                    cout << endl;
                    arcosResaltados.clear();
                    arbol.goToStart();
                    while (!arbol.atEnd()) {
                        arcosResaltados.append(arbol.getElement());
                        arbol.next();
                    }
                    hayResultado = true;
                    delete orden;
                }
                // Tecla D: Dijkstra
                else if (keyPressed->code == sf::Keyboard::Key::D) {
                    if (!nodoDestinoFlag) {
                        cout << "Primero selecciona un destino con clic derecho." << endl;
                        continue;
                    }
                    cout << "Ejecutando Dijkstra desde " << origen << " hasta " << nodoDestino << endl;
                    LinkedList<Arco> camino;
                    double* dist;
                    int* padre;
                    Algoritmos::Dijkstra(grafo, origen, nodoDestino, camino, dist, padre);
                    arcosResaltados.clear();
                    camino.goToStart();
                    while (!camino.atEnd()) {
                        arcosResaltados.append(camino.getElement());
                        camino.next();
                    }
                    hayResultado = true;
                    if (dist[nodoDestino] >= 1e9)
                        cout << "No existe camino." << endl;
                    else
                        cout << "Distancia total: " << dist[nodoDestino] << endl;
                    delete[] dist;
                    delete[] padre;
                }
                // Tecla P: Prim
                else if (keyPressed->code == sf::Keyboard::Key::P) {
                    cout << "Ejecutando Prim desde nodo " << origen << endl;
                    LinkedList<Arco> arbol;
                    Algoritmos::Prim(grafo, origen, arbol);
                    arcosResaltados.clear();
                    arbol.goToStart();
                    while (!arbol.atEnd()) {
                        arcosResaltados.append(arbol.getElement());
                        arbol.next();
                    }
                    hayResultado = true;
                    cout << "Prim completado. Arcos en el arbol: " << arcosResaltados.getSize() << endl;
                }
                // Tecla K: Kruskal
                else if (keyPressed->code == sf::Keyboard::Key::K) {
                    LinkedList<Arco> mst;
                    Algoritmos::Kruskal(grafo, mst);
                    arcosResaltados.clear();
                    mst.goToStart();
                    while (!mst.atEnd()) {
                        arcosResaltados.append(mst.getElement());
                        mst.next();
                    }
                    hayResultado = true;
                    cout << "Kruskal completado." << endl;
                }
                // Tecla C: Limpiar resultados
                else if (keyPressed->code == sf::Keyboard::Key::C) {
                    arcosResaltados.clear();
                    hayResultado = false;
                    cout << "Resultados visuales limpiados." << endl;
                }
            }
        }
        // Dibujar
        window.clear(sf::Color::Black);
        dibujarGrafo(window, grafo, font, arcosResaltados);
        window.display();
    }
    cout << "Gracias por usar el programa :)";
    return 0;
}