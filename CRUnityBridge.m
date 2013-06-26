//
//  CRUnityBridge.m
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


#import "CRUnityBridge.h"
#import "CRNSString+ConversionToChar.h"

@interface CRUnityBridge()

@property (nonatomic, assign) MonoImage *monoImage;
@property (nonatomic, assign) CFMutableDictionaryRef objects;
@property (nonatomic, assign) void *thisObj;

@end

@implementation CRUnityBridge

@synthesize monoImage;
@synthesize objects;
@synthesize thisObj;

static CRUnityBridge *instance;

+(CRUnityBridge*)sharedInstance {
    @synchronized(self) {
        if (instance == nil) {
            [[self alloc] init];
        }
    }
    
    return instance;
}

- (id)init {
    self = [super init];
    instance = self;
    
    if (self) {
        MonoDomain *domain = mono_domain_get();
        
        NSString *assemblyPath = [[[NSBundle mainBundle] bundlePath]
                                  stringByAppendingPathComponent:@"Data/Managed/Assembly-CSharp.dll"];
        MonoAssembly *assembly = mono_domain_assembly_open(domain, [assemblyPath UTF8String]);
        MonoImage *image = mono_assembly_get_image(assembly);
        
        [self setMonoImage:image];
        
         objects = CFDictionaryCreateMutable(kCFAllocatorDefault, 0, &kCFCopyStringDictionaryKeyCallBacks, NULL);
    }
    
    return self;
}

- (void)registerObject:(MonoObject)theObject forName:(NSString*)theName {
    CFDictionaryAddValue(objects, theName, theObject);
}

- (NSString*)invokeStringMethod:(NSString *)theMethodName 
                       onObject:(NSString *)theObjectName 
                           args:(void**)theArgs 
{
    MonoObject *ret = [self invokeMethod:theMethodName 
                                onObject:theObjectName 
                                    args:theArgs 
                         returnValueType:NO];
    
    char *str = mono_string_to_utf8(ret);
    
    return [NSString stringWithUTF8String:str];
}

- (NSArray*)invokeStringArrayMethod:(NSString *)theMethodName 
                            onObject:(NSString *)theObjectName 
                                args:(void**)theArgs 
{
    MonoArray *ret = (MonoArray*)[self invokeMethod:theMethodName 
                                onObject:theObjectName 
                                    args:theArgs 
                         returnValueType:NO];
    
    long num = mono_array_length(ret);
    
    NSMutableArray *mArray = [NSMutableArray array];
    
    for (int i = 0; i < num; i++) {
        MonoString *s = (MonoString*)mono_array_get(ret, i, sizeof(MonoString*));
        char *s2 = mono_string_to_utf8(s);
        
        [mArray addObject:[NSString stringWithUTF8String:s2]];
    }
    
    return mArray;
}

- (void*)invokeMethod:(NSString*)theMethodName 
             onObject:(NSString*)theObjectName 
                 args:(void**)theArgs 
      returnValueType:(BOOL)isValueType 
{
    // TODO: rewrite to store known mono methods
    MonoMethodDesc *desc = mono_method_desc_new([theMethodName convertToChar], FALSE);
    
    MonoMethod *method = mono_method_desc_search_in_image(desc, monoImage);
    
    mono_method_desc_free(desc);
    
    if (CFDictionaryContainsKey(objects, theObjectName)) {
        thisObj = (void *)CFDictionaryGetValue(objects, theObjectName);
    }
    
    MonoObject *obj = mono_gchandle_get_target(thisObj);
    
    MonoObject *ret = mono_runtime_invoke(method, obj, theArgs, NULL);
    
    if (isValueType) {
        ret = mono_object_unbox(ret);
    }
    
    return ret;
}

@end

void register_object(void *object, char *name) {
    [[CRUnityBridge sharedInstance] registerObject:object 
                                         forName:[NSString stringWithUTF8String:name]];
}



