//
//  NSStringToChar.h
//  Unity-iPhone
//
//  Created by Dmitry Utenkov on 24.05.12.
//  Copyright (c) 2012 Coderivium. All rights reserved.
//

#import "UnityBridge.h"

@interface NSString (ConversionToChar)

- (char *)convertToChar;
- (MonoString*)monoString;

@end
