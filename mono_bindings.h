//
//  mono_bindings.h
//  Unity-iPhone
//
//  Created by Igor Ishchenko on 25.06.12.
//  Copyright (c) 2012 Coderivium. All rights reserved.
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
