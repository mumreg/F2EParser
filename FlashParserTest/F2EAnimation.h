//
//  F2EAnimation.h
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#ifndef __FlashParserTest__F2EAnimation__
#define __FlashParserTest__F2EAnimation__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "F2EParser.h"
#include "F2EUtils.h"

using namespace std;

class F2EAnimation
{
public:
    F2EAnimation(const char *animationName);
    
private:
    string getFileContent(const char *fileName);
    
    string name;
    F2EParser *parser;
    vector<F2ESprite> sprites;
    vector<F2EAnimationPart> animations;
};

#endif /* defined(__FlashParserTest__F2EAnimation__) */
