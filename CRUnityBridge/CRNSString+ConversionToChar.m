//
//  CRNSString+ConversionToChar.h
//
//  Created by Dmitry Utenkov on 24.05.12.
//
//  Copyright (C) 2013 Coderivium
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
