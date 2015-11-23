//
//  UsefullFunctions.h
//  PSP
//
//  Created by Sergey Pisarchik on 11/20/15.
//  Copyright © 2015 Sergey Pisarchik. All rights reserved.
//

#ifndef UsefullFunctions_h
#define UsefullFunctions_h

#include "CommonDefines.h"
#include "Cell.h"

double Deg(double const rad);
double FDeg(double const rad);
double Rad(double const deg);
double Speed(Unit const & unit);

// return sign that if add to from will became to
int GetXSign(Cell const & from, Cell const & to);
int GetYSign(Cell const & from, Cell const & to);

#endif /* UsefullFunctions_h */

