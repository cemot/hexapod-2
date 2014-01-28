#include "Limb.h"

Limb::Limb(Servo& svHip, Servo& svUprLimb, Servo& svLwrLimb){
  // initializes some data members
  cntr = 0.0;
  cntrB = 0.0;
  projY = 5; // Note: this is the of the limb's angle (forward)
  projYB = -5; // Note: this is the of the limb's angle (backward)

  length = 13;
  
  mSvHip = svHip;
  mSvUprLimb = svUprLimb;
  mSvLwrLimb = svLwrLimb;
  
  // instantiates the Inverser Kinematics class
  ikLeg = Inversekinematics();
  
  // speed
  pace = 0.25; 
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
  // walks forward
  ikLeg.move(cntr, length);
  
  (side == RIGHT) ? mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), RIGHT)) : mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), LEFT));
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb(), RIGHT)) : mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb(), LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), LEFT));
  Serial.print(" cntr: ");
  Serial.println(cntr); 
  
  cntr = cntr + pace;
  if(cntr >= projY) {
    cntr = 0;
  }

}

void Limb::walkBackward(sides side){
  // walks backward
  ikLeg.move(cntrB, length);

  (side == RIGHT) ? mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), RIGHT)) : mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), LEFT));
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb(), RIGHT)) : mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb(), LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), LEFT));
  Serial.print(" cntrB: ");
  Serial.println(cntrB); 
  Serial.print("Gamma: ");
  Serial.println((int)ikLeg.getHip());
  
  cntrB = cntrB - pace;
  if(cntrB <= projYB) {
    cntrB = 0;
    Serial.print(" =================> resets to 0");
  }

}

void Limb::setPace(double newVal) {
  pace = newVal; 
}

double Limb::getPace() {
  return pace; 
}



