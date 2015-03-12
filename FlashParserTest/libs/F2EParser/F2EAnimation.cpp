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
    m_name = string(animationName);
    
    m_parser = std::shared_ptr<F2EParser>(new F2EParser());
    
    string fileName = m_name + string("_Sheet.xml");
    string buffer = getFileContent(fileName.c_str());
    
    if (buffer[0] != '\0')
        m_parser->parseSprites(buffer, sprites);
    else {
#ifdef F2E_DEBUG
        std::cout << "F2EAnimation error: couldn't find sprites sheet xml file" << std::endl;
#endif
    }
    
    fileName.clear();
    buffer.clear();
    
    fileName = m_name + string("_Anim.xml");
    buffer = getFileContent(fileName.c_str());
    
    if (buffer[0] != '\0')
        framesCount = m_parser->parseAnimations(buffer, animations);
    else {
#ifdef F2E_DEBUG
        std::cout << "F2EAnimtion error: couldn't find animations xml file" << std::endl;
#endif
    }
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
#ifdef F2E_DEBUG
        std::cout << "F2EAnimation error: couldn\'t open file" << std::endl;
#endif
        return m_emptyString;
    }
}