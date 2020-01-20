#include <iostream>
#include "GravityLattice.h"
#include "Node.h"

GravityLattice::GravityLattice() {
  //this->createContinuous();
  this->createOverhanging();
}

GravityLattice::~GravityLattice() {
  //release nodes
  std::vector<Node*>::iterator it;

  for (it = this->nodes.begin(); it < this->nodes.end(); it++) {
    delete *it;
  }
}

void GravityLattice::tick() {
  std::vector<Node*>::iterator it;

  for (it = this->nodes.begin(); it < this->nodes.end(); it++) {
    (*it)->flowEnergyToBuffer();
  }

  for (it = this->nodes.begin(); it < this->nodes.end(); it++) {
    (*it)->updateEnergy();
  }
}

void GravityLattice::printStatus() {
  std::vector<Node*>::iterator it;
  for (it = this->nodes.begin(); it < this->nodes.end(); it++) {
    std::cout << (*it)->getEnergy() << ",";
  }
  std::cout << "\n";
}

void GravityLattice::createContinuous() {
  this->addNode(1, 1, 1); //Fulcrum
  for (int i = 0; i < 10; i++) {
    this->addNode(1, 0, 1);
  }
  this->addNode(1, 1, 1); //Fulcrum
  for (int i = 0; i < 87; i++) {
    this->addNode(1, 0, 1);
  }
  this->addNode(1, 1, 1); //Fulcrum
}

void GravityLattice::createOverhanging() {
  this->addNode(1, 0, 0); //air
  for (int i = 0; i < 10; i++) {
    this->addNode(1, 0, 1);
  }
  this->addNode(1, 1, 1); //Fulcrum
  for (int i = 0; i < 76; i++) {
    this->addNode(1, 0, 1);
  }
  this->addNode(1, 1, 1); //Fulcrum
  for (int i = 0; i < 10; i++) {
    this->addNode(1, 0, 1);
  }
  this->addNode(1, 0, 0); //air
}

void GravityLattice::addNode(float mass, bool isBoundary, bool isSolid) {
  Node* node2 = new Node(mass, isBoundary, isSolid);

  if (this->nodes.size() == 0) {
    this->nodes.push_back(node2);
    return;
  }

  Node* node1 = this->nodes.back();

  if (node1->isSolid()) {
    node2->setContactedLeftNode(node1);
  }
  if (node2->isSolid()) {
    node1->setContactedRightNode(node2);
  }


  this->nodes.push_back(node2);
}