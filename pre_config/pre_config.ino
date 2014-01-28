#include <Servo.h>
#include "Legservos.h"
#include "utility.c"
#include "Inversekinematics.h"
#include "Limb.h"

Servo sLegAHip;
Servo sLegAUpperLimb;
Servo sLegALowerLimb;
Servo sLegBHip;
Servo sLegBUpperLimb;
Servo sLegBLowerLimb;
Servo sLegCHip;
Servo sLegCUpperLimb;
Servo sLegCLowerLimb;
Servo sLegDHip;
Servo sLegDUpperLimb;
Servo sLegDLowerLimb;
Servo sLegEHip;
Servo sLegEUpperLimb;
Servo sLegELowerLimb;
Servo sLegFHip;
Servo sLegFUpperLimb;
Servo sLegFLowerLimb;

// sensors

leg *pinLegA;
leg *pinLegB; 
leg *pinLegC;
leg *pinLegD;
leg *pinLegE;
leg *pinLegF;

// assigns inverse kinematics objects to each Leg
// this is to automatically obtain each servo's angle
Inversekinematics ikLegA = Inversekinematics();
Inversekinematics ikLegB = Inversekinematics();
Inversekinematics ikLegC = Inversekinematics();
Inversekinematics ikLegD = Inversekinematics();
Inversekinematics ikLegE = Inversekinematics();
Inversekinematics ikLegF = Inversekinematics();

double Limb::pace = 0.75; // initializes class variable (necessity)
// associates Inverse Kinematic into the actual Limb's servo sets
// this is the part where the Servo.write() function take place
Limb ikLimbA = Limb(sLegAHip, sLegAUpperLimb, sLegALowerLimb);
Limb ikLimbB = Limb(sLegBHip, sLegBUpperLimb, sLegBLowerLimb);
Limb ikLimbC = Limb(sLegCHip, sLegCUpperLimb, sLegCLowerLimb);
Limb ikLimbD = Limb(sLegDHip, sLegDUpperLimb, sLegDLowerLimb);
Limb ikLimbE = Limb(sLegEHip, sLegEUpperLimb, sLegELowerLimb);
Limb ikLimbF = Limb(sLegFHip, sLegFUpperLimb, sLegFLowerLimb);

void setup() {
  
    // establish serial communication
    Serial.begin(9600);
    // ================================
    //  ABC - LEFT
    // ================================
    //==> Leg A
    pinLegA->hip = LEG_A_HIP;
    pinLegA->upperLimb = LEG_A_UPPER;
    pinLegA->lowerLimb = LEG_A_LOWER;
    
    sLegAHip.attach(pinLegA->hip);
    sLegAUpperLimb.attach(pinLegA->upperLimb);
    sLegALowerLimb.attach(pinLegA->lowerLimb);
    
    sLegAHip.write(getAbsoluteAngle((NINETY_DEGREE), LEFT));
    sLegAUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegALowerLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    
    // LegB
    pinLegB->hip = LEG_B_HIP;
    pinLegB->upperLimb = LEG_B_UPPER;
    pinLegB->lowerLimb = LEG_B_LOWER;
    
    sLegBHip.attach(pinLegB->hip);
    sLegBUpperLimb.attach(pinLegB->upperLimb);
    sLegBLowerLimb.attach(pinLegB->lowerLimb);
    
    sLegBHip.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegBUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegBLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    
    //==> Leg C
    pinLegC->hip = LEG_C_HIP;
    pinLegC->upperLimb = LEG_C_UPPER;
    pinLegC->lowerLimb = LEG_C_LOWER;
    
    sLegCHip.attach(pinLegC->hip);
    sLegCUpperLimb.attach(pinLegC->upperLimb);
    sLegCLowerLimb.attach(pinLegC->lowerLimb);
    
    sLegCHip.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegCUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegCLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    
    
    
    // ================================
    //  DEF - RIGHT
    // ================================
    

    // ==> Leg D
    pinLegD->hip = LEG_D_HIP;
    pinLegD->upperLimb = LEG_D_UPPER;
    pinLegD->lowerLimb = LEG_D_LOWER;
    
    sLegDHip.attach(pinLegD->hip);
    sLegDUpperLimb.attach(pinLegD->upperLimb);
    sLegDLowerLimb.attach(pinLegD->lowerLimb);
    
    sLegDHip.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    sLegDUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    sLegDLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    
    // ==> Leg E
    pinLegE->hip = LEG_E_HIP;
    pinLegE->upperLimb = LEG_E_UPPER;
    pinLegE->lowerLimb = LEG_E_LOWER;
    
    sLegEHip.attach(pinLegE->hip);
    sLegEUpperLimb.attach(pinLegE->upperLimb);
    sLegELowerLimb.attach(pinLegE->lowerLimb);
    
    sLegEHip.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    sLegEUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    sLegELowerLimb.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    
    // ==> Leg F
    pinLegF->hip = LEG_F_HIP;
    pinLegF->upperLimb = LEG_F_UPPER;
    pinLegF->lowerLimb = LEG_F_LOWER;
    
    // LegF
    sLegFHip.attach(pinLegF->hip);
    sLegFUpperLimb.attach(pinLegF->upperLimb);
    sLegFLowerLimb.attach(pinLegF->lowerLimb);
    
    sLegFHip.write(getAbsoluteAngle((NINETY_DEGREE), RIGHT));
    sLegFUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    sLegFLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    
    
}

void loop() {
  
//  Limb::pace = .75;
//  
//  // normal walk
//  ikLimbA.walk(BACKWARD, LEFT);
//  ikLimbB.walk(FORWARD, LEFT);
//  ikLimbC.walk(BACKWARD, LEFT);
//  
//  ikLimbD.walk(FORWARD, RIGHT);
//  ikLimbE.walk(BACKWARD, RIGHT);
//  ikLimbF.walk(FORWARD, RIGHT);
}

