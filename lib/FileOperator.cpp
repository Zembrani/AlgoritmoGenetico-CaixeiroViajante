#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#if !defined(FILEOPERATOR)
#define FILEOPERATOR

typedef map<int, int> myMap;

struct FileOperator {
  vector<string> fileName = {"trainning.txt"};
  ifstream myFile;
  int qtNos;

  void listOptions(void) {
    long unsigned int i;
    for (i = 0; i < fileName.size(); i++) {
      cout << fileName[i] << endl;
    }
  };

// Faz a leitura do arquivo e retorna o vetor de dados
  vector<myMap> read(string fileName) {
    int values[3];
    myFile.open(fileName);
    if (!myFile.is_open())
      exit(1);

    myFile >> qtNos;
    vector <myMap> data(qtNos+1);

    while (!myFile.eof()) {
      myFile >> values[0] >> values[1] >> values[2];
      //cout << values[0] << " " << values[1] << " " << values[2] << " " << endl;
      data[values[0]].insert(myMap::value_type(values[1], values[2]));
      data[values[1]].insert(myMap::value_type(values[0], values[2]));
    }
    myFile.close();
    //printData(data);
    return data;
    }

    int getNos() {
        return qtNos;
    }

  // Imprime o vetor com os nós
    void printData(vector<myMap> data) {
      for (int i = 0; i < (int)data.size(); i++) {
        for (myMap::iterator it = data[i].begin(); it != data[i].end(); it++){
          cout << i << " " << it->first << " " << it->second << endl;
        }
      }
    }

};
#endif // FILEOPERATOR