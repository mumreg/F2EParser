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
#include <memory>
#include "rapidxml.hpp"

#include "F2EUtils.h"

using namespace std;

class F2EParser
{
public:
    F2EParser();
    ~F2EParser();
    
    int parseBuffer(const string &buffer);
    int parseSprites(const string &buffer, vector<std::shared_ptr<F2ESprite>> &sprites);
    int parseAnimations(const string &buffer, vector<std::shared_ptr<F2EAnimationPart>> &animations);
    
private:
    void saveAttrToSprite(const string &attr_name, const string &attr_value, std::shared_ptr<F2ESprite> &sprite);
    void saveAttrToFrame(const string &attr_name, const string &attr_value, std::shared_ptr<F2EFrame> &frame);
    
    std::shared_ptr<rapidxml::xml_document<>> m_doc;
};

#endif /* defined(__FlashParserTest__F2EParser__) */
