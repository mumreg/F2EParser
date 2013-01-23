//
//  F2EParser.cpp
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#include "F2EParser.h"

F2EParser::F2EParser()
{
    
}

F2EParser::~F2EParser()
{
    
}

void F2EParser::parseText(string *text)
{
    rapidxml::xml_document<> doc;
    doc.parse<0>((char *) text->c_str());
}

void F2EParser::parseAnimations(string *buffer, vector<F2EAnimationPart> *animations)
{
    
}

void F2EParser::parseSprites(string *buffer, vector<F2ESprite> *sprites)
{
    
}

