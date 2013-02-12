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
    
    animationObj *currentAnimationObj;
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

-(BOOL)isHD;

-(void)playFullAnimation:(float)time;
-(void)playFullAnimationWithReverse:(float)time;
-(void)playAnimation:(NSString *)animationName time:(float)time;
-(void)playAnimationPart:(animationObj *)part;

-(void)animateFrame;

-(NSString *)makePathForFile:(NSString *)fileName;

@property (nonatomic) BOOL isAnimationPlaying;

@end
