#pragma once

class IElementComputable {
public:

  virtual ~IElementComputable() {
  }

  virtual void flowGravitation() = 0;
  virtual void updateGravitation() = 0;
  virtual void flowCorrection() = 0;
  virtual void updateCorrection() = 0;
  virtual void updateYield() = 0;
};

