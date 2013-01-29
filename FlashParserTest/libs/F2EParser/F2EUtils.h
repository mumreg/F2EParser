//
//  F2EUtils.h
//  Flash2EngineParser
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#ifndef FlashParserTest_F2EUtils_h
#define FlashParserTest_F2EUtils_h

#define DEBUG 1

#ifdef DEBUG
    #define F2E_DEBUG(x) std::cout << x
#else
    #define F2E_DEBUG(x)    ;
#endif

typedef struct _F2ESprite
{
    std::string name;
    
    unsigned int width;
    unsigned int height;
    
    std::string path;
    
    float anchorPointX;
    float anchorPointY;
    
    int zIndex;
} F2ESprite;

typedef struct _F2EFrame
{
    float x;
    float y;
    
    float scaleX;
    float scaleY;
    
    float rotation;
    
    unsigned int index;
} F2EFrame;

typedef struct _F2EPart
{
    std::string partName;
    std::vector<F2EFrame> frames;
} F2EPart;

typedef struct _F2EAnimationPart
{
    std::string animationName;
    unsigned int frameCount;
    std::vector<F2EPart> parts;
} F2EAnimationPart;

#endif
