//
//  F2ECocos2D.h
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 25.01.13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "cocos2d.h"
#import "F2EAnimation.h"
#import "NSMutableArray+QueueAdditions.h"
#import "AnimationObj.h"

@interface F2ECocos2D : CCNode {
    F2EAnimation *animation;
    
    F2EAnimationPart *currentAnimationPart;
    unsigned int frameCount;
    
    NSString *name;
    
    NSMutableArray *sprites;
    NSMutableArray *animations;
    
    NSMutableArray *animationQueue;
    
    BOOL isAnimationPlaying;
}

-(id)initWithAnimation:(NSString *)animationName;

-(void)loadAnimationInfo:(NSString *)animationName;

-(void)loadSprites;
-(void)loadAnimations;

-(void)playFullAnimation:(float)time;
-(void)playAnimation:(NSString *)animationName time:(float)time;
-(void)playAnimationPart:(F2EAnimationPart *)part time:(float)time;

-(void)animateFrame;

-(NSString *)makePathForFile:(NSString *)fileName;

@property (nonatomic) BOOL isAnimationPlaying;

@end
