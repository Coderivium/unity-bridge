//
//  mono_bindings.h
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


#ifndef Unity_iPhone_mono_bindings_h
#define Unity_iPhone_mono_bindings_h

typedef void* MonoDomain;
typedef void* MonoAssembly;
typedef void* MonoImage;
typedef void* MonoClass;
typedef void* MonoObject;
typedef void* MonoMethodDesc;
typedef void* MonoMethod;
typedef void* MonoString;
typedef void* MonoArray;
typedef int gboolean;

MonoDomain     *mono_domain_get();
MonoAssembly   *mono_domain_assembly_open(MonoDomain *domain, const char *assemblyName);
MonoImage      *mono_assembly_get_image(MonoAssembly *assembly);
MonoMethodDesc *mono_method_desc_new(const char *methodString, gboolean useNamespace);
MonoMethodDesc *mono_method_desc_free(MonoMethodDesc *desc);
MonoMethod     *mono_method_desc_search_in_image(MonoMethodDesc *methodDesc, MonoImage *image);
MonoObject     *mono_runtime_invoke(MonoMethod *method, void *obj, void **params, MonoObject **exc);
MonoClass      *mono_object_get_class(MonoObject *object);
MonoMethod     *mono_class_get_method_from_name	(MonoClass *clss, const char *name, int param_count);
MonoObject     *mono_gchandle_get_target(void* obj);
MonoString     *mono_string_new(MonoDomain* domain, const char* str);
void           *mono_object_unbox(MonoObject *obj);
char           *mono_string_to_utf8 (MonoString *s);
int             mono_array_length (MonoArray* array);
MonoObject     *mono_array_get(MonoArray *array, int index, int elem_size);
void            mono_thread_attach();

#endif
