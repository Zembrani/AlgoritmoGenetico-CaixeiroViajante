#include "Solution.cpp"
#include <vector>
#include <map>
#include "ObjectSolution.cpp"

using namespace std;

#if !defined(GENETIC)
#define GENETIC

typedef map<int, int> myMap;

struct Genetic {
  void run(vector<myMap> data, int population, int interactions, int qtNos, int mutationDegree, int survivals) {
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

    cout << "Geração 0" << endl;
    print(sucessSolution);

    int i = 0;
    vector <double> probabilityArray;

    while ( i < interactions) {
      //cout << "Geração " << i << endl;
      i++;
      if (nextGeneration.size() != 0) sucessSolution = nextGeneration;

      nextGeneration = createNextGeneration(sucessSolution, mutationDegree, survivals);
      
      //Avaliação das soluções
      vector < ObjectSolution > aux;
      for (int i = 0; i < population; i++) {
        Solution temp = nextGeneration[i].solution;
        aux.push_back(sucessAmount(data, temp, qtNos));
      }
      nextGeneration = aux;

      probabilityArray = probability(nextGeneration);
      nextGeneration = removeWorst(nextGeneration, (int)nextGeneration.size(), probabilityArray);
      // cout << "geração " << i << endl;
      // print(nextGeneration);
      // cout << "------------------" << endl;
    }
    
    //Ordenação do vetor de resultados ao gerar a saida final
    if (nextGeneration.size() > 1) {
      sucessSolution = mergeSort(nextGeneration);
    }
    cout << endl;
    cout << "Geração final" << endl;
    print(sucessSolution);

  }

  void print(vector < ObjectSolution > solution) {
    for (auto&& it : solution) {
      it.print();
    }
  }

  //Função que verifica a qualidade da solução
  //Considerando primeiro a maior quantidade de cidades visitadas (nodesVisited) e depois a menor distancia percorrida (distance).
  ObjectSolution sucessAmount(vector<myMap> data, Solution solution, int solutionSize) {
    int i;
    int sumDistance = 0;
    int distance = 1;

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
  vector< ObjectSolution > createNextGeneration(vector< ObjectSolution > solution, int mutationDegree, int survivals) {
    vector< ObjectSolution > newSolutions;
    vector <double> probabilityArray;

    int size = (int)solution.size();

    probabilityArray = probability(solution);
    // cout << "probabilidade " << endl;
    // for (int i = 0; i < size; i++) {
    //   cout << probabilityArray[i] << " ";
    // }
    // cout << endl;
    if (solution.size() > 1) {
      solution = mergeSort(solution);
    }

    //Isto é para propagar os melhores sobreviventes sem alterações
    int i = 0;
    for (; i < survivals; i++) {
      newSolutions.push_back(solution[0]);
      newSolutions.push_back(solution[1]);
    }
    for (; i < size; i++) {
      int mutate = select(size, probabilityArray);

      //Adiciona uma chance de o item não ser mutado, quanto melhor for a solução maior as chances
      if (mutate != i) { 
      //Realiza mutação com modify e modifyV2
      //solution[i].solution.modifyV2(mutationDegree, solution[i].nodesVisited);
      if (!solution[i].solution.wasModified) solution[i].solution.modify(mutationDegree);
      }

      newSolutions.push_back(solution[i]);
    }

    return newSolutions;
  }

//Remove as soluções que visitaram zero cidades e troca por outras cidades de acordo com a probabilidade
  vector< ObjectSolution > removeWorst(vector< ObjectSolution > solution, int size, vector <double> probability) {
    for (int i = 0; i < size; i++) {
      if (solution[i].nodesVisited == 0) {
        int selected = select(size, probability);
        //cout << " removendo os piores "; solution[i].print();
        //cout << " trocando por "; solution[selected].solution.print();
        solution[i].solution = solution[selected].solution;
      }
    }
    return solution;
  }


// --- Funções auxiliares ---
  //Função que gera o vetor com as probabilidades de cada solução
  vector < double > probability(vector< ObjectSolution > solution) {
    vector <double> probability;
    int sum = 0;
    double value  = 0.0;
    int size = (int)solution.size();

    for (int i = 0; i < size; i++) {
      sum += solution[i].nodesVisited;
    }

    for (int i = 0; i < size; i++) {
      value += probabilityValue(solution[i].nodesVisited, sum);
      probability.push_back(value);
    }
    return probability;
  }

  //Gera um valor double entre 0.1 e 10 de acordo a quantidade de nós visitados
  double probabilityValue(int nodesVisited, int sum) {
    double result = (nodesVisited * 1.0 / sum * 1.0) * 10;
    return nodesVisited != 0 ? result : 0;
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
    return size-1;
  }

};
#endif