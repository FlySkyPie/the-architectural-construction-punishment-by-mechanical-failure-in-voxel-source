#pragma once

#include <array>
#include "IComputableElement.h"
#include "IGravitationElement.h"
#include "IElementStatus.h"
#include "IElementResult.h"

#include "NewTypDefinition.h"

struct Capacitor {
  float energy;
  float energyBuffer;
  float oldEnergy;
};

class StructureElement : public IComputableElement, public IGravitationElement,
public IElementStatus, public IElementResult {
public:
  StructureElement(float mass, bool isBoundary, bool isSolid);
  ~StructureElement();
  //IGravitationElement
  void addGravitation(float gravitation);
  void addCorrection(float correction);

  //IElementStatus
  void updateDistributary(int axis, int direction, bool status);
  void setNeighbor(HexaheElement elements, HexaheDistributary distributary);
  bool isSolid();

  //IComputableElement
  void flowGravitation();
  void updateGravitation();
  void flowCorrection();
  void updateCorrection();

  //IElementResult
  float getGravitation();
  float getCorrection();
  float getCorrectedGravitation();

private:
  float mass;
  bool boundary;
  bool solid;

  Capacitor gravitaionCapacitor;
  Capacitor correctionCapacitor;

  HexaheElement  neighbors;
  HexaheDistributary distributary;

  float getGravitaionDifference();

};