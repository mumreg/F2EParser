//
//  F2EParser.h
//  Flash2EngineParser
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
    
    int parseBuffer(string *buffer);
    int parseSprites(string *buffer, vector<F2ESprite> *sprites);
    int parseAnimations(string *buffer, vector<F2EAnimationPart> *animations);
    
private:
    void saveAttrToSprite(string *attr_name, string *attr_value, F2ESprite *sprite);
    void saveAttrToFrame(string *attr_name, string *attr_value, F2EFrame *frame);
    
    rapidxml::xml_document<> *doc;
};

#endif /* defined(__FlashParserTest__F2EParser__) */
