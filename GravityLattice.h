#pragma once
#include "Node.h"
#include <vector>

class GravityLattice{
public:
  GravityLattice();
  ~GravityLattice();
  void tick();
  void printStatus();
private:
  void createContinuous();
  void createOverhanging();
  
  void addNode(float mass, bool isBoundary, bool isSolid);
  
  std::vector <Node*> nodes;
};