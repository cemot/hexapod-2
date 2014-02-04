#include "Gait.h"

Gait::Gait(Limb& LimbA, Limb& LimbB, Limb& LimbC, Limb& LimbD, Limb& LimbE, Limb& LimbF) {
  mLimbA = &LimbA;
  mLimbB = &LimbB;
  mLimbC = &LimbC;
  mLimbD = &LimbD;
  mLimbE = &LimbE;
  mLimbF = &LimbF;
}

int Gait::walk(directions directn) {
   switch(directn)  {
      case FORWARD:
        mLimbA->walk(BACKWARD, LEFT, FORWARD);
        // adjusts the B leg || left
        mLimbB->adjustBLeg(true, 20);
        mLimbB->walk(FORWARD, LEFT, FORWARD);
        mLimbC->walk(BACKWARD, LEFT, FORWARD);
        
        mLimbD->walk(FORWARD, RIGHT, FORWARD);
        mLimbE->walk(BACKWARD, RIGHT, FORWARD);
        mLimbF->walk(FORWARD, RIGHT, FORWARD);
        break;
        
      case BACKWARD:
        mLimbA->walk(BACKWARD, LEFT, BACKWARD);
        // adjusts the B leg || left
        mLimbB->adjustBLeg(true, 20);
        mLimbB->walk(FORWARD, LEFT, BACKWARD);
        mLimbC->walk(BACKWARD, LEFT, BACKWARD);
        
        mLimbD->walk(FORWARD, RIGHT, BACKWARD);
        mLimbE->walk(BACKWARD, RIGHT, BACKWARD);
        mLimbF->walk(FORWARD, RIGHT, BACKWARD);
        break;
   }
   
   return 0;
}

int Gait::strafe(sides side) {
  
  switch(side) {
    case LEFT:
        mLimbD->walk(FORWARD, RIGHT, FORWARD);
        mLimbE->walk(BACKWARD, RIGHT, FORWARD);
        mLimbF->walk(FORWARD, RIGHT, FORWARD);
        
        mLimbA->walk(BACKWARD, LEFT, BACKWARD);
        // adjusts the B leg || left
        mLimbB->adjustBLeg(true, 20);
        mLimbB->walk(FORWARD, LEFT, BACKWARD);
        mLimbC->walk(BACKWARD, LEFT, BACKWARD);

       break;
    case RIGHT:
        mLimbD->walk(FORWARD, RIGHT, BACKWARD);
        mLimbE->walk(BACKWARD, RIGHT, BACKWARD);
        mLimbF->walk(FORWARD, RIGHT, BACKWARD);
        
        mLimbA->walk(BACKWARD, LEFT, FORWARD);
        // adjusts the B leg || left
        mLimbB->adjustBLeg(true, 20);
        mLimbB->walk(FORWARD, LEFT, FORWARD);
        mLimbC->walk(BACKWARD, LEFT, FORWARD);
       break;
  }
  
  return 0;
}

int Gait::halt() {
  mLimbA->halt(LEFT);
  mLimbB->halt(LEFT);
  mLimbC->halt(LEFT);
  
  mLimbD->halt(RIGHT);
  mLimbE->halt(RIGHT);
  mLimbF->halt(RIGHT);
   return 0; 
}

int Gait::standby() {
  mLimbA->standby(LEFT);
  mLimbB->standby(LEFT);
  mLimbC->standby(LEFT);
  
  mLimbD->standby(RIGHT);
  mLimbE->standby(RIGHT);
  mLimbF->standby(RIGHT);
   return 0; 
}

