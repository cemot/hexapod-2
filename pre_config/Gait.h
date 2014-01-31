#ifndef GAIT_H
#define GAIT_H

#include "Legservos.h"

class Gait {
  public:
    Gait();
    
    int walk(directions);
    
    int strafe(directions);
  
  private:
};

#endif
