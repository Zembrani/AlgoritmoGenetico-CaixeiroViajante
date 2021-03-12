#include <vector>
#include <random>
#include <iostream>

using namespace std;

#if !defined(OBJECT)
#define OBJECT

struct Object {
  int start, end, distance;
  Object(int rcv1, int rcv2, int rcv3) {
    start = rcv1;
    end = rcv2;
    distance = rcv3;
  };

  int testSolution(vector<Object> instances, vector<int> solution) {
    int count;
    long unsigned int i;
      for (i = 0; i < solution.size(); i++) {
        //Caso a proxima cidade a ser visitada nao esteja definida como vizinha da cidade i, retorna 10
        count += (instances[solution[i]].end == solution[i+1]) ? instances[solution[i]].distance : 10;
      }
      return count;
  };

  void print() {
      cout << start << " " << end << " " << distance << endl;
  }
};
#endif
