#include "Limb.h"

Limb::Limb(Servo& svHip, Servo& svUprLimb, Servo& svLwrLimb){
  // initializes some data members
  cntr = 0.0;
  projY = 6; // Note: this is the of the limb's angle
  length = 10;
  
  mSvHip = svHip;
  mSvUprLimb = svUprLimb;
  mSvLwrLimb = svLwrLimb;
  
  // instantiates the Inverser Kinematics class
  ikLeg = Inversekinematics();
  
}

void Limb::walk(directions directn, sides side) {
  switch(directn) {
     case FORWARD:
         walkForward(side);
         break;
     case BACKWARD:
         walkBackward(side);
         break;
     default:
          FORWARD; 
  }
}

void Limb::walkForward(sides side) {
  // forward & backward
  ikLeg.move(cntr, length);

  mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), RIGHT));
  Serial.print(" cntr: ");
  Serial.println(cntr); 
  
  cntr = cntr + 0.75;
  if(cntr >= projY) {
    cntr = 0;
//    Serial.println(" ===> resetting value of cntr(Gamma)");
//    Serial.println("");
  }

}

void Limb::walkBackward(sides side){}
