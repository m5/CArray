// Include the Ruby headers and goodies
#include "ruby.h"

// Defining a space for information and references about the module to be stored internally
VALUE CArrayExt = Qnil;

// Prototype for the initialization method - Ruby calls this, not you
void Init_carray();

VALUE method_fill_array(VALUE self, VALUE s, VALUE a);
VALUE method_max_index(VALUE self, VALUE s);
VALUE method_get_index(VALUE self, VALUE s, VALUE idx);
VALUE method_set_index(VALUE self, VALUE s, VALUE idx, VALUE val);

// The initialization method for this module
void Init_carray() {
	CArrayExt = rb_define_module("CArrayExt");
	rb_define_method(CArrayExt, "native_fill_array", method_fill_array, 2);
	rb_define_method(CArrayExt, "native_max_index", method_max_index, 1);
	rb_define_method(CArrayExt, "native_get_index", method_get_index, 2);
	rb_define_method(CArrayExt, "native_set_index", method_set_index, 3);
}

VALUE method_fill_array(VALUE self, VALUE s, VALUE a){
    int len = RSTRING_LEN(s) / 4;
    VALUE *rarr = RARRAY_PTR(a);
    int *arr = (int *) RSTRING_PTR(s);
    int i=0;
    for(i=0; i<len; i++){
      arr[i] = NUM2INT(rarr[i]);
    }
    return rb_str_new((char *)arr, len*4); 
}

VALUE method_max_index(VALUE self, VALUE s){
    int len = RSTRING_LEN(s) / 4;
    int* arr = (int *) RSTRING_PTR(s);
    int max = 0;
    int max_idx = 0;
    int i = 0;
    for(i=0; i<len; i++){
      if(arr[i] > max){
        max = arr[i];
        max_idx = i;
      }
    }
    return rb_int_new(max_idx);
}

VALUE method_get_index(VALUE self, VALUE s, VALUE idx){
    int* arr = (int *) RSTRING_PTR(s);
    return rb_int_new(arr[NUM2INT(idx)]);
}

VALUE method_set_index(VALUE self, VALUE s, VALUE idx, VALUE val){
    int* arr = (int *) RSTRING_PTR(s);
    arr[NUM2INT(idx)] = NUM2INT(val);
    return val;
}
