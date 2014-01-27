#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#define ZOFFSET 8.4
#define FEMUR -12.6
#define TIBIA 92.56
#define PI 3.1415926
#define ONEEIGHTY_DEGREE 180

class Inversekinematics {
    public:
        // default coonstructor
        Inversekinematics();
        
        // destructor
        ~Inversekinematics();
        
        // methods
        
        // mutators
//        void setAlpha(double);
//        void setBeta(double);
//        void setGamma(double);
        
        // accessors
        double getAlpha();
        double getBeta();
        double getGamma();
    
     private:    
        // methods
        double toDegree(double);
        
        // data members
        double alpha;
        double beta;
        double gamma;
    
};

#endif
