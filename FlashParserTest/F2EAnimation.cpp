//
//  F2EAnimation.cpp
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#include "F2EAnimation.h"

F2EAnimation::F2EAnimation(const char *animationName)
{
    name = string(animationName);
    
    //TODO:Check if file exists
    //then open
    
    parser = new F2EParser();
}