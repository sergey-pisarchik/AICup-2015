//
//  DebugFunctions.cpp
//  PSP
//
//  Created by Sergey Pisarchik on 11/17/15.
//  Copyright © 2015 Sergey Pisarchik. All rights reserved.
//

#include "DebugFunctions.h"

#ifdef LOG


void PrintMap(TMap const & mp)
{
    for (auto & vr: mp)
    {
        for (auto & val: vr)
        {
            if (val == EMPTY)
                cout << "#";
            else
                cout << ".";
        }
        cout << endl;
    }
}



#endif