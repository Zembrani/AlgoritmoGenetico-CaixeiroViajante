#include "lib/lib.hpp"
#include <sys/time.h>

double wtime() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec + (double) t.tv_usec / 1000000;
}

int main(int argc, char const* argv[]) {
  FileOperator file;
  GetParameters parameters;
  double initialTime, finalTime;

  int population = parameters.getPopulation();
  int interactions = parameters.getInteractions();
  int mutationDegree = parameters.getMutation();
  int survival = parameters.getSurvival();
  int numberFile = parameters.getFile() - 1;

  vector<myMap> data = file.read(file.fileName[numberFile]);
  int qtNos = file.getNos();

  parameters.print(qtNos);

  Genetic genetic;
  initialTime = wtime();
  genetic.run(data, population, interactions, qtNos, mutationDegree, survival);
  finalTime = wtime();
  cout << "Time: " << finalTime - initialTime << endl;

  return 0;
}
