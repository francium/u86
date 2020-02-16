#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#ifndef _FR_DYNSTR_H
#define _FR_DYNSTR_H


typedef struct
{
    int length;
    char *buf;
} String;


static int _cstring_length(const char *cstring);
static void _String_concat_char_array(
    String *this,
    const char *cstring,
    const int cstring_length
);


String* String_new()
{
    String *new = (String *) malloc(sizeof(String));
    new->length = 0;
    new->buf = NULL;
    return new;
}


void String_delete(String *this)
{
    free(this->buf);
    free(this);
}


String* String_from_cstring(const char *cstring)
{
    String *s = String_new();
    const int length = _cstring_length(cstring);
    s->length = length;
    s->buf = (char *) malloc(length);
    strncpy(s->buf, cstring, length);
    return s;
}


void String_concat(String *this, const String *s)
{
    _String_concat_char_array(this, s->buf, s->length);
}


void String_concat_cstring(String *this, const char *cstring)
{
    _String_concat_char_array(this, cstring, _cstring_length(cstring));
}


bool String_equals(const String *this, const String *s)
{
    if (this->length != s->length) return false;

    for (int i = 0; i < this->length; i++) {
        if (this->buf[i] != s->buf[i]) return false;
    }

    return true;
}


static void _String_concat_char_array(
    String *this,
    const char *cstring,
    const int cstring_length
) {
    const int old_len = this->length;
    char *old_buf = this->buf;

    this->length = old_len + cstring_length;
    if (this->length != old_len)
        this->buf = (char *) malloc(this->length);

    if (old_len != 0 && this->buf != NULL)
        strncpy(this->buf, old_buf, old_len);

    if (cstring_length != 0 && cstring != NULL)
        strncpy(this->buf + old_len * sizeof(char), cstring, cstring_length);

    free(old_buf);
}


/**
 * Converts into a standard null-terminated cstring
 */
char* String_to_cstring(const String *this)
{
    char *buf = (char *)malloc((this->length + 1) * sizeof(char));
    strncpy(buf, this->buf, this->length);
    buf[this->length] = '\0';
    return buf;
}


static int _cstring_length(const char *cstring)
{
    int i = 0;
    while (cstring[i] != '\0') i++;
    return i;
}


#endif
