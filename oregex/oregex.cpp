//
//  oregex.cpp
//  oregex
//
//  Created by David Álvarez Pons on 16/11/2019.
//  Copyright © 2019 David Álvarez Pons. All rights reserved.
//

#include <iostream>
#include "oregex.hpp"
#include "oregexPriv.hpp"

void oregex::HelloWorld(const char * s)
{
    oregexPriv *theObj = new oregexPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void oregexPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

