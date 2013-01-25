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
    
    NSString *name;
    
    NSMutableArray *sprites;
    NSMutableArray *animations;
}

-(id)initWithAnimation:(NSString *)animationName;

-(void)loadAnimationInfo:(NSString *)animationName;

-(void)loadSprites;
-(void)loadAnimations;

-(void)playAnimation:(NSString *)animationName loop:(BOOL)loop;

@end
