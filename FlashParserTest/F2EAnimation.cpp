//
//  F2EAnimation.cpp
//  Flash2EngineParser
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//

#include "F2EAnimation.h"

//
// Method looks for animationName_Sheet.xml and animationName_Anim.xml files
// if it finds them than it parses files and fills two vectors
// sprites and animations
//
F2EAnimation::F2EAnimation(const char *animationName)
{
    name = string(animationName);
    
    parser = new F2EParser();
    
    string fileName = name + string("_Sheet.xml");
    string buffer = getFileContent(fileName.c_str());
    
    if (buffer[0] != '\0')
        parser->parseSprites(&buffer, &sprites);
    else
        F2E_DEBUG("F2EAnimation error: couldn't find sprites sheet xml file\n");
    
    fileName.clear();
    buffer.clear();
    
    fileName = name + string("_Anim.xml");
    buffer = getFileContent(fileName.c_str());
    
    if (buffer[0] != '\0')
        parser->parseAnimations(&buffer, &animations);
    else
        F2E_DEBUG("F2EAnimtion error: couldn't find animations xml file");
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
        F2E_DEBUG("F2EAnimation error: couldn\'t open file\n");
        return string('\0');
    }
}