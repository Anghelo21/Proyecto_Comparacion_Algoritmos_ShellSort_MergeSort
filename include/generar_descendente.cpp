#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>  // Para std::sort

using namespace std;

// Función para generar un arreglo de tamaño aleatorio con números aleatorios entre 1 y 100000
void generarArregloAleatorio(vector<long>& arreglo, long tamano) {
    for (long i = 0; i < tamano; i++) {
        arreglo.push_back(rand() % 100000 + 1);  // Números aleatorios entre 1 y 100000
    }
}

// Función para ordenar el arreglo de manera descendente
void ordenarDescendente(vector<long>& arreglo) {
    sort(arreglo.begin(), arreglo.end(), greater<long>());  // Ordenar de mayor a menor
}

// Función para guardar el arreglo en un archivo CSV
void guardarArregloEnCSV(const vector<long>& arreglo, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    for (long i = 0; i < arreglo.size(); i++) {
        archivo << arreglo[i];  // Escribir el número
        if (i < arreglo.size() - 1) {
            archivo << ",";  // Separar con coma
        }
    }

    archivo.close();
    cout << "Datos guardados en el archivo CSV: " << nombreArchivo << endl;
}

int main() {
    srand(time(0));  // Usar el tiempo como semilla para generar números aleatorios

    // Generar 30 archivos CSV
    for (int i = 1; i <= 30; i++) {
        // Generar una cantidad aleatoria de elementos para el arreglo (entre 100 y 1000)
        long tamano = 100000;  // Aleatorio entre 100 y 1000
        vector<long> arreglo;

        // Generar los números aleatorios para el arreglo
        generarArregloAleatorio(arreglo, tamano);

        // Ordenar el arreglo de manera descendente
        ordenarDescendente(arreglo);

        // Guardar el arreglo ordenado en un archivo CSV
        string nombreArchivo = "arreglo" + to_string(i) + ".csv";
        guardarArregloEnCSV(arreglo, nombreArchivo);
    }

    return 0;
}
