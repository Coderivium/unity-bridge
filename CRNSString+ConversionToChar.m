//
//  NSStringToChar.m
//  Unity-iPhone
//
//  Created by Dmitry Utenkov on 24.05.12.
//  Copyright (c) 2012 Coderivium. All rights reserved.
//

#import "CRNSString+ConversionToChar.h"

@implementation NSString (ConversionToChar)

- (char *)convertToChar  {
    char *charString = (char *)"\0";
    
    if (self != nil) {
        charString = (char *)malloc([self lengthOfBytesUsingEncoding:NSUTF8StringEncoding]+1);
        [self getCString:charString 
                 maxLength:[self lengthOfBytesUsingEncoding:NSUTF8StringEncoding]+1 
                  encoding:NSUTF8StringEncoding];
    }
    
    return charString;
}

- (MonoString*)monoString {
    char *cString = [self convertToChar];
    
    return mono_string_new(mono_domain_get(), cString);
}

@end
