//
//  HelloWorldLayer.h
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 23.01.13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//


#import <GameKit/GameKit.h>

// When you import this file, you import all the cocos2d classes
#import "cocos2d.h"
#import "F2ECocos2D.hpp"

// HelloWorldLayer
@interface HelloWorldLayer : CCLayer <GKAchievementViewControllerDelegate, GKLeaderboardViewControllerDelegate, CCTargetedTouchDelegate>
{
    F2ECocos2D *newAnimation;
}

// returns a CCScene that contains the HelloWorldLayer as the only child
+(CCScene *) scene;

@end
