//
// Created by wojma on 14.12.2022.
//

#ifndef PEA_PROJECT_1_SIMULATINGANNEALING_H
#define PEA_PROJECT_1_SIMULATINGANNEALING_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>
#include <cmath>
#include <windows.h>
#include <iomanip>

using namespace std;

class SimulatingAnnealing {
    public:
        SimulatingAnnealing();

        void simulating_annealing(int** matrix, int V);
        void display(int** matrix, int V);
    private:
        int minSum;
        int *path;
};


#endif //PEA_PROJECT_1_SIMULATINGANNEALING_H
