#pragma once

class IFlowControlled {
public:

  virtual ~IFlowControlled() {
  }

  virtual void flowGravitation() = 0;
  virtual void updateGravitation() = 0;
  virtual void flowCorrection() = 0;
  virtual void updateCorrection() = 0;
};

