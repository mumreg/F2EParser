//
//  F2EUtils.h
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//
//

#ifndef FlashParserTest_F2EUtils_h
#define FlashParserTest_F2EUtils_h

typedef struct _F2ESprite
{
    string name;
    
    float width;
    float height;
    
    string path;
    
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
    string partName;
    vector<F2EFrame> frames;
} F2EPart;

typedef struct _F2EAnimationPart
{
    string animationName;
    unsigned int frameCount;
    vector<F2EPart> parts;
} F2EAnimationPart;

#endif
