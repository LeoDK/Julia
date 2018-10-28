#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "complex.h"

typedef struct Complex Complex;

float calcMod (float re, float im)
{
    return sqrt(re*re + im*im);
}

float calcArg (float re, float im, float mod)
{
    float arg = acos(re / mod);
    if (im < 0)
    {
        arg = -arg;
    }
    return arg;
}

float calcRe (float mod, float arg)
{
    return cos(arg)/mod;
}

float calcIm (float mod, float arg)
{
    return sin(arg)/mod;
}

void calcTrig (Complex *z)
{
    z->mod = calcMod(z->re, z->im);
    z->arg = calcArg(z->re, z->im, z->mod);
}

void calcAlg (Complex *z)
{
    if (z->mod != 0)
    {
        z->re = calcRe(z->mod, z->arg);
        z->im = calcIm(z->mod, z->arg);
    }
    else
    {
        z->re = 0;
        z->im = 0;
    }
}

void addCplx (Complex *z1, Complex *z2, Complex *buf)
{
    buf->re = z1->re + z2->re;
    buf->im = z1->im + z2->im;
    calcTrig(buf);
}

void addCplx2 (Complex *z, float re, float im, Complex *buf)
{
    buf->re = z->re + re;
    buf->im = z->im + im;
    calcTrig(buf);
}

void addMod (Complex *z, float mod)
{
    z->mod += mod;
    calcAlg(z);
}

void addArg (Complex *z, float arg)
{
    z->arg += arg;
    calcAlg(z);
}

void multCplx (Complex *z1, Complex *z2, Complex *buf)
{
    float re = z1->re * z2->re - z1->im * z2->im;
    float im = z1->re * z2->im + z1->im * z2->re;
    buf->re = re;
    buf->im = im;
    calcTrig(buf);
}

void cplxPow (Complex *z, unsigned int power, Complex *buf)
{
    float re = z->re;
    float im = z->im;

    int i;
    for (i=1; i<power; i++)
    {
        float tmp = re * z->re - im * z->im;
        im = re * z->im + im * z->re;
        re = tmp;
    }

    buf->re = re;
    buf->im = im;
    calcTrig(buf);
}

Complex *__new__Complex (float re, float im)
{
    Complex *z = malloc(sizeof(*z));

    z->re = re;
    z->im = im;
    calcTrig(z);

    return z;
}

Complex *__new__Complex_Polar (float mod, float arg)
{
    Complex *z = malloc(sizeof(*z));

    z->mod = mod;
    z->arg = arg;
    calcAlg(z);

    return z;
}

void zero (Complex *z)
{
    z->re = 0;
    z->im = 0;
    z->mod = 0;
    z->arg = 0;
}
