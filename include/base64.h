#ifndef _BASE64_H
#define _BASE64_H

#include <stdlib.h>

void build_decoding_table(void);
char *base64_encode(const unsigned char *data, size_t input_length, size_t *);

#endif