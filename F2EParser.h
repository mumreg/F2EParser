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
#include "rapidxml.hpp"

using namespace std;

class F2EParser
{
public:
    F2EParser();
    ~F2EParser();
    
    void parseText(string *text);
};

#endif /* defined(__FlashParserTest__F2EParser__) */
