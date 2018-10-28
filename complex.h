#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex
{
    float re;
    float im;
    float mod;
    float arg;
};
typedef struct Complex Complex;

void addCplx (Complex *z1, Complex *z2, Complex *buf);
void addCplx2 (Complex *z, float re, float im, Complex *buf);
void addMod (Complex *z, float mod);
void addArg (Complex *z, float arg);
void multCplx (Complex *z1, Complex *z2, Complex *buf);
void cplxPow (Complex *z, unsigned int power, Complex *buf);
Complex *__new__Complex (float re, float im);
Complex *__new__Complex_Polar (float mod, float arg);
void zero(Complex *z);

#endif
