#pragma once

#include "IFlowControlled.h"
#include "IFlowElement.h"
#include "IFlowRegisted.h"
#include "IFlowStatistics.h"

struct Capacitor {
  float energy;
  float energyBuffer;
  float oldEnergy;
};

class StructureElement : public IFlowControlled, public IFlowElement,
public IFlowRegisted, public IFlowStatistics {
public:
  StructureElement(float mass, bool isBoundary, bool isSolid);

  //IFlowElement 
  void addGravitation(float gravitation);
  void addCorrection(float correction);

  //IFlowRegisted
  void addNeighbor(uint16_t axis, bool direction, IFlowElement *element);
  bool isSolid();

  //IFlowControlled
  void flowGravitation();
  void updateGravitation();
  void flowCorrection();
  void updateCorrection();

  //IFlowStatistic
  float getGravitation();
  float getCorrection();
  float getCorrectedGravitation();

private:
  float mass;
  bool boundary;
  bool solid;

  Capacitor gravitaionCapacitor;
  Capacitor correctionCapacitor;

  IFlowElement* neighbors [3][2];

  float getGravitaionDifference();

};