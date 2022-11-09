//
// Created by wojma on 07.11.2022.
//

#include "DynamicProgramming.h"

DynamicProgramming::DynamicProgramming() {
    minSum = INT_MAX;
    shortestPath = nullptr;
}

int heldKarp(int** matrix, int V, int** dp, int** path, int visited, int mask, int city){
    if (mask == visited){//sprawdzamy, czy już wszystkie odwiedzone
        return matrix[city][0];
    }
    if (dp[mask][city] != INT_MAX){//sprawdzamy, czy istnieje połączenie
        return dp[mask][city];
    }
    for(int i = 0; i < V; ++i){
        if((mask&(1<<i)) == 0){//szukamy nieodwiedzonych miast
            int newMin = matrix[city][i] + heldKarp(matrix, V, dp, path, visited, mask|(1<<i), i);//rekurncynie wytwarzamy kolejne permutacje (ustawiamy maską na odwiedzone)
            if (dp[mask][city] > newMin){
                dp[mask][city] = newMin;//zapisujemy w tablicy minimalną sumę wag
                path[mask][city] = i;//zapisujemy w tablicy połączenie
            }
        }
    }
    return dp[mask][city];
}
//do napisania funkcji skożystałem z:
//link: https://iq.opengenus.org/travelling-salesman-problem-dp/

void DynamicProgramming::dynamic_programming(int **matrix, int V){
    int visited = (1<<V) - 1;//maska binarna dla ostatniego wierzchołka (2^V-1)
    int n = 1<<V;//maska binarna dla liczby wierzchołków (liczba możliwych permutacji) (2^V)
    int **dp = new int *[n];//tablica minimalnych dróg dla danego podproblemu
    int **path = new int *[n];//tablica krawędzi
    for(int i = 0; i < n; i++)//uzupełniamy danymi początkowymi
    {
        dp[i] = new int[V];
        path[i] = new int[V];
        for(int j = 0; j < V; j++)
        {
            dp[i][j] = INT_MAX;
            path[i][j] = -1;
        }
    }
    minSum = heldKarp(matrix, V, dp, path, visited, 1, 0);//wytwarzamy kolejne permutacje i szukamy minimum
    int mask = 1<<0;//ustawiamy maskę binarną dla 0
    int i = 0;
    cout << "Miasta: ";//wyświetamy
    while (mask != visited){
        cout << i << " -(" << matrix[i][path[mask][i]] << ")-> ";
        i = path[mask][i];
        mask = mask+(1<<i);
    }
    cout << i << " -(" << matrix[i][0] << ")-> " << 0 << endl;
    cout << "Calkowita droga: " << minSum << endl;
}
//do napisania funkcji skożystałem z:
//link: https://iq.opengenus.org/travelling-salesman-problem-dp/

void DynamicProgramming::display(int **matrix, int V){

}
