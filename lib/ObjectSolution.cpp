#include <vector>
#include "Solution.cpp"

using namespace std;

#if !defined(OBJECTSOLUTION)
#define OBJECTSOLUTION

struct ObjectSolution {
  Solution solution;
  int nodesVisited;
  int distance;

  ObjectSolution(Solution solutionv, int nodesVisitedv, int distancev) {
    solution = solutionv;
    nodesVisited = nodesVisitedv;
    distance = distancev;
  }

  // ObjectSolution() {

  // }

  void print() {
    //cout << "Imprimindo a solução" << endl;
    cout << "( " << nodesVisited << ", " << distance << " ) - ";
    solution.print();
    //cout << "nós visitados = " << nodesVisited << " distancia percorrida = " << distance << endl;
    
    //cout << endl;
  }
};

#endif