//
//  F2EUtils.h
//  Flash2EngineParser
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#ifndef FlashParserTest_F2EUtils_h
#define FlashParserTest_F2EUtils_h

typedef struct _F2ESprite
{
    std::string name;
    
    unsigned int width;
    unsigned int height;
    
    std::string path;
    
    float anchorPointX;
    float anchorPointY;
    
    int zIndex;
    _F2ESprite() : width(0), height(0), anchorPointX(0), anchorPointY(0), zIndex(0) {}
} F2ESprite;

typedef struct _F2EFrame
{
    float x;
    float y;
    
    float scaleX;
    float scaleY;
    
    float rotation;
    float opacity;
    
    unsigned int index;
    _F2EFrame() : x(0), y(0), scaleX(1.0f), scaleY(1.0f), rotation(0), opacity(1.0f) {}
} F2EFrame;

typedef struct _F2EPart
{
    std::string partName;
    std::vector<std::shared_ptr<F2EFrame>> frames;
} F2EPart;

typedef struct _F2EAnimationPart
{
    std::string animationName;
    unsigned int frameCount;
    std::vector<std::shared_ptr<F2EPart>> parts;
} F2EAnimationPart;

#endif
