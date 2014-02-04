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
Servo sCamera;

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
Thread* threadLeftPIR = new Thread();
Thread* threadMidPIR = new Thread();
Thread* threadRightPIR = new Thread();
Thread* threadCamera = new Thread();

// Instantiates the NewPing class
NewPing sonar(USONIC_TRIG, USONIC_ECHO, MAX_DISTANCE);

// global variables
int pathDistance = 0;
int cliffHeight = 0;
boolean _boo_autonomous_mode = true;
int incRadarAngle = 5;
int userInput = 0;
boolean lookOtherPath = false;
long simTimer = 0.0; // simulate timer
sides hexpdStrafeDirection = LEFT;
int pirLeftSensor = 0;
int pirMidSensor = 0;
int pirRightSensor = 0;

void camOnWatch() {
  int _pirLEFT = analogRead(PIR_LEFT);
//  int _pirMID = analogRead(PIR_MID);
  int _pirRIGHT = analogRead(PIR_RIGHT);
  
  int threshhold = 5; // due to PIR rough data
  
//  Serial.print("Left "); Serial.print(_pirLEFT);
//  Serial.print("Right: "); Serial.println(_pirRIGHT);
  
  if(_pirLEFT > threshhold){
    // turn left
    sCamera.write(135); //delay(1000);
  } else if(_pirRIGHT > threshhold) {
     // turn mid 
     sCamera.write(45); //delay(1000);
  } else if(_pirLEFT > threshhold && _pirRIGHT > threshhold) {
     sCamera.write(90);
  }
}

// PIR LEFT
void monitorPIRLeft() {
  pirLeftSensor = analogRead(PIR_LEFT);
  // @todo: delete all Serial.print()
//  Serial.print("PIRLeft: ");
//  Serial.println(pirLeftSensor);
}

// PIR MID
void monitorPIRMid() {
  pirMidSensor = analogRead(PIR_MID);
  // @todo: delete all Serial.print()
//  Serial.print("PIRMid: ");
//  Serial.println(pirMidSensor);
}

// PIR RIGHT
void monitorPIRRight() {
  pirRightSensor = analogRead(PIR_RIGHT);
  // @todo: delete all Serial.print()
//  Serial.print("PIRRight: ");
//  Serial.println(pirRightSensor);
//  Serial.println("=====================");
}


// this scan the path of hexapod
void scanPath() {
    int uS = sonar.ping();
    pathDistance = uS / US_ROUNDTRIP_IN;
//    Serial.print("pathDistance ");
//    Serial.println(pathDistance);
//    
}

void scanCliffHeight() {
  cliffHeight = analogRead(IR_DIST);
  cliffHeight = map(cliffHeight, 0, 1023, 1023, 0); 
 
//   Serial.print("cliffHeight ");
//   Serial.println(cliffHeight); 

}

void doRadar() {
 //ULTRASONICSERVO
 int curAngle = sUltraSonic.read();
 curAngle = curAngle + 5;
 
 sUltraSonic.write(curAngle);
 
 if(curAngle >= 100)
    sUltraSonic.write(0);
}

// searches for other path from left to right
sides searchOptionPath(boolean magAngle, int& compareResult) { // magAngle: true -> (0 - 180 degrees turn); false -> (45 - 135 degrees turn)
  int leftPathOption = 0; // variable for optional path
  int rightPathOption = 0; // for left and right
  int uSLeft = 0;
  int uSRight = 0;
  
//  Serial.println(" Scanning Path");
  if(magAngle == true){
    // get left distance, assign to variable
    sUltraSonic.write(ONEEIGHTY_DEGREE); delay(1000);
    uSLeft = sonar.ping();
    leftPathOption = uSLeft / US_ROUNDTRIP_IN;
    
    // get right distance, assign to variable
    sUltraSonic.write(0);  delay(1000);
    uSRight = sonar.ping();
    rightPathOption = uSRight / US_ROUNDTRIP_IN;
    
    // sets back to ulrasonic sensor to the center
    sUltraSonic.write(NINETY_DEGREE); delay(500);

//    Serial.print("Left: "); Serial.println(leftPathOption); Serial.print("Right: "); Serial.println(rightPathOption); delay(30000);
    return (leftPathOption > rightPathOption) ? LEFT : RIGHT;
    
  } else {
    // get left distance, assign to variable
    sUltraSonic.write(ONEHUNDREDTHIRTYFIVE_DEGREE); delay(1000);
    uSLeft = sonar.ping();
    leftPathOption = uSLeft / US_ROUNDTRIP_IN;  
    
    // get right distance, assign to variable
    sUltraSonic.write(FORTYFIVE_DEGREE);    delay(1000);
    uSRight = sonar.ping();
    rightPathOption = uSRight / US_ROUNDTRIP_IN;
    
    // sets back to ulrasonic sensor to the center
    sUltraSonic.write(NINETY_DEGREE);  delay(500);
    
    // compare and get result number
    compareResult = (leftPathOption >= rightPathOption) ? leftPathOption : rightPathOption;
//    Serial.print("Left: "); Serial.println(leftPathOption); Serial.print("Right: "); Serial.println(rightPathOption); delay(30000);
    return (leftPathOption > rightPathOption) ? LEFT : RIGHT;    
  }
  
  return LEFT; // default returned value. fail safe purposes
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


void setup() {
  
    // establish serial communication
    Serial.begin(9600);
    
    // camera servo
    sCamera.attach(CAMERASERVO);
    sCamera.write(90);
    threadCamera->onRun(camOnWatch);
    threadCamera->setInterval(500);
    
    // Ultrasonic sensor
//    threadUSonicSensor->onRun(scanPath);
//    threadUSonicSensor->setInterval(500);

    // servo Ultrasonic
//    threadUSonicServo->onRun(doRadar);
    //threadUSonicServo->onRun(newDoRadar);
//    threadUSonicServo->setInterval(50);
      
    // distance IR
//    threadDistanceIR->onRun(scanCliffHeight);
//    threadDistanceIR->setInterval(500);
    // PIR
    threadLeftPIR->onRun(monitorPIRLeft);
    threadLeftPIR->setInterval(200);
    threadMidPIR->onRun(monitorPIRMid);
    threadMidPIR->setInterval(500);
    threadRightPIR->onRun(monitorPIRRight);
    threadRightPIR->setInterval(200);
    
//    controll.add(threadUSonicSensor);
//    controll.add(threadUSonicServo);
//    controll.add(threadDistanceIR);
    controll.add(threadLeftPIR);
//    controll.add(threadMidPIR);
    controll.add(threadRightPIR);
    controll.add(threadCamera);
    
    // sets the ultrasonic sensor to center
    sUltraSonic.attach(ULTRASONICSERVO);
    sUltraSonic.write(NINETY_DEGREE);
    
    // assigns three servos each leg
    // and sets initial stance of the
    // hexapod. 90-degrees on three servos each leg
    buildLegs();

}

void loop() {
  // Thread controller. This runs all threads
  controll.run();

  Limb::pace = .15; // adjust this to control the speed of gait. (0.025 - .5)
  
  // @todo: temp
//  newDoRadar();
  
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
  
  // read ultra sonic values
  scanPath();
  scanCliffHeight();
//  delay(1000);
//  Serial.println(" This is an infinite loop");

  if(_boo_autonomous_mode) {
    // ultrasonic sensor
    // PIR algo here
    // IR_Distance algo here
//    if((pathDistance >= 15 || cliffHeight >= DANGER_VAL_DISTANCE_IR ) && lookOtherPath == false){ // more than 15 inches and clift height
//      gaitHexapod.walk(FORWARD);
//    } else {
//      gaitHexapod.walk(BACKWARD);
//      Serial.println(" Autonomous mode ni bei ");
//      delay(10000);
      // if pathDistance <= distance.abl and cliffHeight <= cliff.abl then walk
      if(pathDistance >= DISTANCE_ALLOWABLE && cliffHeight < DANGER_VAL_DISTANCE_IR) { // @todo: double check this later
//        Serial.println(" FORWARD bro.");
        gaitHexapod.walk(FORWARD); 
      }
      // if pathDistance >= distance.abl OR cliffHeight >= cliff.abl then stop
      if(pathDistance <= DISTANCE_ALLOWABLE || cliffHeight >= DANGER_VAL_DISTANCE_IR) {
        //if cliff.cur >= cliff.abl 
        if(cliffHeight >= DANGER_VAL_DISTANCE_IR) {
          // then backward t(n).
          for(int i = 0; i <= TIME_DELAY_MS; i++){gaitHexapod.walk(BACKWARD); /*Serial.println(" Atras bro.")*/;} // find a way to omit the latter part of the line from here... forward is one is to N
          
          // int further side
          int  furtherSide = 0;
          
          sides strafeDirection = LEFT; // sets default
          //strafe (left/right)
          strafeDirection = searchOptionPath(true, furtherSide);
//          testScan();
          for(int j = 0; j <= TIME_DELAY_MS; j++){gaitHexapod.strafe(strafeDirection); /*Serial.print(" LIKO."); Serial.println(strafeDirection);*/}                 
        }
        
        // if pathDistance >= distance.abl 
        if(pathDistance <= DISTANCE_ALLOWABLE) {
          // then stop          
//          for(int i = 0; i <= TIME_DELAY_MS; i++) {gaitHexapod.standby(); /*Serial.println("standby2x pag may time");*/}
          
          // int further side
          int furtherSide = 0;
          
          // scan left/righ, then compare
          sides strafeDirection = LEFT; // sets default
          //strafe (left/right)
          strafeDirection = searchOptionPath(false, furtherSide);
            // compare.result <= distance.abl then
            if(furtherSide <= DISTANCE_ALLOWABLE) {
                // sit  <-- how to prolong
                for(int i = 0; i <= TIME_DELAY_MS; i++){gaitHexapod.standby();  /*Serial.println("gikan sa tulog");*/}
               
            } else { // strafe (compare.result n/t)
                for(int j = 0; j <= TIME_DELAY_MS; j++){gaitHexapod.strafe(strafeDirection);/* Serial.println("Strafe");*/} 
            }
        }
        
      }

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
      case 7:
        gaitHexapod.standby();
     }
  }

  }  



