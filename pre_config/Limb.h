#ifndef LIMB_H
  #define LIMB_H
#endif
#include <Arduino.h>
#include <Servo.h>
#include "Legservos.h"
#include "Inversekinematics.h"

class Limb {
  public:
    // constructors for the limb class. this area assigns default values
    // to its own variables
    Limb(Servo&, Servo&, Servo&);
    
    // lets the limb moves as it should be. also gets the angle for each joints
    // of the limb
    void walk(directions, sides);
    
  private:
    void walkForward(sides);
    void walkBackward(sides);
    
    // data members/variables
    double cntr;
    double projY;
    double length;
    Servo mSvHip;
    Servo mSvUprLimb;
    Servo mSvLwrLimb;
    Inversekinematics ikLeg;
};


