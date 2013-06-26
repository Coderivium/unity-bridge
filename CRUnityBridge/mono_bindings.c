//
//  mono_bindings.c
//
//  Created by Igor Ishchenko on 25.06.12.
//
//  Copyright (C) 2013 Coderivium
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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