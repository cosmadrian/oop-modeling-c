#include <stddef.h>

#ifndef __STRING_H__
#define __STRING_H__

extern const void * String;

void * clone (const void * self);
int differ (const void * self, const void * b);

size_t sizeOf (const void * self);

#endif
