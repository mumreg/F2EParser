//
//  F2ECocos2D.m
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 25.01.13.
//  Copyright 2013 TheBestUp. All rights reserved.
//

#import "F2ECocos2D.hpp"

@implementation F2ECocos2D

@synthesize isAnimationPlaying;

-(id)initWithAnimation:(NSString *)animationName
{
    if (self = [super init])
    {
        [self loadAnimationInfo:animationName];
        name = [NSString stringWithString:animationName];
        [self loadSprites];
        [self loadAnimations];
        frameCount = 0;
        isAnimationPlaying = NO;
        currentAnimationPart = NULL;
    }
    return self;
}

-(void)loadAnimationInfo:(NSString *)animationName
{
    NSBundle *b = [NSBundle mainBundle];
    NSString *dir = [b resourcePath];
    NSArray *parts = [NSArray arrayWithObjects:
                      dir, animationName, (void *)nil];
    NSString *path = [NSString pathWithComponents:parts];
    const char *cpath = [path fileSystemRepresentation];
    
    animation = new F2EAnimation(cpath);
    
    NSLog(@"Loaded: %d sprites and %d animations", (int)animation->sprites.size(), (int)animation->animations.size());
}

-(void)loadSprites
{
    sprites = [[NSMutableArray alloc] init];
    
    //Check if there sprites sheet for animation
    BOOL sheetFlag = NO;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    
    NSString *sheetFile = [NSString stringWithFormat:@"%@_Sheet.png", name];
    NSString *plistFile = [NSString stringWithFormat:@"%@_Sheet.plist", name];
    
    if ([fileManager fileExistsAtPath:sheetFile] && [fileManager fileExistsAtPath:plistFile]) {
        //load sprtes sheet
        CCSpriteBatchNode *spritesNode;
        spritesNode = [CCSpriteBatchNode batchNodeWithFile:sheetFile];
        
        [self addChild:spritesNode];
        [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFile];
        
        sheetFlag = YES;
    }
    
    //load sprites
    for (std::vector<F2ESprite>::iterator it = animation->sprites.begin(); it != animation->sprites.end(); it++)
    {
        F2ESprite spriteInfo = *it;
        
        NSString *frameName = [NSString stringWithFormat:@"%s.png", spriteInfo.name.c_str()];
        
        CCSprite *sprite;
        if (sheetFlag)
            sprite = [CCSprite spriteWithSpriteFrameName:frameName];
        else
            sprite = [CCSprite spriteWithFile:frameName];
        
        sprite.userData = malloc(sizeof(unsigned char)*spriteInfo.name.length());
        strcpy((char *)sprite.userData, spriteInfo.name.c_str());

        CGPoint anchorPoint = ccp(spriteInfo.anchorPointX/spriteInfo.width, 1.0f - spriteInfo.anchorPointY/spriteInfo.height);
        [sprite setAnchorPoint:anchorPoint];
        
        [sprite setZOrder:spriteInfo.zIndex];
        
        [sprites addObject:sprite];
    }
}

-(void)loadAnimations
{
    animations = [[NSMutableArray alloc] init];
    
    F2EAnimationPart animationPart = animation->animations[0];
    
    for (CCSprite *sprite in sprites) {
        for (std::vector<F2EPart>::iterator it = animationPart.parts.begin(); it != animationPart.parts.end(); it++) {
            F2EPart part = *it;
        
            NSString *partName = [NSString stringWithFormat:@"%s.png", part.partName.c_str()];
            NSString *spriteName = [NSString stringWithFormat:@"%s.png", (char *) sprite.userData];
            
            if ([partName isEqualToString:spriteName])
            {
                F2EFrame frame = part.frames[0];
                CGPoint position = ccp(frame.x, -1.0f*frame.y);
                [sprite setRotation:frame.rotation];
                [sprite setPosition:position];
                
                [self addChild:sprite];
            }
        }
    }
}

//time - time per one full animation cycle
-(void)playAnimation:(NSString *)animationName loop:(BOOL)loop time:(float)time
{
    for (std::vector<F2EAnimationPart>::iterator it = animation->animations.begin(); it != animation->animations.end(); it++) {
        if ([animationName isEqualToString:[NSString stringWithFormat:@"%s", it->animationName.c_str()]])
        {
            [self playAnimationPart:&(*it) loop:loop time:time];
        }
    }
}

-(void)playAnimationPart:(F2EAnimationPart *)part loop:(BOOL)loop time:(float)time
{
    isAnimationPlaying = YES;
    
    currentAnimationPart = part;
    frameCount = 0;
    float dt = time/part->frameCount;
    [self schedule:@selector(animateFrame) interval:dt];
}

//time - time of full animation cycle
-(void)playFullAnimationAndLoop:(BOOL)loop time:(float)time
{
    
}

-(void)animateFrame
{
    if (frameCount < currentAnimationPart->frameCount)
    {
        std::vector<F2EPart>::iterator it = currentAnimationPart->parts.begin();
        
        for (; it != currentAnimationPart->parts.end(); it++) {
            for (CCSprite *sprite in sprites) {
                
                NSString *partName = [NSString stringWithFormat:@"%s.png", it->partName.c_str()];
                NSString *spriteName = [NSString stringWithFormat:@"%s.png", (char *) sprite.userData];
                
                if ([partName isEqualToString:spriteName])
                {
                    if (frameCount < it->frames.size())
                    {
                        F2EFrame *frame = &(it->frames[frameCount]);
                        
                        CGPoint position = ccp(frame->x, -1.0f*frame->y);
                        [sprite setRotation:frame->rotation];
                        [sprite setPosition:position];
                    }
                }
            }
        }
        
        frameCount++;
    }
    else
    {
        [self unschedule:@selector(animateFrame)];
        isAnimationPlaying = NO;
    }
}

-(void)dealloc
{
    //TODO: добавить удаление строк из sprites.sprite.userData
    delete animation;
    [sprites release];
    [super dealloc];
}

@end
