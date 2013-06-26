///
///  @file CRUnityBridge.h
///
///  @author Created by Igor Ishchenko <igor.ishchenko@coderivium.com> on 22.06.12.
///
///  @section LICENSE
///
///  Copyright (C) 2013 Coderivium
///
///  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
///
///  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
///
///  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///

#import <Foundation/Foundation.h>
#include "mono_bindings.h"

///
/// @brief Singleton for accessing methods in Unity from native code
///
/// CRUnityBridge allows to call methods defined in Unity
/// without using UnitySendMessage() function which is
/// always one frame back.
@interface CRUnityBridge : NSObject

///
/// Returns the shared instance of the class
///
/// @return The shared instance
+(CRUnityBridge*)sharedInstance;

///
/// Add mono object to the list of know objects.
/// Methods can be invoked only after registering object.
///
/// @param theObject Pointer to the object to be registered
/// @param theName   Specifies the name by which object will be accessible
- (void)registerObject:(MonoObject)theObject forName:(NSString*)theName;

///
/// Performs method invokation.
/// Uses mono_runtime_invoke to call methods.
///
/// @param theMathodName   Name of the method to be called. Should be in form ClassName:MethodName
/// @param theObjectName   Name of the object on which method will be called. 
/// @param args            Array of parameters to pass to method. Should contain only primitive data types.
/// @param returnValueType Indicates if value returned from method whould be unboxed
///
/// @return The value returned from mono method
- (void*)invokeMethod:(NSString*)theMethodName 
             onObject:(NSString*)theObjectName 
                 args:(void**)theArgs 
      returnValueType:(BOOL)isValueType;

///
/// Invokes method which should return string value
///
/// @param theMathodName   Name of the method to be called. Should be in form ClassName:MethodName
/// @param theObjectName   Name of the object on which method will be called.
/// @param args            Array of parameters to pass to method. Should contain only primitive data types.
///
/// @return  The string returned from mono method
- (NSString*)invokeStringMethod:(NSString *)theMethodName 
                       onObject:(NSString *)theObjectName 
                           args:(void**)theArgs;

///
/// Invokes method which returns array of strings
/// @param theMathodName   Name of the method to be called. Should be in form ClassName:MethodName
/// @param theObjectName   Name of the object on which method will be called.
/// @param args            Array of parameters to pass to method. Should contain only primitive data types.
///
/// @return  The array of strings returned from mono method
- (NSArray*)invokeStringArrayMethod:(NSString *)theMethodName 
                           onObject:(NSString *)theObjectName 
                               args:(void**)theArgs;

@end

///
/// @brief Register mono object in unity bridge
///
/// Function to be imported in mono code with 
/// [DllImport("__Internal")]
/// public static extern void register_object(IntPtr objectRef, string name);
/// 
/// @param object  Pointer of the object to be registered. Can be received by invoking (System.IntPtr) GCHandle.Alloc( this );
/// @param name    Specifies the name by which object will be accessible
void register_object(MonoObject object, char *name);