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
    
    parser = new F2EParser();
    
    //TODO: Make sprite sheet name and animations config file name
    //read content of files then parse
    
//    parser->parseSprites(&buffer, &sprites);
//    parser->parseAnimations(&buffer, &animations);
}

string F2EAnimation::getFileContent(const char *fileName)
{
    fstream inputFile(fileName, fstream::in);
    
    if (inputFile)
    {
        string buffer;
    
        inputFile.seekg(0, ios::end);
        buffer.resize(inputFile.tellg());
        inputFile.seekg(0, ios::beg);
        
        inputFile.read(&buffer[0], buffer.size());
        
        inputFile.close();
        
        return buffer;
    }
    else
    {
        F2E_DEBUG("F2EAnimation error: couldn\'t open file");
        return NULL;
    }
}