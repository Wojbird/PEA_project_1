//
// Created by wojma on 14.12.2022.
//

#include "SimulatingAnnealing.h"

SimulatingAnnealing::SimulatingAnnealing(){
    startT = 1000.0;//temperatura pocz�tkowa
    endT = 0.001;//temperatura ko�cowa
    factor = 0.99;//zmiana temperatury
    limit = 3000;//limit przeszukiwania
    minSum = 0;
    path = nullptr;
}

void SimulatingAnnealing::set_variables(double newStartT, double newEndT, double newFactor, int newLimit){
    startT = newStartT;
    endT = newEndT;
    factor = newFactor;
    limit = newLimit;
}

void SimulatingAnnealing::simulating_annealing(int** matrix, int V){
    double tempStartT = startT;
    double tempEndT = endT;
    double tempFactor = factor;
    int tempLimit = limit;
    int temp;
    int *cities = new int[V];//tablica miast do generowania permutacji
    path = new int[V];;//tablica z najktr�trz� �cierzk�
    for (int i = 0; i < V; i++){//uzupe�niamy danymi pocz�tkowymi
        cities[i] = i;
        path[i] = i;
        matrix[i][i] = INT_MAX;
    }
    int sum = 0;//rozwi�zanie pocz�tkowe
    for (int i = 0; i < V-1; i++){
        minSum = sum = sum + matrix[cities[i]][cities[i + 1]];
    }
    minSum = sum = sum + matrix[cities[V - 1]][cities[0]];
    srand(time(NULL));
    while(tempStartT > tempEndT){ //warunek zako�czenia
        for(int i = 0; i < tempLimit; i++){
            cities = path;
            sum = 0;
            int x = rand()%V;//losujemy nowe s�siednie u�o�enie
            int y = rand()%V;
            while(x == y){
                x = rand()%V;
                y = rand()%V;
            }
            temp = cities[x];//swap
            cities[x] = cities[y];
            cities[y] = temp;
            for(int j = 0; j < V-1; j++){//sprawdzmy rowi�znie rozwi�zania
                sum = sum + matrix[cities[j]][cities[j+1]];
            }
            sum = sum + matrix[cities[V-1]][cities[0]];
            double delta = sum - minSum;// liczymy delt�
            if(delta < 0){
                path = cities;
                minSum = sum;
            }
            else{
                double s = rand()/(RAND_MAX+1.0);//warto�� od 0 od 1
                if (exp(-delta/tempStartT) > s){//rozk�ad boltzmanna
                    path = cities;
                    minSum = sum;
                }
            }
        }
        tempStartT *= tempFactor;//geometrycznie zmieniamy temperatur�
    }
}

void SimulatingAnnealing::display(int **matrix, int V) {
    cout << "Miasta: ";//wy�wietalmy �cie�k� + sum�
    for (int i = 0; i < V-1; i++){
        cout << path[i] << " -(" << matrix[path[i]][path[i+1]] << ")-> ";
    }
    cout << path[V-1] << " -(" << matrix[path[V-1]][path[0]] << ")-> " << path[0] << endl;
    cout << "Calkowita droga: " << minSum << endl;
}