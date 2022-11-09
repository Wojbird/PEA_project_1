//
// Created by wojma on 07.11.2022.
//

#ifndef PEA_PROJECT_1_MENU_H
#define PEA_PROJECT_1_MENU_H

#include <windows.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <string>

using namespace std;

class Menu {
    public:
        Menu();
        ~Menu();

        void start();
    private:
        bool again;
        int choice;
        string name;
        string type;
        string comment;
        int V;
        string edge_weight_type;
        string edge_weight_format;
        int **matrix;
        void display();
};


#endif //PEA_PROJECT_1_MENU_H
