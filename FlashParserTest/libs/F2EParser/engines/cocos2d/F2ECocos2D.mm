//
//  F2ECocos2D.m
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 25.01.13.
//  Copyright 2013 TheBestUp. All rights reserved.
//

#import "F2ECocos2D.hpp"

#define HD_PREFIX   @"-ipadhd"

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
        
        animationQueue = [[NSMutableArray alloc] init];
        
        frameCount = 0;
        isAnimationPlaying = NO;
        currentAnimationObj = nil;
        
        [self scheduleUpdate];
    }
    return self;
}

-(BOOL)isHD
{
    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)])
    {
        if ([[UIScreen mainScreen] scale] > 1.0)
            return YES;
    }
    
    return NO;
}

-(NSString *)makePathForFile:(NSString *)fileName
{
    NSBundle *b = [NSBundle mainBundle];
    NSString *dir = [b resourcePath];
    NSArray *parts = [NSArray arrayWithObjects:
                      dir, fileName, (void *)nil];
    
    return [NSString pathWithComponents:parts];
}

-(void)loadAnimationInfo:(NSString *)animationName
{
    NSString *path = [self makePathForFile:animationName];
    const char *cpath = [path fileSystemRepresentation];
    
    animation = new F2EAnimation(cpath);
    
    NSLog(@"Loaded: %d sprites and %d animations", (int)animation->sprites.size(), (int)animation->animations.size());
    NSLog(@"Frames: %d", animation->framesCount);
}

-(void)loadSprites
{
    sprites = [[NSMutableArray alloc] init];
    
    //Check if there sprites sheet for animation
    BOOL sheetFlag = NO;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    
    NSString *sheetFile;
    NSString *plistFile;
    
    if ([self isHD])
    {
        sheetFile = [NSString stringWithFormat:@"%@_Sheet-ipadhd.png", name];
        plistFile = [NSString stringWithFormat:@"%@_Sheet-ipadhd.plist", name];
    }
    else
    {
        sheetFile = [NSString stringWithFormat:@"%@_Sheet.png", name];
        plistFile = [NSString stringWithFormat:@"%@_Sheet.plist", name];
    }
    
    NSString *path1 = [self makePathForFile:sheetFile];
    NSString *path2 = [self makePathForFile:plistFile];
    
    if ([fileManager fileExistsAtPath:path1] && [fileManager fileExistsAtPath:path2]) {
        //load sprtes sheet
        CCSpriteBatchNode *spritesNode;
        spritesNode = [CCSpriteBatchNode batchNodeWithFile:sheetFile];
        
        [self addChild:spritesNode];
        [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:plistFile];
        
        sheetFlag = YES;
        NSLog(@"F2E info: Found sprite sheet. Using it.");
    }
    else
        NSLog(@"F2E info: No sprite sheet. Using single sprites.");
    
    //load sprites
    for (std::vector<F2ESprite>::iterator it = animation->sprites.begin(); it != animation->sprites.end(); it++)
    {
        F2ESprite spriteInfo = *it;
        
        NSString *frameName;
        
        if (!sheetFlag && [self isHD])
            frameName = [NSString stringWithFormat:@"%s%@.png", spriteInfo.name.c_str(), HD_PREFIX];
        else
            frameName = [NSString stringWithFormat:@"%s.png", spriteInfo.name.c_str()];
        
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
                if (part.frames.size() != 0)
                {
                    F2EFrame frame = part.frames[0];
                    
                    CGPoint position = ccp(frame.x, -1.0f*frame.y);
                    [sprite setPosition:position];
                    
                    [sprite setRotation:frame.rotation];
                    
                    NSInteger opacity = (NSInteger)(255.0f*frame.opacity);
                    [sprite setOpacity:opacity];
                    
                    [sprite setScaleX:frame.scaleX];
                    [sprite setScaleY:frame.scaleY];
                }
                
                [self addChild:sprite];
            }
        }
    }
}

//time - time per one full animation cycle
-(void)playAnimation:(NSString *)animationName time:(float)time
{
    for (std::vector<F2EAnimationPart>::iterator it = animation->animations.begin(); it != animation->animations.end(); it++) {
        if ([animationName isEqualToString:[NSString stringWithFormat:@"%s", it->animationName.c_str()]])
        {   
            animationObj *obj = [[animationObj alloc] init];
            obj.part = &(*it);
            obj.time = time;
            
            [animationQueue enqueue:obj];
            
            [obj release];
            
            break;
        }
    }
}

-(void)playAnimationPart:(animationObj *)obj
{
    currentAnimationObj = obj;
    frameCount = 0;
    float dt = obj.time/obj.part->frameCount;
    [self schedule:@selector(animateFrame) interval:dt];
}

-(void)playFullAnimationWithReverse:(float)time
{
    [self playFullAnimation:time/2.0f];
    
    time = time/2.0f;
    
    //time per frame
    float dt = time/animation->framesCount;
    
    std::vector<F2EAnimationPart>::reverse_iterator it = animation->animations.rbegin();
    
    for (; it != animation->animations.rend(); it++) {
        animationObj *obj = [[animationObj alloc] init];
        
        obj.part = &(*it);
        obj.time = it->frameCount*dt;
        obj.isReversed = YES;
        
        [animationQueue addObject:obj];
        [obj release];
    }
}

//time - time of full animation cycle
-(void)playFullAnimation:(float)time
{
    //time per frame
    float dt = time/animation->framesCount;
    
    std::vector<F2EAnimationPart>::iterator it = animation->animations.begin();
    
    for (; it != animation->animations.end(); it++) {
        animationObj *obj = [[animationObj alloc] init];

        obj.part = &(*it);
        obj.time = it->frameCount*dt;
        obj.isReversed = NO;
        
        [animationQueue addObject:obj];
        [obj release];
    }
    
}

-(void)update:(ccTime)dt
{    
    if ([animationQueue count] > 0 && !isAnimationPlaying)
    {
        isAnimationPlaying = YES;
        [self playAnimationPart:[animationQueue objectAtIndex:0]];
    }
}

-(void)animateFrame
{
    if (frameCount < currentAnimationObj.part->frameCount)
    {
        std::vector<F2EPart>::iterator it = currentAnimationObj.part->parts.begin();
        
        for (; it != currentAnimationObj.part->parts.end(); it++) {
            for (CCSprite *sprite in sprites) {
                
                NSString *partName = [NSString stringWithFormat:@"%s.png", it->partName.c_str()];
                NSString *spriteName = [NSString stringWithFormat:@"%s.png", (char *) sprite.userData];
                
                if ([partName isEqualToString:spriteName])
                {
                    if (frameCount < it->frames.size())
                    {
                        F2EFrame *frame;
                        
                        if (!currentAnimationObj.isReversed)
                            frame = &(it->frames[frameCount]);
                        else
                            frame = &(it->frames[currentAnimationObj.part->frameCount - frameCount - 1]);
                        
                        CGPoint position = ccp(frame->x, -1.0f*frame->y);
                        [sprite setPosition:position];
                        
                        [sprite setRotation:frame->rotation];
                        
                        NSInteger opacity = (NSInteger)(255.0f*frame->opacity);
                        [sprite setOpacity:opacity];
                        
                        [sprite setScaleX:frame->scaleX];
                        [sprite setScaleY:frame->scaleY];
                    }
                }
            }
        }
        
        frameCount++;
    }
    else
    {
        [self unschedule:@selector(animateFrame)];
        [animationQueue dequeue];
        isAnimationPlaying = NO;
    }
}

-(void)dealloc
{
    for (CCSprite *sprite in sprites) {
        free(sprite.userData);
    }
    
    delete animation;
    [sprites release];
    [super dealloc];
}

@end
