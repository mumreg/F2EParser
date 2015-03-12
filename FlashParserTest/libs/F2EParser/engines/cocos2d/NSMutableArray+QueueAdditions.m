//
//  NSMutableArray+QueueAdditions.m
//  FlashParserTest
//
//  Created by Mikhail Perekhodtsev on 29.01.13.
//
//

#import "NSMutableArray+QueueAdditions.h"

@implementation NSMutableArray (QueueAdditions)
// Queues are first-in-first-out, so we remove objects from the head
- (id) dequeue {
    // if ([self count] == 0) return nil; // to avoid raising exception (Quinn)
    id headObject = [self objectAtIndex:0];
    if (headObject != nil) {
        [[headObject retain] autorelease]; // so it isn't dealloc'ed on remove
        [self removeObjectAtIndex:0];
    }
    return headObject;
}

// Add to the tail of the queue (no one likes it when people cut in line!)
- (void) enqueue:(id)anObject {
    [self addObject:anObject];
    //this method automatically adds to the end of the array
}
@end
