/**
* Note: Half stand -- 45 degrees (upperlimb) & 45 degrees (lower limb)|| hip 90 degrees
*       Full stand -- 90 degrees (upperlimb) & 90 degrees (lower limb) || hip 90 degrees\
*       -> HIP servo "+" paddles backward, thus hexapod goes forward
*       -> Hip servo "-" paddles forward, thus hexapod goes backward
*
**/
// defines constant angles
#define NINETY_DEGREE 90
#define FORTYFIVE_DEGREE 45
#define ONETHREEFIVE_DEGREE 100
#define ONEEIGHTY_DEGREE 180

// defines pins for each leg and leg partition
#define LEG_A_HIP A2
#define LEG_A_UPPER A1
#define LEG_A_LOWER  A0

#define LEG_B_HIP A5
#define LEG_B_UPPER A4
#define LEG_B_LOWER A3

#define LEG_C_HIP A8 // something is not right with this pin (be sure to select Mega 2560 board).
#define LEG_C_UPPER A7
#define LEG_C_LOWER A6

#define LEG_D_HIP 4
#define LEG_D_UPPER 3
#define LEG_D_LOWER  2

#define LEG_E_HIP 7
#define LEG_E_UPPER 6
#define LEG_E_LOWER  5

#define LEG_F_HIP 10
#define LEG_F_UPPER 9
#define LEG_F_LOWER  8

// direction
//#define LEFT 0
//#define RIGHT 1
//#define FORWARD 2
//#define BACKWARD 3
//#define GAIT 4

enum directions {
    LEFT, RIGHT, FORWARD, BACKWARD, GAIT 
};

// macros


// defines user-defined data type
struct Leg {
    int hip;
    int upperLimb;
    int lowerLimb; 
}; 

typedef struct Leg leg;

// prototypes
void assignPins();
void attachServos();
int getAbsoluteAngle(int, int);
void walk(int);
