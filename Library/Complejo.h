#ifndef Complejo_h
#define Complejo_h

#pragma once

#include <math.h>
// La clase Complejo permite trabajar con números complejos

class Complejo
{
public:
    Complejo():real(0),imag(0),theta(0){}
    Complejo(float r,float i):real(r),imag(i),theta(atan(imag/real)){}
    Complejo(const Complejo& c):real(c.real),imag(c.imag),theta(c.theta){}
    virtual ~Complejo(){}
     
    float real;
    float imag;
    float theta;
};

#endif
