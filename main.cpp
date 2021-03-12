#include "lib/lib.hpp"

  pair<int, int> sucessAmount(vector<myMap> data, Solution solution, int solutionSize) {
    int i;
    int sumDistance = 0;
    int distance = 0;

    for (i = 0; i < solutionSize-1; i++) {
      if (data[solution.solution[i]][solution.solution[i+1]] != 0) {
        sumDistance += data[solution.solution[i]][solution.solution[i+1]];
        distance++;
      } else {
        pair<int, int> sucessValues(sumDistance, distance);
        return sucessValues;
      }
    }
    if (data[solution.solution[i]][solution.solution[0]] != 0) {
        sumDistance += data[solution.solution[i]][solution.solution[0]];
        distance++;
      } else {
        pair<int, int> sucessValues(sumDistance, distance);
        return sucessValues;
      }
      pair<int, int> sucessValues(sumDistance, distance);
      return sucessValues;
  };

int main(int argc, char const* argv[]) {
  FileOperator file;
  GetParameters parameters;
  vector<myMap> data = file.read(file.fileName[0]);

  int qtNos = file.getNos();
  Solution bestSolution(qtNos);
  pair <int, int> bestSucess(100, 0);
  //vector<int> teste = {1,7,6,3,4,5,2};
  parameters.print(qtNos);
  
  for (int i = 0; i < parameters.qtPopulation; i++) {
    Solution solution(qtNos);
    solution.generate();
    //solution.print();
    pair<int, int> result = sucessAmount(data, solution, qtNos);
    //cout << "Soma das distancias " << result.first << ", cidades visitadas " << result.second << endl;
    if (bestSucess.second < result.second) {
      bestSucess = result;
      bestSolution = solution;
    } else if (bestSucess.second == result.second) {
      bestSucess = bestSucess.first > result.first ? result : bestSucess;
      bestSolution = solution;
    }
  }
  cout << "melhor solução "; 
  bestSolution.print();
  cout << "Soma das distancias " << bestSucess.first << ", cidades visitadas " << bestSucess.second << endl;

  return 0;
}
