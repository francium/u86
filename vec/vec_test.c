#include <criterion/criterion.h>

#include "string.h"
#include "vec.h"


static inline void assert_cstrings_equals(const char *a, const char *b, const int length)
{
    if (length == 0) cr_assert(true);

    for (int i = 0; i < length; i++) {
        cr_assert(a[i] == b[i]);
    }
}


Test(vec_int, create_int_vector)
{
    Vec(int) *vec = Vec_new(int);
    Vec_init(int, vec, 20);

    for (int i = 0; i < 10; i++) {
        Vec_push(int, vec, i);
        cr_assert(Vec_get(vec, i) == i);
        cr_assert(Vec_size(vec) == i);
    }

    for (int i = 9; i <= 0; i++) {
        int j;
        Vec_pop(int, vec, j);
        cr_assert(j == i);
        cr_assert(Vec_size(vec) == i - 1);
    }
}


Test(vec_int, int_vector_get_set)
{
    Vec(int) *vec = Vec_new(int);
    Vec_init(int, vec, 20);

    Vec_set(vec, 2, 42);
    cr_assert(Vec_get(vec, 2) == 42);
}


Test(vec_float, create_float_vector)
{
    Vec(float) *vec = Vec_new(float);
    Vec_init(float, vec, 20);

    for (int i = 0; i < 10; i++) {
        Vec_push(float, vec, i + 0.2);
        cr_assert(Vec_get(vec, i) - (i + 0.2) <= 0.001);
        cr_assert(Vec_size(vec) == i);
    }

    for (int i = 9; i <= 0; i++) {
        int j;
        Vec_pop(float, vec, j);
        cr_assert(j == i);
        cr_assert(Vec_size(vec) - (i - 1) <= 0.001);
    }
}


Test(vec_float, float_vector_get_set)
{
    Vec(float) *vec = Vec_new(float);
    Vec_init(float, vec, 20);

    Vec_set(vec, 2, 42.2);
    cr_assert(Vec_get(vec, 2) - 42.2 <= 0.001);
}


/* Test(vec_string, create_string_vector) */
/* { */
/*     Vec(String*) *vec = Vec_new(String); */
/*     Vec_init(String*, vec, 10); */
/*  */
/*     for (int i = 0; i < 10; i++) { */
/*         char cstring[32]; */
/*         sprintf(cstring, "hello %d", i); */
/*         Vec_push(String*, vec, String_from_cstring(cstring)); */
/*     } */
/*  */
/*     for (int i = 0; i < 10; i++) { */
/*         String *s; */
/*         Vec_pop(String*, vec, s); */
/*         char *cstring = String_to_cstring(s); */
/*         assert_cstrings_equals(cstring, cstring, 7); */
/*         free(cstring); */
/*         } */
/*     } */
/*     printf("\n"); */
/* } */
