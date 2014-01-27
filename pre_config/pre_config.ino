#include <Servo.h>
#include "Legservos.h"
#include "utility.c"

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
        
    // ================================
    //  ACE - LEFT
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
    
    // ==> Leg E
    pinLegE->hip = LEG_E_HIP;
    pinLegE->upperLimb = LEG_E_UPPER;
    pinLegE->lowerLimb = LEG_E_LOWER;
    
    sLegEHip.attach(pinLegE->hip);
    sLegEUpperLimb.attach(pinLegE->upperLimb);
    sLegELowerLimb.attach(pinLegE->lowerLimb);
    
    sLegEHip.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegEUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    sLegELowerLimb.write(getAbsoluteAngle(NINETY_DEGREE, LEFT));
    
    // ================================
    //  BDF - RIGHT
    // ================================
    // LegB
    pinLegB->hip = LEG_B_HIP;
    pinLegB->upperLimb = LEG_B_UPPER;
    pinLegB->lowerLimb = LEG_B_LOWER;
    
    sLegBHip.attach(pinLegB->hip);
    sLegBUpperLimb.attach(pinLegB->upperLimb);
    sLegBLowerLimb.attach(pinLegB->lowerLimb);
    
    sLegBHip.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    sLegBUpperLimb.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));
    sLegBLowerLimb.write(getAbsoluteAngle(NINETY_DEGREE, RIGHT));

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

void loop() {}

void toggleAce(int directn) { // toggles sets of leg. on the LEFT -- UP/DOWN as per say
     switch(directn) {
         case 0:
           up(sLegAUpperLimb, sLegALowerLimb);
           up(sLegCUpperLimb, sLegCLowerLimb);
           up(sLegCUpperLimb, sLegELowerLimb);
           break;
         case 1:
           down(sLegAUpperLimb, sLegALowerLimb);
           down(sLegCUpperLimb, sLegCLowerLimb);
           down(sLegCUpperLimb, sLegELowerLimb);
     }
     
}

void toggleBDF(int directn) {
     switch(directn) {
        case 0:
            up(sLegBUpperLimb, sLegBLowerLimb);
            up(sLegDUpperLimb, sLegDLowerLimb);
            up(sLegFUpperLimb, sLegFLowerLimb);
            break;
        case 1:
            down(sLegBUpperLimb, sLegBLowerLimb);
            down(sLegDUpperLimb, sLegDLowerLimb);
            down(sLegFUpperLimb, sLegFLowerLimb);  
     }
     
}

void walk(int mode) {
    switch(mode) {
        case FORWARD:
            toggleAce(0);
            toggleBDF(1);
            delay(500);
            toggleAce(1);
            toggleBDF(0);
            delay(500);
            break;
        case BACKWARD:
            break;
        case GAIT:
            break;
    }
}


/* basic moves on each limbs */
// moves leg up
void up(Servo upperLimb, Servo lowerLimb) {
    const int UPINCREMENT = 20;
    
    int currentUpper = upperLimb.read();
    int currentLower = lowerLimb.read();
    
    upperLimb.write(currentUpper - UPINCREMENT);
    lowerLimb.write(currentLower - UPINCREMENT);
//    delay(1000); // @todo: delete this
}

// moves down
void down(Servo upperLimb, Servo lowerLimb) {
    const int UPINCREMENT = 20;
    
    int currentUpper = upperLimb.read();
    int currentLower = lowerLimb.read();
    
    upperLimb.write(currentUpper + UPINCREMENT);
    lowerLimb.write(currentLower + UPINCREMENT);
//    delay(1000); // @todo: delete this
}

