#pragma once

#include <array>
#include "IElementComputable.h"
#include "IElementBoundary.h"
#include "IElementLink.h"
#include "IElementStatus.h"

#include "NewTypDefinition.h"

struct Capacitor {
  float energy;
  float energyBuffer;
  float oldEnergy;
};

class StructureElement : public IElementComputable, public IElementBoundary,
public IElementLink, public IElementStatus {
public:
  StructureElement(float mass, bool isBoundary, bool isSolid);
  ~StructureElement();
  //IElementBoundary
  void addGravitation(float gravitation);
  void addCorrection(float correction);
  void updateDistributary(int axis, int direction, bool status);

  //IElementLink
  void setNeighbor(HexaheElement elements, HexaheDistributary distributary);

  //IElementComputable
  void flowGravitation();
  void updateGravitation();
  void flowCorrection();
  void updateCorrection();
  bool updateYield();

  //IElementStatus
  float getGravitation();
  float getCorrection();
  float getCorrectedGravitation();
  bool isSolid();

private:
  float mass;
  /*
   * The boundary of gravitation,
   * used to remove gravitation under bottom of chunk.
   */
  bool boundary;
  float yieldPoint;
  bool solid;

  Capacitor gravitaionCapacitor;
  Capacitor correctionCapacitor;

  HexaheElement neighbors;
  HexaheDistributary distributary;

  float getGravitaionDifference();
  void yield();
  void initCapacitor();

};