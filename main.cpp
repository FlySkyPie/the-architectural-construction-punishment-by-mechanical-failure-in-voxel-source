#include  "GravityLattice.h"


int main(){
  GravityLattice g;
  for(int i=0;i<1000;i++){
    g.tick();
    g.printStatus();
  }
  return 0;
}