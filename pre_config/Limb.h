#ifndef LIMB_H
  #define LIMB_H

#include <Arduino.h>
#include <Servo.h>
#include "Legservos.h"
#include "Inversekinematics.h"

class Limb {
  public:
    static double pace;
    // constructors for the limb class. this area assigns default values
    // to its own variables
    Limb(Servo&, Servo&, Servo&);
    
    // lets the limb moves as it should be. also gets the angle for each joints
    // of the limb
    void walk(directions, sides, directions);
    void strafe(directions, sides, directions, int);
    
    void setPace(double);
    
    double getPace();
    
  private:
    void walkForward(sides, directions);
    void walkBackward(sides, directions);
    void strafeForward(sides, directions, int);
    void strafeBackward(sides, directions, int);
    
    // data members/variables
    double cntr;
    double cntrB;
    double projY;
    double projYB;
    double projYBackward;
    double projYBBackward;
    double length;
    double raiseLegOffsetForward;
    double raiseLegOffsetBackward;
    
    revolution revDirectionFrontPrior;
    revolution revDirectionBackPrior;
    
    Servo mSvHip;
    Servo mSvUprLimb;
    Servo mSvLwrLimb;
    Inversekinematics ikLeg;
};

#endif
  
