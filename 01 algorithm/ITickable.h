
#pragma once

class ITickable {
public:

  virtual ~ITickable() {
  }

  virtual void tick() = 0;
};