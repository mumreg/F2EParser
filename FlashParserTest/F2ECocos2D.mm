//
//  F2ECocos2D.m
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 25.01.13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#import "F2ECocos2D.hpp"

@implementation F2ECocos2D

-(id)initWithAnimation:(NSString *)animationName
{
    if (self = [super init])
    {
        [self loadAnimationInfo:animationName];
        name = [NSString stringWithString:animationName];
        [self loadSprites];
        [self loadAnimations];
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
        
        NSLog(@"Loading frame %@", frameName);
        
        CCSprite *sprite;
        if (sheetFlag)
            sprite = [CCSprite spriteWithSpriteFrameName:frameName];
        else
            sprite = [CCSprite spriteWithFile:frameName];
        
        sprite.userData = malloc(sizeof(unsigned char)*spriteInfo.name.length());
        strcpy((char *)sprite.userData, spriteInfo.name.c_str());

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
                [sprite setPosition:ccp(frame.x, frame.y)];
                
                //TODO: подумать как поступать если величина отсутствует
                // в xml-файле
                
                NSLog(@"frameName: %@ pos: %f %f", partName, frame.x, frame.y);
                
                [self addChild:sprite];
            }
        }
    }
}

-(void)playAnimation:(NSString *)animationName loop:(BOOL)loop
{
    
}

-(void)dealloc
{
    delete animation;
    [sprites release];
    [super dealloc];
}

@end
