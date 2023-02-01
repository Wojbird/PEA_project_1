//
// Created by wojma on 07.11.2022.
//

#include "Menu.h"
#include "DynamicProgramming.h"
#include "Bruteforce.h"
#include "SimulatingAnnealing.h"
#include "GeneticAlgorithm.h"

Menu::Menu()
{
    again = false;
    choice = 0;
    name = "";
    type = "";
    comment = "";
    V = 0;
    edge_weight_type = "";
    edge_weight_format = "";
    matrix = nullptr;
}

Menu::~Menu()
{
    for (int i = 0; i < V; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Menu::display(){
    cout << "Nazwa: " << name << endl;
    cout << "Rodzaj: " << type << endl;
    cout << "Komentarz: " << comment << endl;
    cout << "Rozmiar: " << V << endl;
    cout << "Rodzaj wag krawedzi: " << edge_weight_type << endl;
    cout << "Format wag krawedzi: " << edge_weight_format << endl;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            if (matrix[i][j] == INT_MAX){
                cout << "-" << " ";
            }
            else{
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int random(){
    return rand()%10000;
}

long long int read_QPC(){
    LARGE_INTEGER count;
    DWORD_PTR oldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
    QueryPerformanceCounter(&count);
    SetThreadAffinityMask(GetCurrentThread(), oldMask);
    return((long long int)count.QuadPart);
}
//do napisania funkcji skożystałem z:
//link: http://staff.iiar.pwr.wroc.pl/antoni.sterna/sdizo/SDiZO_time.pdf

void Menu::start(){
    Bruteforce BFInstance;
    DynamicProgramming DPInstance;
    SimulatingAnnealing SAInstance;
    srand(time(nullptr));
    again = true;

    int bestVal = INT_MAX;//najlepszy wynik
    int* bestRoad = new int [V];//tablica z wynikiem
    int population_size = 100;//liczba osobnik�w w pokoleniu
    int generations = 100;//liczba pokolen
    float crossover_p = 0.85;//prawdopodobienstwo wyst�pienia krzyzowania
    float mutation_p = 0.09;//prawdopodobienstwo mutacji
    int tournament_size = 5;

    cout << endl << "Implementacja algorytmu podzialu i ograniczen dla asymetrycznego problemu komiwojażera." << endl;
    cout << endl << "Autor: Wojciech Makuch" << endl;
    while(again){
        cout << endl << "Wybierz opcje:" << endl;
        cout << "1) Wczytanie pliku." << endl;
        cout << "2) Wczytanie losowej drogi." << endl;
        cout << "3) Wyswietlenie macierzy." << endl;
        cout << "4) Zmiana zmiennych dla symulowanego wyzarzania." << endl;
        cout << "5) Zmiana zmiennych dla algorytmu genetycznego." << endl;
        cout << "6) Brute force." << endl;
        cout << "7) Programowanie dynamiczne." << endl;
        cout << "8) Symulowane wyzarzanie." << endl;
        cout << "9) Algotyrm Genetyczny - Invert." << endl;
        cout << "10) Algotyrm Genetyczny - Insert." << endl;
        cout << "0) Zakoncz." << endl;
        cin >> choice;
        switch(choice){
            case 1:{
                name = "";
                cout << endl << "Wpisz nazwe pliku:" << endl;
                cin >> name;
                ifstream file;
                string info;
                int v, w;
                string s, temp;
                file.open(name.c_str());
                if(file.is_open())
                {
                    while(s != "NAME:"){
                        file >> s;
                    }
                    file >> s;
                    while(s != "TYPE:"){
                        temp += s;
                        temp += " ";
                        file >> s;
                    }
                    name = temp;
                    temp = "";
                    file >> s;
                    while(s != "COMMENT:"){
                        temp += s;
                        temp += " ";
                        file >> s;
                    }
                    type = temp;
                    temp = "";
                    file >> s;
                    while(s != "DIMENSION:"){
                        temp += s;
                        temp += " ";
                        file >> s;
                    }
                    comment = temp;
                    temp = "";
                    file >> v;
                    V = v;
                    while(s != "EDGE_WEIGHT_TYPE:"){
                        file >> s;
                    }
                    file >> s;
                    while(s != "EDGE_WEIGHT_FORMAT:"){
                        temp += s;
                        temp += " ";
                        file >> s;
                    }
                    edge_weight_type = temp;
                    temp = "";
                    file >> s;
                    while(s != "EDGE_WEIGHT_SECTION"){
                        temp += s;
                        temp += " ";
                        file >> s;
                    }
                    edge_weight_format	= temp;
                    if(file.fail()){
                        cout << "File error - READ SIZE" << endl;
                    }
                    else{
                        int **newMatrix = new int *[v];
                        for(int i = 0; i < v; i++){
                            newMatrix[i] = new int [v];
                            for(int j = 0; j < v; j++){
                                file >> w;
                                if(file.fail())
                                {
                                    cout << "File error - READ DATA" << endl;
                                    break;
                                }
                                else{
                                    newMatrix[i][j] = w;
                                }
                            }
                        }
                        matrix = newMatrix;
                    }
                    file.close();
                }
                else{
                    cout << "File error - OPEN" << endl;
                }
                break;
            }
            case 2:{
                int v;
                cout << endl << "Podaj liczbe wierzcholkow: " << endl;
                cin >> v;
                V = v;
                int **newMatrix = new int *[v];
                for(int i = 0; i < v; i++){
                    newMatrix[i] = new int [v];
                    for(int j = 0; j < v; j++){
                        newMatrix[i][j] = random();
                    }
                    newMatrix[i][i] = INT_MAX;
                }
                matrix = newMatrix;
                break;
            }
            case 3:{
                cout << endl;
                display();
                break;
            }
            case 4:{
                cout << endl;
                double newStartT, newEndT, newFactor;
                int newLimit;
                cout << endl << "Podaj temperature poczatkowa: " << endl;
                cin >> newStartT;
                cout << endl << "Podaj temperature koncowa: " << endl;
                cin >> newEndT;
                cout << endl << "Podaj zmiane temperatury: " << endl;
                cin >> newFactor;
                cout << endl << "Podaj limit przeszukiwania: " << endl;
                cin >> newLimit;
                SAInstance.set_variables(newStartT, newEndT, newFactor, newLimit);
                break;
            }
            case 5:{
                cout << endl << "nowa populacja:" << endl;
				cin >> population_size;
				cout << endl << "nowa liczba pokolen:" << endl;
				cin >> generations;
				cout << endl << "nowy wspolczynnik krzyzowania:" << endl;
				cin >> crossover_p;
				cout << endl << "nowy wspolczynnik mutacji:" << endl;
				cin >> mutation_p;
				cout << endl << "nowy rozmiar turnieju:" << endl;
				cin >> tournament_size;
				break;
            }
            case 6:{
                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                BFInstance.bruteforce(matrix, V);

                elapsed = read_QPC() - start;

                BFInstance.display(matrix, V);

                cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / (float)frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * (double)elapsed) / (double)frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * (double)elapsed) / (double)frequency << endl << endl;
                system("PAUSE");
                //do napisania funkcji skożystałem z:
                //link: http://staff.iiar.pwr.wroc.pl/antoni.sterna/sdizo/SDiZO_time.pdf
                break;
            }
            case 61:{
                int iterations, v;
                cout << endl << "Podaj liczbe iteracji: ";
                cin >> iterations;
                cout << endl << "Podaj liczbe wierzcholkow: ";
                cin >> v;
                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();
                Bruteforce BF;
                for (int ii = 0; ii < iterations; ii++){
                    V = v;
                    int **newMatrix = new int *[v];
                    for(int i = 0; i < v; i++){
                        newMatrix[i] = new int [v];
                        for(int j = 0; j < v; j++){
                            newMatrix[i][j] = random();
                        }
                        newMatrix[i][i] = INT_MAX;
                    }
                    matrix = newMatrix;

                    BF.bruteforce(matrix, V);

                    elapsed = read_QPC() - start;

                    BF.display(matrix, V);

                    cout << ii+1 << "; ";
                }
                cout << endl;
                cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / (float)(frequency * iterations) << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * (double)elapsed) / (double)(frequency * iterations) << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * (double)elapsed) / (double)(frequency * iterations) << endl << endl;
                system("PAUSE");
                //do napisania funkcji skożystałem z:
                //link: http://staff.iiar.pwr.wroc.pl/antoni.sterna/sdizo/SDiZO_time.pdf
                break;
            }
            case 7:{
                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                DPInstance.dynamic_programming(matrix, V);

                elapsed = read_QPC() - start;

                DPInstance.display(matrix, V);

                cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / (float)frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * (double)elapsed) / (double)frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * (double)elapsed) / (double)frequency << endl << endl;
                system("PAUSE");
                //do napisania funkcji skożystałem z:
                //link: http://staff.iiar.pwr.wroc.pl/antoni.sterna/sdizo/SDiZO_time.pdf
                break;
            }
            case 71:{
                int iterations, v;
                cout << endl << "Podaj liczbe iteracji: ";
                cin >> iterations;
                cout << endl << "Podaj liczbe wierzcholkow: ";
                cin >> v;
                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();
                DynamicProgramming DP;
                for (int ii = 0; ii < iterations; ii++){
                    V = v;
                    int **newMatrix = new int *[v];
                    for(int i = 0; i < v; i++){
                        newMatrix[i] = new int [v];
                        for(int j = 0; j < v; j++){
                            newMatrix[i][j] = random();
                        }
                        newMatrix[i][i] = INT_MAX;
                    }
                    matrix = newMatrix;

                    DP.dynamic_programming(matrix, V);

                    elapsed = read_QPC() - start;

                    DP.display(matrix, V);

                    cout << ii+1 << "; ";
                }
                cout << endl;
                cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / (float)(frequency * iterations) << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * (double)elapsed) / (double)(frequency * iterations) << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * (double)elapsed) / (double)(frequency * iterations) << endl << endl;
                system("PAUSE");
                //do napisania funkcji skożystałem z:
                //link: http://staff.iiar.pwr.wroc.pl/antoni.sterna/sdizo/SDiZO_time.pdf
                break;
            }
            case 8:{
                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                SAInstance.simulating_annealing(matrix, V);

                elapsed = read_QPC() - start;

                SAInstance.display(matrix, V);

                cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / (float)frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * (double)elapsed) / (double)frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * (double)elapsed) / (double)frequency << endl << endl;
                system("PAUSE");
                //do napisania funkcji skożystałem z:
                //link: http://staff.iiar.pwr.wroc.pl/antoni.sterna/sdizo/SDiZO_time.pdf
                break;
            }
            case 81:{
                int iterations, v;
                cout << endl << "Podaj liczbe iteracji: ";
                cin >> iterations;
                cout << endl << "Podaj liczbe wierzcholkow: ";
                cin >> v;
                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();
                SimulatingAnnealing SA;
                for (int ii = 0; ii < iterations; ii++){
                    V = v;
                    int **newMatrix = new int *[v];
                    for(int i = 0; i < v; i++){
                        newMatrix[i] = new int [v];
                        for(int j = 0; j < v; j++){
                            newMatrix[i][j] = random();
                        }
                        newMatrix[i][i] = INT_MAX;
                    }
                    matrix = newMatrix;

                    SA.simulating_annealing(matrix, V);

                    elapsed = read_QPC() - start;

                    SA.display(matrix, V);

                    cout << ii+1 << "; ";
                }
                cout << endl;
                cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / (float)(frequency * iterations) << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * (double)elapsed) / (double)(frequency * iterations) << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * (double)elapsed) / (double)(frequency * iterations) << endl << endl;
                system("PAUSE");
                //do napisania funkcji skożystałem z:
                //link: http://staff.iiar.pwr.wroc.pl/antoni.sterna/sdizo/SDiZO_time.pdf
                break;
            }
            case 9:{
                bool mutation_t = true;//typ mutacji

                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                GeneticAlgorithm* G = new GeneticAlgorithm(matrix, V, mutation_t);
                G->solutionG(bestRoad, bestVal, tournament_size, mutation_p, crossover_p, population_size, generations);
//				G->solutionG100(bestRoad, bestVal, tournament_size, mutation_p, crossover_p, population_size, generations);

                elapsed = read_QPC() - start;
                cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / (float)frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * (double)elapsed) / (double)frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * (double)elapsed) / (double)frequency << endl << endl;
                for (int i = 0; i < V-1; i++){
                    cout << bestRoad[i] << " -(" << matrix[bestRoad[i]][bestRoad[i+1]] << ")-> ";
                }
                cout << bestRoad[V-1] << " -(" << matrix[bestRoad[V-1]][bestRoad[0]] << ")-> " << bestRoad[0] << endl;
                cout << "Calkowita droga: " << bestVal << endl;

                bestVal = INT_MAX;//najlepszy wynik
                bestRoad = new int [V];//tablica z wynikiem

                system("PAUSE");

                break;
            }
            case 10:{
                bool mutation_t = false;//typ mutacji

                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();

                GeneticAlgorithm* G = new GeneticAlgorithm(matrix, V, mutation_t);
                G->solutionG(bestRoad, bestVal, tournament_size, mutation_p, crossover_p, population_size, generations);
//				G->solutionG100(bestRoad, bestVal, tournament_size, mutation_p, crossover_p, population_size, generations);

                elapsed = read_QPC() - start;
                cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed / (float)frequency << endl;
                cout << "Time [ms] = " << setprecision(0) << (1000.0 * (double)elapsed) / (double)frequency << endl;
                cout << "Time [us] = " << setprecision(0) << (1000000.0 * (double)elapsed) / (double)frequency << endl << endl;
                for (int i = 0; i < V-1; i++){
                    cout << bestRoad[i] << " -(" << matrix[bestRoad[i]][bestRoad[i+1]] << ")-> ";
                }
                cout << bestRoad[V-1] << " -(" << matrix[bestRoad[V-1]][bestRoad[0]] << ")-> " << bestRoad[0] << endl;
                cout << "Calkowita droga: " << bestVal << endl;

                bestVal = INT_MAX;//najlepszy wynik
                bestRoad = new int [V];//tablica z wynikiem

                system("PAUSE");

                break;
            }
            case 0:{
                again = false;
                break;
            }
        }
    }
}
