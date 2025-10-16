#include <iostream>
#include <fstream>    // Para trabajar con archivos
#include <cstdlib>    // Para rand() y srand()
#include <ctime>      // Para usar time(0) como semilla

using namespace std;

// Función para generar el arreglo y guardarlo en un archivo CSV
void generarArregloYGuardarCSV(long arreglo[], long n, const string& nombreArchivo, int semilla) {
    srand(semilla);  // Usar una semilla diferente para cada archivo
    
    // Abrir el archivo CSV en modo de escritura
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    // Llenar el arreglo con números aleatorios y escribirlos en el archivo CSV
    for (long i = 0; i < n; i++) {
        arreglo[i] = rand() % 100000 + 1;  // Números aleatorios entre 1 y 100000
        archivo << arreglo[i];         // Escribir el número
        if (i < n - 1) {
            archivo << ",";            // Separar con coma
        }
    }

    archivo.close();  // Cerrar el archivo
    cout << "Datos guardados en el archivo CSV: " << nombreArchivo << endl;
}

int main() {
    const long n = 100000;  // Número de elementos por archivo (puedes cambiarlo)
    long A[n];

    // Generar 30 archivos CSV con datos aleatorios, cada uno con una semilla diferente
    for (int i = 1; i <= 30; i++) {  
        // Usar la semilla con base en el tiempo y la iteración
        int semilla = time(0) + i;  // Cambiar la semilla para cada archivo
        string nombreArchivo = "arreglo" + to_string(i) + ".csv";
        generarArregloYGuardarCSV(A, n, nombreArchivo, semilla);
    }

    return 0;
}
