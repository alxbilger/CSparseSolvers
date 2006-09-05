#ifndef SOFA_COMPONENTS_COMMON_RMATH_H
#define SOFA_COMPONENTS_COMMON_RMATH_H

#include <math.h>

namespace Sofa
{

namespace Components
{

namespace Common
{

/*
// Most portable version, but also the slowest
inline int rfloor(double r)
{
  return ((int)(r+1000000))-1000000;
}

inline int rnear(double r)
{
  return ((int)(r+1000000.5))-1000000;
}
*/

/*
// Does not work on gcc 4.x due to more aggressive optimizations
inline int rfloor(double r)
{
  static const double FLOATTOINTCONST=(1.5*(1LL<<(52-16)));
  r+=FLOATTOINTCONST;
  return ((((int*)&r)[0])>>16);
}

inline int rnear(double r)
{
  static const double FLOATTOINTCONST_0_5=(1.5*(1LL<<(52-16)))+0.5;
  r+=FLOATTOINTCONST_0_5;
  return ((((int*)&r)[0])>>16);
}
*/

// Works on gcc 3.x and 4.x
template<class real>
inline int rfloor(real r)
{
    static const double FLOATTOINTCONST=(1.5*(1LL<<(52-16)));
    union { double d; int i; } temp;
    temp.d = r+FLOATTOINTCONST;
    return ((temp.i)>>16);
}

template<class real>
inline int rnear(real r)
{
    static const double FLOATTOINTCONST_0_5=(1.5*(1LL<<(52-16)))+0.5;
    union { double d; int i; } temp;
    temp.d = r+FLOATTOINTCONST_0_5;
    return ((temp.i)>>16);
}

inline int rceil(double r)
{
    return -rfloor(-r);
}

template<class real>
inline real rabs(real r)
{
    return (r>=0)?r:-r;
}

template<class real>
inline real rmin(real r, real s)
{
    return (r<=s)?r:s;
}

template<class real>
inline real rmax(real r, real s)
{
    return (r>s)?r:s;
}

template<class T>
inline T rlerp(const T& a, const T& b, float f)
{
    return a+(b-a)*f;
}

} // namespace Common

} // namespace Components

} // namespace Sofa

#endif
