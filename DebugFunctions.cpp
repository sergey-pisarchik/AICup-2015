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
    for (size_t y = 0; y < mp[0].size(); ++y)
    {
        for (size_t x = 0; x < mp.size(); ++x)
            cout << (mp[x][y] == 0 ? "." : "0");
        cout << endl;
    }

}



#endif