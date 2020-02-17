#include <stdio.h>

#include "vec.h"
#include "dynstr.h"


void ints()
{
    printf("ints\n");

    Vec(int) *vec = Vec_new(int);
    Vec_init(int, vec, 10);
    printf("vec length = %ld\n", vec->length);
    printf("vec size = %ld\n", sizeof(vec));

    for (int i = 0; i < 10; i++) {
        Vec_push(int, vec, i);
    }

    int eli;
    Vec_foreach(vec, eli) {
        printf("%d, ", eli);
    }
    printf("\n");
}


void floats()
{
    printf("floats\n");

    Vec(float) *vec = Vec_new(float);
    Vec_init(float, vec, 10);
    printf("vec length = %ld\n", vec->length);
    printf("vec size = %ld\n", sizeof(vec));

    for (int i = 0; i < 10; i++) {
        Vec_push(float, vec, i + 0.1);
    }

    float eli;
    Vec_foreach(vec, eli) {
        printf("%f, ", eli);
    }
    printf("\n");
}


void strings()
{
    printf("strings\n");

    Vec(String*) *vec = Vec_new(String);
    Vec_init(String*, vec, 10);
    printf("vec length = %ld\n", vec->length);
    printf("vec size = %ld\n", sizeof(vec));

    for (int i = 0; i < 10; i++) {
        char cstring[32];
        sprintf(cstring, "hello %d", i);
        Vec_push(String*, vec, String_from_cstring(cstring));
    }

    String *eli;
    Vec_foreach(vec, eli) {
        printf("%s, ", String_to_cstring(eli));
    }
    printf("\n");

    for (int i = 0; i < 10; i++) {
        String *s;
        Vec_pop(String*, vec, s);
        if (s != NULL) {
            printf("%s, ", String_to_cstring(s));
        }
    }
    printf("\n");
}


int main()
{
    ints();
    floats();
    strings();
    return 0;
}
