//
// Created by wojma on 07.11.2022.
//

#include "Bruteforce.h"

Bruteforce::Bruteforce()
{
    minSum = INT_MAX;
    shortestPath = nullptr;
}

void Bruteforce::permutation(int** matrix, int* cities, int begin, int end, int V, int* path) {
    int temp;
    if (begin == end){//sprawdzamy czy powstała permutacja
        int sum = 0;//suma wag krawędzi
        for (int i = 0; i < V-1; i++){
            sum = sum + matrix[cities[i]][cities[i+1]];//zliczamy sumę dla danej permutacji
        }
        sum = sum + matrix[cities[V-1]][cities[0]];//dodajemy wagę ostatniej krawędzi
        if (sum < minSum) {//sprawdzamy, czy mniejsza
            for (int i = 0; i < V; i++){
                path[i] = cities[i];//podmieniamy minimalną drogę
            }
            minSum = sum;//podmieniamy minimalną sumę
        }
    }
    else {
        for (int i = begin; i <= end; ++i) {
            temp = cities[begin];//swap
            cities[begin] = cities[i];
            cities[i] = temp;
            permutation(matrix, cities, begin + 1, end, V, path);//rekurencyjnie generujemy kolejne permutacja
            temp = cities[begin];//swap
            cities[begin] = cities[i];
            cities[i] = temp;
        }
    }
}

void Bruteforce::bruteforce(int** matrix, int V){
    minSum = INT_MAX;
    int cities[V];//tablica miast do generowania permutacji
    int* path = new int[V];//tablica z najktrótrzą ścierzkę
    for (int i = 0; i < V; i++){//uzupełniamy danymi początkowymi
        cities[i] = i;
        path[i] = i;
        matrix[i][i] = INT_MAX;
    }
    permutation(matrix, cities, 0, V-1, V, path);//generujemy permuacje
    shortestPath = path;
}

void Bruteforce::display(int** matrix, int V) {
    cout << "Miasta: ";//wyświetalmy ścieżkę + sumę
    for (int i = 0; i < V-1; i++){
        cout << shortestPath[i] << " -(" << matrix[shortestPath[i]][shortestPath[i+1]] << ")-> ";
    }
    cout << shortestPath[V-1] << " -(" << matrix[shortestPath[V-1]][shortestPath[0]] << ")-> " << shortestPath[0] << endl;
    cout << "Calkowita droga: " << minSum << endl;
}