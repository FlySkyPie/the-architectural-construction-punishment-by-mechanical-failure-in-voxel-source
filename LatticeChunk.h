#pragma once

#include <array>
#include "StructureElement.h"
#include "IChunckStatus.h"
#include "ITickable.h"
#include "NewTypDefinition.h"

class LatticeChunk : public ITickable, public IChunckStatus {
public:
  LatticeChunk(ChunkMap chunkConfig);
  ~LatticeChunk();

  void tick();
  float getGravitation(int x, int y, int z) ;
  float getCorrection(int x, int y, int z) ;
  float getCorrectedGravitation(int x, int y, int z) ;

private:
  ChunkElements elements ;

  void createElements(ChunkMap chunkConfig);
  void updateElementConnections();
  void updateElementConnection(int x, int y, int z);

  HexaheElement getElementNeighbors(int x, int y, int z);
  HexaheDistributary getElementDistributary(HexaheElement neighbors);
  StructureElement * getElement(int x, int y, int z);
};