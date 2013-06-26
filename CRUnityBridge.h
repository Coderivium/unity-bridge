//
//  CRUnityBridge.h
//
//  Created by Igor Ishchenko on 22.06.12.
//
//  Copyright (C) 2013 Coderivium
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#include "mono_bindings.h"

@interface CRUnityBridge : NSObject

+(CRUnityBridge*)sharedInstance;

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