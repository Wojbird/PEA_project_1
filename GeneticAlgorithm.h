//
// Created by wojma on 24.01.2023.
//

#ifndef PEA_PROJECT_1_GENETICALGORITHM_H
#define PEA_PROJECT_1_GENETICALGORITHM_H

#include <algorithm>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iostream>
#include<bits/stdc++.h>

using namespace std;

class GeneticAlgorithm {
    public:
        GeneticAlgorithm(int** matrix, int V, bool mutation_type);
        int countSum(vector<int> sciezka);
        void solutionG(int* bestRoad, int &bestVal, int tournament_size, float mutation_prob, float crossover_prob, int population_size, int generations);
        void solutionG100(int* bestRoad, int &bestVal, int tournament_size, float mutation_prob, float crossover_prob, int population_size, int generations);
        void crossOX(vector<int> &parent1, vector<int> &parent2);
        void mutationInsertion(vector<int> &chiled);
        void mutationInversion(vector<int> &chiled);
        void crossover(vector<vector <int> > &population, vector<vector<int> > &newPopulation, float crossover_prob);
        void mutation(vector<vector<int> > &population, float mutation_prob);
        void selectionTournament(vector<vector<int> > &population, int tournament_size, int population_size);
        void saveBest(vector < vector<int> > &population, int* bestRoad, int &bestVal);

    private:
        int** matrix;
        int V;
        bool mutation_type;
};


#endif //PEA_PROJECT_1_GENETICALGORITHM_H
