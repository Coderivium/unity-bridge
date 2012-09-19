//
//  UnityBridge.h
//  Unity-iPhone
//
//  Created by Igor Ishchenko on 22.06.12.
//  Copyright (c) 2012 Coderivium. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "mono_bindings.h"

@interface UnityBridge : NSObject

+(UnityBridge*)sharedInstance;

- (void)registerObject:(MonoObject)theObject forName:(NSString*)theName;

- (void*)invokeMethod:(NSString*)theMethodName 
             onObject:(NSString*)theObjectName 
                 args:(void**)theArgs 
      returnValueType:(BOOL)isValueType;

- (NSString*)invokeStringMethod:(NSString *)theMethodName 
                       onObject:(NSString *)theObjectName 
                           args:(void**)theArgs;

- (NSArray*)invokeStringArrayMethod:(NSString *)theMethodName 
                           onObject:(NSString *)theObjectName 
                               args:(void**)theArgs;

@end

// interface for accessing bridge from Unity
void register_object(MonoObject object, char *name);