#include "lib/lib.hpp"

int main(int argc, char const* argv[]) {
  FileOperator file;
  GetParameters parameters;
  vector<myMap> data = file.read(file.fileName[0]);

  int qtNos = file.getNos();
  //Solution bestSolution(qtNos);
  //pair <int, int> bestSucess(100, 0);

  parameters.print(qtNos);
  int population = parameters.getPopulation();
  int interactions = parameters.getInteractions();

  Genetic genetic;
  genetic.run(data, population, interactions, qtNos);

  return 0;
}
