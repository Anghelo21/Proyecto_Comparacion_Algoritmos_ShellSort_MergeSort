#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>  

using namespace std;


void generarArregloAleatorio(vector<long>& arreglo, long tamano) {
    for (long i = 0; i < tamano; i++) {
        arreglo.push_back(rand() % 100000 + 1);  
    }
}


void ordenarDescendente(vector<long>& arreglo) {
    sort(arreglo.begin(), arreglo.end(), greater<long>());  
}


void guardarArregloEnCSV(const vector<long>& arreglo, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    for (long i = 0; i < arreglo.size(); i++) {
        archivo << arreglo[i];  
        if (i < arreglo.size() - 1) {
            archivo << ",";  
        }
    }

    archivo.close();
    cout << "Datos guardados en el archivo CSV: " << nombreArchivo << endl;
}

int main() {
    srand(time(0));  

    
    for (int i = 1; i <= 30; i++) {
        
        long tamano = 100000;  
        vector<long> arreglo;

        
        generarArregloAleatorio(arreglo, tamano);

        
        ordenarDescendente(arreglo);

        
        string nombreArchivo = "arreglo" + to_string(i) + ".csv";
        guardarArregloEnCSV(arreglo, nombreArchivo);
    }

    return 0;
}
