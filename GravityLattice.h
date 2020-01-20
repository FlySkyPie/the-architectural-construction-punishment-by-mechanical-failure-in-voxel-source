#pragma once
#include "StructureElement.h"
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
  
  void addStructureElement(float mass, bool isBoundary, bool isSolid);
  
  std::vector <StructureElement*> structureElements;
};