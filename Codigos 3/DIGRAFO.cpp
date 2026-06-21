#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ADT: Estructura básica para representar una Arista/Camino (Datos Básicos)
struct Arista {
    string origen;
    string destino;
    int costo;
    int tiempo;
};

// ADT: Clase que representa el Grafo utilizando Arreglos
class Grafo {
private:
    string nodos[20];           // Arreglo para almacenar los nombres de los nodos
    Arista aristas[50];         // Arreglo de estructuras para los caminos
    int numNodos;
    int numAristas;

public:
    // Constructor
    Grafo() {
        numNodos = 0;
        numAristas = 0;
    }

    // Método para agregar un nodo (evitando duplicados)
    void agregarNodo(string nombre) {
        for (int i = 0; i < numNodos; i++) {
            if (nodos[i] == nombre) return; 
        }
        if (numNodos < 20) {
            nodos[numNodos] = nombre;
            numNodos++;
        }
    }

    // Método para agregar una arista dirigida con sus atributos
    void agregarArista(string orig, string dest, int c, int t) {
        if (numAristas < 50) {
            aristas[numAristas].origen = orig;
            aristas[numAristas].destino = dest;
            aristas[numAristas].costo = c;
            aristas[numAristas].tiempo = t;
            numAristas++;
            
            // Asegurar que los nodos existan en el arreglo de nodos
            agregarNodo(orig);
            agregarNodo(dest);
        }
    }

    // Muestra el grafo actual en la consola
    void mostrarGrafo() {
        cout << "\n--- ESTADO ACTUAL DEL GRAFO ---" << endl;
        cout << "Nodos registrados: ";
        for (int i = 0; i < numNodos; i++) {
            cout << "[" << nodos[i] << "] ";
        }
        cout << "\n\nCaminos / Aristas:" << endl;
        if (numAristas == 0) {
            cout << "(Grafo vacio)" << endl;
        }
        for (int i = 0; i < numAristas; i++) {
            cout << aristas[i].origen << " -> " << aristas[i].destino 
                 << " | Costo: " << aristas[i].costo 
                 << " | Tiempo: " << aristas[i].tiempo << endl;
        }
    }

    // ESCRITURA EN ARCHIVO TXT
    void guardarEnArchivo(string nombreArchivo) {
        ofstream archivo(nombreArchivo.c_str()); // .c_str() por compatibilidad en Dev-C++ antiguo
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo para escribir." << endl;
            return;
        }

        // Primero guardamos la cantidad de aristas para saber cuántas leer después
        archivo << numAristas << endl;

        // Guardamos cada camino línea por línea separado por espacios
        for (int i = 0; i < numAristas; i++) {
            archivo << aristas[i].origen << " " 
                    << aristas[i].destino << " " 
                    << aristas[i].costo << " " 
                    << aristas[i].tiempo << endl;
        }

        archivo.close();
        cout << "¡Datos del grafo guardados exitosamente en " << nombreArchivo << "!" << endl;
    }

    // LECTURA DESDE ARCHIVO TXT
    void cargarDesdeArchivo(string nombreArchivo) {
        ifstream archivo(nombreArchivo.c_str());
        if (!archivo.is_open()) {
            cout << "No se encontro un archivo previo o hubo un error al abrirlo. Iniciando grafo vacio." << endl;
            return;
        }

        // Limpiamos los arreglos actuales antes de cargar
        numNodos = 0;
        numAristas = 0;

        int totalAristas;
        if (archivo >> totalAristas) {
            string orig, dest;
            int c, t;
            for (int i = 0; i < totalAristas; i++) {
                if (archivo >> orig >> dest >> c >> t) {
                    agregarArista(orig, dest, c, t);
                }
            }
        }

        archivo.close();
        cout << "¡Grafo cargado correctamente desde " << nombreArchivo << "!" << endl;
    }
};

int main() {
    Grafo miGrafo;
    string archivoDatos = "grafo_datos.txt";

    // Intentar cargar datos guardados al arrancar el programa (Lectura)
    miGrafo.cargarDesdeArchivo(archivoDatos);

    int opcion;
    do {
        cout << "\n===============================" << endl;
        cout << "       MENU DE GRAFOS (ADT)    " << endl;
        cout << "===============================" << endl;
        cout << "1. Agregar Camino (Arista)" << endl;
        cout << "2. Mostrar Grafo Completo" << endl;
        cout << "3. Guardar en Archivo TXT" << endl;
        cout << "4. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string orig, dest;
                int costo, tiempo;
                cout << "\nNodo Origen (ej. A): ";
                cin >> orig;
                cout << "Nodo Destino (ej. B): ";
                cin >> dest;
                cout << "Costo del camino: ";
                cin >> costo;
                cout << "Tiempo del camino: ";
                cin >> tiempo;

                miGrafo.agregarArista(orig, dest, costo, tiempo);
                cout << "Camino agregado exitosamente." << endl;
                break;
            }
            case 2:
                miGrafo.mostrarGrafo();
                break;
            case 3:
                miGrafo.guardarEnArchivo(archivoDatos);
                break;
            case 4:
                // Auto-guardar antes de salir para asegurar persistencia
                miGrafo.guardarEnArchivo(archivoDatos);
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intenta de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}