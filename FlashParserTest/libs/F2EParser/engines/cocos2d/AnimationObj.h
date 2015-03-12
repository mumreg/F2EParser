//
//  AnimationObj.h
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 29.01.13.
//
//

#import <Foundation/Foundation.h>
#import "F2EAnimation.h"

@interface animationObj : NSObject
{
}

@property (nonatomic) F2EAnimationPart *part;
@property (nonatomic) float time;

@end