#pragma once

class IChunckStatus {
public:

  virtual ~IChunckStatus() {
  }

  virtual float getGravitation(int x, int y, int z) = 0;
  virtual float getCorrection(int x, int y, int z) = 0;
  virtual float getCorrectedGravitation(int x, int y, int z) = 0;

  virtual void tick() = 0;

};

