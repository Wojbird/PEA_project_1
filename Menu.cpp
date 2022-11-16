//
// Created by wojma on 07.11.2022.
//

#include "Menu.h"
#include "DynamicProgramming.h"
#include "Bruteforce.h"

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
    srand(time(nullptr));
    again = true;
    cout << endl << "Implementacja algorytmu podzialu i ograniczen dla asymetrycznego problemu komiwojażera." << endl;
    cout << endl << "Autor: Wojciech Makuch" << endl;
    while(again){
        cout << endl << "Wybierz opcje:" << endl;
        cout << "1) Wczytanie pliku." << endl;
        cout << "2) Wczytanie losowej drogi" << endl;
        cout << "3) Wyswietlenie macierzy" << endl;
        cout << "4) Brute force." << endl;
        cout << "5) Programowanie dynamiczne." << endl;
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
            case 41:{
                int iterations, v;
                cout << endl << "Podaj liczbe iteracji: ";
                cin >> iterations;
                cout << endl << "Podaj liczbe wierzcholkow: ";
                cin >> v;
                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();
                for (int ii = 0; ii < iterations; ii++){
                    Bruteforce BF;
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

//                    BF.display(matrix, V);

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
            case 5:{
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
            case 51:{
                int iterations, v;
                cout << endl << "Podaj liczbe iteracji: ";
                cin >> iterations;
                cout << endl << "Podaj liczbe wierzcholkow: ";
                cin >> v;
                cout << endl;
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = read_QPC();
                for (int ii = 0; ii < iterations; ii++){
                    DynamicProgramming DP;
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

//                    DP.display(matrix, V);

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
            case 0:{
                again = false;
                break;
            }
        }
    }
}
