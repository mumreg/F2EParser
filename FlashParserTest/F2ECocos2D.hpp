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

@interface F2ECocos2D : CCNode {
    F2EAnimation *animation;
    
    F2EAnimationPart *currentAnimationPart;
    unsigned int frameCount;
    
    NSString *name;
    
    NSMutableArray *sprites;
    NSMutableArray *animations;
    
    BOOL isAnimationPlaying;
}

-(id)initWithAnimation:(NSString *)animationName;

-(void)loadAnimationInfo:(NSString *)animationName;

-(void)loadSprites;
-(void)loadAnimations;

-(void)playFullAnimationAndLoop:(BOOL)loop time:(float)time;
-(void)playAnimation:(NSString *)animationName loop:(BOOL)loop time:(float)time;
-(void)playAnimationPart:(F2EAnimationPart *)part loop:(BOOL)loop time:(float)time;
-(void)animateFrame;

@property (nonatomic) BOOL isAnimationPlaying;

@end
