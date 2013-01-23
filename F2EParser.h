//
//  F2EParser.h
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#ifndef __FlashParserTest__F2EParser__
#define __FlashParserTest__F2EParser__

#include <iostream>
#include <string>
#include <vector>
#include "rapidxml.hpp"

#include "F2EUtils.h"

using namespace std;

class F2EParser
{
public:
    F2EParser();
    ~F2EParser();
    
    void parseText(string *text);
    void parseSprites(string *buffer, vector<F2ESprite> *sprites);
    void parseAnimations(string *buffer, vector<F2EAnimationPart> *animations);
};

#endif /* defined(__FlashParserTest__F2EParser__) */
