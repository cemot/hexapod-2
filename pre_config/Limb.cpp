#include "Limb.h"

Limb::Limb(Servo& svHip, Servo& svUprLimb, Servo& svLwrLimb){
  // initializes some data members
  cntr = 0.0;
  cntrB = 0.0;
  projY = 5; // Note: this is the of the limb's angle (forward)
  projYB = -5; // Note: this is the of the limb's angle (backward)
  projYBackward = -5; // for gait backward
  projYBBackward = 5; // for gait backward

  // the distance of step each leg
  length = 11;
  
  mSvHip = svHip;
  mSvUprLimb = svUprLimb;
  mSvLwrLimb = svLwrLimb;
  
  // instantiates the Inverser Kinematics class
  ikLeg = Inversekinematics();
  
  // sets the orietation priority of the leg
  revDirectionFrontPrior = revFORWARD;
  revDirectionBackPrior = revBACKWARD;
  raiseLegOffsetForward = 0.0;
  raiseLegOffsetBackward = 0.0;
  
  // speed
  pace = 0.25; 
}

void Limb::walk(directions directn, sides side, directions hexpdDirections) {
  switch(directn) {
     case FORWARD:
         walkForward(side, hexpdDirections);
         break;
     case BACKWARD:
         walkBackward(side, hexpdDirections);
         break;
     default:
          FORWARD; 
  }
}

void Limb::walkForward(sides side, directions hxpDirections) {
  // walks forward
  ikLeg.move(cntr, length);
  
  (side == RIGHT) ? mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), RIGHT)) : mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), LEFT));
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb() - raiseLegOffsetForward, RIGHT)) : mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb() - raiseLegOffsetForward, LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), LEFT));
  

  Serial.println(revDirectionFrontPrior);
//  delay(500);
  if(revDirectionFrontPrior == revFORWARD) {
    cntr = cntr + pace;
    if(cntr > projY)
      revDirectionFrontPrior = revBACKWARD;
      
    // raise leg
    if(hxpDirections == FORWARD)
      raiseLegOffsetForward = RAISELEGOFFSET_Y;
    else if (hxpDirections == BACKWARD)
      raiseLegOffsetForward = 0;
  } else {
    cntr = cntr - pace;
    if(cntr < 0) revDirectionFrontPrior = revFORWARD;
    
    // down leg
    if(hxpDirections == FORWARD)
      raiseLegOffsetForward = 0.0;
    else if(hxpDirections == BACKWARD)
      raiseLegOffsetForward = RAISELEGOFFSET_Y;
  }
}

void Limb::walkBackward(sides side, directions hxpDirections){
  // walks backward
  ikLeg.move(cntrB, length);

  (side == RIGHT) ? mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), RIGHT)) : mSvHip.write(getAbsoluteAngle((int)ikLeg.getHip(), LEFT));
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb() - raiseLegOffsetBackward, RIGHT)) : mSvUprLimb.write(getAbsoluteAngle((int)ikLeg.getUpperLimb() - raiseLegOffsetBackward, LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle((int)ikLeg.getLowerLimb(), LEFT));

  
  if(revDirectionBackPrior == revBACKWARD) {
    cntrB = cntrB - pace;
    if(cntrB < projYB)
      revDirectionBackPrior = revFORWARD; 
  
    if(hxpDirections == FORWARD)    
      raiseLegOffsetBackward = 0;
    else if(hxpDirections == BACKWARD)
      raiseLegOffsetBackward = RAISELEGOFFSET_Y;
      
  } else {
    cntrB = cntrB + pace;
    if(cntrB > 0) 
      revDirectionBackPrior = revBACKWARD;
      
     if(hxpDirections == FORWARD)
       raiseLegOffsetBackward = RAISELEGOFFSET_Y;
     else if(hxpDirections == BACKWARD)
        raiseLegOffsetBackward = 0;
  }  
}

void Limb::halt(sides side) {
   ikLeg.move(projY, 14);
  
  (side == RIGHT) ? mSvHip.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT)) : mSvHip.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
  (side == RIGHT) ? mSvUprLimb.write(getAbsoluteAngle(FORTYFIVE_DEGREE, RIGHT)) : mSvUprLimb.write(getAbsoluteAngle(FORTYFIVE_DEGREE, LEFT));
  (side == RIGHT) ? mSvLwrLimb.write(getAbsoluteAngle(FORTYFIVE_DEGREE, RIGHT)) : mSvLwrLimb.write(getAbsoluteAngle(FORTYFIVE_DEGREE, LEFT)); 
}

void Limb::setPace(double newVal) {
  pace = newVal; 
}

double Limb::getPace() {
  return pace; 
}



