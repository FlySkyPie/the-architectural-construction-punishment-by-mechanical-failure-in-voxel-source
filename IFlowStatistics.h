#pragma once

class IFlowStatistics {
public:

  virtual ~IFlowStatistics() {
  }

  virtual float getGravitation() = 0;
  virtual float getCorrection() = 0;
  virtual float getCorrectedGravitation() = 0;
};

