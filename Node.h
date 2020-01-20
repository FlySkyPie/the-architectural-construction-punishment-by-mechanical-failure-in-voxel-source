#pragma once

class Node {
public:
  Node(float mass, bool isBoundary, bool isSolid);

  void setContactedNodes(Node *Contact1, Node *Contact2);
  void setContactedRightNode(Node *Contact);
  void setContactedLeftNode(Node *Contact);
  void addEnegy(float energy);

  //void addGravityFlow();
  void flowEnergyToBuffer();
  void updateEnergy();

  float getEnergy();
  bool isSolid();
private:
  bool isBoundary;
  bool _isSolid;
  //bool **isContact;
  Node *contactedNode[2];
  float mass;
  float energy;
  float energyBuffer;
};