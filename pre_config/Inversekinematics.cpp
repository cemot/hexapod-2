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

// ==================================
// mutators
// ==================================


// ==================================
// destructor
// ==================================
Inversekinematics::~Inversekinematics(){}


