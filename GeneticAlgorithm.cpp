//
// Created by wojma on 24.01.2023.
//

#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(int** matrix, int V, bool mutation_type){
    this->matrix = matrix;//macierz
    this->V = V;//rozmiar
    this->mutation_type = mutation_type;//typ mutcji
}

void GeneticAlgorithm::selectionTournament(vector<vector<int> > &population, int tournament_size, int population_size){
    vector<vector<int> > newPopulation;
    for (int i = 0;i < population_size; i++){
        int best = INT_MAX;
        int best_index, r, sum;
        for (int j = 0;j < tournament_size; j++){
            r = rand() % population.size();//losujemy do turnieju
            sum = countSum(population.at(r));//sprawdzamy wagi
            if (sum < best){//wybieramy najlepszego
                best_index = r;
                best = sum;
            }
        }
        newPopulation.push_back(population.at(best_index));
    }
    population = newPopulation;
}

void GeneticAlgorithm::crossover(vector<vector<int> > &population, vector<vector<int> > &newPopulation, float crossover_prob){
    vector<int> parent1;
    vector<int> parent2;
    for (int i = 0;i < population.size()*crossover_prob;i++){//szansa na skrzyzowanie
        int x1, x2;
        do {//losujmey rodzic�w do krzyzowania
            x1 = rand() % population.size();
            x2 = rand() % population.size();
        } while (x1 == x2);
        parent1 = population.at(x1);
        parent2 = population.at(x2);
        crossOX(parent1, parent2);//order crossover
        newPopulation.push_back(parent1);
        newPopulation.push_back(parent2);
    }
}

void GeneticAlgorithm::crossOX(vector<int>& parent1, vector<int>& parent2)//order crossover
{
    vector <int> child1(V);
    vector <int> child2(V);
    int x1, x2;
    do{//losujemy pocz�tek i koniec fragmentu do skrzyzowania
        x1 = rand() % V;
        x2 = rand() % V;
    } while (x1 == x2);
    if (x2 < x1){//naprawiamy losoawnie
        swap(x1, x2);
    }
    move(parent1.begin() + x1, parent1.begin() + x2, child1.begin() + x1);//umieszczamy f1 => d1
    move(parent2.begin() + x1, parent2.begin() + x2, child2.begin() + x1);//umieszczamy f2 => d2
    int index[2] = { x2, x2 };
    for (int i = x2; i < V + x2; i++){//sprawdzamy czy si� powtarza w fragmentach
        bool check[2] = { true, true };
        for (int j = x1; j < x2; j++){
            if (parent1.at(j) == parent2.at(i % V)) check[0] = false;
            if (parent2.at(j) == parent1.at(i % V)) check[1] = false;
        }
        if (check[0]){//jak nie to uzupeniamy d1 (w przecciwnym wypadku przesuawamy si� dalej po r2)
            child1.at(index[0]) = parent2.at(i % V);
            index[0]++;
            index[0] %= V;
        }
        if (check[1]){//jak nie to uzupeniamy d2 (w przecciwnym wypadku przesuawamy si� dalej po r1)
            child2.at(index[1]) = parent1.at(i % V);
            index[1]++;
            index[1] %= V;
        }
    }
    parent1 = child1;//zast�pujemy
    parent2 = child2;
}

void GeneticAlgorithm::mutation(vector<vector<int> > &population, float mutation_prob){
    for (int i = 0;i < population.size();i++){//sprawdzamy czy mutuje i kt�ra mutacja
        double p = (double)rand() / RAND_MAX;
        if (p < mutation_prob){
            if (mutation_type == true){
                mutationInversion(population.at(i));
            }
            else {
                mutationInsertion(population.at(i));
            }
        }
    }
}

void GeneticAlgorithm::mutationInsertion(vector<int>& child){//mutacja prze transportacj� => przesuwamy ca�o�� i wstawiaymy wylosowany element
    int i, j;
    do{
        i = rand() % V;
        j = rand() % V;
    } while (i == j);
    if (i > j){
        swap(i, j);
    }
    int temp = child.at(j);
    for (int k = j; k > i; k--){
        child.at(k) = child.at(k-1);
    }
    child.at(i) = temp;
}

void GeneticAlgorithm::mutationInversion(vector<int>& child){//mutacja prze inwersj� => zamieniamy stronami
    int i, j;
    do{
        i = rand() % V;
        j = rand() % V;
    } while (i == j);
    if (i > j){
        swap(i, j);
    }
    for (int k = 0; k < (j - i) / 2; k++){
        swap(child.at(i + k), child.at(j - k));
    }
}

void GeneticAlgorithm::saveBest(vector < vector<int> >& population, int* bestRoad, int &bestVal){
    int min_sum = INT_MAX;
    int sum;
    vector<int> best;
    for (int i = 0; i < population.size(); i++){
        sum = countSum(population.at(i));
        if (min_sum > sum){//szukamy najlepszego osobnika w danej populacji
            min_sum = sum;
            best = population.at(i);
        }
    }
    if (bestVal > min_sum){//nadpisujemmy
        for(int i = 0; i < V; i++){
            bestRoad[i] = best.at(i);
        }
        bestVal = min_sum;
    }
}

int GeneticAlgorithm::countSum(vector<int> cities) {//zliczamu wagi
    int sum = 0;
    for (int i = 0; i < cities.size() - 1; ++i) {
        sum += matrix[cities[i]][cities[i + 1]];
    }
    sum += matrix[cities[V - 1]][cities[0]];
    return sum;
}

void GeneticAlgorithm::solutionG(int* bestRoad, int &bestVal, int tournament_size, float mutation_prob, float crossover_prob, int population_size, int generations){
    vector<vector<int> > population;//aktualna populacja
    vector<vector<int> > newPopulation;//nowa populacja
    vector<int> entity;//osobnik
    for (int i = 0;i < V;i++){
        entity.push_back(i);//generujemy pierwszego osobnika
    }
    for (int i = 0; i < population_size; i++){
        random_shuffle(entity.begin(), entity.end());//generujemy piersze pokolenie
        population.push_back(entity);
    }
    for (int g = 0; g < generations; g++){
        selectionTournament(population, tournament_size, population_size);//selekcja turniejowa
        newPopulation = population;//zapisanie populacji
        crossover(population, newPopulation, crossover_prob);//krzyzowanie
        mutation(newPopulation, mutation_prob);//mutacja
        population = newPopulation;//nadpisanie starej populacji
        newPopulation.clear();
        saveBest(population, bestRoad, bestVal);//zapami�tujemy najlepsze osobniki w danym pokoleniu
    }
}

//void Genetic::solutionG100(int* bestRoad, int &bestVal, int tournament_size, float mutation_prob, float crossover_prob, int population_size, int generations){
//	int najlepszy = 2755.0;
//  int licznik = 0;
//  bestVal = INT_MAX;//najlepszy wynik
//	bestRoad = new int [V];//tablica z wynikiem
//	population_size = 150;//liczba osobnik�w w pokoleniu
//	generations = 100;//liczba pokolen
//	tournament_size = 5;
//	crossover_prob = 0.85;//prawdopodobienstwo wyst�pienia krzyzowania
//	mutation_prob = 0.09;//prawdopodobienstwo mutacji
//	for (int z = 0; z <100; z++){
//		vector<vector<int> > population;
//		vector<vector<int> > newPopulation;
//		vector<int> entity;
//		for (int i = 0;i < V;i++){
//			entity.push_back(i);
//		}
//		for (int i = 0; i < population_size; i++){
//			random_shuffle(entity.begin(), entity.end());
//			population.push_back(entity);
//		}
//		for (int g = 0; g < generations; g++){
//			selectionTournament(population, tournament_size, population_size);
//			newPopulation = population;
//			crossover(population, newPopulation, crossover_prob);
//			mutation(newPopulation, mutation_prob);
//			population = newPopulation;
//			newPopulation.clear();
//			saveBest(population, bestRoad, bestVal);
//		}
//		population.clear();
//		licznik = licznik + (bestVal - najlepszy);
//	}
//	cout << endl;
//	cout << licznik << endl;
//	cout << endl;
//}
