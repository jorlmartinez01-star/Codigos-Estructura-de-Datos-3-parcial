#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class NodoArbol {
public:
    string dato;
    NodoArbol* izquierdo;
    NodoArbol* derecho;
    NodoArbol(string valor) : dato(valor), izquierdo(NULL), derecho(NULL) {}
};

class ArbolBinario {
private:
    NodoArbol* raiz;
    string archivoArbol;

    // Retorna el nodo modificado al insertar
    NodoArbol* insertarRecursivo(NodoArbol* nodo, string valor) {
        if (nodo == NULL) return new NodoArbol(valor);
        if (valor < nodo->dato) nodo->izquierdo = insertarRecursivo(nodo->izquierdo, valor);
        else if (valor > nodo->dato) nodo->derecho = insertarRecursivo(nodo->derecho, valor);
        return nodo;
    }

    NodoArbol* encontrarMinimo(NodoArbol* nodo) {
        NodoArbol* actual = nodo;
        while (actual && actual->izquierdo != NULL) actual = actual->izquierdo;
        return actual;
    }

    // Retorna el nodo modificado al eliminar
    NodoArbol* eliminarRecursivo(NodoArbol* nodo, string valor) {
        if (nodo == NULL) return nodo;

        if (valor < nodo->dato) {
            nodo->izquierdo = eliminarRecursivo(nodo->izquierdo, valor);
        } else if (valor > nodo->dato) {
            nodo->derecho = eliminarRecursivo(nodo->derecho, valor);
        } else {
            // Caso 1: Nodo con un solo hijo o vacío
            if (nodo->izquierdo == NULL) {
                NodoArbol* temp = nodo->derecho;
                delete nodo;
                return temp;
            } else if (nodo->derecho == NULL) {
                NodoArbol* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            // Caso 2: Nodo con dos hijos
            NodoArbol* temp = encontrarMinimo(nodo->derecho);
            nodo->dato = temp->dato;
            nodo->derecho = eliminarRecursivo(nodo->derecho, temp->dato);
        }
        return nodo;
    }

    void mostrarInorden(NodoArbol* nodo) {
        if (nodo != NULL) {
            mostrarInorden(nodo->izquierdo);
            cout << nodo->dato << " ";
            mostrarInorden(nodo->derecho);
        }
    }

    void mostrarPreorden(NodoArbol* nodo) {
        if (nodo != NULL) {
            cout << nodo->dato << " ";
            mostrarPreorden(nodo->izquierdo);
            mostrarPreorden(nodo->derecho);
        }
    }

    void mostrarPostorden(NodoArbol* nodo) {
        if (nodo != NULL) {
            mostrarPostorden(nodo->izquierdo);
            mostrarPostorden(nodo->derecho);
            cout << nodo->dato << " ";
        }
    }

    void guardarPreordenEstructura(NodoArbol* nodo, ostream& archivo) {
        if (nodo != NULL) {
            archivo << nodo->dato << "\n";
            guardarPreordenEstructura(nodo->izquierdo, archivo);
            guardarPreordenEstructura(nodo->derecho, archivo);
        }
    }

public:
    ArbolBinario() {
        raiz = NULL;
        archivoArbol = "datos_arbol.txt";
    }

    // Aseguramos que actualice la raíz de la RAM correctamente
    void insertar(string valor) {
        raiz = insertarRecursivo(raiz, valor);
    }

    // Aseguramos que actualice la raíz de la RAM al eliminar
    void eliminar(string valor) {
        raiz = eliminarRecursivo(raiz, valor);
    }

    void imprimirTodosLosRecorridos() {
        if (raiz == NULL) {
            cout << "  (Arbol vacio en RAM)\n";
            return;
        }
        cout << "  -> Inorden:   [ "; mostrarInorden(raiz); cout << "]\n";
        cout << "  -> Preorden:  [ "; mostrarPreorden(raiz); cout << "]\n";
        cout << "  -> Postorden: [ "; mostrarPostorden(raiz); cout << "]\n";
    }

    void guardarEnArchivo() {
        ofstream archivoTxt(archivoArbol.c_str());
        if (archivoTxt.is_open()) {
            guardarPreordenEstructura(raiz, archivoTxt);
            archivoTxt.close();
            cout << "[OK] Arbol guardado con exito en '" << archivoArbol << "' usando Preorden.\n";
        }
    }

    void cargarDesdeArchivo() {
        ifstream archivoTxt(archivoArbol.c_str());
        if (archivoTxt.is_open()) {
            string valor;
            while (archivoTxt >> valor) {
                // Usamos el método público para mantener la estructura limpia
                insertar(valor); 
            }
            archivoTxt.close();
        }
    }
};

int main() {
    ArbolBinario arbol;
    
    // 1. LEER: Recupera el archivo base (datos_arbol.txt)
    arbol.cargarDesdeArchivo(); 

    string archivoComandos = "comandos.txt";
    ifstream fComandos(archivoComandos.c_str());

    if (!fComandos.is_open()) {
        cout << "[ERROR] No se pudo abrir '" << archivoComandos << "'.\n";
        return 1;
    }

    // 2. MODIFICAR: Procesa insertar/eliminar desde comandos.txt
    string accion, valor;
    while (fComandos >> accion >> valor) {
        if (accion == "insertar") {
            arbol.insertar(valor);
        } 
        else if (accion == "eliminar") {
            arbol.eliminar(valor);
        }
    }
    fComandos.close();

    cout << "--- ARBOL ---\n";
    arbol.imprimirTodosLosRecorridos();
    cout << "--------------------------------------------------\n";

    
    arbol.guardarEnArchivo(); 

    return 0;
}