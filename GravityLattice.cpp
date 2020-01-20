#include <iostream>
#include "GravityLattice.h"
#include "StructureElement.h"

GravityLattice::GravityLattice() {
  //this->createContinuous();
  this->createOverhanging();
}

GravityLattice::~GravityLattice() {
  //release StructureElements
  std::vector<StructureElement*>::iterator it;

  for (it = this->structureElements.begin(); it < this->structureElements.end(); it++) {
    delete *it;
  }
}

void GravityLattice::tick() {
  std::vector<StructureElement*>::iterator it;

  for (it = this->structureElements.begin(); it < this->structureElements.end(); it++) {
    (*it)->flowGravitation();
  }

  for (it = this->structureElements.begin(); it < this->structureElements.end(); it++) {
    (*it)->updateGravitation();
  }

  for (it = this->structureElements.begin(); it < this->structureElements.end(); it++) {
    (*it)->flowCorrection();
  }

  for (it = this->structureElements.begin(); it < this->structureElements.end(); it++) {
    (*it)->updateCorrection();
  }
}

void GravityLattice::printStatus() {
  std::vector<StructureElement*>::iterator it;
  for (it = this->structureElements.begin(); it < this->structureElements.end(); it++) {
    std::cout << (*it)->getGravitation() << ",";
  }
  std::cout << "\n";
}

void GravityLattice::createContinuous() {
  this->addStructureElement(1, 1, 1); //Fulcrum
  for (int i = 0; i < 10; i++) {
    this->addStructureElement(1, 0, 1);
  }
  this->addStructureElement(1, 1, 1); //Fulcrum
  for (int i = 0; i < 87; i++) {
    this->addStructureElement(1, 0, 1);
  }
  this->addStructureElement(1, 1, 1); //Fulcrum
}

void GravityLattice::createOverhanging() {
  this->addStructureElement(1, 0, 0); //air
  for (int i = 0; i < 10; i++) {
    this->addStructureElement(1, 0, 1);
  }
  this->addStructureElement(1, 1, 1); //Fulcrum
  for (int i = 0; i < 76; i++) {
    this->addStructureElement(1, 0, 1);
  }
  this->addStructureElement(1, 1, 1); //Fulcrum
  for (int i = 0; i < 10; i++) {
    this->addStructureElement(1, 0, 1);
  }
  this->addStructureElement(1, 0, 0); //air
}

void GravityLattice::addStructureElement(float mass, bool isBoundary, bool isSolid) {
  //std::cout << "mass: " << mass << ", isBoundary: " << isBoundary << ", isSolid: " << isSolid << "\n";

  StructureElement* StructureElement2 = new StructureElement(mass, isBoundary, isSolid);

  if (this->structureElements.size() == 0) {
    this->structureElements.push_back(StructureElement2);
    return;
  }

  StructureElement* StructureElement1 = this->structureElements.back();

  //std::cout << "StructureElement1->isSolid(): " << StructureElement1->isSolid() << "\n";

  if (StructureElement1->isSolid()) {
    StructureElement2->addNeighbor(0, 0, StructureElement1);
  }
  if (StructureElement2->isSolid()) {
    StructureElement1->addNeighbor(0, 1, StructureElement2);
  }

  this->structureElements.push_back(StructureElement2);
}