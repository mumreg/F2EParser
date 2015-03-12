//
//  F2EAnimation.h
//  Flash2EngineParser
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
    vector<std::shared_ptr<F2ESprite>> sprites;
    vector<std::shared_ptr<F2EAnimationPart>> animations;
    int framesCount;
    
private:
    string getFileContent(const char *fileName);
    
    string m_name;
    std::shared_ptr<F2EParser> m_parser;
    string m_emptyString;
};

#endif /* defined(__FlashParserTest__F2EAnimation__) */
