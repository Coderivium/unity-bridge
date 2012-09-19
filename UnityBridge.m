//
//  UnityBridge.m
//  Unity-iPhone
//
//  Created by Igor Ishchenko on 22.06.12.
//  Copyright (c) 2012 Coderivium. All rights reserved.
//

#import "UnityBridge.h"
#import "CRNSString+ConversionToChar.h"

@interface UnityBridge()

@property (nonatomic, assign) MonoImage *monoImage;
@property (nonatomic, assign) CFMutableDictionaryRef objects;
@property (nonatomic, assign) void *thisObj;

@end

@implementation UnityBridge

@synthesize monoImage;
@synthesize objects;
@synthesize thisObj;

static UnityBridge *instance;

+(UnityBridge*)sharedInstance {
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
    [[UnityBridge sharedInstance] registerObject:object 
                                         forName:[NSString stringWithUTF8String:name]];
}



