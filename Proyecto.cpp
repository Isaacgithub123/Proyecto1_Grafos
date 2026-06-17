// Probar con double
cout << "\n--- Grafo con double ---" << endl;
Grafo<double> g2(3);
g2.agregarArista(0, 1, 1.5);
g2.agregarArista(1, 2, 2.7);
g2.print();

// Probar con string
cout << "\n--- Grafo con string ---" << endl;
Grafo<string> g3(3);
g3.agregarArista(0, 1, "amigo");
g3.agregarArista(1, 2, "familiar");
g3.print();