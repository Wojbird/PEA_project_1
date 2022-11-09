//
// Created by wojma on 07.11.2022.
//

#ifndef PEA_PROJECT_1_BRUTEFORCE_H
#define PEA_PROJECT_1_BRUTEFORCE_H

#include <iostream>

using namespace std;

class Bruteforce {
    public:
        Bruteforce();

        void bruteforce(int** matrix, int V);
        void display(int **matrix, int V);
    private:
        int minSum;
        int *shortestPath;
        void permutation(int** matrix, int* cities, int begin, int end, int V, int* path);
};


#endif //PEA_PROJECT_1_BRUTEFORCE_H
