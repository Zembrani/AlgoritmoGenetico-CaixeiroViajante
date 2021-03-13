#include "Solution.cpp"
#include <vector>
#include <map>
#include "ObjectSolution.cpp"

using namespace std;

#if !defined(GENETIC)
#define GENETIC

typedef map<int, int> myMap;

struct Genetic {
  void run(vector<myMap> data, int population, int interactions, int qtNos) {
    vector <Solution> solutions;
    vector < ObjectSolution > sucessSolution;
    vector < ObjectSolution > nextGeneration;
    
    //Criando a população
    for (int i = 0; i < population; i++) {
        Solution solution(qtNos);
        solution.generate();
        solutions.push_back(solution);
    }

    //Avaliação das soluções
    for (int i = 0; i < population; i++) {
      Solution temp = solutions[i];
      sucessSolution.push_back(sucessAmount(data, temp, qtNos));
    }


    //Ordenação do vetor de resultados
    if (sucessSolution.size() > 1) {
      sucessSolution = mergeSort(sucessSolution);
    }

    for (auto&& it : sucessSolution) {
      it.print();
    }

    cout << "entrando no while" << endl;
    int i = 0;
    while ( i < interactions) {
      i++;
      if (nextGeneration.size() != 0) sucessSolution = nextGeneration;

      nextGeneration = createNextGeneration(sucessSolution);
      
      //Avaliação das soluções
      vector < ObjectSolution > aux;
      for (int i = 0; i < population; i++) {
        Solution temp = nextGeneration[i].solution;
        aux.push_back(sucessAmount(data, temp, qtNos));
      }
      nextGeneration = aux;

      for (auto&& it : sucessSolution) {
        it.print();
      }
    }

  }

  //Função que verifica a qualidade da solução
  //Considerando primeiro a maior quantidade de cidades visitadas (nodesVisited) e depois a menor distancia percorrida (distance).
  ObjectSolution sucessAmount(vector<myMap> data, Solution solution, int solutionSize) {
    int i;
    int sumDistance = 0;
    int distance = 0;

    for (i = 0; i < solutionSize-1; i++) {
      if (data[solution.solution[i]][solution.solution[i+1]] != 0) {
        sumDistance += data[solution.solution[i]][solution.solution[i+1]];
        distance++;
      } else {
        ObjectSolution objectSolution(solution, distance, sumDistance);
        return objectSolution;
      }
    }
    if (data[solution.solution[i]][solution.solution[0]] != 0) {
        sumDistance += data[solution.solution[i]][solution.solution[0]];
        distance++;
      } else {
        ObjectSolution objectSolution(solution, distance, sumDistance);
        return objectSolution;
      }
      ObjectSolution objectSolution(solution, distance, sumDistance);
      return objectSolution;
  };

//Função de ordenação utilizando merge sort
  vector< ObjectSolution > mergeSort(vector < ObjectSolution > solution) {
    int size = (int)solution.size();
    //Fim da chamada recursiva
    if (size <= 1) return solution;

    vector < ObjectSolution > merge1;
    vector < ObjectSolution > merge2;
    vector < ObjectSolution > result;

    // Divisão do vetor em duas partes
    int k;
    for (k = 0; k < size/2; k++) {
      merge1.push_back(solution[k]);
    }
    for (; k < size; k++) {
      merge2.push_back(solution[k]);
    }

    // Chamada recursiva
    merge1 = mergeSort(merge1);
    merge2 = mergeSort(merge2);

    int merge1Size = (int)merge1.size();
    int merge2Size = (int)merge2.size();
    int i = 0; int j = 0;

    while (i < merge1Size || j < merge2Size) {
      //saida do while, quando um vetor terminar aloca tudo que sobrou do outro
      if (i == merge1Size && j < merge2Size) {
        for (int m = j; m < merge2Size; m++) result.push_back(merge2[m]);
        return result;
      } 
      if (j == merge2Size && i < merge1Size)  {
        for (int m = i; m < merge1Size; m++) result.push_back(merge1[m]);
        return result;
      }
      //Verificação por quem visitou mais cidades (nodesVisited) na menor distancia (distance)
      if (merge1[i].nodesVisited > merge2[j].nodesVisited) {
          result.push_back(merge1[i]);
          i++;
        } else if (merge1[i].nodesVisited == merge2[j].nodesVisited) {
            if (merge1[i].distance < merge2[j].distance) {
              result.push_back(merge1[i]);    
              i++;
            } else {
              result.push_back(merge2[j]);    
              j++;
            }
        } else {
          result.push_back(merge2[j]);
          j++;
        }
    }
    return result;
  }

//Realiza a seleção probabilistica e gera um novo vetor com as soluções modificadas
  vector< ObjectSolution > createNextGeneration(vector< ObjectSolution > solution) {
    vector <double> probability;
    vector< ObjectSolution > newSolutions;

    int size = (int)solution.size();
    int sum = 0;

    for (int i = 0; i < size; i++) {
      sum += solution[i].nodesVisited;
    }

    double value  = 0.0;
    for (int i = 0; i < size; i++) {
      value += probabilityValue(solution[i].nodesVisited, sum);
      probability.push_back(value);
    }

    // cout << "probabilidade " << endl;
    // for (int i = 0; i < size; i++) {
    //   cout << probability[i] << " ";
    // }
    // cout << endl;

    for (int i = 0; i < size; i++) {
      int mutate = select(size, probability);
      cout << "solução a ser mutada " << mutate << endl;

      solution[mutate].solution.modify(1);
      newSolutions.push_back(solution[mutate]);
    }
    return newSolutions;
  }



// --- Funções auxiliares ---


  //Gera um valor double entre 0.1 e 10 de acordo a quantidade de nós visitados
  double probabilityValue(int nodesVisited, int sum) {
    return (nodesVisited * 1.0 / sum * 1.0) * 10;
  }

  //Função para selecionar probabilisticamente uma solução
  int select(int size, vector <double> probability) {
    //Rambom para gera um double aletatório
    random_device rd;
    default_random_engine gen(rd());
    uniform_real_distribution<double> distrib(0.1, size);

    double item = distrib(gen);

    for (int i = 0; i < size; i++) {
      if (item < probability[i]) return i;
    }
    return 0;
  }

};
#endif