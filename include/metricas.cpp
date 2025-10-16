#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

// Contadores globales
long merge_comparaciones = 0;
long merge_intercambios = 0;

long shell_comparaciones = 0;
long shell_intercambios = 0;

// -------------------- Shell Sort --------------------
void ShellSort(long a[], long num) {
    long k = num + 1;
    while (k > 1) {
        k = k / 2;
        for (long i = k + 1; i <= num; i++) {
            long temp = a[i];
            long j = i;
            while (j - k >= 1 && a[j - k] > temp) {
                a[j] = a[j - k];
                j = j - k;
                shell_comparaciones++;  // Comparación realizada
                shell_intercambios++;   // Intercambio realizado
            }
            a[j] = temp;
            shell_intercambios++;  // Intercambio realizado (cuando se coloca el temp en su lugar)
        }
    }
}

// -------------------- Merge Sort --------------------
void merge(long A[], long izquierda, long medio, long derecha) {
    long n1 = medio - izquierda + 1;
    long n2 = derecha - medio;

    long L[n1], R[n2];

    for (long i = 0; i < n1; i++)
        L[i] = A[izquierda + i];
    for (long j = 0; j < n2; j++)
        R[j] = A[medio + 1 + j];

    long i = 0, j = 0;
    long k = izquierda;

    while (i < n1 && j < n2) {
        merge_comparaciones++;  // Comparación realizada
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
        merge_intercambios++;  // Intercambio realizado
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
        merge_intercambios++;  // Intercambio realizado
    }
}

void mergeSort(long A[], long izquierda, long derecha) {
    if (izquierda < derecha) {
        long medio = izquierda + (derecha - izquierda) / 2;
        mergeSort(A, izquierda, medio);
        mergeSort(A, medio + 1, derecha);
        merge(A, izquierda, medio, derecha);
    }
}

// -------------------- Leer archivo CSV --------------------
void readCSV(const string& filename, vector<long>& arreglo) {
    ifstream file(filename);
    string line;
    arreglo.clear();

    while (getline(file, line)) {
        stringstream ss(line);
        string value;

        while (getline(ss, value, ',')) {
            arreglo.push_back(stol(value));  // Agrega cada número al vector
        }
    }
}

// -------------------- Escribir resultados en CSV --------------------
void writeCSV(const string& filename, const vector<vector<string>>& resultados) {
    ofstream file(filename);
    
    // Escribir los encabezados
    file << "Archivo,Tamaño del Arreglo,Tiempo Merge Sort (µs),Tiempo Shell Sort (µs),Comparaciones Merge Sort,Intercambios Merge Sort,Comparaciones Shell Sort,Intercambios Shell Sort\n";

    // Escribir los resultados
    for (const auto& resultado : resultados) {
        file << resultado[0] << "," << resultado[1] << ","
             << resultado[2] << "," << resultado[3] << ","
             << resultado[4] << "," << resultado[5] << ","
             << resultado[6] << "," << resultado[7] << "\n";
    }
}

// -------------------- PROGRAMA PRINCIPAL --------------------
int main() {
    vector<vector<string>> resultados;  // Almacena los resultados de todos los archivos

    // Lista de nombres de los archivos CSV
    vector<string> archivos = {
        "arreglo1.csv", "arreglo2.csv", "arreglo3.csv", "arreglo4.csv", "arreglo5.csv",
        "arreglo6.csv", "arreglo7.csv", "arreglo8.csv", "arreglo9.csv", "arreglo10.csv",
        "arreglo11.csv", "arreglo12.csv", "arreglo13.csv", "arreglo14.csv", "arreglo15.csv",
        "arreglo16.csv", "arreglo17.csv", "arreglo18.csv", "arreglo19.csv", "arreglo20.csv",
        "arreglo21.csv", "arreglo22.csv", "arreglo23.csv", "arreglo24.csv", "arreglo25.csv",
        "arreglo26.csv", "arreglo27.csv", "arreglo28.csv", "arreglo29.csv", "arreglo30.csv"
    };

    // Iterar sobre cada archivo CSV
    for (const string& archivo : archivos) {
        vector<long> arreglo;
        readCSV(archivo, arreglo);  // Leer el arreglo desde el archivo

        long n = arreglo.size();

        if (n == 0) continue;  // Si el arreglo está vacío, continuar con el siguiente

        long A[n], B[n];

        // Copiar los arreglos en A y B
        for (long j = 0; j < n; j++) {
            A[j] = arreglo[j];
            B[j] = arreglo[j];
        }

        // Medir el tiempo de ejecución de Merge Sort
        auto inicio_merge = high_resolution_clock::now();
        mergeSort(A, 0, n - 1);
        auto fin_merge = high_resolution_clock::now();
        
        auto tiempo_merge_us = duration_cast<microseconds>(fin_merge - inicio_merge).count();

        // Medir el tiempo de ejecución de Shell Sort
        auto inicio_shell = high_resolution_clock::now();
        ShellSort(B, n - 1);
        auto fin_shell = high_resolution_clock::now();
        
        auto tiempo_shell_us = duration_cast<microseconds>(fin_shell - inicio_shell).count();

        // Guardar los resultados para este archivo
        resultados.push_back({
            archivo, to_string(n), to_string(tiempo_merge_us), to_string(tiempo_shell_us),
            to_string(merge_comparaciones), to_string(merge_intercambios),
            to_string(shell_comparaciones), to_string(shell_intercambios)
        });

        // Resetear los contadores para el siguiente archivo
        merge_comparaciones = 0;
        merge_intercambios = 0;
        shell_comparaciones = 0;
        shell_intercambios = 0;
    }

    // Escribir todos los resultados en un archivo CSV
    writeCSV("resultados_comparacion.csv", resultados);

    cout << "Los resultados han sido guardados en 'resultados_comparacion.csv'." << endl;

    return 0;
}
