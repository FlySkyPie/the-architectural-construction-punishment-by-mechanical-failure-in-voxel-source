#include "Node.h"

Node::Node(float mass, bool isBoundary, bool isSolid) {
  this->mass = mass;
  this->isBoundary = isBoundary;
  this->_isSolid = isSolid;

  this->energy = 0;
  this->energyBuffer = 0;

  this->contactedNode[0] = nullptr;
  this->contactedNode[1] = nullptr;
}

void Node::setContactedNodes(Node *Contact1, Node *Contact2) {
  this->contactedNode[0] = Contact1;
  this->contactedNode[1] = Contact2;
}

void Node::setContactedRightNode(Node *Contact) {
  this->contactedNode[1] = Contact;
}

void Node::setContactedLeftNode(Node *Contact) {
  this->contactedNode[0] = Contact;
}

void Node::addEnegy(float energy) {
  this->energyBuffer += energy;
}

void Node::flowEnergyToBuffer() {
  char allocation = 0;
  if (this->contactedNode[0]) {
    allocation += 1;
  }

  if (this->contactedNode[1]) {
    allocation += 1;
  }

  float value = this->energy / allocation;

  if (this->contactedNode[0]) {
    this->contactedNode[0]->addEnegy(value);
  }
  if (this->contactedNode[1]) {
    this->contactedNode[1]->addEnegy(value);
  }

  //natural flow
  this->energyBuffer += this->mass;
}

void Node::updateEnergy() {
  if(this->isBoundary){
    this->energyBuffer=0;
  }
  this->energy = this->energyBuffer;
  this->energyBuffer = 0;
}

float Node::getEnergy() {
  return this->energy;
}

bool Node::isSolid() {
  return this->_isSolid;
}