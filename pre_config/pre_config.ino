#include <Servo.h>
#include "Legservos.h"
#include "utility.c"
#include "Inversekinematics.h"

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

leg *pinLegA;
leg *pinLegB; 
leg *pinLegC;
leg *pinLegD;
leg *pinLegE;
leg *pinLegF;

// stores the current stance value of the hexapod
int currentStanceUpperLimb = 0; 
int currentStanceLowerLimb = 0;

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
    // determines which leg is being oriented to which side
    if(Serial.available()) {
      int signal = Serial.read() - '0'; 
      
      switch(signal) {
        case 1: raiseLegA(); break;
        case 2: raiseLegB(); break;
        case 3: raiseLegC(); break;
        case 4:raiseLegD(); break;
        case 5:raiseLegE(); break;
        case 6:raiseLegF(); break;
        default: raiseLegA();
      }      
    }
}

void raiseLegA() {
    sLegAHip.write(getAbsoluteAngle((NINETY_DEGREE), LEFT));
    sLegAUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegALowerLimb.write(getAbsoluteAngle(NINETY_DEGREE + FORTYFIVE_DEGREE, LEFT)); 
}

void raiseLegB() {
    sLegBHip.write(getAbsoluteAngle((NINETY_DEGREE), LEFT));
    sLegBUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegBLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE + FORTYFIVE_DEGREE, LEFT)); 
}

void raiseLegC() {
    sLegCHip.write(getAbsoluteAngle((NINETY_DEGREE), LEFT));
    sLegCUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegCLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE + FORTYFIVE_DEGREE, LEFT)); 
}

void raiseLegD() {
    sLegDHip.write(getAbsoluteAngle((NINETY_DEGREE), LEFT));
    sLegDUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegDLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE + FORTYFIVE_DEGREE, RIGHT)); 
}

void raiseLegE() {
    sLegEHip.write(getAbsoluteAngle((NINETY_DEGREE), LEFT));
    sLegEUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegELowerLimb.write(getAbsoluteAngle(NINETY_DEGREE + FORTYFIVE_DEGREE, RIGHT)); 
}

void raiseLegF() {
    sLegFHip.write(getAbsoluteAngle((NINETY_DEGREE), LEFT));
    sLegFUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegFLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE + FORTYFIVE_DEGREE, RIGHT)); 
}
