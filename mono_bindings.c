//
//  mono_bindings.c
//  Unity-iPhone
//
//  Created by Igor Ishchenko on 25.06.12.
//  Copyright (c) 2012 Coderivium. All rights reserved.
//

#include "mono_bindings.h"

enum kMonoOffsetTypes {
    kMonoAddressOffset = 12,
    kMonoDataOffset = 16
};

// some magic applied here
// from http://forum.unity3d.com/threads/5687-C-plugin-pass-arrays-from-C
int mono_array_length(MonoArray *array) {
    char *raw = kMonoAddressOffset + (char*)array;
    
    return *(int*)(raw);
}

MonoObject *mono_array_get(MonoArray *array, int index, int elem_size) {
    char *raw = kMonoDataOffset + index*elem_size + (char*)array;
    
    return *(MonoObject*)raw;
}