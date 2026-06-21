#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string origen[100], destino[100];
int total = 0;

void cargarGrafo() {
    ifstream archivo("grafo.txt");
    total = 0;

    while (archivo >> origen[total] >> destino[total]) {
        total++;
    }

    archivo.close();
}

void guardarGrafo() {
    ofstream archivo("grafo.txt");

    for (int i = 0; i < total; i++) {
        archivo << origen[i] << " " << destino[i] << endl;
    }

    archivo.close();
}

void mostrarGrafo() {
    cout << "\nConexiones del grafo:\n";
    for (int i = 0; i < total; i++) {
        cout << origen[i] << " -> " << destino[i] << endl;
    }
}

void agregarConexion() {
    string a, b;

    cout << "Nodo origen: ";
    cin >> a;
    cout << "Nodo destino: ";
    cin >> b;

    origen[total] = a;
    destino[total] = b;
    total++;

    guardarGrafo();
    cout << "Conexion agregada.\n";
}

void eliminarConexion() {
    string a, b;
    cout << "Nodo origen a eliminar: ";
    cin >> a;
    cout << "Nodo destino a eliminar: ";
    cin >> b;

    for (int i = 0; i < total; i++) {
        if (origen[i] == a && destino[i] == b) {
            for (int j = i; j < total - 1; j++) {
                origen[j] = origen[j + 1];
                destino[j] = destino[j + 1];
            }
            total--;
            guardarGrafo();
            cout << "Conexion eliminada.\n";
            return;
        }
    }

    cout << "Conexion no encontrada.\n";
}

int main() {
    cargarGrafo();

    int opcion;

    do {
        cout << "\n--- MENU GRAFO ---\n";
        cout << "1. Mostrar grafo\n";
        cout << "2. Agregar conexion\n";
        cout << "3. Eliminar conexion\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                mostrarGrafo();
                break;
            case 2:
                agregarConexion();
                break;
            case 3:
                eliminarConexion();
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 4);

    return 0;
}