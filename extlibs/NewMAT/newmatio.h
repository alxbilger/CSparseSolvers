//$$ newmatio.h           definition file for matrix package input/output

// Copyright (C) 1991,2,3,4: R B Davies

#ifndef NEWMATIO_LIB
#define NEWMATIO_LIB 0

#ifndef WANT_STREAM
#define WANT_STREAM
#endif

#include "newmat.h"

#ifndef newmat_no_namespace
namespace NewMAT {
#endif



/**************************** input/output *****************************/

ostream& operator<<(ostream&, const BaseMatrix&);

ostream& operator<<(ostream&, const GeneralMatrix&);


/*  Use in some old versions of G++ without complete iomanipulators

class Omanip_precision
{
   int x;
public:
   Omanip_precision(int i) : x(i) {}
   friend ostream& operator<<(ostream& os, Omanip_precision i);
};


Omanip_precision setprecision(int i);

class Omanip_width
{
   int x;
public:
   Omanip_width(int i) : x(i) {}
   friend ostream& operator<<(ostream& os, Omanip_width i);
};

Omanip_width setw(int i);

*/

#ifndef newmat_no_namespace
}
#endif



#endif

// body file: newmat9.cpp

