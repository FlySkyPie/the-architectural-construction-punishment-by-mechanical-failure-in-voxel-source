#pragma once

class IComputableElement {
public:

  virtual ~IComputableElement() {
  }

  virtual void flowGravitation() = 0;
  virtual void updateGravitation() = 0;
  virtual void flowCorrection() = 0;
  virtual void updateCorrection() = 0;
};

