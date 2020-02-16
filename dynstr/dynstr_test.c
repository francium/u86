#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdio.h>

#include "dynstr.h"


static inline void assert_cstrings_equals(const char *a, const char *b, const int length)
{
    if (length == 0) cr_assert(true);

    for (int i = 0; i < length; i++) {
        cr_assert(a[i] == b[i]);
    }
}

Test(dynstr, create_from_cstring)
{
    const int cs_length = 11;
    char cs[] = "hello world";
    String *s = String_from_cstring(cs);
    cr_assert(s->length == cs_length);
    assert_cstrings_equals(cs, s->buf, cs_length);

    String_delete(s);
}


Test(dynstr, init_and_compare_empty_strings)
{
    String *s = String_new();
    String *s2 = String_new();

    cr_assert(s != NULL);
    cr_assert(s->length == 0);
    cr_assert(String_equals(s, s2) == 1);

    String_delete(s);
    String_delete(s2);
}


Test(dynstr, init_from_literal_compare_non_empty_string)
{
    String *s = String_new();
    String *s2 = String_new();

    cr_assert(s != NULL);
    cr_assert(s->length == 0);
    assert_cstrings_equals("hello world", s->buf, 0);
    cr_assert(String_equals(s, s2) == 1);

    String_delete(s);
    String_delete(s2);
}


Test(dynstr, to_cstring)
{
    const int cs_length = 11;
    char cs[] = "hello world";
    String *s = String_from_cstring(cs);
    char *cs_copy = String_to_cstring(s);

    assert_cstrings_equals(cs, cs_copy, cs_length);

    String_delete(s);
    free(cs_copy);
}


Test(dynstr, concat_two_strings)
{
    const int inidividual_length = 5;
    const int total_length = 10;
    String *s = String_from_cstring("hello");
    String *s2 = String_from_cstring("world");

    cr_assert(s->length == inidividual_length);
    String_concat(s, s2);
    assert_cstrings_equals("helloworld", s->buf, total_length);
    cr_assert(s->length == total_length);

    String_delete(s);
    String_delete(s2);
}


Test(dynstr, concat_with_cstring)
{
    const int inidividual_length = 5;
    const int total_length = 10;
    String *s = String_from_cstring("hello");
    char cs[] = "world";

    cr_assert(s->length == inidividual_length);
    String_concat_cstring(s, cs);
    assert_cstrings_equals("helloworld", s->buf, total_length);
    cr_assert(s->length == total_length);

    String_delete(s);
}
