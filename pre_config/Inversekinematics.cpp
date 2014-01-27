#include "Inversekinematics.h"

// ==================================
// default constructor
// ==================================
Inversekinematics::Inversekinematics() {
    // initializes data members
    alpha = 0.0;
    beta = 0.0;
    gamma = 0.0;
}
// ==================================
// accessors
// ==================================
double Inversekinematics::getAlpha() {
    return alpha;
}

double Inversekinematics::getBeta() {
   return beta; 
}

double Inversekinematics::getGamma() {
    return gamma; 
}

// ==================================
// methods -- public/private
// ==================================
double Inversekinematics::toDegree(double val) {
    return val * (ONEEIGHTY_DEGREE / PI);
}

void Inversekinematics::move(double projY, double length) {
	calculateAlpha(length);
}

void Inversekinematics::calculateAlpha(double length) {
	alpha = toDegree(acos(ZOFFSET / length))  + toDegree(acos((TIBIA - pow(length, 2))/(FEMUR * length)));
//	alpha = toDegree(acos(ZOFFSET / length));
//	alpha = toDegree(acos((TIBIA - pow(length, 2))/(FEMUR * length)));
}

// ==================================
// mutators
// ==================================


// ==================================
// destructor
// ==================================
Inversekinematics::~Inversekinematics(){}



