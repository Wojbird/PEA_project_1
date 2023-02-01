cmake_minimum_required(VERSION 3.23)
project(PEA_project_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(PEA_project_1 main.cpp Menu.cpp Menu.h DynamicProgramming.cpp DynamicProgramming.h Bruteforce.cpp Bruteforce.h SimulatingAnnealing.cpp SimulatingAnnealing.h GeneticAlgorithm.cpp GeneticAlgorithm.h)