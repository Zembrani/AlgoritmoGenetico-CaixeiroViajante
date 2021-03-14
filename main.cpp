#include "lib/lib.hpp"

int main(int argc, char const* argv[]) {
  FileOperator file;
  GetParameters parameters;

  int population = parameters.getPopulation();
  int interactions = parameters.getInteractions();
  int mutationDegree = parameters.getMutation();
  int survival = parameters.getSurvival();
  int numberFile = parameters.getFile() - 1;

  vector<myMap> data = file.read(file.fileName[numberFile]);
  int qtNos = file.getNos();

  parameters.print(qtNos);

  Genetic genetic;
  genetic.run(data, population, interactions, qtNos, mutationDegree, survival);

  return 0;
}
