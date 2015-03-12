//
//  NSMutableArray+QueueAdditions.h
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 29.01.13.
//
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (QueueAdditions)
-(id) dequeue;
-(void) enqueue:(id)obj;
@end
