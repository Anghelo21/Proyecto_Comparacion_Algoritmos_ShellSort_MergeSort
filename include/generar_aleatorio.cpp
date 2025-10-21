#include <iostream>
#include <fstream>    
#include <cstdlib>   
#include <ctime>      

using namespace std;


void generarArregloYGuardarCSV(long arreglo[], long n, const string& nombreArchivo, int semilla) {
    srand(semilla);  
    
    
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escritura." << endl;
        return;
    }

    
    for (long i = 0; i < n; i++) {
        arreglo[i] = rand() % 100000 + 1;  
        archivo << arreglo[i];         
        if (i < n - 1) {
            archivo << ",";            
        }
    }

    archivo.close();  
    cout << "Datos guardados en el archivo CSV: " << nombreArchivo << endl;
}

int main() {
    const long n = 100000;  
    long A[n];

    
    for (int i = 1; i <= 30; i++) {  
        
        int semilla = time(0) + i;  
        string nombreArchivo = "arreglo" + to_string(i) + ".csv";
        generarArregloYGuardarCSV(A, n, nombreArchivo, semilla);
    }

    return 0;
}
