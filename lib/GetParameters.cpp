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

    void read(string fileName) {
        myFile.open(fileName);
        if (!myFile.is_open())
            exit(1);

        myFile >> qtPopulation;
        myFile >> qtInteractions;

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
        cout << "**************************" << endl;
    }
};
#endif // FILEOPERATOR