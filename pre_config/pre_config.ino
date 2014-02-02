#include <NewPing.h>
#include <Thread.h>
#include <ThreadController.h>
#include <Servo.h>
#include "Legservos.h"
#include "utility.c"
#include "Inversekinematics.h"
#include "Limb.h"
#include "Gait.h"


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
Servo sUltraSonic;

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

// determines what kind of walking the
// hexapod should perform. And assigns
// all the limbs into the Gait class
// for brevity & simplicity of the command
Gait gaitHexapod = Gait(ikLimbA, ikLimbB, ikLimbC, ikLimbD, ikLimbE, ikLimbF);

// ThreadController that will controll all threads
ThreadController controll = ThreadController();  

// thread for ultrasonic sensor's reading
Thread* threadUSonicSensor = new Thread();
Thread* threadUSonicServo = new Thread();
Thread* threadDistanceIR = new Thread();

// newping
NewPing sonar(USONIC_TRIG, USONIC_ECHO, MAX_DISTANCE);
// temp constant
int pathDistance = 0;
int cliffHeight = 0;
boolean _boo_autonomous_mode = true;

// this scan the path of hexapod
void scanPath() {
    int uS = sonar.ping();
    pathDistance = uS / US_ROUNDTRIP_IN;
}

void scanCliffHeight() {
  cliffHeight = analogRead(IR_DIST);
  cliffHeight = map(cliffHeight, 0, 1023, 1023, 0);  

}


// @todo: todo
int incRadarAngle = 5;

void doRadar() {
 //ULTRASONICSERVO
 int curAngle = sUltraSonic.read();
 curAngle = curAngle + 5;
 
 sUltraSonic.write(curAngle);
 
 if(curAngle >= 100)
    sUltraSonic.write(0);
}

void buildLegs() {
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

int userInput = 0;
void setup() {
  
    // establish serial communication
    Serial.begin(9600);
    
    // Ultrasonic sensor
    threadUSonicSensor->onRun(scanPath);
    threadUSonicSensor->setInterval(500);
    // servo Ultrasonic
    threadUSonicServo->onRun(doRadar);
    threadUSonicServo->setInterval(50);
    // distance IR
    threadDistanceIR->onRun(scanCliffHeight);
    threadDistanceIR->setInterval(500);
    
    controll.add(threadUSonicSensor);
    controll.add(threadUSonicServo);
    controll.add(threadDistanceIR);
    
    // @todo: temp. do oop on this
    sUltraSonic.attach(ULTRASONICSERVO);
    
    // assigns three servos each leg
    // and sets initial stance of the
    // hexapod. 90-degrees on three servos each leg
    buildLegs();

}

void loop() {
  // Thread controller. This runs all threads
  controll.run();

  Limb::pace = .15; // adjust this to control the speed of gait. (0.025 - .5)
  
  // wait for serial communication
  if(Serial.available()) {
    userInput = Serial.read() - '0';
    
    switch(userInput) {
      case 0:
        _boo_autonomous_mode = false;
        break;
      case 1:
        _boo_autonomous_mode = true;
         break;  
    }
  }
  
  if(_boo_autonomous_mode) {
    // sensors section
    // ultrasonic sensor
    if(pathDistance >= 15 || cliffHeight >= DANGER_VAL_DISTANCE_IR){ // more than 15 inches
      gaitHexapod.walk(FORWARD);
    } else if (pathDistance < 15) {
      gaitHexapod.strafe(LEFT);
    }
      // rotate 180 degrees with time interval
      // PIR algo here
      // IR_Distance algo here
  
  
  // gait section
  
    // if exists collision then strafe (left or right)
    // if exists collision and collision distance is very close then stop or walk backwards
        // if gait sidewards is availbe then do sidewards          
  } else {
    switch(userInput) {
      case 2:
         gaitHexapod.walk(FORWARD);
         break;       
      case 3:
        gaitHexapod.walk(BACKWARD);
        break;
      case 4:
        gaitHexapod.strafe(LEFT);
        break;
      case 5:
        gaitHexapod.strafe(RIGHT);
        break;
      case 6:
        gaitHexapod.halt();
     }
  }
   
}

