//
// Created by wojma on 07.11.2022.
//

#ifndef PEA_PROJECT_1_DYNAMICPROGRAMMING_H
#define PEA_PROJECT_1_DYNAMICPROGRAMMING_H

#include <iostream>

using namespace std;

class DynamicProgramming {
    public:
        DynamicProgramming();

        void dynamic_programming(int** matrix, int V);
        void display(int **matrix, int V);
    private:
        int minSum;
        int *shortestPath;
};


#endif //PEA_PROJECT_1_DYNAMICPROGRAMMING_H