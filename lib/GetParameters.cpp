#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#if !defined(GETPARAMETERS)
#define GETPARAMETERS

struct GetParameters {
    string fileName = "parameters.txt";
    ifstream myFile;
    int qtPopulation;
    int qtInteractions;
    int mutation;
    int survival;
    int file;

    void read(string fileName) {
        myFile.open(fileName);
        if (!myFile.is_open())
            exit(1);

        myFile >> qtPopulation;
        myFile >> qtInteractions;
        myFile >> mutation;
        myFile >> survival;
        myFile >> file;

        myFile.close();
    }

    GetParameters() {
        read(fileName);
    }

    void print(int qtInstances) {
        cout << "*****  Parametros  ***** " << endl;
        cout << "\tQuantidade de interações : " << qtInteractions << endl;
        cout << "\tPopulação : " << qtPopulation << endl;
        cout << "\tNúmero de Nós : " << qtInstances << endl;
        cout << "\tNós para mutação : " << mutation << endl;
        cout << "\tQt de sobreviventes : " << survival << endl;
        cout << "\tArquivo : trainning" << file << ".txt" << endl;
        cout << "**************************" << endl;
    }

    int getPopulation() {
        return qtPopulation;
    }
    
    int getInteractions() {
        return qtInteractions;
    }

    int getMutation() {
        return mutation;
    }

    int getSurvival() {
        return survival;
    }

    int getFile() {
        return file;
    }
};
#endif