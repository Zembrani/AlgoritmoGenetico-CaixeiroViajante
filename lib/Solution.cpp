#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

#if !defined(SOLUTION)
#define SOLUTION

struct Solution {
  int qtInstances = 0;
  vector<int> solution = vector<int>(0);
  bool wasModified = false;

// Gera uma solucao aleatoria
  void generate(void) {
    // Se qtInstances não for setada retorna vetor vazio;
    if (!qtInstances) { solution = vector<int>(0); return; }

    if (!solution.empty()) solution.clear();
    // eng para usar no shuffle
    std::mt19937 eng{std::random_device{}()};

    // vera um vetor ordenado e entao embaralha, de 1 ate o numero de nos;
    for (int i = 1; i <= qtInstances; i++) {
        solution.push_back(i);
    }
    //Aumenta um no inicio para iniciar sempre pelo no 1 (facilita no while do sucessAmount)
    shuffle(solution.begin()+1, solution.end(), eng);
  }

//Realiza amountOfChanges alterações, cada alteração é consiste em fazer swap de dois nós.
  void modify(int amountOfChanges) {
    // Random functions 
    random_device rd;
    mt19937 gen(rd());
    //Manter o ponto de partida sempre do 1
    uniform_int_distribution<> distrib(1, qtInstances-1);
    // Real code
    for(int i=0; i < amountOfChanges; i++){
      int first = distrib(gen);
      int second = distrib(gen);
      flip(first, second);
    }
  }

//Realiza alterações apenas após o nó em que a solução falha. (altas chances de levar a ótimos locais)
  void modifyV2(int amountOfChanges, int startChange) {
    if (startChange >= qtInstances-1) {
      wasModified = false; 
      return;
    }
    random_device rd;
    mt19937 gen(rd());
    //Manter o ponto partida sempre do 1
    uniform_int_distribution<> distrib(startChange, qtInstances-1);
    // Real code
    for(int i=0; i < amountOfChanges; i++){
      int first = distrib(gen);
      int second = distrib(gen);
      flip(first, second);
    }
    wasModified = true;
  }

  void flip(int first, int second){
    int aux = solution[first];
    solution[first] = solution[second];
    solution[second] = aux;
  }

  void print(void) {
    //cout << "Possivel solucao" << endl;
    for (auto&& literal : solution) {
      cout << literal << " ";
    }
    cout << endl;
  }

  Solution() {

  }

  // Solution Constructor
  Solution(int n) {
    // Inicializa a estrutura
    qtInstances = n;
  }

  Solution(int n, vector<int> initialValues) {
    qtInstances = n;
    for (int i = 0; i < n; i++) {
      solution.push_back(initialValues[i]);
    }
  }

};

#endif